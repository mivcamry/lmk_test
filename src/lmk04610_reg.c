#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "lmk04610_reg.h"
#include "api_errors.h"
#include "hal.h"


#define IN_OUT_BUFF_SZ 3

int lmk04610_register_write(const uint16_t address, const uint8_t data)
{
	uint8_t rd[] = {0,0,0};
	uint8_t wr[3];

	wr[2] = data;
	wr[1] = address & 0xFF;
	wr[0] = (address >> 8) & 0x1F;

	//printf("----------------------- write --------------------------------------------------------------------\n");
	//printf("--- write data to register %x  << [0]:%x, [1]:%x, [2]:%x >> ---\n", address, wr[0], wr[1], wr[2]);
	//printf("--- read data from register %x  << [0]:%x, [1]:%x, [2]:%x >> ---\n", address, rd[0], rd[1], rd[2]);

	return spi_xfer_lmk0482x(wr, rd, IN_OUT_BUFF_SZ);
}

int lmk04610_register_read(const uint16_t address, uint8_t *data)
{
	int ret = API_ERROR_INVALID_PARAM;
	uint8_t rd[] = {0,0,0};
	uint8_t wr[3];

	wr[2] = 0xFF;
	wr[1] = address & 0xFF;
	wr[0] = (address >> 8) & 0x1F;
	wr[0] |= 0x80;
	ret = spi_xfer_lmk0482x(wr, rd, IN_OUT_BUFF_SZ);

	if(ret == API_ERROR_OK)
		*data = rd[2];

	//printf("----------------------- read --------------------------------------------------------------------\n");
	//printf("--- write data to register %x  << [0]:%x, [1]:%x, [2]:%x >> ---\n", address, wr[0], wr[1], wr[2]);
	//printf("--- read data from register %x  << [0]:%x, [1]:%x, [2]:%x >> ---\n", address, rd[0], rd[1], rd[2]);

	return ret;
}

int lmk04610_register_write_tbl(struct lmk04610_reg_data* tbl, uint32_t count)
{
	uint16_t i =0;

	for (i = 0; i<count; i++) {
		lmk04610_register_write(tbl[i].reg, tbl[i].val);
	}

	return API_ERROR_OK;
}
