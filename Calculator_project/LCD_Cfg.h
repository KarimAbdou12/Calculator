


#ifndef LCD_CFG_H_
#define LCD_CFG_H_


// for config. mode
#define _4_BIT    5
#define _8_BIT    7 



// config.
/* _4_BIT : _8_BIT */
#define LCD_Mode   _4_BIT

#define RS PINA1
#define EN PINA2

// _8_Bit mode
#define LCD_PORT PC


// _4_Bit mode
#define D7 PINA6
#define D6 PINA5
#define D5 PINA4
#define D4 PINA3



#endif /* LCD_CFG_H_ */