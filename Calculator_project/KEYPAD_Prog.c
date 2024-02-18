

#define  KEYPAD_PROG  1
#include "StdTypes.h"
#include "DIO_Int.h"
#include "KeyPad_Int.h"
#include "KeyPad_Cfg.h"

#define  F_CPU   8000000
#include <util/delay.h>



void KEYPAD_Init(void)
{
	u8 r;
	for (r=0;r<4;r++)
	{
		DIO_WritePin(FIRST_OUTPUT+r,HIGH);
	}
}

u8 KEYPAD_GetKey(void)
{
	u8 r,c,key=NO_KEY;
	
	for (r=0;r<ROW;r++)
	{
		DIO_WritePin(FIRST_OUTPUT+r,LOW);
		for (c=0;c<COL;c++)
		{
			if (DIO_ReadPin(FIRST_INPUT+c)==LOW)
			{
				key=KeysArray[r][c];
				_delay_ms(10);
				while(DIO_ReadPin(FIRST_INPUT+c)==LOW);
				_delay_ms(10);
			}
		}
		DIO_WritePin(FIRST_OUTPUT+r,HIGH);
	}
	return key;
}