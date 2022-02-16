#ifndef MAX17055_H
#define MAX17055_H

#ifdef __cplusplus
extern "C" {
#endif

#include <math.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

typedef int32_t (*max17055_write_ptr)(void *, uint8_t, const uint8_t *, uint16_t);
typedef int32_t (*max17055_read_ptr)(void *, uint8_t, uint8_t *, uint16_t);

typedef struct {
    max17055_write_ptr write_reg;
    max17055_read_ptr read_reg;
    void *handle;
} max17055_ctx_t;

#define MAX17055_I2C_ADD_L  ( 0x36 << 1 )
#define MAX17055_ID         0x4010


#ifdef __cplusplus
}
#endif

#endif /* MAX17055_H */