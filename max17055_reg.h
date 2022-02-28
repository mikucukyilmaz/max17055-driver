#ifndef MAX17055_REG_H
#define MAX17055_REG_H

#ifdef __cplusplus
extern "C" {
#endif

#define MAX17055_STATUS_REG       0x00
#define MAX17055_VALRT_TH_REG     0x01
#define MAX17055_TALRT_TH_REG     0x02
#define MAX17055_SALRT_TH_REG     0x03
#define MAX17055_AT_RATE_REG      0x04
#define MAX17055_REP_CAP_REG      0x05
#define MAX17055_REP_SOC_REG      0x06
#define MAX17055_AGE_REG          0x07
#define MAX17055_TEMP_REG         0x08
#define MAX17055_VCELL_REG        0x09
#define MAX17055_CURRENT_REG      0x0A
#define MAX17055_AVG_CURRENT_REG  0x0B
#define MAX17055_QRESIDUAL_REG    0x0C
#define MAX17055_MIX_SOC_REG      0x0D
#define MAX17055_AV_SOC_REG       0x0E
#define MAX17055_MIX_CAP_REG      0x0F
#define MAX17055_FULL_CAP_REP_REG 0x10
#define MAX17055_TTE_REG          0x11
#define MAX17055_QR_TABLE00_REG   0x12
#define MAX17055_FULL_SOC_THR_REG 0x13
#define MAX17055_RCELL_REG        0x14
// #define MAX17055_RESERVED_REG        0x15
#define MAX17055_AVG_TA_REG       0x16
#define MAX17055_CYCLES_REG       0x17
#define MAX17055_DESIGN_CAP_REG   0x18
#define MAX17055_AVG_VCELL_REG    0x19
#define MAX17055_MAX_MIN_TEMP_REG 0x1A
#define MAX17055_MAX_MIN_VOLT_REG 0x1B
#define MAX17055_MAX_MIN_CURR_REG 0x1C
#define MAX17055_CONFIG_REG       0x1D
#define MAX17055_ICHG_TERM_REG    0x1E
#define MAX17055_AV_CAP_REG       0x1F
#define MAX17055_TTF_REG          0x20
#define MAX17055_DEVNAME_REG      0x21
#define MAX17055_QR_TABLE10_REG   0x22
#define MAX17055_FULL_CAP_NOM_REG 0x23
// #define MAX17055_RESERVED_REG        0x24
// #define MAX17055_RESERVED_REG        0x25
// #define MAX17055_RESERVED_REG        0x26
#define MAX17055_AIN_REG        0x27
#define MAX17055_LEARN_CFG_REG  0x28
#define MAX17055_FILTER_CFG_REG 0x29
#define MAX17055_RELAX_CFG_REG  0x2A
#define MAX17055_MISC_CFG_REG   0x2B
#define MAX17055_TGAIN_REG      0x2C
#define MAX17055_TOFF_REG       0x2D
#define MAX17055_CGAIN_REG      0x2E
#define MAX17055_COFF_REG       0x2F
// #define MAX17055_RESERVED_REG        0x30
// #define MAX17055_RESERVED_REG        0x31
#define MAX17055_QR_TABLE20_REG 0x32
// #define MAX17055_RESERVED_REG        0x33
#define MAX17055_DIE_TEMP_REG 0x34
#define MAX17055_FULL_CAP_REG 0x35
// #define MAX17055_RESERVED_REG        0x36
// #define MAX17055_RESERVED_REG        0x37
#define MAX17055_R_COMP0_REG 0x38
#define MAX17055_TEMP_CO_REG 0x39
#define MAX17055_VEMPTY_REG  0x3A
// #define MAX17055_RESERVED_REG        0x3B
// #define MAX17055_RESERVED_REG        0x3C
#define MAX17055_FSTAT_REG      0x3D
#define MAX17055_TIMER_REG      0x3E
#define MAX17055_SHDN_TIMER_REG 0x3F
#define MAX17055_USER_MEM1_REG  0x40
// #define MAX17055_RESERVED_REG        0x41
#define MAX17055_QRTABLE30_REG 0x42
#define MAX17055_R_GAIN_REG    0x43
// #define MAX17055_RESERVED_REG        0x44
#define MAX17055_DQACC_REG 0x45
#define MAX17055_DPACC_REG 0x46
// #define MAX17055_RESERVED_REG        0x47
// #define MAX17055_RESERVED_REG        0x48
#define MAX17055_CONVG_CFG_REG  0x49
#define MAX17055_VF_REM_CAP_REG 0x4A
// #define MAX17055_RESERVED_REG        0x4B
// #define MAX17055_RESERVED_REG        0x4C
#define MAX17055_QH_REG 0x4D
// #define MAX17055_RESERVED_REG        0x4E
// #define MAX17055_RESERVED_REG        0x4F
#define MAX17055_STATUS2_REG      0xB0
#define MAX17055_POWER_REG        0xB1
#define MAX17055_ID_USERMEM2_REG  0xB2
#define MAX17055_AVG_POWER_REG    0xB3
#define MAX17055_IALRT_TH_REG     0xB4
#define MAX17055_TTF_CFG_REG      0xB5
#define MAX17055_CV_MIX_CAP_REG   0xB6
#define MAX17055_CV_HALF_TIME_REG 0xB7
#define MAX17055_CG_TEMP_CO_REG   0xB8
#define MAX17055_CURVE_REG        0xB9
#define MAX17055_HIB_CFG_REG      0xBA
#define MAX17055_CONFIG2_REG      0xBB
#define MAX17055_VRIPPLE_REG      0xBC
#define MAX17055_RIPPLE_CFG_REG   0xBD
#define MAX17055_TIMER_H_REG      0xBE
// #define MAX17055_RESERVED_REG        0xBF
#define MAX17055_RSENSE_USERMEM3_REG 0xD0
#define MAX17055_SC_OCV_LIM_REG      0xD1
// #define MAX17055_RESERVED_REG        0xD2
#define MAX17055_SOC_HOLD_REG        0xD3
#define MAX17055_MAX_PEAK_POWER_REG  0xD4
#define MAX17055_SUS_PEAK_POWER_REG  0xD5
#define MAX17055_PACK_RESISTANCE_REG 0xD6
#define MAX17055_SYS_RESISTANCE_REG  0xD7
#define MAX17055_MIN_SYS_VOLTAGE_REG 0xD8
#define MAX17055_MPP_CURRENT_REG     0xD9
#define MAX17055_SPP_CURRENT_REG     0xDA
#define MAX17055_MODEL_CFG_REG       0xDB
#define MAX17055_AT_Q_RESIDUAL_REG   0xDC
#define MAX17055_AT_TTE_REG          0xDD
#define MAX17055_AT_AV_SOC_REG       0xDE
#define MAX17055_AT_AV_CAP_REG       0xDF
#define MAX17055_VFSOC_REG           0xFF
#define MAX17055_VFOCV_REG           0xFB

#define MAX17055_SOFTWAKEUP 0x60
typedef struct {

} max17055_status_reg_t;

typedef union {
    uint16_t val;
    struct {
        uint16_t v_recovery : 7;
        uint16_t v_empty    : 9;
    } bits;
} max17055_vempty_t;

typedef union {
    uint16_t val;
    struct {
        uint16_t data_not_ready     : 1;
        uint16_t                    : 5;
        uint16_t longrelax_cell_det : 1;
        uint16_t full_qualified     : 1;
        uint16_t empty_det          : 1;
        uint16_t relax_cell_det     : 1;
        uint16_t                    : 6;
    } bits;
} max17055_fstat_t;

typedef union {
    uint16_t val;
    struct {
        uint16_t           : 1;
        uint16_t POR       : 1;
        uint16_t I_min     : 1;
        uint16_t Bstatus   : 1;
        uint16_t           : 1;
        uint16_t           : 1;
        uint16_t I_max     : 1;
        uint16_t dSOCi     : 1;
        uint16_t V_min     : 1;
        uint16_t T_min     : 1;
        uint16_t S_min     : 1;
        uint16_t B_insert  : 1;
        uint16_t V_max     : 1;
        uint16_t T_max     : 1;
        uint16_t S_max     : 1;
        uint16_t B_removal : 1;
    } bits;
} max17055_status_t;

typedef struct {
    uint16_t val;
    struct {
        uint16_t             : 4;
        uint16_t learn_stage : 3;
        uint16_t             : 9;
    } bits;
} max17055_learncfg_t;

typedef struct {
    uint16_t val;
    struct {
        uint16_t          : 4;
        uint16_t model_id : 4;
        uint16_t          : 2;
        uint16_t vchg     : 1;
        uint16_t          : 4;
        uint16_t refresh  : 1;
    } bits;
} max17055_modelcfg_t;

#ifdef __cplusplus
}
#endif

#endif /* MAX17055_H */