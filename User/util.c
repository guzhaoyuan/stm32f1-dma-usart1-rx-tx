#include "util.h"

void Delay(u32 nCount)
{
   for(; nCount != 0; nCount--);
}

void Delay_Ms(uint16_t time)  //ÑÓÊ±º¯Êý
{ 
	uint16_t i,j;
	for(i=0;i<time;i++)
  		for(j=0;j<10260;j++);
}
