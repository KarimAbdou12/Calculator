


#include "StdTypes.h"
#include "MemMap.h"
#include "DIO_Int.h"
#include "LCD_Cfg.h"
#include "LCD_Int.h"

#define F_CPU 8000000
#include <util/delay.h>

#if LCD_Mode==_8_BIT

void WriteIns(u8 ins)
{
	DIO_WritePin(RS,LOW);
	DIO_WritePort(LCD_PORT,ins);
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
	
}


void WriteData(unsigned char data)
{
	DIO_WritePin(RS,HIGH);
	DIO_WritePort(LCD_PORT,data);
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
}

void LCD_Init(void)
{
	_delay_ms(50);
	
	WriteIns(0x38);
	WriteIns(0x0C);
	WriteIns(0x01);
	_delay_ms(1);
	WriteIns(0x06);
}

#elif LCD_Mode==_4_BIT
void WriteIns(u8 ins)
{
	
	
	DIO_WritePin(RS,LOW);
	
	DIO_WritePin(D7,READ_BIT(ins,7));
	DIO_WritePin(D6,READ_BIT(ins,6));
	DIO_WritePin(D5,READ_BIT(ins,5));
	DIO_WritePin(D4,READ_BIT(ins,4));
	
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
	
	
	DIO_WritePin(D7,READ_BIT(ins,3));
	DIO_WritePin(D6,READ_BIT(ins,2));
	DIO_WritePin(D5,READ_BIT(ins,1));
	DIO_WritePin(D4,READ_BIT(ins,0));
	
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
	
}

void WriteData(unsigned char data)
{
	DIO_WritePin(RS,HIGH);
	
	DIO_WritePin(D7,READ_BIT(data,7));
	DIO_WritePin(D6,READ_BIT(data,6));
	DIO_WritePin(D5,READ_BIT(data,5));
	DIO_WritePin(D4,READ_BIT(data,4));

	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
	
	DIO_WritePin(D7,READ_BIT(data,3));
	DIO_WritePin(D6,READ_BIT(data,2));
	DIO_WritePin(D5,READ_BIT(data,1));
	DIO_WritePin(D4,READ_BIT(data,0));
	
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
	
}

void LCD_Init(void)
{
	_delay_ms(50);
	
	WriteIns(0x02);
	WriteIns(0x28);
	
	// func set
	WriteIns(0x0C);
	WriteIns(0x01);
	_delay_ms(1); 
	WriteIns(0x06);
}
#endif

void LCD_WriteChar(u8 ch)
{
	WriteData(ch);
}

void LCD_WriteNumber(s32 num)
{
	u8 str[10],i=0;
	s8 j;
	if(num==0)
	{
		LCD_WriteChar('0');
	}
	else
	{
		if(num<0)
		{
			num=num*-1;
			LCD_WriteChar('-');
		}
		while(num)
		{
			str[i]=num%10+'0';
			i++;
			num=num/10;
		}
		for(j=i-1;j>=0;j--)
		{
			LCD_WriteChar(str[j]);
		}
	}
}

void LCD_WriteString(char*str)
{
	u8 i;
	for (i=0;str[i];i++)
	{
		WriteData(str[i]);
		_delay_ms(40);
	}
}

void LCD_SetCursor(u8 line,u8 cell)
{
	if (line==1)
	{
		WriteIns(0x80|(cell-1));
	}
	else if (line ==2)
	{
		WriteIns(0x80|0x40|(cell-1));
	}
}

void LCD_Clear(void)
{
	WriteIns(0x01);
	_delay_ms(1);
}


void LCD_CustomChar(u8 location,u8*pattern)
{
	
	WriteIns(0x40+location*8);  
	s8 i;
	for(i=0;i<8;i++)
	{
		WriteData(pattern[i]);
	}
	
	LCD_SetCursor(1,1); 
	
	
}


void Welcome (void)
{

	LCD_SetCursor(1,4);
	LCD_WriteString("WELCOME TO");
	LCD_SetCursor(2,4);
	LCD_WriteString("CALCULATOR");
	_delay_ms(1000);
	LCD_Clear();
	
	LCD_SetCursor(1,6);
	LCD_WriteString("START");
	_delay_ms(500);
	LCD_Clear();
	
}