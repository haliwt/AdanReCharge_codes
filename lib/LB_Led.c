/*

---------- file information -----------------------------------------------
file name: 
define   : <文件说明>
version  : 见文件尾端
---------------------------------------------------------------------------
*/

//全局变量声明
#define  KAKA_Led_GB

#ifdef   CodeC_Includes
#include "PJ_Includes.h"
#else
//#include "LB_hc89f003_IO.h"
#include "..\include\HC89F0541.h"
#include "..\include\PJ_TypeRedefine.h"
#include "LB_Led.h"

#endif

void InitT1(void)
{
	TCON1 = 0x00;						//T1定时器时钟为Fosc
	TMOD = 0x00;						//16位重装载定时器/计数器

	//Tim1计算时间 	= (65536 - 0xFACB) * (1 / (Fosc /Timer分频系数))
	//				= 1333 / (16000000 / 12)
	//				= 1 ms

	//定时0.1ms
	//反推初值 	= 65536 - ((1/10000) / (1/(Fosc / Timer分频系数)))
	//		   	= 65536 - ((1/10000) / (1/(16000000 / 12)))
	//			= 65536 - 133
	//			= 0xFf78
	TH1 = 0xFf;
	TL1 = 0x78;
	IE |= 0x08;							//打开T1中断
	TCON |= 0x40;						//使能T1
    
	EA = 1;	

}

void InitLed(void)
{
  P3M3=0X84;
  P3_3=1;
   P2M3=0X84;
  P2_3=1;
}



void LedRedON()
{
  P3_3=0;
}


void LedRedOff()
{
  P3_3=1;
}

void LedGreenON()
{
  P2_3=0;
}


void LedGreenOff()
{
  P2_3=1;
}
void InitKey(void)
{
  P3M4 = 0x60;                        //P00设置为施密特数字带上拉输入
  P3_4=1;
  P3M5 = 0x60;                        //P00设置为施密特数字带上拉输入
  P3_5=1;

}

void InitIMP(void)
{
  P3M2 = 0x50;                        
  P3_2=1;
  P1M5 = 0x50;                        
  P1_5=1;
  IMP=0;
}

void ReadIMP(void)
{
  if(P3_2)
	IMP|=1;
  else
	IMP&=0xfe;
  if(P1_5)
	IMP|=2;
  else
	IMP&=0xfd;
}
INT8U ReadKey(void)
{

  static INT16U  K1=0;
  static INT16U  K2=0;
  INT8U	 tmp;
  if(P3_4==0)
  {
    // LedBlueON();
    if(K1<200)
   	 K1++;
  }
  else	
  {	  
    //LedRedOff();
   	K1=0;
  }

   if(P3_5==0)
  {
    // LedBlueON();
    if(K2<200)
   	 K2++;
  }
  else	
  {	  
    //LedRedOff();
   	K2=0;
  }
  tmp=0;
  if(K1>190)
  {
    //
    K1=201;
	//LedBlueON();
    tmp|=1;;

  }
  if(K2>190)
  {
    //
    K2=201;
	//LedBlueON();
    tmp|=2;;

  }
  return (tmp);
}
void InitPowerIn(void)
{
  P1M0 = 0x50;                        //P10设置为施密特数字带上拉输入
  P2M1 = 0x50;                        //P32设置为施密特数字带上拉输入
  P1_0=1;
  P2_1=1;
}
INT8U ReadPowerAutoIn(void)
{
  return(P2_1);
}

 INT8U ReadPowerDCIn(void)
{
  return(P1_0);
}
void InitBuzzer(void)
{

    P2M2 = 0xC2;                        //P35设置为推挽输出
	PWM3_MAP = 0x22;					//PWM3映射P35口
	//周期计算 	= 0xFF / (Fosc / PWM分频系数)		（Fosc见系统时钟配置的部分）
	//			= 0xFF /(16000000 / 4)			
	// 			= 255 /4000000
	//			= 63.75us		即15.69KHZ		

	PWM3P = 0xc4;						//PWM周期为0xFF
	//有效电平时间计算（即占空比） 	
	//			= 0x55 / (Fosc / PWM分频系数)		（Fosc见系统时钟配置的部分）
	//			= 0x55 /(16000000 / 4)			
	// 			= 85 /4000000
	//			= 21.25us		占空比为 21.25 / 63.75 = 34%

	PWM3D = 0x30;						//PWM占空比设置
	PWM3C = 0x06; 						//使能PWM3，关闭中断，允许输出，时钟32分频	


//  P2M2 = 0x84;                        //P01设置为施密特数字带上拉输入
//  P2_2=0;

}
void BuzzerON()
{
 // BuzzerFlag=1;
  SetBuzzerTime(4);
//  PWM3C = 0x96; 						//使能PWM3，关闭中断，允许输出，时钟32分频
//  P2_2=0;
}


void BuzzerOff()
{
 // BuzzerFlag=0;
//  PWM3C = 0x06; 						//使能PWM3，关闭中断，允许输出，时钟32分频
//  P2_2=1;
}

void SetBuzzerTime(INT8U time)
{
	BuzzerTime=time;
	
	PWM3C = 0x96; 						//使能PWM3，关闭中断，允许输出，时钟32分频	
}

void CheckBuzzer()
{
   if(BuzzerTime<200)
   {
     
     BuzzerTime--;

	 if(BuzzerTime<1)
	 {
	   PWM3C = 0x06; 						//使能PWM3，关闭中断，允许输出，时钟32分频	
	 }
   }
}