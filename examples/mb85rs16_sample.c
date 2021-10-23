#include "mb85rs16.h"
#include <rtthread.h>
#include <stdlib.h>
#include <string.h>

#define DBG_ENABLE
#define DBG_SECTION_NAME  "FRAM"
#define DBG_LEVEL         DBG_LOG
#include <rtdbg.h>



void fram_cmd(int argc, char **argv)
{
		uint16_t addr = 0;
		uint16_t num = 0;
		uint8_t read_buff[256] = {0};
		uint8_t write_buff[256] = {0};
		uint8_t id_buf[32] = {0};
		uint16_t id_buf_len = 0;
		uint8_t status = 0;
		int i = 0;
		
		if (rt_strcmp(argv[1], "id") == 0)
		{
				mb85rs16_read_device_id(id_buf, &id_buf_len);
			  
				hex_dump("the id is ", id_buf, id_buf_len);
		}
		else if (rt_strcmp(argv[1], "read") == 0)
		{	
			 addr = atoi(argv[2]);
			 num = atoi(argv[3]);
			 LOG_D("the read start addr is 0x%04x the read num is %d\n",addr, num);
			 mb85rs16_read_bytes(addr, read_buff, num);
			 hex_dump("the read data is ", read_buff, num);			
		}
		else if (rt_strcmp(argv[1], "write") == 0)
		{
			 addr = atoi(argv[2]);
			 num = atoi(argv[3]);
			 for (i = 0; i < num; i++)
			{
					write_buff[i] = i;
			}
			 LOG_D("the write start addr is 0x%04x the write num is %d\n",addr, num);
			 mb85rs_write_bytes(addr, write_buff, num);
		}
		else if (rt_strcmp(argv[1],"status") == 0)
		{
			status = mb85rs16_read_status();
			LOG_D("the status is  0x%02x \n",status);

		}
		else if (rt_strcmp(argv[1],"wrsr") == 0)
		{
			  LOG_D("write WRSR\n");
			  mb85rs16_write_enable(REG_WRITE_ENABLE);

				mb85rs16_write_status(0);
		}
}




MSH_CMD_EXPORT(fram_cmd, fram_cmd <id | read | write |>);
