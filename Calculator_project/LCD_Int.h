

#ifndef LCD_INT_H_
#define LCD_INT_H_


void LCD_Init(void);
void WriteData(u8 data);
void LCD_WriteChar(u8 ch);
void LCD_WriteNumber(s32 num);
void LCD_CustomChar(u8 location,u8*pattern);
void LCD_WriteString(char*str);
void LCD_SetCursor(u8 line,u8 cell);
void LCD_Clear(void);
void Welcome (void);



#endif /* LCD_INT_H_ */