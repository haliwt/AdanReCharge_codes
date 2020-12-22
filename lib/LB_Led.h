/*

---------- file information -----------------------------------------------
file name: 
define   : <�ļ�˵��>
version  : ���ļ�β��
---------------------------------------------------------------------------
*/
#ifndef  LB_Led_h
#define  LB_Led_h



#ifdef   CodeC_Includes
#include "PJ_Includes.h"
#else

#include "..\include\PJ_TypeRedefine.h"


#endif


//ȫ�ֱ�������
#ifdef  KAKA_Led_GB
#define KAKA_Led_EXT
#else
#define  KAKA_Led_EXT extern
#endif


#define BatterCharge    		P2_1 
#define CloseSwitch_L  			P1_5	
#define CloseSwitch_R  			P3_2

#define Power_Key             P3_4
#define Cleaning_Key          P3_5
#define POWER_PRES             1
#define CLEANING_PRES          2 
#define GROUP_PRES            3     

KAKA_Led_EXT  INT8U BuzzerTime;
KAKA_Led_EXT  INT8U IMP;
KAKA_Led_EXT  void InitLed(void);

KAKA_Led_EXT  void LedRedOff();
KAKA_Led_EXT  void LedRedON();
KAKA_Led_EXT  void LedGreenON() ;
KAKA_Led_EXT  void LedGreenOff();
KAKA_Led_EXT void InitT1(void);
KAKA_Led_EXT void InitKey(void);
KAKA_Led_EXT INT8U ReadKey(void);
KAKA_Led_EXT void InitIMP(void);
KAKA_Led_EXT void ReadIMP(void);
KAKA_Led_EXT void InitPowerIn(void);
KAKA_Led_EXT INT8U ReadPowerAutoIn(void);
KAKA_Led_EXT INT8U ReadPowerDCIn(void);
KAKA_Led_EXT void InitBuzzer(void);
KAKA_Led_EXT void BuzzerON()	;
KAKA_Led_EXT void BuzzerOff() ;
KAKA_Led_EXT void SetBuzzerTime(INT8U time);
KAKA_Led_EXT void CheckBuzzer();
KAKA_Led_EXT INT8U HDKey_Scan(INT8U mode);//WT.EDIT 2020.12.22
#endif