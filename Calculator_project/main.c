/*
 * Calculator_project.c
 *
 * Author : Karim Abdou
 */ 

#include "StdTypes.h"
#include "MemMap.h"
#include "DIO_Int.h"
#include "LCD_Int.h"
#include "KEYPAD_Int.h"
#include "CALCULATOR_Int.h"

#define F_CPU 8000000
#include <util/delay.h>

/*******************************/


int main(void)
{
   DIO_Init();
   LCD_Init();
   Calc_Init();
   
   KEYPAD_Init();
   while (1)
   {  
	  Calc_Runnable();
   }
   
}
