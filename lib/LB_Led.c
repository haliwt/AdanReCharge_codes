/*

---------- file information -----------------------------------------------
file name: 
define   : <�ļ�˵��>
version  : ���ļ�β��
---------------------------------------------------------------------------
*/

//ȫ�ֱ�������
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
	TCON1 = 0x00;						//T1��ʱ��ʱ��ΪFosc
	TMOD = 0x00;						//16λ��װ�ض�ʱ��/������

	//Tim1����ʱ�� 	= (65536 - 0xFACB) * (1 / (Fosc /Timer��Ƶϵ��))
	//				= 1333 / (16000000 / 12)
	//				= 1 ms

	//��ʱ0.1ms
	//���Ƴ�ֵ 	= 65536 - ((1/10000) / (1/(Fosc / Timer��Ƶϵ��)))
	//		   	= 65536 - ((1/10000) / (1/(16000000 / 12)))
	//			= 65536 - 133
	//			= 0xFf78
	TH1 = 0xFf;
	TL1 = 0x78;
	IE |= 0x08;							//��T1�ж�
	TCON |= 0x40;						//ʹ��T1
    
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
  P3M4 = 0x60;                        //P00����Ϊʩ�������ִ���������
  P3_4=1;
  P3M5 = 0x60;                        //P00����Ϊʩ�������ִ���������
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
     P2M1 = 0X58 ; //ReCharge input SMT pull down
     P1M0 = 0x58;  //DC INPUT pull down 
     P2_1 =1; 
	 P1_0 =1;
}

/***********************************************************
 *  *
    *Function Name: INT8U ReadPowerAutoIn(void)
    *Function: ReCharge battery be detected
    *Input Ref: NO
    *Return Ref: 1 -battery recharge   0-no recharge
    * 
***********************************************************/
INT8U ReadPowerAutoIn(void)
{
  return(P2_1);
}
/***********************************************************
 *  *
    *Function Name: ReadPowerDCIn(void)
    *Function: DC adapte input be dected 
    *Input Ref: NO
    *Return Ref: 1 -DC 5V    0-No DC 5V 
    * 
***********************************************************/
 INT8U ReadPowerDCIn(void)
{
  return(P1_0);
}
/***********************************************************
 *  *
    *Function Name: INT8U ReadPowerAutoIn(void)
    *Function: ReCharge battery be detected
    *Input Ref: NO
    *Return Ref: 1 -battery recharge   0-no recharge
    * 
***********************************************************/
void InitBuzzer(void)
{

    P2M2 = 0xC2;                        //P35����Ϊ�������
	PWM3_MAP = 0x22;					//PWM3ӳ��P35��
	//���ڼ��� 	= 0xFF / (Fosc / PWM��Ƶϵ��)		��Fosc��ϵͳʱ�����õĲ��֣�
	//			= 0xFF /(16000000 / 4)			
	// 			= 255 /4000000
	//			= 63.75us		��15.69KHZ		

	PWM3P = 0xc4;						//PWM����Ϊ0xFF
	//��Ч��ƽʱ����㣨��ռ�ձȣ� 	
	//			= 0x55 / (Fosc / PWM��Ƶϵ��)		��Fosc��ϵͳʱ�����õĲ��֣�
	//			= 0x55 /(16000000 / 4)			
	// 			= 85 /4000000
	//			= 21.25us		ռ�ձ�Ϊ 21.25 / 63.75 = 34%

	PWM3D = 0x30;						//PWMռ�ձ�����
	PWM3C = 0x06; 						//ʹ��PWM3���ر��жϣ����������ʱ��32��Ƶ	


//  P2M2 = 0x84;                        //P01����Ϊʩ�������ִ���������
//  P2_2=0;

}
void BuzzerON()
{
 // BuzzerFlag=1;
  SetBuzzerTime(4);
//  PWM3C = 0x96; 						//ʹ��PWM3���ر��жϣ����������ʱ��32��Ƶ
//  P2_2=0;
}


void BuzzerOff()
{
 // BuzzerFlag=0;
//  PWM3C = 0x06; 						//ʹ��PWM3���ر��жϣ����������ʱ��32��Ƶ
//  P2_2=1;
}

void SetBuzzerTime(INT8U time)
{
	BuzzerTime=time;
	
	PWM3C = 0x96; 						//ʹ��PWM3���ر��жϣ����������ʱ��32��Ƶ	
}

void CheckBuzzer()
{
   if(BuzzerTime<200)
   {
     
     BuzzerTime--;

	 if(BuzzerTime<1)
	 {
	   PWM3C = 0x06; 						//ʹ��PWM3���ر��жϣ����������ʱ��32��Ƶ	
	 }
   }
}
