#include "delay.h"
#include "sys.h"
#include <dwt_stm32_delay.h>

		    								   
void delay_us(u32 nus)
{		
	DWT_Delay_us(nus);
}


void delay_ms(u16 nms)
{
	HAL_Delay(nms);
} 

































