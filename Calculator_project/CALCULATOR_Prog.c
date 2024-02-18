

#include "StdTypes.h"
#include "LCD_Int.h"
#include "KEYPAD_Int.h"

static s32 Complete_Operation (s32 result)
{
	LCD_Clear();
	LCD_SetCursor(1,1);
	LCD_WriteNumber(result);
	return result;
}

static u8 Store_operations (s32* arr,u8 operation,u8 ind,u32 num)
{
	arr[ind]=num;
	ind++;
	arr[ind]=operation;
	ind++;
	
	return ind;
}

static void shift_data (s32* DataArr,u8 ind)
{
	while(DataArr[ind+2] != '=' )
	{
		DataArr[ind]=DataArr[ind+2];
		ind++;
	}
	DataArr[ind]=DataArr[ind+2];
	return;
}

static u32 Calc_Result (s32* DataArr,u8 ind,u8 flag_prod_div,u8 flag_add_sub)
{
	s8 i=0;
	s32 result=0;
	while(DataArr[i]!='=' && flag_prod_div!=0 )
	{
		if(DataArr[i]=='*')
		{
			DataArr[i-1]=DataArr[i-1]*DataArr[i+1];
			shift_data(DataArr,i);
			flag_prod_div--;
			i--;
		}
		else if(DataArr[i]=='/')
		{
			DataArr[i-1]=DataArr[i-1]/DataArr[i+1];
			shift_data(DataArr,i);
			flag_prod_div--;
			i--;
		}
		i++;
	}
	i=0;
	while(DataArr[i]!='=' && flag_add_sub!=0)
	{
		if(DataArr[i]=='+')
		{
			DataArr[i-1]=DataArr[i-1]+DataArr[i+1];
			shift_data(DataArr,i);
			flag_add_sub--;
			i--;
		}
		else if(DataArr[i]=='-')
		{
			DataArr[i-1]=DataArr[i-1]-DataArr[i+1];
			shift_data(DataArr,i);
			flag_add_sub--;
			i--;
		}
		i++;
	}
	result=DataArr[0];
	
	for(i=0;i<ind;i++)
	{
		DataArr[i]=0;
	}
	
	return result;
}

void Calc_Init (void)
{
	Welcome();
	LCD_SetCursor(1,1);
}

void Calc_Runnable (void)
{
	
	static  u8 k,flag_prod_div=0,flag_add_sub=0,flag_comp=0xAA;
	static  s32 num=0,result;
	static  u8 flag_start=0,ind=0;
	static  s32 arr[17];
	
		k=KEYPAD_GetKey();
		if (k!=NO_KEY)
		{
			if(k>='0'&&k<='9')
			{
				if (flag_start==0)
				{
					LCD_Clear();
					LCD_SetCursor(1,1);
					flag_start=1;
				}
				num=num*10+k-'0';
				LCD_WriteChar(k);
				flag_comp=0xAA;
			}
			switch (k)
			{
				case '*' :
				if(0x55==flag_comp)
				{
					num=Complete_Operation(result);
					flag_start=1;
				}
				LCD_WriteChar(k);
				ind=Store_operations(arr,'*',ind,num);
				flag_prod_div++;
				num=0;
				break;
				
				case '/' :
				if(0x55==flag_comp)
				{
					num=Complete_Operation(result);
					flag_start=1;
				}
				LCD_WriteChar(k);
				ind=Store_operations(arr,'/',ind,num);
				flag_prod_div++;
				num=0;
				break;
				
				case '+' :
				if(0x55==flag_comp)
				{
					num=Complete_Operation(result);
					flag_start=1;
				}
				LCD_WriteChar(k);
				ind=Store_operations(arr,'+',ind,num);
				flag_add_sub++;
				num=0;
				break;
				
				case '-' :
				if(0x55==flag_comp)
				{
					num=Complete_Operation(result);
					flag_start=1;
				}
				LCD_WriteChar(k);
				ind=Store_operations(arr,'-',ind,num);
				flag_add_sub++;
				num=0;
				break;
				
				case '=' :
				ind=Store_operations(arr,'=',ind,num);
				num=0;
				
				result=Calc_Result(arr,ind,flag_prod_div,flag_add_sub);
				
				LCD_SetCursor(2,1);
				LCD_WriteNumber(result);
				
				for(;ind!=0;ind--)
				{
					arr[ind]=0;
				}
				ind=0;
				flag_add_sub=0;
				flag_prod_div=0;
				flag_start=0;
				flag_comp=0x55;
				break;
				
				case 'c' :
				LCD_Clear();
				
				flag_add_sub=0;
				flag_prod_div=0;
				flag_start=0;
				flag_comp=0xAA;
				result=0;
				num=0;
				
				for(s8 j=0;j<ind;j++)
				{
					arr[j]=0;
				}
				ind=0;
				break;
			}
			
		}
		
}