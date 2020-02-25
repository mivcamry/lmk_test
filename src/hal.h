#ifndef __HAL_H__
#define __HAL_H__

#include <stdint.h>


#ifdef __cplusplus
extern "C" {
#endif

void spi_init();
int spi_open(int bus, int channel);
int spi_close();

int spi_set_mode(uint8_t m);
int spi_set_clk_polarity(uint8_t pol);
int spi_set_clk_phase(uint8_t phase);
int spi_set_lsb_first(int lsb_first);
int spi_set_bits_per_word(int bits);
int spi_set_speed(uint32_t speed);
int spi_xfer_lmk0482x(uint8_t* wbuf, uint8_t* rbuf, int len);
int delay_us(unsigned int time_us);
#ifdef __cplusplus
}
#endif

#endif /* !__HAL_H__*/
