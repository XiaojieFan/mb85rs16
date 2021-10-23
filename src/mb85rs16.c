
/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-02-20     XiaojieFan   add port file
 */

#include "drv_spi.h"
#include "board.h"
#include "drv_gpio.h"
#include <rtthread.h>
#include <rtdevice.h>
#include "mb85rs16.h"

#define PKG_USING_MB85RS16

#ifdef PKG_USING_MB85RS16

#define DBG_ENABLE
#define DBG_SECTION_NAME  "mb85rs16"
#define DBG_LEVEL  			DBG_LOG //DBG_INFO
#include <rtdbg.h>

#define MB85RS16_SPI_DEVICE_NAME  "spi30"


extern int fram_init();
static struct rt_spi_device *spi_dev_mb85rs16;     /* SPI Éè±¸¾ä±ú */

//CS- PD0
int mb85rs16_spi_device_init()
{
    __HAL_RCC_GPIOD_CLK_ENABLE();
		rt_err_t res = RT_EOK;
    res = rt_hw_spi_device_attach("spi3", MB85RS16_SPI_DEVICE_NAME, GPIOD, GPIO_PIN_0);
	  if (res != RT_EOK)
		{
			LOG_E("mb85rs16 Failed to attach device %s\n", MB85RS16_SPI_DEVICE_NAME);
			return res;
		}
		fram_init();
}
INIT_COMPONENT_EXPORT(mb85rs16_spi_device_init);
int fram_init()
{
	  rt_err_t res = RT_EOK;
		spi_dev_mb85rs16 = (struct rt_spi_device *)rt_device_find(MB85RS16_SPI_DEVICE_NAME);
    if (!spi_dev_mb85rs16)
    {
        LOG_E("spi find run failed! cant't find %s device!\n", MB85RS16_SPI_DEVICE_NAME);
        return RT_NULL;
    }
		//Set device SPI Mode
		struct rt_spi_configuration cfg = {0};
		cfg.data_width = 8;
		cfg.mode = RT_SPI_MASTER |RT_SPI_MODE_0 | RT_SPI_MSB ;//| RT_SPI_NO_CS;// 
		cfg.max_hz = MB85RS16_SPICLOCK;
		rt_spi_configure(spi_dev_mb85rs16, &cfg);
		return res;
}

void mb85rs16_write_enable(uint8_t select)
{
		rt_spi_send(spi_dev_mb85rs16, &select,1);
}
void mb85rs16_write_byte(uint16_t write_addr, uint8_t write_data)
{
		uint8_t send_buff[3];
		mb85rs16_write_enable(REG_WRITE_ENABLE);
		send_buff[0] = REG_WRITE_COMMAND;
		send_buff[1] = (write_addr>>8) &0xff;
		send_buff[2] = write_addr&0xff;
		rt_spi_send_then_send(spi_dev_mb85rs16, send_buff, 3,&write_data, 1);
		mb85rs16_write_enable(REG_WRITE_DISABLE);	
}

void mb85rs_write_bytes(uint16_t write_addr, uint8_t *write_buff, uint16_t write_bytes)
{
			uint8_t send_buff[3];
		mb85rs16_write_enable(REG_WRITE_ENABLE);
		send_buff[0] = REG_WRITE_COMMAND;
		send_buff[1] = (write_addr>>8) &0xff;
		send_buff[2] = write_addr&0xff;
		rt_spi_send_then_send(spi_dev_mb85rs16, send_buff, 3,write_buff, write_bytes);
		mb85rs16_write_enable(REG_WRITE_DISABLE);
	
}



void mb85rs16_read_bytes(uint16_t read_addr, uint8_t *read_buff, uint16_t read_bytes)
{
			uint8_t send_buff[3] = {0};
			send_buff[0] = REG_READ_COMMAND;
			send_buff[1] = (read_addr>>8)&0xff;
			send_buff[2] = read_addr&0xff;
			rt_spi_send_then_recv(spi_dev_mb85rs16,send_buff,3, read_buff, read_bytes);
}

void mb85rs16_read_device_id(uint8_t *read_buff, uint16_t *read_bytes)
{
			uint8_t send_buff[3] = {0};
			send_buff[0] =  REG_READ_DEVICE_ID;
			rt_spi_send_then_recv(spi_dev_mb85rs16, send_buff, 1, read_buff, 4);
			*read_bytes = 4;
}




void mb85rs16_read_device_id_write_status(uint8_t write_data)
{
	uint8_t send_buff[2];
	
	send_buff[0] = REG_WRITE_STATUS;
	send_buff[1] = write_data;
	rt_spi_send(spi_dev_mb85rs16,send_buff,2);
}

uint8_t mb85rs16_read_status(void)
{
	uint8_t read_status = 0,send_buff[1];
	
	send_buff[0] = REG_READ_STATUS;
	rt_spi_send_then_recv(spi_dev_mb85rs16,send_buff,1,&read_status,1);
	
	return read_status;
}


void mb85rs16_write_status(uint8_t write_data)
{
	uint8_t send_buff[2];
	
	send_buff[0] = REG_WRITE_STATUS;
	send_buff[1] = write_data;
	rt_spi_send(spi_dev_mb85rs16,send_buff,2);
}













#endif