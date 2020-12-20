/*

---------- file information -----------------------------------------------
file name: 
define   : <文件说明>
version  : 见文件尾端
---------------------------------------------------------------------------
*/
#ifndef  LB_IR_h
#define  LB_IR_h



#ifdef   CodeC_Includes
#include "PJ_Includes.h"
#else

#include "..\include\PJ_TypeRedefine.h"


#endif


//全局变量声明
#ifdef  KAKA_IR_GB
#define KAKA_IR_EXT
#else
#define  KAKA_IR_EXT extern
#endif

 typedef struct
{
	INT8U  NowVoltage;
	INT8U  Nowcount;
	INT8U  ReadIRBit;
	INT8U  ReadIRFlag;
	INT8U  ReadIRByte;
	INT8U  AABit;
	INT8U  ReadIR[4];
	INT8U  ReadIRData[100];
} ReadIRByte ;

 typedef struct
{
	INT8U  NearMid;
	INT8U  NearPreLeft;
	INT8U  NearPreRight;
	INT8U  NearLeft;
	INT8U  NearRight;
	INT8U  FarMid;
	INT8U  FarLeft;
	INT8U  FarRight;
	INT8U  FarPreLeft;
	INT8U  FarPreRight;
	INT8U  CloseList[3];
} IRLocationByte;


KAKA_IR_EXT	 xdata ReadIRByte Mid_ReadIR;
KAKA_IR_EXT	 xdata IRLocationByte IRLocation;

KAKA_IR_EXT void Init_IR();

KAKA_IR_EXT void MidIR_Count(void);
KAKA_IR_EXT void CheckHandsetIR();
KAKA_IR_EXT void CheckRechargeIR();
KAKA_IR_EXT void ClearAllIR();
#endif