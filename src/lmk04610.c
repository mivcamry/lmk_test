#include "lmk04610.h"
#include <stdio.h>
#include <unistd.h>
#include "hal.h"

#include "lmk04610_reg_values.h"


int lmk04610_configure()
{
	int ret = 0;

	uint8_t data = 0;
	uint8_t chip_type;
	uint16_t prod_id;
	uint8_t mask_rev;
	uint16_t vendor_id;

	//-----  Reset Chip -----
	ret = lmk04610_register_write(LMK04610_REG_CFG_A, 0x81);
	if(ret != 0)
		printf("--- Error spi_write_master(LMK04610_REG_CFG_A, 0x80) ---\n");
	else
		printf("--- Chip reset success (NO 3-Wire SPI)---\n");

	sleep(1);

	//
	data = 0x00;
	ret = lmk04610_register_write(0x0011, data);
	ret = lmk04610_register_write(0x0085, data);
	ret = lmk04610_register_write(0x0086, data);
	data = 0x02;
	ret = lmk04610_register_write(0x00F6, data);


	data = 0x18;
	ret = lmk04610_register_write(LMK04610_REG_CFG_A, data);
	if(ret != 0)
		printf("--- Error spi_write_master(LMK04610_REG_CFG_A, 0x10) ---\n");

	printf("**************************   ***************************\n");

	data = 0xFF;
	//====================================================
	while (data != 0x18)
	{

		data = 0;
		ret = lmk04610_register_read(LMK04610_REG_CFG_A, &data);
		if(ret != 0)
			printf("--- Error lmk04610_register_read(LMK04610_REG_CFG_A, &data) ---\n");
		else
			printf("--- read register LMK04610_REG_CFG_A [0]:%x, ---\n", data);

		sleep(1);

	}

	printf("---------------------------------------------------------\n");

	//======================================================================
	if((ret = lmk04610_register_read(LMK04610_REG_CHIP_TYPE, &data)) != 0)
	{
		printf("--- Error spi_read_master(LMK0482x_REG_CHIP_TYPE, &data) ---\n");
		return ret;
	}
	else
		printf("--- read register LMK0482x_REG_CHIP_TYPE:%x, ---\n", data);

	chip_type = data;


	if((ret = lmk04610_register_read(LMK04610_REG_PROD_ID_MSB, &data)) != 0)
	{
		printf("--- Error spi_read_master(LMK0482x_REG_PROD_ID_MSB, &data) ---\n");
		return ret;
	}
	else
		printf("--- read register LMK04610_REG_PROD_ID_MSB:%x, ---\n", data);

	prod_id = data;
	prod_id <<= 8;

	if((ret = lmk04610_register_read(LMK04610_REG_PROD_ID_LSB, &data)) != 0)
	{
		printf("--- Error spi_read_master(LMK0482x_REG_PROD_ID_LSB, &data) ---\n");
		return ret;
	}
	else
		printf("--- read register LMK0482x_REG_PROD_ID_LSB:%x, ---\n", data);

	prod_id |= data;

	if((ret = lmk04610_register_read(LMK04610_REG_CHIP_MASK_REV, &data)) != 0)
	{
		printf("--- Error spi_read_master(LMK0482x_REG_CHIP_MASK_REV, &data) ---\n");
		return ret;
	}
	else
		printf("--- read register LMK0482x_REG_CHIP_MASK_REV:%x, ---\n", data);
	mask_rev = data;


	if((ret = lmk04610_register_read(LMK04610_REG_VNDR_ID_MSB, &data)) != 0)
	{
		printf("--- Error spi_read_master(LMK04610_REG_VNDR_ID_MSB, &data) ---\n");
		return ret;
	}

	vendor_id = data;
	vendor_id <<= 8;

	if((ret = lmk04610_register_read(LMK04610_REG_VNDR_ID_LSB, &data)) != 0)
	{
		printf("--- Error spi_read_master(LMK0482x_REG_VNDR_ID_LSB, &data) ---\n");
		return ret;
	}
	else
		printf("--- read register LMK0482x_REG_VNDR_ID_LSB:%x, ---\n", data);

	vendor_id |= data;

	printf("*********************************************\r\n");
	printf("LMK04610 Chip ID: %x \r\n", chip_type);
	printf("LMK04610 Product ID: %x \r\n", prod_id);
	printf("LMK04610 Vendor ID: %x \r\n", mask_rev);
	printf("LMK04610 Product Revision: %x \r\n", vendor_id);
	printf("*********************************************\r\n");


	printf("=============  Setup lmk registers  ============\n");
	lmk04610_register_write_tbl(&LMK_INIT_TBL[0], sizeof(LMK_INIT_TBL) / sizeof(LMK_INIT_TBL[0]));


	printf("============= Custom set registers ============\n");



	printf("=============  Start device  ============\n");
	data = 0x01;
	ret = lmk04610_register_write(0x0011, data);
	if(ret != 0)
		printf("--- Error spi_write_master(0x0011, 0x01) ---\n");


	// ============= Set PLL2 Lock detect  ==================
	data = 0x30;
	ret = lmk04610_register_write(0x00AD, data);
	if(ret != 0)
		printf("--- Error spi_write_master(0x00AD, 0x30) ---\n");

	delay_us(30000);

	data = 0x00;
	ret = lmk04610_register_write(0x00AD, data);


	return ret;

}



