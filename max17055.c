#include "max17055.h"

osThreadId_t max17055AppTaskHandle;
uint32_t max17055AppTaskBuffer[1024];
StaticTask_t max17055AppTaskControlBlock;

uint16_t hib_cfg, por_count;
uint8_t learn_count;
static void inline max17055_init(void);
static void inline max17055_option_1(void);
static void inline max17055_option_2(void);

max17055_ctx_t max_ctx;

int32_t max17055_read_reg(max17055_ctx_t *ctx, uint8_t reg, uint8_t *data, uint16_t len)
{
    int32_t ret;
    ret = ctx->read_reg(ctx->handle, reg, data, len);
    return ret;
}

int32_t max17055_write_reg(max17055_ctx_t *ctx, uint8_t reg, uint8_t *data, uint16_t len)
{
    int32_t ret;
    ret = ctx->write_reg(ctx->handle, reg, data, len);
    return ret;
}

static void max17055_app_task(void *argument)
{
    for (;;)
    {
        max17055_status_t status;
        max17055_status_get(&max_ctx, &status);
        if (status.bits.POR == 1)
        {
            HAL_UART_Transmit(&huart3, "POR=1\r\n", 6, 100);
            max17055_init();
        }

        uint16_t cap;
        max17055_repCap_get(&max_ctx, &cap);
        cap *= 0.5; // Capacity of battery as a mAh

        // state of charge as a percent
        uint16_t socPercentage;
        max17055_repSoc_get(&max_ctx, &socPercentage);
        socPercentage /= 256.0;

        int16_t temperature;
        max17055_temp_get(&max_ctx, &temperature);
        temperature /= 256.0;

        uint16_t instantVoltage;
        // i2c_read_data_u16(MAX17055_VCELL_REG, &instantVoltage, 1);
        max17055_vcell_get(&max_ctx, &instantVoltage);
        instantVoltage *= 0.078125; // mV

        int16_t instantCurrent;
        // i2c_read_data_u16(MAX17055_CURRENT_REG, (uint16_t *)&instantCurrent, 1);
        max17055_current_get(&max_ctx, &instantCurrent);
        instantCurrent *= 0.15625; // mAmper

        int16_t averageCurrent;
        // i2c_read_data_u16(MAX17055_AVG_CURRENT_REG, (uint16_t *)&AverageCurrent, 1);
        max17055_avgcurrent_get(&max_ctx, &averageCurrent);
        averageCurrent *= 0.15625; // mAmper

        uint16_t timeToEmpty;
        // i2c_read_data_u16(MAX17055_TTE_REG, &timeToEmpty, 1);
        max17055_tte_get(&max_ctx, &timeToEmpty);
        timeToEmpty *= 0.09375; // minutes

        uint16_t timeToFull;
        // i2c_read_data_u16(MAX17055_TTF_REG, &timeToFull, 1);
        max17055_ttf_get(&max_ctx, &timeToFull);
        timeToFull *= 0.09375; // minutes

        max17055_learncfg_t learnCfg;

        // i2c_read_data_u16(MAX17055_LEARN_CFG_REG, &learnCfg.val, 1);
        max17055_learncfg_get(&max_ctx, &learnCfg);
        learn_count = (uint8_t)((learnCfg.val & 0x0070) >> 4);

        uint16_t cycles;
        // i2c_read_data_u16(MAX17055_CYCLES_REG, &cycles, 1);
        max17055_cycles_get(&max_ctx, &cycles);
        cycles;

        uint16_t rComp0;
        // i2c_read_data_u16(MAX17055_R_COMP0_REG, &rComp0, 1);
        max17055_rcomp0_get(&max_ctx, &rComp0);

        uint16_t tempCo;
        // i2c_read_data_u16(MAX17055_TEMP_CO_REG, &tempCo, 1);
        max17055_tempco_get(&max_ctx, &tempCo);
        tempCo /= 256.0;

        uint16_t fullCapNom;
        // i2c_read_data_u16(MAX17055_FULL_CAP_NOM_REG, &fullCapNom, 1);
        max17055_fullcapnom_get(&max_ctx, &fullCapNom);
        fullCapNom *= 0.5;

        uint16_t age;
        // i2c_read_data_u16(MAX17055_AGE_REG, &age, 1);
        max17055_age_get(&max_ctx, &age);
        age /= 256;

        uint16_t rCell;
        // i2c_read_data_u16(MAX17055_RCELL_REG, &rCell, 1);
        max17055_rcell_get(&max_ctx, &rCell);
        rCell /= 4.1; // mohm

        char uartBuffer[100];
        bzero(uartBuffer, 100);
        sprintf(uartBuffer, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\r\n", cap, socPercentage, temperature,
                instantVoltage, instantCurrent, averageCurrent, timeToEmpty, timeToFull, learn_count, cycles, rComp0,
                tempCo, fullCapNom, age, rCell, por_count);
        HAL_UART_Transmit(&huart3, (const uint8_t *)uartBuffer, sizeof(uartBuffer), 100);
        osDelay(10000);
    }
}

static void inline max17055_init(void)
{
    uint16_t deviceName;
    max17055_status_t status;
    max17055_fstat_t fstat;

    max17055_devname_get(&max_ctx, &deviceName);
    // i2c_read_data_u16(MAX17055_DEVNAME_REG, &deviceName, 1);
    HAL_Delay(100);
    if (deviceName == MAX17055_ID)
    {
        HAL_Delay(1000);
        // i2c_read_data_u16(MAX17055_STATUS_REG, &status.val, 1);
        // Check Power on Reset status
        max17055_status_get(&max_ctx, &status);
        if (status.bits.POR == 1)
        {
            por_count++;
            HAL_Delay(1000);
            // i2c_read_data_u16(MAX17055_FSTAT_REG, &fstat.val, 1);
            max17055_fstat_get(&max_ctx, &fstat);

            while (fstat.bits.data_not_ready == 1)
            {
                // i2c_read_data_u16(MAX17055_FSTAT_REG, &fstat.val, 1);
                max17055_fstat_get(&max_ctx, &fstat);
                HAL_Delay(50);
            }
            // Wake-up Process
            // Store original HibCFG value
            // i2c_read_data_u16(MAX17055_HIB_CFG_REG, &hib_cfg, 1);
            max17055_hibcfg_get(&max_ctx, &hib_cfg);
            // Exit Hibernate Mode step 1
            // HAL_I2C_Mem_Write(&hi2c1, MAX17055_I2C_ADD_L, MAX17055_SOFTWAKEUP, 1, (uint8_t *)0x90, 2, 100);
            max17055_softwakeup_set(&max_ctx, 0x0090);
            // Exit Hibernate Mode step 2
            // HAL_I2C_Mem_Write(&hi2c1, MAX17055_I2C_ADD_L, MAX17055_HIB_CFG_REG, 1, 0x00, 2, 100);
            max17055_hibcfg_set(&max_ctx, 0x0000);
            // Exit Hibernate Mode step 3
            // HAL_I2C_Mem_Write(&hi2c1, MAX17055_I2C_ADD_L, MAX17055_SOFTWAKEUP, 1, 0x00, 2, 100);
            max17055_softwakeup_set(&max_ctx, 0x0000);
            // Init design parameters
            // -> 3.1 OPTION 1: EZ Config (no INI file is needed)
            // max17055_option_1();

            // -> 3.2 OPTION 2: Custom Short INI without OCV table
            max17055_option_2();

            // Initialization complete  -> Clear and Check POR
            // i2c_read_data_u16(MAX17055_STATUS_REG, &status.val, 1);
            max17055_status_get(&max_ctx, &status);
            status.bits.POR = 0;
            // i2c_write_data_u16(MAX17055_STATUS_REG, &status.val, 1);
            max17055_status_set(&max_ctx, status);
            // i2c_read_data_u16(MAX17055_STATUS_REG, &status.val, 1);
            max17055_status_get(&max_ctx, &status);
            HAL_Delay(1);
        }
    }
}

static void inline max17055_option_1(void)
{
    uint16_t realcap, designcap, dqacc, dpacc, ichgterm;
    realcap   = 9600;
    designcap = realcap / 0.5;
    // i2c_write_data_u16(MAX17055_DESIGN_CAP_REG, &designcap, 1);
    max17055_designcap_set(&max_ctx, designcap);

    dqacc = designcap / 32;
    // i2c_write_data_u16(MAX17055_DQACC_REG, &dqacc, 1);
    max17055_dqacc_set(&max_ctx, dqacc);

    ichgterm = 384 / 0.15625;
    // i2c_write_data_u16(MAX17055_ICHG_TERM_REG, &ichgterm, 1);
    max17055_ichgterm_set(&max_ctx, ichgterm);

    max17055_vempty_t vempty;
    vempty.bits.v_empty    = 3100 / 10;
    vempty.bits.v_recovery = 3880 / 40;
    // i2c_write_data_u16(MAX17055_VEMPTY_REG, &vempty.val, 1);
    max17055_vempty_set(&max_ctx, vempty);

    dpacc = (44138) / 32;
    // i2c_write_data_u16(MAX17055_DPACC_REG, &dpacc, 1);
    max17055_dpacc_set(&max_ctx, dpacc);

    max17055_modelcfg_t modelCFG;
    modelCFG.val = 0x8000;
    // i2c_write_data_u16(MAX17055_MODEL_CFG_REG, &modelCFG, 1);
    max17055_modelcfg_set(&max_ctx, modelCFG);

    // Wait model_cfg.refresh
    // i2c_read_data_u16(MAX17055_MODEL_CFG_REG, &refresh, 1);
    max17055_modelcfg_get(&max_ctx, &modelCFG);
    while ((modelCFG.bits.refresh & 0x01))
    {
        // i2c_read_data_u16(MAX17055_MODEL_CFG_REG, &refresh, 1);
        max17055_modelcfg_get(&max_ctx, &modelCFG);
        HAL_Delay(50);
    }
    // Restore Hibernation Config
    // i2c_write_data_u16(MAX17055_HIB_CFG_REG, &hib_cfg, 1);
    max17055_hibcfg_set(&max_ctx, hib_cfg);
}

static void inline max17055_option_2(void)
{
    uint16_t realcap, designcap, dqacc, dpacc, ichgterm;

    realcap   = 9600;
    designcap = realcap / 0.5;
    // i2c_write_data_u16(MAX17055_DESIGN_CAP_REG, &designcap, 1);
    max17055_designcap_set(&max_ctx, designcap);

    dqacc = designcap / 16;
    // i2c_write_data_u16(MAX17055_DQACC_REG, &dqacc, 1);
    max17055_dqacc_set(&max_ctx, dqacc);

    ichgterm = 384 / 0.15625;
    // i2c_write_data_u16(MAX17055_ICHG_TERM_REG, &ichgterm, 1);
    max17055_ichgterm_set(&max_ctx, ichgterm);

    max17055_vempty_t vempty;
    vempty.bits.v_empty    = 3100 / 10;
    vempty.bits.v_recovery = 3880 / 40;
    // i2c_write_data_u16(MAX17055_VEMPTY_REG, &vempty.val, 1);
    max17055_vempty_set(&max_ctx, vempty);

    max17055_learncfg_t learnConfig;
    uint16_t data;
    // i2c_read_data_u16(MAX17055_LEARN_CFG_REG, &data, 1);
    max17055_learncfg_get(&max_ctx, &learnConfig);
    learnConfig.val = 0x4486;

    max17055_learncfg_set(&max_ctx, learnConfig);
    max17055_learncfg_get(&max_ctx, &learnConfig);

    dpacc = (44138) / 32;
    // i2c_write_data_u16(MAX17055_DPACC_REG, &dpacc, 1);
    max17055_dpacc_set(&max_ctx, dpacc);

    max17055_modelcfg_t modelCFG;
    modelCFG.val = 0x8000;
    // i2c_write_data_u16(MAX17055_MODEL_CFG_REG, &modelCFG, 1);
    max17055_modelcfg_set(&max_ctx, modelCFG);

    // Wait model_cfg.refresh
    // i2c_read_data_u16(MAX17055_MODEL_CFG_REG, &refresh, 1);
    max17055_modelcfg_get(&max_ctx, &modelCFG);
    while ((modelCFG.bits.refresh & 0x01))
    {
        // i2c_read_data_u16(MAX17055_MODEL_CFG_REG, &refresh, 1);
        max17055_modelcfg_get(&max_ctx, &modelCFG);
        HAL_Delay(50);
    }

    uint16_t rcomp0 = 0x004D; // 77 - OcV
    // i2c_write_data_u16(MAX17055_R_COMP0_REG, &rcomp0, 1);
    max17055_rcomp0_set(&max_ctx, rcomp0);

    uint16_t tempco = 0x223E; // 34,24 celsius
    // i2c_write_data_u16(MAX17055_TEMP_CO_REG, &tempco, 1);
    max17055_tempco_set(&max_ctx, tempco);

    uint16_t qrTable00 = 0x1050;
    uint16_t qrTable10 = 0x2012;
    // i2c_write_data_u16(MAX17055_QR_TABLE00_REG, &qrTable00, 1);
    max17055_qrTable00_set(&max_ctx, qrTable00);
    // i2c_write_data_u16(MAX17055_QR_TABLE10_REG, &qrTable10, 1);
    max17055_qrTable10_set(&max_ctx, qrTable10);
    // Restore Hibernation Config
    // i2c_write_data_u16(MAX17055_HIB_CFG_REG, &hib_cfg, 1);
    max17055_hibcfg_set(&max_ctx, hib_cfg);
}

void max17055_start(void)
{
    max_ctx.handle    = &hi2c1;
    max_ctx.read_reg  = max_platform_read;
    max_ctx.write_reg = max_platform_write;

    max17055_init();
    osThreadAttr_t max17055AppTask_attributes = {
        .name       = "max17055AppTask",
        .cb_mem     = &max17055AppTaskControlBlock,
        .cb_size    = sizeof(max17055AppTaskControlBlock),
        .stack_mem  = &max17055AppTaskBuffer[0],
        .stack_size = sizeof(max17055AppTaskBuffer),
        .priority   = (osPriority_t)osPriorityBelowNormal,
    };
    max17055AppTaskHandle = osThreadNew(max17055_app_task, NULL, &max17055AppTask_attributes);
}

int32_t max17055_status_set(max17055_ctx_t *ctx, max17055_status_t val)
{
    short_uint8 _val;
    int32_t ret;
    _val.u16bit = val.val;
    ret         = max17055_write_reg(ctx, MAX17055_STATUS_REG, (uint8_t *)&_val, 2);
    return ret;
}

int32_t max17055_status_get(max17055_ctx_t *ctx, max17055_status_t *val)
{
    short_uint8 _val;
    int32_t ret;
    ret      = max17055_read_reg(ctx, MAX17055_STATUS_REG, (uint8_t *)&_val, 2);
    val->val = _val.u16bit;
    return ret;
}

// int32_t max17055_valrtth_set(max17055_ctx_t *ctx, max17055_valrtth_t val)
// {
//   int32_t ret;
// 	ret = max17055_write_reg(ctx, MAX17055_VALRT_TH_REG, (uint8_t*)&val, 2);
// 	return ret;
// }

// int32_t max17055_valrtth_get(max17055_ctx_t *ctx, max17055_valrtth_t *val)
// {
//   int32_t ret;
// 	ret = max17055_read_reg(ctx, MAX17055_VALRTTH, (uint8_t*)val, 2);
//   return ret;
// }

// int32_t max17055_talrtth_set(max17055_ctx_t *ctx, max17055_talrtth_t val)
// {
//   int32_t ret;
// 	ret = max17055_write_reg(ctx, MAX17055_TALRTTH, (uint8_t*)&val, 2);
// 	return ret;
// }

// int32_t max17055_talrtth_get(max17055_ctx_t *ctx, max17055_talrtth_t *val)
// {
//   int32_t ret;
// 	ret = max17055_read_reg(ctx, MAX17055_SALRTTH, (uint8_t*)val, 2);
//   return ret;
// }

// int32_t max17055_salrtth_set(max17055_ctx_t *ctx, max17055_salrtth_t val)
// {
//   int32_t ret;
// 	ret = max17055_write_reg(ctx, MAX17055_SALRTTH, (uint8_t*)&val, 2);
// 	return ret;
// }

// int32_t max17055_salrtth_get(max17055_ctx_t *ctx, max17055_salrtth_t *val)
// {
//   int32_t ret;
// 	ret = max17055_read_reg(ctx, MAX17055_SALRTTH, (uint8_t*)val, 2);
//   return ret;
// }

int32_t max17055_repCap_get(max17055_ctx_t *ctx, uint16_t *val)
{
    int32_t ret;
    short_uint8 _val;
    ret  = max17055_read_reg(ctx, MAX17055_REP_CAP_REG, (uint8_t *)&_val, 2);
    *val = _val.u16bit;
    return ret;
}

int32_t max17055_repSoc_get(max17055_ctx_t *ctx, uint16_t *val)
{
    int32_t ret;
    short_uint8 _val;
    ret  = max17055_read_reg(ctx, MAX17055_REP_SOC_REG, (uint8_t *)&_val, 2);
    *val = _val.u16bit;
    return ret;
}

int32_t max17055_age_get(max17055_ctx_t *ctx, uint16_t *val)
{
    int32_t ret;
    short_uint8 _val;
    ret  = max17055_read_reg(ctx, MAX17055_AGE_REG, (uint8_t *)&_val, 2);
    *val = _val.u16bit;
    return ret;
}

int32_t max17055_temp_get(max17055_ctx_t *ctx, int16_t *val)
{
    int32_t ret;
    axis1bit16_t _val;
    ret  = max17055_read_reg(ctx, MAX17055_TEMP_REG, (uint8_t *)&_val, 2);
    *val = _val.i16bit;
    return ret;
}

int32_t max17055_vcell_get(max17055_ctx_t *ctx, uint16_t *val)
{
    int32_t ret;
    short_uint8 _val;
    ret  = max17055_read_reg(ctx, MAX17055_VCELL_REG, (uint8_t *)&_val, 2);
    *val = _val.u16bit;
    return ret;
}

int32_t max17055_current_get(max17055_ctx_t *ctx, int16_t *val)
{
    int32_t ret;
    axis1bit16_t _val;
    ret  = max17055_read_reg(ctx, MAX17055_CURRENT_REG, (uint8_t *)&_val, 2);
    *val = _val.i16bit;
    return ret;
}

int32_t max17055_avgcurrent_get(max17055_ctx_t *ctx, int16_t *val)
{
    int32_t ret;
    axis1bit16_t _val;
    ret  = max17055_read_reg(ctx, MAX17055_AVG_CURRENT_REG, (uint8_t *)&_val, 2);
    *val = _val.i16bit;
    return ret;
}

// int32_t max17055_qresidual_get(max17055_ctx_t *ctx, uint16_t *val)
// {
// 	int32_t ret;
// 	short_uint8 _val;
//   ret = max17055_read_reg(ctx, MAX17055_QRESIDUAL, (uint8_t*)&_val, 2);
// 	*val = _val.u16bit;
//   return ret;
// }

// int32_t max17055_mixsoc_get(max17055_ctx_t *ctx, uint16_t *val)
// {
// 	int32_t ret;
// 	short_uint8 _val;
//   ret = max17055_read_reg(ctx, MAX17055_MIXSOC, (uint8_t*)&_val, 2);
// 	*val = _val.u16bit;
//   return ret;
// }

int32_t max17055_avsoc_get(max17055_ctx_t *ctx, uint16_t *val)
{
    int32_t ret;
    short_uint8 _val;
    ret  = max17055_read_reg(ctx, MAX17055_AV_SOC_REG, (uint8_t *)&_val, 2);
    *val = _val.u16bit;
    return ret;
}

int32_t max17055_mixcap_get(max17055_ctx_t *ctx, uint16_t *val)
{
    int32_t ret;
    short_uint8 _val;
    ret  = max17055_read_reg(ctx, MAX17055_MIX_CAP_REG, (uint8_t *)&_val, 2);
    *val = _val.u16bit;
    return ret;
}

int32_t max17055_fullcaprep_get(max17055_ctx_t *ctx, uint16_t *val)
{
    int32_t ret;
    short_uint8 _val;
    ret  = max17055_read_reg(ctx, MAX17055_FULL_CAP_REP_REG, (uint8_t *)&_val, 2);
    *val = _val.u16bit;
    return ret;
}

int32_t max17055_tte_get(max17055_ctx_t *ctx, uint16_t *val)
{
    int32_t ret;
    short_uint8 _val;
    ret  = max17055_read_reg(ctx, MAX17055_TTE_REG, (uint8_t *)&_val, 2);
    *val = _val.u16bit;
    return ret;
}

// int32_t max17055_fullsocthr_set(max17055_ctx_t *ctx, uint16_t val)
// {
// 	max17055_fullsocthr_t max17055_fullsocthr;
//   int32_t ret;
// 	ret = max17055_read_reg(ctx, MAX17055_FULL_SOC_THR_REG, (uint8_t*)&max17055_fullsocthr, 2);
//   if(ret == 0){
// 		max17055_fullsocthr.full_soc_thr = val;
// 		ret = max17055_write_reg(ctx, MAX17055_FULL_SOC_THR_REG, (uint8_t*)&max17055_fullsocthr, 2);
//   }
// 	return ret;
// }

// int32_t max17055_fullsocthr_get(max17055_ctx_t *ctx, uint16_t *val)
// {
// 	int32_t ret;
// 	max17055_fullsocthr_t max17055_fullsocthr;
//   ret = max17055_read_reg(ctx, MAX17055_FULLSOCTHR, (uint8_t*)&max17055_fullsocthr, 2);
// 	*val = (uint16_t)max17055_fullsocthr.full_soc_thr;
//   return ret;
// }

// int32_t max17055_rcell_set(max17055_ctx_t *ctx, uint16_t val)
// {
// 	int32_t ret;
// 	short_uint8 _val;
// 	_val.u16bit = val;
//   ret = max17055_write_reg(ctx, MAX17055_RCELL_REG, (uint8_t*)&_val, 2);
//   return ret;
// }

int32_t max17055_rcell_get(max17055_ctx_t *ctx, uint16_t *val)
{
    int32_t ret;
    short_uint8 _val;
    ret  = max17055_read_reg(ctx, MAX17055_RCELL_REG, (uint8_t *)&_val, 2);
    *val = _val.u16bit;
    return ret;
}

// int32_t max17055_avgta_get(max17055_ctx_t *ctx, uint16_t *val)
// {
// 	int32_t ret;
// 	short_uint8 _val;
//   ret = max17055_read_reg(ctx, MAX17055_AVG_TA_REG, (uint8_t*)&_val, 2);
// 	*val = _val.u16bit;
//   return ret;
// }

int32_t max17055_cycles_get(max17055_ctx_t *ctx, uint16_t *val)
{
    int32_t ret;
    short_uint8 _val;
    ret  = max17055_read_reg(ctx, MAX17055_CYCLES_REG, (uint8_t *)&_val, 2);
    *val = _val.u16bit;
    return ret;
}

int32_t max17055_designcap_set(max17055_ctx_t *ctx, uint16_t val)
{
    int32_t ret;
    short_uint8 _val;
    _val.u16bit = val;
    ret         = max17055_write_reg(ctx, MAX17055_DESIGN_CAP_REG, (uint8_t *)&_val, 2);
    return ret;
}

int32_t max17055_designcap_get(max17055_ctx_t *ctx, uint16_t *val)
{
    int32_t ret;
    short_uint8 _val;
    ret  = max17055_read_reg(ctx, MAX17055_DESIGN_CAP_REG, (uint8_t *)&_val, 2);
    *val = _val.u16bit;
    return ret;
}

int32_t max17055_avgvcell_get(max17055_ctx_t *ctx, uint16_t *val)
{
    int32_t ret;
    short_uint8 _val;
    ret  = max17055_read_reg(ctx, MAX17055_AVG_VCELL_REG, (uint8_t *)&_val, 2);
    *val = _val.u16bit;
    return ret;
}

// int32_t max17055_maxmintemp_set(max17055_ctx_t *ctx, max17055_maxmintemp_t val)
// {
//   int32_t ret;
// 	ret = max17055_write_reg(ctx, MAX17055_MAXMINTEMP, (uint8_t*)&val, 2);
// 	return ret;
// }

// int32_t max17055_maxmintemp_get(max17055_ctx_t *ctx, max17055_maxmintemp_t *val)
// {
//   int32_t ret;
// 	ret = max17055_read_reg(ctx, MAX17055_MAXMINTEMP, (uint8_t*)val, 2);
//   return ret;
// }

// int32_t max17055_maxminvolt_set(max17055_ctx_t *ctx, max17055_maxminvolt_t val)
// {
//   int32_t ret;
// 	ret = max17055_write_reg(ctx, MAX17055_MAXMINVOLT, (uint8_t*)&val, 2);
// 	return ret;
// }

// int32_t max17055_maxminvolt_get(max17055_ctx_t *ctx, max17055_maxminvolt_t *val)
// {
//   int32_t ret;
// 	ret = max17055_read_reg(ctx, MAX17055_MAXMINVOLT, (uint8_t*)val, 2);
//   return ret;
// }

// int32_t max17055_maxmincurr_set(max17055_ctx_t *ctx, max17055_maxmincurr_t val)
// {
//   int32_t ret;
// 	ret = max17055_write_reg(ctx, MAX17055_MAXMINCURR, (uint8_t*)&val, 2);
// 	return ret;
// }

// int32_t max17055_maxmincurr_get(max17055_ctx_t *ctx, max17055_maxmincurr_t *val)
// {
//   int32_t ret;
// 	ret = max17055_read_reg(ctx, MAX17055_MAXMINCURR, (uint8_t*)val, 2);
//   return ret;
// }

// int32_t max17055_config_set(max17055_ctx_t *ctx, max17055_config_t val)
// {
//   int32_t ret;
// 	ret = max17055_write_reg(ctx, MAX17055_CONFIG, (uint8_t*)&val, 2);
// 	return ret;
// }

// int32_t max17055_config_get(max17055_ctx_t *ctx, max17055_config_t *val)
// {
//   int32_t ret;
// 	ret = max17055_read_reg(ctx, MAX17055_CONFIG_REG, (uint8_t*)val, 2);
//   return ret;
// }

int32_t max17055_ichgterm_set(max17055_ctx_t *ctx, uint16_t val)
{
    int32_t ret;
    short_uint8 _val;
    _val.u16bit = val;
    ret         = max17055_write_reg(ctx, MAX17055_ICHG_TERM_REG, (uint8_t *)&_val, 2);
    return ret;
}

int32_t max17055_ichgterm_get(max17055_ctx_t *ctx, uint16_t *val)
{
    int32_t ret;
    short_uint8 _val;
    ret  = max17055_read_reg(ctx, MAX17055_ICHG_TERM_REG, (uint8_t *)&_val, 2);
    *val = _val.u16bit;
    return ret;
}

int32_t max17055_avcap_get(max17055_ctx_t *ctx, uint16_t *val)
{
    int32_t ret;
    short_uint8 _val;
    ret  = max17055_read_reg(ctx, MAX17055_AV_CAP_REG, (uint8_t *)&_val, 2);
    *val = _val.u16bit;
    return ret;
}

int32_t max17055_ttf_get(max17055_ctx_t *ctx, uint16_t *val)
{
    int32_t ret;
    short_uint8 _val;
    ret  = max17055_read_reg(ctx, MAX17055_TTF_REG, (uint8_t *)&_val, 2);
    *val = _val.u16bit;
    return ret;
}

int32_t max17055_devname_get(max17055_ctx_t *ctx, uint16_t *val)
{
    int32_t ret;
    short_uint8 _val;
    ret  = max17055_read_reg(ctx, MAX17055_DEVNAME_REG, (uint8_t *)&_val, 2);
    *val = _val.u16bit;
    return ret;
}

int32_t max17055_fullcapnom_get(max17055_ctx_t *ctx, uint16_t *val)
{
    int32_t ret;
    short_uint8 _val;
    ret  = max17055_read_reg(ctx, MAX17055_FULL_CAP_NOM_REG, (uint8_t *)&_val, 2);
    *val = _val.u16bit;
    return ret;
}

// int32_t max17055_ain_get(max17055_ctx_t *ctx, uint16_t *val)
// {
// 	int32_t ret;
// 	short_uint8 _val;
//   ret = max17055_read_reg(ctx, MAX17055_AIN_REG, (uint8_t*)&_val, 2);
// 	*val = _val.u16bit;
//   return ret;
// }

int32_t max17055_learncfg_set(max17055_ctx_t *ctx, max17055_learncfg_t val)
{
    short_uint8 _val;
    int32_t ret;
    _val.u16bit = val.val;
    ret         = max17055_write_reg(ctx, MAX17055_LEARN_CFG_REG, (uint8_t *)&_val, 2);
    return ret;
}

int32_t max17055_learncfg_get(max17055_ctx_t *ctx, max17055_learncfg_t *val)
{
    int32_t ret;
    short_uint8 _val;
    ret      = max17055_read_reg(ctx, MAX17055_LEARN_CFG_REG, (uint8_t *)&_val, 2);
    val->val = _val.u16bit;
    return ret;
}

// int32_t max17055_filtercfg_set(max17055_ctx_t *ctx, max17055_filtercfg_t val);
// int32_t max17055_filtercfg_get(max17055_ctx_t *ctx, max17055_filtercfg_t *val);

// int32_t max17055_relaxcfg_set(max17055_ctx_t *ctx, max17055_relaxcfg_t val);
// int32_t max17055_relaxcfg_get(max17055_ctx_t *ctx, max17055_relaxcfg_t *val);

// int32_t max17055_mixcfg_set(max17055_ctx_t *ctx, max17055_miscfg_t val);
// int32_t max17055_mixcfg_get(max17055_ctx_t *ctx, max17055_miscfg_t *val);

// int32_t max17055_tgain_set(max17055_ctx_t *ctx, uint8_t val);
// int32_t max17055_tgain_get(max17055_ctx_t *ctx, uint8_t *val);

// int32_t max17055_toff_set(max17055_ctx_t *ctx, uint8_t val);
// int32_t max17055_toff_get(max17055_ctx_t *ctx, uint8_t *val);

// int32_t max17055_cgain_set(max17055_ctx_t *ctx, uint8_t val);
// int32_t max17055_cgain_get(max17055_ctx_t *ctx, uint8_t *val);

// int32_t max17055_coff_set(max17055_ctx_t *ctx, uint8_t val);
// int32_t max17055_coff_get(max17055_ctx_t *ctx, uint8_t *val);

// int32_t max17055_dietemp_get(max17055_ctx_t *ctx, uint16_t *val);

int32_t max17055_fullcap_get(max17055_ctx_t *ctx, uint16_t *val);

int32_t max17055_rcomp0_set(max17055_ctx_t *ctx, uint16_t val)
{
    int32_t ret;
    short_uint8 _val;
    _val.u16bit = val;
    ret         = max17055_write_reg(ctx, MAX17055_R_COMP0_REG, (uint8_t *)&_val, 2);
    return ret;
}

int32_t max17055_rcomp0_get(max17055_ctx_t *ctx, uint16_t *val)
{
    int32_t ret;
    short_uint8 _val;
    ret  = max17055_read_reg(ctx, MAX17055_R_COMP0_REG, (uint8_t *)&_val, 2);
    *val = _val.u16bit;
    return ret;
}

int32_t max17055_tempco_set(max17055_ctx_t *ctx, uint16_t val)
{
    int32_t ret;
    short_uint8 _val;
    _val.u16bit = val;
    ret         = max17055_write_reg(ctx, MAX17055_TEMP_CO_REG, (uint8_t *)&_val, 2);
    return ret;
}

int32_t max17055_tempco_get(max17055_ctx_t *ctx, uint16_t *val)
{
    int32_t ret;
    short_uint8 _val;
    ret  = max17055_read_reg(ctx, MAX17055_TEMP_CO_REG, (uint8_t *)&_val, 2);
    *val = _val.u16bit;
    return ret;
}

int32_t max17055_vempty_set(max17055_ctx_t *ctx, max17055_vempty_t val)
{
    int32_t ret;
    short_uint8 _val;
    _val.u16bit = val.val;
    ret         = max17055_write_reg(ctx, MAX17055_VEMPTY_REG, (uint8_t *)&_val, 2);
    return ret;
}
// int32_t max17055_vempty_get(max17055_ctx_t *ctx, max17055_vempty_t *val);

int32_t max17055_fstat_get(max17055_ctx_t *ctx, max17055_fstat_t *val)
{
    int32_t ret;
    short_uint8 _val;
    ret      = max17055_read_reg(ctx, MAX17055_STATUS_REG, (uint8_t *)&_val, 2);
    val->val = _val.u16bit;
    return ret;
}

// int32_t max17055_timer_get(max17055_ctx_t *ctx, uint8_t *val);

// int32_t max17055_shdntimer_set(max17055_ctx_t *ctx, max17055_shdntimer_t val);
// int32_t max17055_shdntimer_get(max17055_ctx_t *ctx, max17055_shdntimer_t *val);

// int32_t max17055_rgain_set(max17055_ctx_t *ctx, max17055_rgain_t val);
// int32_t max17055_rgain_get(max17055_ctx_t *ctx, max17055_rgain_t *val);

int32_t max17055_dqacc_set(max17055_ctx_t *ctx, uint16_t val)
{
    int32_t ret;
    short_uint8 _val;
    _val.u16bit = val;
    ret         = max17055_write_reg(ctx, MAX17055_DQACC_REG, (uint8_t *)&_val, 2);
    return ret;
}

int32_t max17055_dqacc_get(max17055_ctx_t *ctx, uint16_t *val)
{
    int32_t ret;
    short_uint8 _val;
    ret  = max17055_read_reg(ctx, MAX17055_DQACC_REG, (uint8_t *)&_val, 2);
    *val = _val.u16bit;
    return ret;
}

int32_t max17055_dpacc_set(max17055_ctx_t *ctx, uint16_t val)
{
    int32_t ret;
    short_uint8 _val;
    _val.u16bit = val;
    ret         = max17055_write_reg(ctx, MAX17055_DPACC_REG, (uint8_t *)&_val, 2);
    return ret;
}

int32_t max17055_dpacc_get(max17055_ctx_t *ctx, uint16_t *val)
{
    int32_t ret;
    short_uint8 _val;
    ret  = max17055_read_reg(ctx, MAX17055_DPACC_REG, (uint8_t *)&_val, 2);
    *val = _val.u16bit;
    return ret;
}

// int32_t max17055_qh_get(max17055_ctx_t *ctx, uint8_t *val);

int32_t max17055_softwakeup_set(max17055_ctx_t *ctx, uint16_t val)
{
    int32_t ret;
    short_uint8 _val;
    _val.u16bit = val;
    ret         = max17055_write_reg(ctx, MAX17055_SOFTWAKEUP, (uint8_t *)&_val, 2);
    return ret;
}

// int32_t max17055_status2_get(max17055_ctx_t *ctx, max17055_status2_t *val)
// {
//     int32_t ret;
//     ret = max17055_read_reg(ctx, MAX17055_STATUS2, (uint8_t *)val, 2);
//     return ret;
// }

// int32_t max17055_power_get(max17055_ctx_t *ctx, uint8_t *val);

// int32_t max17055_avgpower_get(max17055_ctx_t *ctx, uint8_t *val);

// int32_t max17055_ilartth_set(max17055_ctx_t *ctx, max17055_ialrtth_t val);
// int32_t max17055_ilartth_get(max17055_ctx_t *ctx, max17055_ialrtth_t *val);

int32_t max17055_hibcfg_set(max17055_ctx_t *ctx, uint16_t val)
{
    int32_t ret;
    short_uint8 _val;
    _val.u16bit = val;
    ret         = max17055_write_reg(ctx, MAX17055_HIB_CFG_REG, (uint8_t *)&_val, 2);
    return ret;
}

int32_t max17055_hibcfg_get(max17055_ctx_t *ctx, uint16_t *val)
{
    int32_t ret;
    short_uint8 _val;
    ret  = max17055_read_reg(ctx, MAX17055_HIB_CFG_REG, (uint8_t *)&_val, 2);
    *val = _val.u16bit;
    return ret;
}

// int32_t max17055_config2_set(max17055_ctx_t *ctx, max17055_config2_t val)
// {
//     int32_t ret;
//     ret = max17055_write_reg(ctx, MAX17055_CONFIG2, (uint8_t *)&val, 2);
//     return ret;
// }

// int32_t max17055_config2_get(max17055_ctx_t *ctx, max17055_config2_t *val)
// {
//     int32_t ret;
//     ret = max17055_read_reg(ctx, MAX17055_CONFIG2, (uint8_t *)val, 2);
//     return ret;
// }

// int32_t max17055_vripple_set(max17055_ctx_t *ctx, uint8_t val);
// int32_t max17055_vripple_get(max17055_ctx_t *ctx, uint8_t *val);

// int32_t max17055_ripplecfg_set(max17055_ctx_t *ctx, max17055_ripplecfg_t val);
// int32_t max17055_ripplecfg_get(max17055_ctx_t *ctx, max17055_ripplecfg_t *val);

// int32_t max17055_timerh_get(max17055_ctx_t *ctx, uint8_t *val);

// int32_t max17055_rsense_set(max17055_ctx_t *ctx, uint16_t val)
// {
//     int32_t ret;
//     short_uint8 _val;
//     _val.u16bit = val;
//     ret         = max17055_write_reg(ctx, MAX17055_RSENSE_USERMEM3, (uint8_t *)&_val, 2);
//     return ret;
// }

// int32_t max17055_rsense_get(max17055_ctx_t *ctx, uint16_t *val)
// {
//     int32_t ret;
//     short_uint8 _val;
//     ret  = max17055_read_reg(ctx, MAX17055_RSENSE_USERMEM3, (uint8_t *)&_val, 2);
//     *val = _val.u16bit;
//     return ret;
// }

// int32_t max17055_scocvlim_set(max17055_ctx_t *ctx, max17055_scocvlim_t val);
// int32_t max17055_scocvlim_get(max17055_ctx_t *ctx, max17055_scocvlim_t *val);

// int32_t max17055_sochold_set(max17055_ctx_t *ctx, max17055_sochold_t val);
// int32_t max17055_sochold_get(max17055_ctx_t *ctx, max17055_sochold_t *val);

// int32_t max17055_packresistance_set(max17055_ctx_t *ctx, uint16_t val)
// {
//     int32_t ret;
//     short_uint8 _val;
//     _val.u16bit = val;
//     ret         = max17055_write_reg(ctx, MAX17055_PACKRESISTANCE, (uint8_t *)&_val, 2);
//     return ret;
// }

// int32_t max17055_packresistance_get(max17055_ctx_t *ctx, uint16_t *val)
// {
//     int32_t ret;
//     short_uint8 _val;
//     ret  = max17055_read_reg(ctx, MAX17055_PACKRESISTANCE, (uint8_t *)&_val, 2);
//     *val = _val.u16bit;
//     return ret;
// }

// int32_t max17055_syresistance_set(max17055_ctx_t *ctx, uint16_t val)
// {
//     int32_t ret;
//     short_uint8 _val;
//     _val.u16bit = val;
//     ret         = max17055_write_reg(ctx, MAX17055_SYSRESISTANCE, (uint8_t *)&_val, 2);
//     return ret;
// }

// int32_t max17055_sysresistance_get(max17055_ctx_t *ctx, uint16_t *val)
// {
//     int32_t ret;
//     short_uint8 _val;
//     ret  = max17055_read_reg(ctx, MAX17055_SYSRESISTANCE, (uint8_t *)&_val, 2);
//     *val = _val.u16bit;
//     return ret;
// }

// int32_t max17055_minsysvoltage_set(max17055_ctx_t *ctx, uint16_t val)
// {
//     int32_t ret;
//     short_uint8 _val;
//     _val.u16bit = val;
//     ret         = max17055_write_reg(ctx, MAX17055_MINSYSVOLTAGE, (uint8_t *)&_val, 2);
//     return ret;
// }

// int32_t max17055_minsysvoltage_get(max17055_ctx_t *ctx, uint16_t *val)
// {
//     int32_t ret;
//     short_uint8 _val;
//     ret  = max17055_read_reg(ctx, MAX17055_MINSYSVOLTAGE, (uint8_t *)&_val, 2);
//     *val = _val.u16bit;
//     return ret;
// }

int32_t max17055_modelcfg_set(max17055_ctx_t *ctx, max17055_modelcfg_t val)
{
    int32_t ret;
    short_uint8 _val;
    _val.u16bit = val.val;
    ret         = max17055_write_reg(ctx, MAX17055_MODEL_CFG_REG, (uint8_t *)&_val, 2);
    return ret;
}

int32_t max17055_modelcfg_get(max17055_ctx_t *ctx, max17055_modelcfg_t *val)
{
    int32_t ret;
    short_uint8 _val;
    ret      = max17055_read_reg(ctx, MAX17055_MODEL_CFG_REG, (uint8_t *)&_val, 2);
    val->val = _val.u16bit;
    return ret;
}

// int32_t max17055_modelcfg_refresh_get(max17055_ctx_t *ctx, uint8_t *val)
// {
//     max17055_modelcfg_t max17055_modelcfg;
//     int32_t ret;
//     ret  = max17055_read_reg(ctx, MAX17055_MODEL_CFG_REG, (uint8_t *)&max17055_modelcfg, 1);
//     *val = (uint8_t)max17055_modelcfg.refresh;
//     return ret;
// }

int32_t max17055_qrTable00_set(max17055_ctx_t *ctx, uint16_t val)
{
    int32_t ret;
    short_uint8 _val;
    _val.u16bit = val;
    ret         = max17055_write_reg(ctx, MAX17055_QR_TABLE00_REG, (uint8_t *)&_val, 2);
    return ret;
}
int32_t max17055_qrTable10_set(max17055_ctx_t *ctx, uint16_t val)
{
    int32_t ret;
    short_uint8 _val;
    _val.u16bit = val;
    ret         = max17055_write_reg(ctx, MAX17055_QR_TABLE10_REG, (uint8_t *)&_val, 2);
    return ret;
}

static int32_t max_platform_write(void *handle, uint8_t reg, uint8_t *bufp, uint16_t len)
{
    HAL_I2C_Mem_Write(handle, MAX17055_I2C_ADD_L, reg, I2C_MEMADD_SIZE_8BIT, bufp, len, 1000);
    return 0;
}

static int32_t max_platform_read(void *handle, uint8_t reg, uint8_t *bufp, uint16_t len)
{
    HAL_I2C_Mem_Read(handle, MAX17055_I2C_ADD_L, reg, I2C_MEMADD_SIZE_8BIT, bufp, len, 1000);
    return 0;
}

// void i2c_write_data_u16(uint16_t MemAddress, uint16_t *pData, uint16_t Size)
// {
//     uint8_t writeData[(uint8_t)Size];
//     for (int i = 0; i < Size; i++)
//     {
//         writeData[i]     = *pData & 0x00FF;
//         writeData[i + 1] = (*pData & 0xFF00) >> 8;
//     }
//     HAL_I2C_Mem_Write(&hi2c1, MAX17055_I2C_ADD_L, MemAddress, 1, writeData, Size * 2, 100);
// }

// void i2c_read_data_u16(uint16_t MemAddress, uint16_t *pData, uint16_t Size)
// {
//     uint8_t readData[Size * 2];
//     HAL_I2C_Mem_Read(&hi2c1, MAX17055_I2C_ADD_L, MemAddress, 1, readData, Size * 2, 100);
//     for (int i = 0; i < Size; i++) { pData[i] = readData[i] | (uint16_t)(readData[i + 1] << 8); }
// }