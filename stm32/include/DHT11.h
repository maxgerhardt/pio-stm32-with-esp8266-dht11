#ifndef __DHT11_H
#define __DHT11_H 
#include "sys.h"   
 
//Set GPIO Direction
#define DHT11_IO_IN()  {GPIOA->CRL&=0XFFFFFFF0;GPIOA->CRL|=8<<0;}	//PA0
#define DHT11_IO_OUT() {GPIOA->CRL&=0XFFFFFFF0;GPIOA->CRL|=3<<0;}	//PA0
											   
#define	DHT11_DQ_OUT PAout(0) 
#define	DHT11_DQ_IN  PAin(0)   


u8 DHT11_Init(void); //Init DHT11
u8 DHT11_Read_Data(u8 *temperature,u8 *humidity); //Read DHT11 Value
u8 DHT11_Read_Byte(void);//Read One Byte
u8 DHT11_Read_Bit(void);//Read One Bit
u8 DHT11_Check(void);//Chack DHT11
void DHT11_Rst(void);//Reset DHT11    
#endif















