#ifndef __LMK_0482X_H__
#define __LMK_0482X_H__

#include <stdint.h>
#include "lmk04610_reg.h"

#include <stdint.h>

int lmk04610_init();
int lmk04610_reset();

int lmk04610_configure();

int lmk04610_register_write(uint16_t address, uint8_t data);
int lmk04610_register_read(const uint16_t address, uint8_t* data);

int lmk04610_register_write_tbl(struct lmk04610_reg_data* tbl, uint32_t count);

#endif // __LMK_0482X_H__

