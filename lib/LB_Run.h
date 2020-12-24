/*

---------- file information -----------------------------------------------
file name: 
define   : <�ļ�˵��>
version  : ���ļ�β��
---------------------------------------------------------------------------
*/
#ifndef  LB_Run_h
#define  LB_Run_h



#ifdef   CodeC_Includes
#include "PJ_Includes.h"
#else

#include "..\include\PJ_TypeRedefine.h"
#include "..\include\HC89F0541.h"

#endif


//ȫ�ֱ�������
#ifdef  KAKA_Run_GB
#define KAKA_Run_EXT
#else
#define  KAKA_Run_EXT extern
#endif
#define  WallMin 50

KAKA_Run_EXT   INT8U Mode;
KAKA_Run_EXT  INT8U Step;
KAKA_Run_EXT  INT8U RunMode;
KAKA_Run_EXT  INT8U RunStep;
KAKA_Run_EXT  INT8U RunNoIRsenorTime;
KAKA_Run_EXT  INT8U RunNoIRsenorLastStep;
KAKA_Run_EXT  INT8U BatteryRechargeFlag;
KAKA_Run_EXT  INT16U RunMs;
KAKA_Run_EXT  INT8U  EdgeTime;
KAKA_Run_EXT  INT16U twinkle;
KAKA_Run_EXT  INT16U Imp2Time;

KAKA_Run_EXT  INT16U ImpSecond;
KAKA_Run_EXT  INT16U Imp2Second;

KAKA_Run_EXT  INT8U  CurrentMax;
KAKA_Run_EXT  INT16U WallSecond;
KAKA_Run_EXT  INT16U NoImpSecond;
KAKA_Run_EXT  INT16U SysSecond;
KAKA_Run_EXT  INT8U Run100MSecond;
KAKA_Run_EXT  INT8U MidWallOffSecond;
KAKA_Run_EXT  idata INT16U RunSecond;
KAKA_Run_EXT  void  CheckRun();
KAKA_Run_EXT  INT8U  LowVoltageFlag;
KAKA_Run_EXT  void CheckMode(INT8U Key);
KAKA_Run_EXT  void InitSysclk(INT8U SYS);
KAKA_Run_EXT  void Delay_ms(INT16U fui_i);
KAKA_Run_EXT  void Auto_ReChargeBattery(void);
KAKA_Run_EXT   void CleanMode_BOW(void);
KAKA_Run_EXT   void CleanMode_Random(void);

//vic 2020.12.23 add
#define  WallModeMin 10
#define  WallModeNormal 80
#define  WallModeMax	150	
KAKA_Run_EXT void circleMode(void);
KAKA_Run_EXT void wallMode(void);
#endif