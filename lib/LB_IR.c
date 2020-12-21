/*

---------- file information -----------------------------------------------
file name: 
define   : <�ļ�˵��>
version  : ���ļ�β��
---------------------------------------------------------------------------
*/

//ȫ�ֱ�������
#define  KAKA_IR_GB

#ifdef   CodeC_Includes
#include "PJ_Includes.h"
#else
//#include "LB_hc89f003_IO.h"
#include "..\include\HC89F0541.h"
#include "..\include\PJ_TypeRedefine.h"
#include "LB_IR.h"
#include "LB_Usart.h"
#endif
code INT8U IRcode[100]={

0x18,0x61,0xa0,	  //����        0
0x18,0x61,0x18,	  //��ƫ��		1
0x44,0x44,0x00,	  //��ƫ��		2
0x18,0x61,0x18,	  //��ƫ��		3
0x11,0x11,0x11,	  //����		4
0x86,0x11,0x18,	  //��ƫ��		5
0x86,0x15,0x18,	  //��ƫ��	    6
0x86,0x46,0x00,	  //��ƫ��		7
0xa8,0x61,0x80,	  //����	    8 
0xa8,0x60,0x80,	  //����		9

0xaa,0x1a,0x00,	  //Զ��		10
0xa1,0x86,0x80,   //Զ��		11
0x18,0x61,0xa0,	  //Զƫ��		12
0x18,0x41,0x11,	  //Զ��		13
0x18,0x44,0x46,   //Զ��	 	14
0xA1,0x11,0x18,   //Զ��		15
0x86,0x18,0x60,	  //Զƫ��		16
0xa8,0x61,0x80,	  //Զ��		17
0x61,0x80,0x00,   //Զ��		18
0xaa,0x86,0x00,	  //Զ��		19

0x00,0x00,0x00, 
};
void Init_IR()
{


	P1M6 = 0x68;			        	//P16����Ϊ��SMT��������


 	PITS3 |= 0x30;						//INT15	14 13

    PINTE1 |= 0x40;						//ʹ��INT15 14 13

	IE2 |= 0x01;						//��INT8-17�ж�
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

0x18,0x61,0xa0,	  //����        0
0x18,0x61,0x18,	  //��ƫ��		1
0x44,0x44,0x00,	  //��ƫ��		2
0x18,0x61,0x18,	  //��ƫ��		3
0x11,0x11,0x11,	  //����		4
0x86,0x11,0x18,	  //��ƫ��		5
0x86,0x15,0x18,	  //��ƫ��	    6
0x86,0x46,0x00,	  //��ƫ��		7
0xa8,0x61,0x80,	  //����	    8 
0xa8,0x60,0x80,	  //����		9

0xaa,0x1a,0x00,	  //Զ��		10
0xa1,0x86,0x80,   //Զ��		11
0x18,0x61,0xa0,	  //Զƫ��		12
0x18,0x41,0x11,	  //Զ��		13
0x18,0x44,0x46,   //Զ��	 	14
0xA1,0x11,0x18,   //Զ��		15
0x86,0x18,0x60,	  //Զƫ��		16
0xa8,0x61,0x80,	  //Զ��		17
0x61,0x80,0x00,   //Զ��		18
0xaa,0x86,0x00,	  //Զ��		19


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
		IRLocation.NearLeft++;

		break;
	  	case 1:
	  	case 2:
	  	case 3:
		IRLocation.NearPreLeft++;

		break;
	  	case 4:
		IRLocation.NearMid++;

		break;
	  	case 5:
	  	case 6:
	  	case 7:
		IRLocation.NearPreRight++;

		break;
	  	case 8:
	  	case 9:
		IRLocation.NearRight++;

		break;

	  	case 10:
	  	case 11:
		IRLocation.FarLeft++;

		break;		

	  	case 12:
		IRLocation.FarPreLeft++;
 		break;
	  	case 13:
	  	case 14:
	  	case 15:
		IRLocation.FarMid++;
		break;
	  	case 16:
		IRLocation.FarPreRight++;
		break;
 	  	case 17:
	  	case 18:
	  	case 19:
		IRLocation.FarPreRight++;
	  }

	  #if 1
	  Usart1Send[0]=4;
	  Usart1Send[1]=Mid_ReadIR.ReadIR[0];
	  Usart1Send[2]=Mid_ReadIR.ReadIR[1];
	  Usart1Send[3]=Mid_ReadIR.ReadIR[2];
	  Usart1Send[4]=i;
	  SendCount=1;
	  SBUF=Usart1Send[SendCount];
	  #endif 



//			Mid_ReadIR.ReadIR[0]=0;
//		    Mid_ReadIR.ReadIR[1]=0;
//			Mid_ReadIR.ReadIR[2]=0;
			Mid_ReadIR.ReadIRFlag=0;

	}
}

void ClearAllIR(void)
 {
   	 IRLocation.NearMid=0;
	 IRLocation.NearPreLeft=0;
	 IRLocation.NearPreRight=0;
	 IRLocation.NearLeft=0;
	 IRLocation.NearRight=0;
     IRLocation.FarMid=0;
     IRLocation.FarLeft=0;
	 IRLocation.FarRight=0;
	 IRLocation.FarPreLeft=0;
	 IRLocation.FarPreRight=0;
 }
void CheckHandsetIR()
{

   CheckXReadIR(&Mid_ReadIR);
   if(Mid_ReadIR.ReadIRFlag==3)
   {
      Mid_ReadIR.ReadIRFlag=0;
	  //if(Mid_ReadIR.ReadIR[0]==0X44)
   	  //  SBUF=Mid_ReadIR.ReadIR[2];
   }

}
/***************************************************************************************
  * @˵��  	INT8-17�жϷ�����
  *	@����	��
  * @����ֵ ��
  * @ע		��
***************************************************************************************/
void INT8_17_Rpt() interrupt INT8_17_VECTOR 
{
	
	if(PINTF1&0x80)						//�ж�INT15�жϱ�־λ
	{
		PINTF1 &=~ 0x80;				//���INT15�жϱ�־λ
	
	}
	
	if(PINTF1&0x40)						//�ж�INT14�жϱ�־λ
	{
		PINTF1 &=~ 0x40;				//���INT14�жϱ�־λ	
		Read_MidIR();
	}
	
	if(PINTF1&0x20)						//�ж�INT13�жϱ�־λ
	{
		PINTF1 &=~ 0x20;				//���INT13�жϱ�־λ	
		
	}

}

