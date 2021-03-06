/**
*   ************************************************************************************
*								上海芯圣电子股份有限公司
*								    www.holychip.cn
*	************************************************************************************
*	@Examle Version		V1.0.0.0
*	@Demo Version		V1.0.1.0
*	@Date				2017.09.18
*	************************************************************************************
*									 模块性能介绍
*	1、输入（无SMT）模式下VDD=5V时，低电平即输入低电压（VIL1）范围为0~1.5V、高电平即输入
*	   高电压（VIH1）范围为3.5~5V。
*	2、输入（SMT）模式下VDD=5V时，低电平即输入低电压（VIL1）范围为0~1V、高电平即输入高电
*	   压（VIH1）范围为4~5V。
*	3、P0xDBCT [5:0]配置的消抖时间是一个范围，分频系数*Tosc*P0xDBCT[5:0]-Tosc<消抖时间<
*	   分频系数*Tosc*(P0xDBCT[5:0]+1)-Tosc。
	4、HC89F003上电复位以及其它复位功能的复位，所有的IO相关寄存器都会恢复为默认值。
*	************************************************************************************
*									 应用注意事项
*	1、在使用仿真器时，与JTAG复用的IO口会有读取或写入数据异常，因此建议使用仿真器时不要
*	   操作这几个IO口。断开仿真器使用电源供电即可以正常操作。
*	2、分配到P0.0/P0.1/P0.2这三个管脚上的功能脚、外部中断输入、故障检测引脚都受消抖控制。
*   3、HC89F003自B版及其以后版本，IO口P23、P24、P25、P27口增加了上下拉输入同时使能的功能，
       但是不可以使用带上拉输入以及带下拉输入，但是可以使用带施密特上拉输入以及带施密特
       下拉输入，具体详见DateSheet。（关于芯片版本问题可以询问代理商以及原厂业务）
*	************************************************************************************
*  								       客户服务
*	感谢您使用我们的单片机，若发现错误或对函数的使用存在疑问。请添加上海芯圣电子官方QQ群
*	****************************技术支持群：201030494***********************************
*   ************************************************************************************
**/
#define	ALLOCATE_EXTERN
#define	ver 5

#include "HC89F0541.h"

#include "..\lib\LB_Led.h"
#include "..\lib\LB_AD.h"
#include "..\lib\LB_Usart.h"
#include "..\lib\LB_eeprom.h"
#include "..\lib\LB_Motor.h"
#include "..\lib\LB_IR.h"
#include "..\lib\LB_Run.h"

void InitSysclk(INT8U SYS)
{

	/************************************系统初始化****************************************/
	WDTCCR = 0x00;						//关闭看门狗

	while((CLKCON&0x20)!=0x20);			//等待内部高频晶振起振
	CLKSWR = 0x51;						//选择内部高频时钟为主时钟，内部高频RC2分频，Fosc=16MHz
	while((CLKSWR&0xC0)!=0x40);			//等待内部高频切换完成
	CLKDIV = SYS;						//Fosc1分频得到Fcpu，Fcpu=16MHz
}



/***************************************************************************************
  * @实现效果	将P02端口的上拉电阻设置为100K
***************************************************************************************/
void main(void)
{
	INT8U kk;
	
	InitSysclk(1);

	InitT1();
	InitADIO();
    InitMotorIO();
	Init_Usart1();
	//InitMotorForward();
	InitFanEdgeIO();
	InitLed();
	InitKey();
	InitPowerIn();
	Init_IR();
	InitBuzzer();
	InitIMP();
	ADCtl=0;   //强检信号 IR 发射标志 0--关闭， 1 --打开
	LedRedON();
	Mode=2;
	Step=0;
	RunMode=1;
	RunStep=0;
	RCurrentMax=150;
	LCurrentMax=150;
	LCurrent=0;
	RCurrent=0;
	SetBuzzerTime(10);
	//InitMotorForwardRightSlow();
	//SetFan(0xa0);
	//SetEdge(0xFA);
	while(1)
	{
	  
		//InitMotorForwardRight();//直线运行
		//InitMotorForwardRightSlow();
		//InitMotorRight(); //CW
		//InitMotorLeft();  //CCW
		
		#if 1
		if(P2_1 ==1|| P1_0 ==1){//回充和电源适配器DC输入检测，没有用中??
	      SetStop();
		 LedGreenON();
		 Delay_ms(500);
		 LedGreenOff();
		 Delay_ms(500);
	  
	  }
      else{
	//kk=ReadKey();
	   //CheckWall();
		   
		   CheckRechargeIR();
	       CheckRun();
		  CheckMode(kk);
      }
	  #endif 

	}

}



void TIMER1_Rpt(void) interrupt TIMER1_VECTOR
{
  static INT8U t_10ms;
  static INT8U t_100ms;
  static INT8U t_1s;
  //IRTime++;
  t_10ms++;  //0.1ms 
  ReadAD5ms();

  MidIR_Count();

  if(t_10ms>99) //10ms
  {
  	t_10ms=0;
	t_100ms++;
	t_1s++;
	RunMs++;
	CheckBuzzer();
	SetMotorForwardPWMUP();
	if(t_100ms>9)
	{

	  t_100ms=0;
	  Run100MSecond++;
			 RunSecond++;
			 ImpSecond++;
			 Imp2Second++;
			 NoImpSecond++;
			 SysSecond++;
			 WallSecond++;
	  ReadIMP();
	  CheckLCurrent();
	  CheckRCurrent();
	  CheckEdgeCurrent();
	  CheckFanCurrent();
	}
	CheckVoltage();
	if(t_1s>99)
	{
	  t_1s=0;
	  MidWallOffSecond++;
      #if 0
	  if(SendCount>=12)
	  {
//	  Usart1Send[0]=12;
//	  Usart1Send[1]=IRLocation.NearMid;
//	  Usart1Send[2]=IRLocation.NearPreRight;
//	  Usart1Send[3]=IRLocation.NearPreLeft;
//	  Usart1Send[4]=IRLocation.NearRight;
//	  Usart1Send[5]=IRLocation.NearLeft;
//	  Usart1Send[6]=IRLocation.FarMid;
//	  Usart1Send[7]=IRLocation.FarPreRight;
//	  Usart1Send[8]=IRLocation.FarPreLeft;
//	  Usart1Send[9]=IRLocation.FarRight;
//	  Usart1Send[10]=IRLocation.FarLeft;
//	  Usart1Send[11]=IMP;
//	  Usart1Send[12]=RunStep;
 	  SendCount=1;
	  SBUF=Usart1Send[SendCount];
	   }
	  #endif 
	  /*
	  Usart1Send[0]=12;
	  Usart1Send[1]=Voltage/100;
	  Usart1Send[2]=Voltage%100;
	  Usart1Send[3]=WallDp[0];
	  Usart1Send[4]=WallDp[1];
	  Usart1Send[5]=WallDp[2];
	  Usart1Send[6]=WallDp[3];
	  Usart1Send[7]=LCurrent;
	  Usart1Send[8]=RCurrent;
	  Usart1Send[9]=EdgeCurrent;
	  Usart1Send[10]=FanCurrent;
	  Usart1Send[11]=IMP;
	  Usart1Send[12]=RunStep;
	  SendCount=1;
	  SBUF=Usart1Send[SendCount];
	  */
	  /*
	  Usart1Send[0]=13;
	  Usart1Send[1]=LeftIR.Left;
	  Usart1Send[2]=LeftIR.Right;
	  Usart1Send[3]=LeftIR.Mid;
	  Usart1Send[4]=LeftIR.Top;

	  Usart1Send[5]=MidIR.Left;
	  Usart1Send[6]=MidIR.Right;
	  Usart1Send[7]=MidIR.Mid;
	  Usart1Send[8]=MidIR.Top;

	  Usart1Send[9]=RightIR.Left;
	  Usart1Send[10]=RightIR.Right;
	  Usart1Send[11]=RightIR.Mid;
	  Usart1Send[12]=RightIR.Top;

	  Usart1Send[13]=RunStep;
	  SendCount=1;
	  SBUF=Usart1Send[SendCount];
  	  */
	  //SBUF=Usart1Send[SendCount];	
	}
  }
}
void WDT_Rpt() interrupt WDT_VECTOR
{
	WDTC &=~ 0x20;						//清除WDT中断标志位
}
