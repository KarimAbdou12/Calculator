

#ifndef STDTYPES_H_
#define STDTYPES_H_


typedef unsigned char  u8;
typedef signed char  s8;

typedef unsigned int u16;
typedef signed int s16;

typedef unsigned long u32;
typedef signed long  s32;

#define NULLPTR  ((void*)0)

typedef enum{
	FALSE,
	TRUE
}bool_t;

typedef enum{
	OK,
	NOK,
	NULL_PTR,
	OUT_OF_RANGE
}error_t;

#define MAX_U8   ((u8)255)
#define MIN_U8   ((u8)0)

#define MAX_S8   ((s8)127)
#define MIN_S8   ((s8)-128)
#define ZERO_S8   ((s8)0)


#define  SET_BIT(reg,bit)  (reg|=(1<<bit))
#define  CLR_BIT(reg,bit)  (reg&=~(1<<bit))
#define  TOG_BIT(reg,bit)  (reg^=(1<<bit))
#define  READ_BIT(reg,bit)  ((reg>>bit)&1)



#endif /* STDTYPES_H_ */