/*

---------- file information -----------------------------------------------
file name: 
define   : <文件说明>
version  : 见文件尾端
---------------------------------------------------------------------------
*/

//全局变量声明
#define  KAKA_AD_GB

#ifdef   CodeC_Includes
#include "PJ_Includes.h"
#else
//#include "LB_hc89f003_IO.h"
#include "..\include\PJ_TypeRedefine.h"
#include "..\lib\LB_Led.h"
#include "LB_AD.h"

#endif
/**
  * @说明  	延时函数
  * @参数  	fui_i : 延时时间
  * @返回值 无
  * @注 	Fcpu = 16MHz,fui_i = 1时,延时时间约为2us
  */
void Delay_2us(unsigned int fui_i)
{
	while(fui_i--);	
}
void InitADIO(void)
{
	P0M0 = 0x02;				        //P25设置为模拟输入
	P0M1 = 0x02;				        //P02设置为模拟输入
	P0M2 = 0x02;				        //P03设置为模拟输入
	P0M4 = 0x02;				        //P04设置为模拟输入
	P0M5 = 0x02;				        //P05设置为模拟输入
	P0M6 = 0x02;				        //P06设置为模拟输入
	P0M7 = 0x02;				        //P07设置为模拟输入
	P2M4 = 0x02;				        //P25设置为模拟输入
	P2M5 = 0x02;				        //P25设置为模拟输入
	P0M3 = 0X80;

   ///*
    P2M0 = 0xC2;                        //P20设置为推挽输出
    P0M3 = 0xC2;                        //P03设置为推挽输出
	PWM2_MAP = 0x03;					//PWM1通道映射P03口
	PWM21_MAP = 0x20;					//PWM1通道映射P03口
    PWM2C = 0x00;						//PWM1高有效，PWM11高有效，时钟8分频 
    PWMM |= 0x40;						//PWM1工作于


	PWM2PH = 0x0;						//周期高4位设置为0x03
	PWM2PL = 0x60;						//周期低8位设置为0xFF



	PWM2DH = 0x00;						//PWM1高4位占空比0x01
	PWM2DL = 0x02;						//PWM1低8位占空比0x55
	PWM2DTH = 0x00;						//PWM1高4位占空比0x01
	PWM2DTL = 0x02;						//PWM1低8位占空比0x55
	PWMEN |= 0x44;						//使能PWM2
   //*/

}

void SeleADChanel(INT8U ADChanel)
{
	ADCC0 = 0x81;						//打开ADC转换电源
	ADCC1 = (ADChanel&0X0F);			//选择外部通道0
	ADCC2 = 0x4f;						//转换结果12位数据，数据右对齐，ADC时钟16分频

}

void StartAD()
{
	ADCC0&=0XDF;
	ADCC0 |= 0x40;					//启动ADC转换
}
void SetADINT(void)
{
    EADC = 1;                                   //使能ADC中断
    EA = 1;
}


void  SetAD(INT8U ADChanel)
{
  code INT8U ADCC[9]={2,1,0,4,5,6,7,12,13};
  SeleADChanel(ADCC[ADChanel]);
  SetADINT();
  StartAD();
}
void ReadAD5ms()
{
  static INT8U i=0;
  static INT8U chanel=0;
  static INT16U ADtemp[5];  
  ADtemp[i]=ADCR;
  i++;
  if(i>2)
  {
     i=0;
	 AD5ms[chanel]=ADtemp[2]; //(ADtemp[1]+ADtemp[2])/2;
	 //AD5ms[5]=0xaa;
	 chanel++;
	 if(chanel>8)
	 {
	   if(ADCtl)
	   { 
		   if(ADFlag)  //调节PMW 占空比 来减少IR干扰   回充 接收发射和接收的 合适点。 
		   {
			 //P0_3 = 1;
			 PWM2DL = 0x8; // 
			 PWM2DTL = 0x8;
			 ADFlag=0;
			 ADFlashFlag=1;
		   }
		  else
		  {
			 //P0_3 = 0; // 
			 PWM2DL = 0x1;
			 PWM2DTL = 0x1;
			 ADFlag=1;
			 ADFlashFlag=1;
		  }
	  }
	  else
	  {
	  	 //P0_3 = 0;
		 PWM2DL = 0;
		 PWM2DTL = 0;
	  }
		//SBUF=(AD5ms[1]>>4);
		//SBUF=AD5ms[2]/16;
	 chanel=0;
	 }
  }
  else
  {
  	 SetAD(chanel);
  }
}
/*
INT8U ReadWallDp(INT8U *p)
{
  INT8U i;
  INT16U temp,tempMin,tempMax;
  temp=0;


  tempMin=*p;
  tempMax=*p;
  for(i=1;i<10;i++)
  {
    
	if(tempMin>*(p+i))
	{
	   tempMin=*(p+i);
	}
	else if(tempMax<*(p+i))
	{
	   tempMax=*(p+i);
	}
	else
	 temp+=*(p+i);
  }
  
  return(temp/8);
}
*/
void CheckWall()
{
 if(ADFlashFlag)
 {
   if(ADFlag)
   {
   	   WallAD[0][0]=(AD5ms[4]>>4);
	   WallAD[1][0]=(AD5ms[3]>>4);
	   WallAD[2][0]=(AD5ms[1]>>4);
 	   WallAD[3][0]=(AD5ms[2]>>4);
	   ADFlashFlag=0;
	 //SBUF=WallAD[0][0];
    if(WallAD[0][1]>WallAD[0][0])
	{
       WallAD100Ms[0][ADTime]=WallAD[0][1]-WallAD[0][0];
	}
	else
       WallAD100Ms[0][ADTime]=WallAD[0][0]-WallAD[0][1];

    if(WallAD[1][1]>WallAD[1][0])
	{
       WallAD100Ms[1][ADTime]=WallAD[1][1]-WallAD[1][0];
	}
	else
	  WallAD100Ms[1][ADTime]=WallAD[1][0]-WallAD[1][1];

    if(WallAD[2][1]>WallAD[2][0])
	{

       WallAD100Ms[2][ADTime]=WallAD[2][1]-WallAD[2][0];
	}
	else
	  WallAD100Ms[2][ADTime]=WallAD[2][0]-WallAD[2][1];

    if(WallAD[3][1]>WallAD[3][0])
	{

       WallAD100Ms[3][ADTime]=WallAD[3][1]-WallAD[3][0];
	}
	else
	  WallAD100Ms[3][ADTime]=WallAD[3][0]-WallAD[3][1];

    LCurrentAD[ADTime]=AD5ms[5];
	RCurrentAD[ADTime]=AD5ms[6];
	FanCurrentAD[ADTime]=AD5ms[7];
	EdgeCurrentAD[ADTime]=AD5ms[8];
	 ADTime++;
   if(ADTime>7)
   {
   	  ADTime=0;
	  WallDp[0]=(WallAD100Ms[0][0]+WallAD100Ms[0][2]+WallAD100Ms[0][4]+WallAD100Ms[0][6])/4;
	  WallDp[1]=(WallAD100Ms[1][0]+WallAD100Ms[1][2]+WallAD100Ms[1][4]+WallAD100Ms[1][6])/4;
	  WallDp[2]=(WallAD100Ms[2][0]+WallAD100Ms[2][2]+WallAD100Ms[2][4]+WallAD100Ms[2][6])/4;
	  WallDp[3]=(WallAD100Ms[3][0]+WallAD100Ms[3][2]+WallAD100Ms[3][4]+WallAD100Ms[3][6])/4;
   }
   //SBUF=AD5ms[6];///16;

	//SBUF=AD5ms[6];  
   }
   else
   {


   	   WallAD[0][1]=(AD5ms[4]>>4);
	   WallAD[1][1]=(AD5ms[3]>>4);
	   WallAD[2][1]=(AD5ms[1]>>4);
 	   WallAD[3][1]=(AD5ms[2]>>4);
	   ADFlashFlag=0;
   }

 }
}
void CheckEdgeCurrent()
{

 //EdgeCurrent=(EdgeCurrent*9+((AD5ms[8])/2))/10;
  EdgeCurrent=(EdgeCurrentAD[0]+EdgeCurrentAD[2]+EdgeCurrentAD[4]+EdgeCurrentAD[6])/4;
 //EdgeCurrent=0xaabb;
 if(EdgeCurrent>0x80)
 EdgeCurrentCount++;
 else 
 {
   if(EdgeCurrentCount>1)
     EdgeCurrentCount--;
 }
}

void CheckFanCurrent()
{

 FanCurrent=(FanCurrentAD[0]+FanCurrentAD[1]+FanCurrentAD[2]+FanCurrentAD[3]+FanCurrentAD[4]+FanCurrentAD[5]+FanCurrentAD[6]+FanCurrentAD[7])/64;
 //FanCurrent=0xaabb;
// FanCurrentCount++;

}

void CheckLCurrent()
{
 //INT16U	LCurrentADAvg;
 LCurrent=(LCurrentAD[0]+LCurrentAD[2]+LCurrentAD[4]+LCurrentAD[6])/4;
 //SBUF= (INT8U)LCurrentADAvg;
 //LCurrent=(LCurrent*9+(LCurrentADAvg*9)/2)/10;

}
void CheckRCurrent()
{
// INT16U	RCurrentADAvg;
 RCurrent=(RCurrentAD[0]+RCurrentAD[2]+RCurrentAD[4]+RCurrentAD[6])/4;

 //RCurrent=(RCurrent*9+(RCurrentADAvg*11)/2)/10;
 //RCurrent=(RCurrent*9+(RCurrentADAvg*9)/2)/10;
 //4000*100/4096/22
 
}

void CheckVoltage()
{
   //Voltage=(Voltage*9+((AD5ms[0])/25)*6)/10;
   Voltage=(Voltage*9+(AD5ms[0]/4))/10;
   //4000*3/40960
}

/***************************************************************************************
  * @说明  	ADC中断服务函数
  *	@参数	无
  * @返回值 无
  * @注		无
***************************************************************************************/
void ADC_Rpt() interrupt ADC_VECTOR
{

    IE1 &=~ 0x40;                       //关闭ADC中断
    ADCC0 &=~ 0x20;						//清除ADC中断标志位

} 