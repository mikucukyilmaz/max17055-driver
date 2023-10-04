#include "max17055.h"

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

int32_t max17055_rep_cap_get(max17055_ctx_t *ctx, uint16_t *val)
{
    int32_t ret;
    short_uint8 _val;
    ret  = max17055_read_reg(ctx, MAX17055_REP_CAP_REG, (uint8_t *)&_val, 2);
    *val = _val.u16bit;
    return ret;
}

int32_t max17055_rep_soc_get(max17055_ctx_t *ctx, uint16_t *val)
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

int32_t max17055_mixsoc_get(max17055_ctx_t *ctx, uint16_t *val)
{
    int32_t ret;
    short_uint8 _val;
    ret  = max17055_read_reg(ctx, MAX17055_MIX_SOC_REG, (uint8_t *)&_val, 2);
    *val = _val.u16bit;
    return ret;
}

int32_t max17055_avg_soc_get(max17055_ctx_t *ctx, uint16_t *val)
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

int32_t max17055_mixcap_set(max17055_ctx_t *ctx, uint16_t val)
{
    int32_t ret;
    short_uint8 _val;
    _val.u16bit = val;
    ret         = max17055_write_reg(ctx, MAX17055_MIX_CAP_REG, (uint8_t *)&_val, 2);
    return ret;
}

int32_t max17055_full_cap_rep_get(max17055_ctx_t *ctx, uint16_t *val)
{
    int32_t ret;
    short_uint8 _val;
    ret  = max17055_read_reg(ctx, MAX17055_FULL_CAP_REP_REG, (uint8_t *)&_val, 2);
    *val = _val.u16bit;
    return ret;
}

int32_t max17055_full_cap_rep_set(max17055_ctx_t *ctx, uint16_t val)
{
    int32_t ret;
    short_uint8 _val;
    _val.u16bit = val;
    ret         = max17055_write_reg(ctx, MAX17055_FULL_CAP_REP_REG, (uint8_t *)&_val, 2);
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

int32_t max17055_cycles_set(max17055_ctx_t *ctx, uint16_t val)
{
    int32_t ret;
    short_uint8 _val;
    _val.u16bit = val;
    ret         = max17055_write_reg(ctx, MAX17055_CYCLES_REG, (uint8_t *)&_val, 2);
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

int32_t max17055_avg_cap_get(max17055_ctx_t *ctx, uint16_t *val)
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

int32_t max17055_full_cap_nom_get(max17055_ctx_t *ctx, uint16_t *val)
{
    int32_t ret;
    short_uint8 _val;
    ret  = max17055_read_reg(ctx, MAX17055_FULL_CAP_NOM_REG, (uint8_t *)&_val, 2);
    *val = _val.u16bit;
    return ret;
}

int32_t max17055_full_cap_nom_set(max17055_ctx_t *ctx, uint16_t val)
{
    int32_t ret;
    short_uint8 _val;
    _val.u16bit = val;
    ret         = max17055_write_reg(ctx, MAX17055_FULL_CAP_NOM_REG, (uint8_t *)&_val, 2);
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

int32_t max17055_full_cap_get(max17055_ctx_t *ctx, uint16_t *val);

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

int32_t max17055_vempty_set(max17055_ctx_t *ctx, uint16_t val)
{
    int32_t ret;
    short_uint8 _val;
    _val.u16bit = val;
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

int32_t max17055_qr_table00_set(max17055_ctx_t *ctx, uint16_t val)
{
    int32_t ret;
    short_uint8 _val;
    _val.u16bit = val;
    ret         = max17055_write_reg(ctx, MAX17055_QR_TABLE00_REG, (uint8_t *)&_val, 2);
    return ret;
}

int32_t max17055_qr_table10_set(max17055_ctx_t *ctx, uint16_t val)
{
    int32_t ret;
    short_uint8 _val;
    _val.u16bit = val;
    ret         = max17055_write_reg(ctx, MAX17055_QR_TABLE10_REG, (uint8_t *)&_val, 2);
    return ret;
}

int32_t max17055_qr_table20_set(max17055_ctx_t *ctx, uint16_t val)
{
    int32_t ret;
    short_uint8 _val;
    _val.u16bit = val;
    ret         = max17055_write_reg(ctx, MAX17055_QR_TABLE20_REG, (uint8_t *)&_val, 2);
    return ret;
}

int32_t max17055_qr_table30_set(max17055_ctx_t *ctx, uint16_t val)
{
    int32_t ret;
    short_uint8 _val;
    _val.u16bit = val;
    ret         = max17055_write_reg(ctx, MAX17055_QR_TABLE30_REG, (uint8_t *)&_val, 2);
    return ret;
}

int32_t max17055_qr_table00_get(max17055_ctx_t *ctx, uint16_t *val)
{
    int32_t ret;
    short_uint8 _val;
    ret  = max17055_read_reg(ctx, MAX17055_QR_TABLE00_REG, (uint8_t *)&_val, 2);
    *val = _val.u16bit;
    return ret;
}

int32_t max17055_qr_table10_get(max17055_ctx_t *ctx, uint16_t *val)
{
    int32_t ret;
    short_uint8 _val;
    ret  = max17055_read_reg(ctx, MAX17055_QR_TABLE10_REG, (uint8_t *)&_val, 2);
    *val = _val.u16bit;
    return ret;
}

int32_t max17055_qr_table20_get(max17055_ctx_t *ctx, uint16_t *val)
{
    int32_t ret;
    short_uint8 _val;
    ret  = max17055_read_reg(ctx, MAX17055_QR_TABLE20_REG, (uint8_t *)&_val, 2);
    *val = _val.u16bit;
    return ret;
}

int32_t max17055_qr_table30_get(max17055_ctx_t *ctx, uint16_t *val)
{
    int32_t ret;
    short_uint8 _val;
    ret  = max17055_read_reg(ctx, MAX17055_QR_TABLE30_REG, (uint8_t *)&_val, 2);
    *val = _val.u16bit;
    return ret;
}

int32_t max17055_vf_ocv_get(max17055_ctx_t *ctx, uint16_t *val)
{
    int32_t ret;
    short_uint8 _val;
    ret  = max17055_read_reg(ctx, MAX17055_VFOCV_REG, (uint8_t *)&_val, 2);
    *val = _val.u16bit;
    return ret;
}