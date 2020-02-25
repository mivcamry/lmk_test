#ifndef __LMK0482x_REGISTERS_H__
#define __LMK0482x_REGISTERS_H__



struct lmk04610_reg_data {
	uint16_t reg;
	uint8_t  val;
};

/*SILICON Revision SUMMARY: (AD916x_REGMAP_V4)*/
#define LMK04610_ID_DEVICE_TYPE                     0x06
#define LMK04610_PROD_ID_LSB                        91
#define LMK04610_PROD_ID_MSB                        208
#define LMK04610_MASK_REV	                        36
#define LMK04610_VNDR_ID_LSB                        4
#define LMK04610_VNDR_ID_MSB                        81

/*REGISTER SUMMARY : (AD916x_REGMAP_V4)*/
#define LMK04610_REG_CFG_A                       0x000
#define LMK04610_REG_CFG_B                       0x002
#define LMK04610_REG_CHIP_TYPE                   0x003
#define LMK04610_REG_PROD_ID_MSB                 0x004
#define LMK04610_REG_PROD_ID_LSB                 0x005
#define LMK04610_REG_CHIP_MASK_REV               0x006
#define LMK04610_REG_VNDR_ID_MSB                 0x00C
#define LMK04610_REG_VNDR_ID_LSB                 0x00D

#define LMK04610_REG_STARTUP                     0x001
#define LMK04610_REG_IOCTRL_SPI0				 0x08D




#endif /*__LMK0482x_REG_H__*/

