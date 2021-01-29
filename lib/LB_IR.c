/*

---------- file information -----------------------------------------------
file name: 
define   : <文件说明>
version  : 见文件尾端
---------------------------------------------------------------------------
*/

//全局变量声明
#define  KAKA_IR_GB

#ifdef   CodeC_Includes
#include "PJ_Includes.h"
#else
//#include "LB_hc89f003_IO.h"
#include "..\include\HC89F0541.h"
#include "..\include\PJ_TypeRedefine.h"
#include "LB_IR.h"
#include "LB_Usart.h"
#include "LB_Run.h"
#endif
code INT8U IRcode[100]={

0xA1,0x84,0x60,    //近中     0
0xA8,0x44,0x60,    //近中     1
0xAA,0x11,0x80,    //远中	  2
0xAA,0x1a,0x00,	   //远left	  3
0xAA,0x86,0x00,	   //远右	  4
0xAA,0xA8,0X00,    //头顶     5
0x18,0x61,0xA0,     //近中 6
0x86,0x11,0x18,     //近中 7	
0x11,0x11,0x11,     //近中 8
0x18,0x61,0x18,     //近left 9	
0x00,0x00,0x00, 
};
void Init_IR()
{


	P1M6 = 0x68;			        	//P16设置为带SMT上拉输入


 	PITS3 |= 0x30;						//INT15	14 13

    PINTE1 |= 0x40;						//使能INT15 14 13

	IE2 |= 0x01;						//打开INT8-17中断
	EA=1;

	Mid_ReadIR.ReadIRFlag=0;
}

void MidIR_Count(void)
{
	if(Mid_ReadIR.ReadIRFlag==1)
	{
		Mid_ReadIR.Nowcount++;
		if(Mid_ReadIR.Nowcount>200)
		{
			Mid_ReadIR.ReadIRFlag=2;
		}
	}
}

void Read_MidIR(void)
{
	Mid_ReadIR.NowVoltage=P1_6;
	if(
	    (Mid_ReadIR.NowVoltage==0)&&(Mid_ReadIR.ReadIRFlag==0)
	)
	{
		Mid_ReadIR.ReadIRFlag=1;
		Mid_ReadIR.Nowcount=0;
		Mid_ReadIR.ReadIRBit=0;
	}
	else if(
	    (Mid_ReadIR.NowVoltage==1)&&(Mid_ReadIR.ReadIRFlag==1)
	)
	{
	   //SBUF=Mid_ReadIR.Nowcount;
		Mid_ReadIR.ReadIRData[Mid_ReadIR.ReadIRBit]=Mid_ReadIR.Nowcount;
		Mid_ReadIR.Nowcount=0;
		Mid_ReadIR.ReadIRBit++;
		if(Mid_ReadIR.ReadIRBit>80)
			Mid_ReadIR.ReadIRFlag=2;

	}
	else if(
	    (Mid_ReadIR.NowVoltage==0)&&(Mid_ReadIR.ReadIRFlag==1)
	)
	{
	   //SBUF=Mid_ReadIR.Nowcount;
		Mid_ReadIR.ReadIRData[Mid_ReadIR.ReadIRBit]=Mid_ReadIR.Nowcount;
		Mid_ReadIR.Nowcount=0;
		Mid_ReadIR.ReadIRBit++;
		if(Mid_ReadIR.ReadIRBit>80)
			Mid_ReadIR.ReadIRFlag=2;
	}
}


void CheckXReadIR(ReadIRByte *P)
{
	INT8U i,k;
	 i=0;
	{
		if(P->ReadIRFlag==2)
		{
			{

				P->ReadIR[0]=0;

				k=0;
				P->ReadIRByte=0;
				for(P->AABit=1; P->AABit<24;)
				{
					if(
					    (P->ReadIRData[P->AABit]>9)&&(P->ReadIRData[P->AABit]<19)
					)
					{
						P->ReadIRByte<<=2;
						//P->ReadIRByte|=1;
						P->AABit+=2;

						k+=2;
						if(k>7)
						{

							P->ReadIR[i]=P->ReadIRByte;
							k=0;
							 i++;
							P->ReadIRByte=0;

						}
					}
					else  if(
					    (P->ReadIRData[P->AABit]>25)&&(P->ReadIRData[P->AABit]<39)
					)
					{
						P->ReadIRByte<<=2;
						P->ReadIRByte|=1;
						P->AABit+=2;

						k+=2;
						if(k>7)
						{

							P->ReadIR[i]=P->ReadIRByte;
							k=0;
							i++;
							P->ReadIRByte=0;

						}
					}
					else  if(
					    (P->ReadIRData[P->AABit]>45)&&(P->ReadIRData[P->AABit]<70)
					)
					{
						P->ReadIRByte<<=2;
						P->ReadIRByte|=2;
						P->AABit+=2;

						k+=2;
						if(k>7)
						{

							P->ReadIR[i]=P->ReadIRByte;
							k=0;
							 i++;
							P->ReadIRByte=0;

						}
					}
					else
					{
						P->AABit+=2;
						P->ReadIRByte<<=2;
						k+=2;
						if(k>7)
						{

							P->ReadIR[i]=P->ReadIRByte;
							k=0;

							P->ReadIRByte=0;
							//P->AABit++;
						}
					}
				}
				for(P->AABit=0; P->AABit<30; P->AABit++)
					P->ReadIRData[P->AABit]=0;
			}

			P->ReadIRFlag=3;
		}
	}
}


void CheckRechargeIR()
{
	INT8U i;
   CheckXReadIR(&Mid_ReadIR);
   /*
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

0xA1,0x84,0x60,    //近中     0
0xA8,0x44,0x60,    //近中     1
0xAA,0x11,0x80,    //远中	  2
0xAA,0x1a,0x00,	   //远left	  3
0xAA,0x86,0x00,	   //远右	  4
0xAA,0xA8,0X00,    //头顶     5
0x18,0x61,0xA0,     //近中 6
0x86,0x11,0x18,     //近中 7	
0x11,0x11,0x11,     //近中 8
0x18,0x61,0x18,     //近left 9	
0x00,0x00,0x00, 



*/
	
	if(Mid_ReadIR.ReadIRFlag==3)
	{

	  for(i=0;i<30;i++)	
	  {
	    if((IRcode[i*3]==Mid_ReadIR.ReadIR[0])&&(IRcode[i*3+1]==Mid_ReadIR.ReadIR[1])&&(IRcode[i*3+2]==Mid_ReadIR.ReadIR[2]))
			{
				break;
			}
	  }

	  switch(i)
	  {
	  


		case 0:
	  	case 1:
	  	case 6:	
	  	case 7:	
	  	case 8:				
			  IRLocation.NearMid++;

		break ;


		case 2:
				IRLocation.FarMid++;
		break;
	  	case 3:
	  	case 9:		
				IRLocation.FarLeft++;
		break;
	  	case 4:
	  
		    IRLocation.FarRight++;

		break;
	 
	  	case 5:
				IRLocation.TopIR++;

		break;

	  	
	  }

	  #if 0
	  Usart1Send[0]=4; 
	  Usart1Send[1]=Mid_ReadIR.ReadIR[0];
	  Usart1Send[2]=Mid_ReadIR.ReadIR[1];
	  Usart1Send[3]=Mid_ReadIR.ReadIR[2];
	  Usart1Send[4]=i;
	  SendCount=1;
	  SBUF=Usart1Send[SendCount];
	  #endif 
		
		if(wallRechargeModeFlag){
			if(i<=20)
				findRechargeFlag = 1;	
		}

// 		    Mid_ReadIR.ReadIR[0]=0;
//		    Mid_ReadIR.ReadIR[1]=0;
//			Mid_ReadIR.ReadIR[2]=0;
			Mid_ReadIR.ReadIRFlag=0;

	}
	return;
}




 void ClearAllIR(void)
 {
   	 IRLocation.NearMid=0;
     IRLocation.FarMid=0;
     IRLocation.FarLeft=0;
	 IRLocation.FarRight=0;
	 IRLocation.TopIR=0;
 }
/***************************************************************************************
  * @说明  	INT8-17中断服务函数
  *	@参数	无
  * @返回值 无
  * @注		无
***************************************************************************************/
void INT8_17_Rpt() interrupt INT8_17_VECTOR 
{
	
	
	if(PINTF1&0x40)						//判断INT14中断标志位
	{
		PINTF1 &=~ 0x40;				//清除INT14中断标志位	
		Read_MidIR();
	}
	


}


