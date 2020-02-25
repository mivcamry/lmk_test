#include <stdio.h>
#include "app.h"
#include "hal.h"
#include "lmk04610.h"
#include "app_error.h"

int APP_init(void)
{
	int appError = APP_ERR_OK;
	/*Initialise SPI Driver on Platform*/
	printf("APP:INIT: SPI \r\n");

	spi_init();
	appError = spi_open(1,0);
	if(appError != APP_ERR_OK) {
		printf("APP_init: spi_open() failed! Error: %d \n", appError);
		return appError;
	}

	appError = lmk04610_configure();
	if(appError != APP_ERR_OK) {
		printf("APP_init: spi_configure() failed! Error: %d \n", appError);
		return appError;
	}
	else
		printf("spi_configure() succesfull! \n");


	return appError;
}

int APP_shutdown(void)
{
	int appError = APP_ERR_OK;

	printf("APP:SHTDWN: SPI \r\n");
	spi_close();

	return appError;
}
