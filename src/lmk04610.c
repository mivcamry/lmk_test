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
	int cnt = 0;

	//-----  Reset Chip -----
	ret = lmk04610_register_write(LMK04610_REG_CFG_A, 0x81);
	if(ret != 0) {
		printf("--- Error lmk04610_register_write(LMK04610_REG_CFG_A, 0x81) ---\n");
		return ret;
	}
	else
		printf("--- Chip reset success ---\n");

	sleep(1);

	//
	ret = lmk04610_register_write(0x0011, 0x00);
	ret = lmk04610_register_write(0x0085, 0x00);
	ret = lmk04610_register_write(0x0086, 0x00);
	ret = lmk04610_register_write(0x00F6, 0x02);


	data = 0x18;
	ret = lmk04610_register_write(LMK04610_REG_CFG_A, data);
	if(ret != 0) {
		printf("--- Error lmk04610_register_write(LMK04610_REG_CFG_A, 0x18) ---\n");
		return ret;
	}

	printf("**************************   ***************************\n");
	ret = lmk04610_register_write(0x0094, 0x04); // Set SPI

	data = 0xFF;
	//====================================================
	while (data != 0x18)
	{

		data = 0;
		ret = lmk04610_register_read(LMK04610_REG_CFG_A, &data);
		if(ret != 0) {
			printf("--- Error lmk04610_register_read(LMK04610_REG_CFG_A, &data) ---\n");
			return ret;
		}
		else
			printf("--- read register LMK04610_REG_CFG_A [0]:%x, ---\n", data);

		sleep(1);

	}

	printf("---------------------------------------------------------\n");

	//======================================================================
	if((ret = lmk04610_register_read(LMK04610_REG_CHIP_TYPE, &data)) != 0)
	{
		printf("--- Error lmk04610_register_read(LMK0482x_REG_CHIP_TYPE, &data) ---\n");
		return ret;
	}
	else
		printf("--- read register LMK0482x_REG_CHIP_TYPE:%x, ---\n", data);

	chip_type = data;


	if((ret = lmk04610_register_read(LMK04610_REG_PROD_ID_MSB, &data)) != 0)
	{
		printf("--- Error lmk04610_register_read(LMK0482x_REG_PROD_ID_MSB, &data) ---\n");
		return ret;
	}
	else
		printf("--- read register LMK04610_REG_PROD_ID_MSB:%x, ---\n", data);

	prod_id = data;
	prod_id <<= 8;

	if((ret = lmk04610_register_read(LMK04610_REG_PROD_ID_LSB, &data)) != 0)
	{
		printf("--- Error lmk04610_register_read(LMK0482x_REG_PROD_ID_LSB, &data) ---\n");
		return ret;
	}
	else
		printf("--- read register LMK0482x_REG_PROD_ID_LSB:%x, ---\n", data);

	prod_id |= data;

	if((ret = lmk04610_register_read(LMK04610_REG_CHIP_MASK_REV, &data)) != 0)
	{
		printf("--- Error lmk04610_register_read(LMK0482x_REG_CHIP_MASK_REV, &data) ---\n");
		return ret;
	}
	else
		printf("--- read register LMK0482x_REG_CHIP_MASK_REV:%x, ---\n", data);
	mask_rev = data;


	if((ret = lmk04610_register_read(LMK04610_REG_VNDR_ID_MSB, &data)) != 0)
	{
		printf("--- Error lmk04610_register_read(LMK04610_REG_VNDR_ID_MSB, &data) ---\n");
		return ret;
	}

	vendor_id = data;
	vendor_id <<= 8;

	if((ret = lmk04610_register_read(LMK04610_REG_VNDR_ID_LSB, &data)) != 0)
	{
		printf("--- Error lmk04610_register_read(LMK0482x_REG_VNDR_ID_LSB, &data) ---\n");
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

	// STAT0MUX Register. Detect
	ret = lmk04610_register_write(0x0095, 0x02);

	// Set Clock Input source
	ret = lmk04610_register_write(0x002C, 0x44);

	// =============   Set PLL2 Lock detect    ==================================
	// The PLL2_DLD_EN Register supports PLL2 DLD EN Feature
	ret = lmk04610_register_write(0x00F6, 0x02);
	// The PLL2_LD_WNDW_SIZE Register sets the PLL2 Window Comparator Setting
	ret = lmk04610_register_write(0x0085, 0x00);
	// ThePLL2_LD_WNDW_SIZE_INITIAL Register sets the PLL2 Window Comparator Initial Setting
	ret = lmk04610_register_write(0x0086, 0x00);

	printf("=============  Start device  ============\n");
	ret = lmk04610_register_write(0x0011, 0x01);
	if(ret != 0)
		printf("--- Error lmk04610_register_write(0x0011, 0x01) ---\n");

	//
	// The PLL2_CTRL Register supports other PLL2 features.
	// Before using PLL2 DLD signal, set this field to 0x3, wait 20ms, set to 0x0.
	ret = lmk04610_register_write(0x00AD, 0x30);
	if(ret != 0) {
		printf("--- Error lmk04610_register_write(0x00AD, 0x30) ---\n");
		return 0;
	}

	delay_ms(20);

	ret = lmk04610_register_write(0x00AD, 0x00);


	data = 0;
	cnt = 0;
	printf("====== Wait for PLL2 Locked...  ====== \r\n");
	while(!(data & 0x02))
	{
		delay_ms(100);

		if((ret = lmk04610_register_read(0x0BE, &data)) != 0)
		{
			printf("--- Error lmk04610_register_read(0x0BE, &data) ---\n");
			return ret;
		}
		if(!(data & 0x02))
		{
			ret = lmk04610_register_write(0x0011, 0x01);
			if(ret != 0)
				printf("--- Error lmk04610_register_write(0x0011, 0x01) ---\n");

			// The PLL2_CTRL Register supports other PLL2 features.
			// Before using PLL2 DLD signal, set this field to 0x3, wait 20ms, set to 0x0.
			ret = lmk04610_register_write(0x00AD, 0x30);
			if(ret != 0)
			{
				printf("--- Error lmk04610_register_write(0x00AD, 0x30) ---\n");
				return 0;
			}
			delay_ms(20);
			ret = lmk04610_register_write(0x00AD, 0x00);
			cnt++;
		}
	}

	printf("***************************************************\r\n");
	printf("****** Read  STATUS Register: %x  Count: %d  ******\r\n", data, cnt);
	printf("************** PLL2 Lock Detected *****************\r\n");
	printf("***************************************************\r\n");

	return ret;

}

