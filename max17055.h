#ifndef MAX17055_H
#define MAX17055_H

#ifdef __cplusplus
extern "C" {
#endif

#include "max17055_reg.h"


typedef int32_t (*max17055_write_ptr)(void *, uint8_t, uint8_t *, uint16_t);
typedef int32_t (*max17055_read_ptr)(void *, uint8_t, uint8_t *, uint16_t);

typedef struct {
    /** Component mandatory fields **/
    max17055_write_ptr write_reg;
    max17055_read_ptr read_reg;
    /** Customizable optional pointer **/
    void *handle;
} max17055_ctx_t;

typedef union {
    int16_t i16bit[3];
    uint8_t u8bit[6];
} axis3bit16_t;

typedef union {
    int16_t i16bit;
    uint8_t u8bit[2];
} axis1bit16_t;

typedef union {
    uint16_t u16bit;
    uint8_t u8bit[2];
} short_uint8;

typedef union {
    int32_t i32bit[3];
    uint8_t u8bit[12];
} axis3bit32_t;

typedef union {
    int32_t i32bit;
    uint8_t u8bit[4];
} axis1bit32_t;

int32_t max17055_devname_get(max17055_ctx_t *ctx, uint16_t *val);
int32_t max17055_rep_cap_get(max17055_ctx_t *ctx, uint16_t *val);
int32_t max17055_avg_cap_get(max17055_ctx_t *ctx, uint16_t *val);
int32_t max17055_full_cap_rep_get(max17055_ctx_t *ctx, uint16_t *val);
int32_t max17055_full_cap_rep_set(max17055_ctx_t *ctx, uint16_t val);
int32_t max17055_full_cap_get(max17055_ctx_t *ctx, uint16_t *val);
int32_t max17055_full_cap_nom_get(max17055_ctx_t *ctx, uint16_t *val);
int32_t max17055_full_cap_nom_set(max17055_ctx_t *ctx, uint16_t val);
int32_t max17055_rep_soc_get(max17055_ctx_t *ctx, uint16_t *val);
int32_t max17055_avg_soc_get(max17055_ctx_t *ctx, uint16_t *val);
int32_t max17055_rcell_get(max17055_ctx_t *ctx, uint16_t *val);
int32_t max17055_vf_ocv_get(max17055_ctx_t *ctx, uint16_t *val);
int32_t max17055_vf_soc_get(max17055_ctx_t *ctx, uint16_t *val);
int32_t max17055_vripple_get(max17055_ctx_t *ctx, uint16_t *val);
int32_t max17055_age_get(max17055_ctx_t *ctx, uint16_t *val);
int32_t max17055_cycles_get(max17055_ctx_t *ctx, uint16_t *val);
int32_t max17055_cycles_set(max17055_ctx_t *ctx, uint16_t val);
int32_t max17055_temp_get(max17055_ctx_t *ctx, int16_t *val);
int32_t max17055_vcell_get(max17055_ctx_t *ctx, uint16_t *val);
int32_t max17055_current_get(max17055_ctx_t *ctx, int16_t *val);
int32_t max17055_avgcurrent_get(max17055_ctx_t *ctx, int16_t *val);
int32_t max17055_tte_get(max17055_ctx_t *ctx, uint16_t *val);
int32_t max17055_tff_get(max17055_ctx_t *ctx, uint16_t *val);
int32_t max17055_rcomp0_get(max17055_ctx_t *ctx, uint16_t *val);
int32_t max17055_rcomp0_set(max17055_ctx_t *ctx, uint16_t val);
int32_t max17055_tempco_get(max17055_ctx_t *ctx, uint16_t *val);
int32_t max17055_tempco_set(max17055_ctx_t *ctx, uint16_t val);
int32_t max17055_qr_table00_set(max17055_ctx_t *ctx, uint16_t val);
int32_t max17055_qr_table10_set(max17055_ctx_t *ctx, uint16_t val);
int32_t max17055_qr_table20_set(max17055_ctx_t *ctx, uint16_t val);
int32_t max17055_qr_table30_set(max17055_ctx_t *ctx, uint16_t val);
int32_t max17055_qr_table00_get(max17055_ctx_t *ctx, uint16_t *val);
int32_t max17055_qr_table10_get(max17055_ctx_t *ctx, uint16_t *val);
int32_t max17055_qr_table20_get(max17055_ctx_t *ctx, uint16_t *val);
int32_t max17055_qr_table30_get(max17055_ctx_t *ctx, uint16_t *val);
int32_t max17055_status_set(max17055_ctx_t *ctx, max17055_status_t val);
int32_t max17055_status_get(max17055_ctx_t *ctx, max17055_status_t *val);
int32_t max17055_vcell_get(max17055_ctx_t *ctx, uint16_t *val);
int32_t max17055_tte_get(max17055_ctx_t *ctx, uint16_t *val);
int32_t max17055_rcell_get(max17055_ctx_t *ctx, uint16_t *val);
int32_t max17055_designcap_set(max17055_ctx_t *ctx, uint16_t val);
int32_t max17055_ichgterm_set(max17055_ctx_t *ctx, uint16_t val);
int32_t max17055_ttf_get(max17055_ctx_t *ctx, uint16_t *val);
int32_t max17055_learncfg_get(max17055_ctx_t *ctx, max17055_learncfg_t *val);
int32_t max17055_learncfg_set(max17055_ctx_t *ctx, max17055_learncfg_t val);
int32_t max17055_vempty_set(max17055_ctx_t *ctx, uint16_t val);
int32_t max17055_fstat_get(max17055_ctx_t *ctx, max17055_fstat_t *val);
int32_t max17055_dqacc_set(max17055_ctx_t *ctx, uint16_t val);
int32_t max17055_dpacc_set(max17055_ctx_t *ctx, uint16_t val);
int32_t max17055_softwakeup_set(max17055_ctx_t *ctx, uint16_t val);
int32_t max17055_hibcfg_set(max17055_ctx_t *ctx, uint16_t val);
int32_t max17055_hibcfg_get(max17055_ctx_t *ctx, uint16_t *val);
int32_t max17055_modelcfg_set(max17055_ctx_t *ctx, max17055_modelcfg_t val);
int32_t max17055_modelcfg_get(max17055_ctx_t *ctx, max17055_modelcfg_t *val);
int32_t max17055_mixcap_get(max17055_ctx_t *ctx, uint16_t *val);
int32_t max17055_mixcap_set(max17055_ctx_t *ctx, uint16_t val);
int32_t max17055_dqacc_get(max17055_ctx_t *ctx, uint16_t *val);
int32_t max17055_dpacc_get(max17055_ctx_t *ctx, uint16_t *val);
int32_t max17055_vf_ocv_get(max17055_ctx_t *ctx, uint16_t *val);
int32_t max17055_mixsoc_get(max17055_ctx_t *ctx, uint16_t *val);
#endif /* MAX17055_H */