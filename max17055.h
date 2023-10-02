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
int32_t max17055_repCap_get(max17055_ctx_t *ctx, uint16_t *val);
int32_t max17055_avCap_get(max17055_ctx_t *ctx, uint16_t *val);
int32_t max17055_fullcaprep_get(max17055_ctx_t *ctx, uint16_t *val);
int32_t max17055_fullcaprep_set(max17055_ctx_t *ctx, uint16_t val);
int32_t max17055_fullCap_get(max17055_ctx_t *ctx, uint16_t *val);
int32_t max17055_fullcapnom_get(max17055_ctx_t *ctx, uint16_t *val);
int32_t max17055_fullcapnom_set(max17055_ctx_t *ctx, uint16_t val);
int32_t max17055_repSoc_get(max17055_ctx_t *ctx, uint16_t *val);
int32_t max17055_avSoc_get(max17055_ctx_t *ctx, uint16_t *val);
int32_t max17055_rCell_get(max17055_ctx_t *ctx, uint16_t *val);
int32_t max17055_vFOCV_get(max17055_ctx_t *ctx, uint16_t *val);
int32_t max17055_vFSOC_get(max17055_ctx_t *ctx, uint16_t *val);
int32_t max17055_vRipple_get(max17055_ctx_t *ctx, uint16_t *val);
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
int32_t max17055_qrTable00_set(max17055_ctx_t *ctx, uint16_t val);
int32_t max17055_qrTable10_set(max17055_ctx_t *ctx, uint16_t val);
int32_t max17055_qrTable20_set(max17055_ctx_t *ctx, uint16_t val);
int32_t max17055_qrTable30_set(max17055_ctx_t *ctx, uint16_t val);
int32_t max17055_qrTable00_get(max17055_ctx_t *ctx, uint16_t *val);
int32_t max17055_qrTable10_get(max17055_ctx_t *ctx, uint16_t *val);
int32_t max17055_qrTable20_get(max17055_ctx_t *ctx, uint16_t *val);
int32_t max17055_qrTable30_get(max17055_ctx_t *ctx, uint16_t *val);
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
int32_t max17055_vempty_set(max17055_ctx_t *ctx, max17055_vempty_t val);
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
int32_t max17055_vfocv_get(max17055_ctx_t *ctx, uint16_t *val);
int32_t max17055_mixsoc_get(max17055_ctx_t *ctx, uint16_t *val);
#endif /* MAX17055_H */