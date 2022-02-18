#include "max17055.h"

void max17055_init(void)
{
    uint16_t deviceName, hib_cfg, refresh;
    max17055_status_t status;
    max17055_fstat_t fstat;
    i2c_read_data_u16(MAX17055_DEVNAME_REG, &deviceName, 1);
    HAL_Delay(100);
    if (deviceName == MAX17055_ID)
    {
        uint8_t statusbuff[2];
        HAL_I2C_Mem_Read(&hi2c1, MAX17055_I2C_ADD_L, MAX17055_STATUS_REG, 1, statusbuff, 2, 100);
        i2c_read_data_u16(MAX17055_STATUS_REG, &status.val, 1);
        if (status.bits.POR == 1)
        {
            HAL_Delay(1000);
            i2c_read_data_u16(MAX17055_FSTAT_REG, &fstat.val, 1);
            while (fstat.bits.data_not_ready == 1)
            {
                i2c_read_data_u16(MAX17055_FSTAT_REG, &fstat.val, 1);
                HAL_Delay(50);
            }
            // Wake-up Process
            // Store original HibCFG value
            i2c_read_data_u16(MAX17055_HIB_CFG_REG, &hib_cfg, 1);
            // Exit Hibernate Mode step 1
            HAL_I2C_Mem_Write(&hi2c1, MAX17055_I2C_ADD_L, MAX17055_SOFTWAKEUP, 1, (uint8_t *)0x90, 2, 100);
            // Exit Hibernate Mode step 2
            HAL_I2C_Mem_Write(&hi2c1, MAX17055_I2C_ADD_L, MAX17055_HIB_CFG_REG, 1, 0x00, 2, 100);
            // Exit Hibernate Mode step 3
            HAL_I2C_Mem_Write(&hi2c1, MAX17055_I2C_ADD_L, MAX17055_SOFTWAKEUP, 1, 0x00, 2, 100);

            // Init design parameters -> 3.1 OPTION 1 EZ Config (no INI file is needed)
            uint16_t realcap, designcap, dqacc, dpacc, ichgterm;

            realcap   = 12800;
            designcap = realcap * 2;
            i2c_write_data_u16(MAX17055_DESIGN_CAP_REG, &designcap, 1);

            dqacc = designcap / 32;
            i2c_write_data_u16(MAX17055_DQACC_REG, &dqacc, 1);

            ichgterm = 256 * 0.15625;
            i2c_write_data_u16(MAX17055_ICHG_TERM_REG, &ichgterm, 1);

            max17055_vempty_t vempty;
            vempty.bits.v_empty    = 3100 / 10;
            vempty.bits.v_recovery = 3400 / 40;
            i2c_write_data_u16(MAX17055_VEMPTY_REG, &vempty.val, 1);

            dpacc = (44138) / 32;
            i2c_write_data_u16(MAX17055_DPACC_REG, &dpacc, 1);

            uint16_t modelCFG = 0x8000;
            i2c_write_data_u16(MAX17055_MODEL_CFG_REG, &modelCFG, 1);

            // Wait model_cfg.refresh
            i2c_read_data_u16(MAX17055_MODEL_CFG_REG, &refresh, 1);
            while ((refresh & 0x8000))
            {
                i2c_read_data_u16(MAX17055_MODEL_CFG_REG, &refresh, 1);
                HAL_Delay(50);
            }
            // Restore Hibernation Config
            i2c_read_data_u16(MAX17055_HIB_CFG_REG, &hib_cfg, 1);
        }

        // Initialization complete  -> Clear and Check POR
        i2c_read_data_u16(MAX17055_STATUS_REG, &status.val, 1);
        status.bits.POR = 0;
        i2c_write_data_u16(MAX17055_STATUS_REG, &status.val, 1);
        i2c_read_data_u16(MAX17055_STATUS_REG, &status.val, 1);

        uint16_t cap;
        i2c_read_data_u16(MAX17055_REP_CAP_REG, &cap, 1);
        cap *= 0.016; // Capacity of battery as a Ah

        uint8_t socPercentage;
        HAL_I2C_Mem_Read(&hi2c1, MAX17055_I2C_ADD_L, MAX17055_REP_SOC_REG, 1, &socPercentage, 1,
                         100); // state of charge as a percent

        uint16_t temperature;
        i2c_read_data_u16(MAX17055_TEMP_REG, &temperature, 1);
        temperature /= 256.0;

        uint16_t instantVoltage;
        i2c_read_data_u16(MAX17055_VCELL_REG, &instantVoltage, 1);
        instantVoltage *= 0.078125;

        uint16_t instantCurrent;
        i2c_read_data_u16(MAX17055_CURRENT_REG, &instantCurrent, 1);
        instantCurrent *= 0.15625;

        uint16_t AverageCurrent;
        i2c_read_data_u16(MAX17055_AVG_CURRENT_REG, &AverageCurrent, 1);
        AverageCurrent *= 0.15625;



        HAL_Delay(100);
    }
}

void i2c_write_data_u16(uint16_t MemAddress, uint16_t *pData, uint16_t Size)
{
    uint8_t writeData[Size];
    for (int i = 0; i < Size; i++)
    {
        writeData[i]     = *pData & 0x00FF;
        writeData[i + 1] = (*pData & 0xFF00) >> 8;
    }
    HAL_I2C_Mem_Write(&hi2c1, MAX17055_I2C_ADD_L, MemAddress, 1, writeData, Size * 2, 100);
}

void i2c_read_data_u16(uint16_t MemAddress, uint16_t *pData, uint16_t Size)
{
    uint8_t readData[Size * 2];
    HAL_I2C_Mem_Read(&hi2c1, MAX17055_I2C_ADD_L, MemAddress, 1, readData, Size * 2, 100);
    for (int i = 0; i < Size; i++) { pData[i] = readData[i] | (uint16_t)(readData[i + 1] << 8); }
}