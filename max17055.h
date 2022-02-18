#ifndef MAX17055_H
#define MAX17055_H

#ifdef __cplusplus
extern "C" {
#endif

#include "i2c.h"
#include "max17055_reg.h"
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define MAX17055_I2C_ADD_L (0x36 << 1)
#define MAX17055_ID        0x4010

void max17055_init(void);
void i2c_write_data_u16(uint16_t MemAddress, uint16_t *pData, uint16_t Size);
void i2c_read_data_u16(uint16_t MemAddress, uint16_t *pData, uint16_t Size);

#endif /* MAX17055_H */