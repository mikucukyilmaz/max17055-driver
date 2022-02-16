#include "max17055.h"

static int32_t max17055_read_reg(max17055_ctx_t *ctx, uint8_t reg, uint8_t *data, uint16_t len)
{
    int32_t ret;
    ret = ctx->read_reg(ctx->handle, reg, data, len);
    return ret;
}

static int32_t max17055_write_reg(max17055_ctx_t *ctx, uint8_t reg, const uint8_t *data, uint16_t len)
{
    int32_t ret;
    ret = ctx->write_reg(ctx->handle, reg, data, len);
    return ret;
}
