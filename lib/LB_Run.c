/*

---------- file information -----------------------------------------------
file name:
define   : <锟侥硷拷说锟斤拷>
version  : 锟斤拷锟侥硷拷尾锟斤拷
---------------------------------------------------------------------------
*/

//全锟街憋拷锟斤拷锟斤拷锟斤拷
#define  KAKA_Run_GB

#ifdef   CodeC_Includes
#include "PJ_Includes.h"
#else
//#include "LB_hc89f003_IO.h"
#include "..\include\PJ_TypeRedefine.h"
#include "LB_Motor.h"
#include "LB_Run.h"
#include "LB_AD.h"
#include "LB_Led.h"
#include "LB_IR.h"
#include "LB_Usart.h"
#include "..\lib\LB_Key.h"

#endif
#include "..\lib\LB_Key.h"
/*******************************************************
  * @?|篓卢???  	?隆搂?隆搂o?篓陇o?拢陇隆搂oy
  * @2?隆搂oy  	fui_i : ?隆搂?隆搂o?篓陇隆搂o?篓陇??
  * @?隆猫|篓卢???|篓卢 ?T
  * @?篓垄?篓娄 	Fcpu = 16MHz?篓潞?fui_i = 1隆搂o?篓陇?篓潞??隆搂?隆搂o?篓陇隆搂o?篓陇?????a1Ms
**************************************************************/
void Delay_ms(INT16U fui_i)
{
	INT16U fui_j;
	for(;fui_i > 0;fui_i --)
	for(fui_j = 1596;fui_j > 0;fui_j --)
	{
		;
	}
}
/*******************************************************
  * @?|篓卢???  	?隆搂?隆搂o?篓陇o?拢陇隆搂oy
  * @2?隆搂oy  	fui_i : ?隆搂?隆搂o?篓陇隆搂o?篓陇??
  * @?隆猫|篓卢???|篓卢 ?T
  * @?篓垄?篓娄 	Fcpu = 16MHz?篓潞?fui_i = 1隆搂o?篓陇?篓潞??隆搂?隆搂o?篓陇隆搂o?篓陇?????a1Ms
**************************************************************/
INT8U readRunTime()
{
	INT8U i;
	if(Voltage>820)
		i=35;
	else if(Voltage>810)
		i=36;
	else if(Voltage>800)
		i= 36;
	else if(Voltage>790)
		i= 37;
	else if(Voltage>780)
		i= 38;
	else if(Voltage>770)
		i= 38;
	else if(Voltage>760)
		i= 39;
	else if(Voltage>750)
		i= 39;
	else if(Voltage>740)
		i= 40;
	else if(Voltage>730)
		i= 40;
	else if(Voltage>720)
		i= 41;
	else if(Voltage>710)
		i= 42;
	else if(Voltage>700)
		i= 43;
	else if(Voltage>690)
		i= 43;
	else if(Voltage>680)
		i= 44;
	else if(Voltage>670)
		i= 45;
	else if(Voltage>660)
		i= 45;
	else if(Voltage>650)
		i= 46;
	else if(Voltage>640)
		i= 47;
	else if(Voltage>630)
		i= 48;
	else if(Voltage>620)
		i= 49;
	else
		i= 61;
	return (i+40);
}
/***********************************************************************
 * ***
 *Function Name:void ReChargeBattery(void) 
 *Function :Auto recharge batter 
 * 
 * 
 * 
 * 
************************************************************************/
void Auto_ReChargeBattery(void)
{
	static INT8U j,z,left_Circular,i;
	switch(RunStep)
	{

		case 0:
		{
            if(RunMs< 60)
			  InitMotorForward();
			
			RunStep=1;
			ClearAllIR();
			RunMs = 0;
			
		}
		break;
		case 1:
		{
			if(RunMs>30)
			{
				RunMs=0;
				if(IRLocation.NearMid>0)
				{
					RunStep=0x50;
				}
				else if(IRLocation.NearPreRight>0)
				{
					RunStep=0x50;
					InitMotorForwardLeftSlow();
				}
				else if(IRLocation.NearPreLeft>0)
				{
					RunStep=0x50;
					InitMotorForwardRightSlow();
				}
				else if(IRLocation.NearRight>0)
				{
					RunStep=0x50;
					InitMotorForwardLeftSlow();
				}
				else if(IRLocation.NearLeft>0)
				{
					RunStep=0x50;
					InitMotorForwardRightSlow();
				}
				else if(IRLocation.FarMid>0)
				{
					RunStep=0x40;
					InitMotorForwardSlow();
				}
				else if(IRLocation.FarPreRight>0)
				{
					RunStep=0x40;
					InitMotorForwardLeftSlow();
				}
				else if(IRLocation.FarPreLeft>0)
				{
					RunStep=0x40;
					InitMotorForwardRightSlow();
				}
				else if(IRLocation.FarRight>0)
				{
					RunStep=0x40;
					InitMotorForwardLeftSlow();
				}
				else if(IRLocation.FarLeft>0)
				{
					RunStep=0x40;
					InitMotorForwardRightSlow();
				}
				else
				{

				}
				ClearAllIR();
			}
		}
		break;
		//far target 
		case 0x40:
		{
			if(RunMs>30)
			{
				RunMs=0;
				#if 0
				if(SendCount>=12)
				{
					Usart1Send[0]=12;
					Usart1Send[1]=IRLocation.NearMid;
					Usart1Send[2]=IRLocation.NearPreRight;
					Usart1Send[3]=IRLocation.NearPreLeft;
					Usart1Send[4]=IRLocation.NearRight;
					Usart1Send[5]=IRLocation.NearLeft;
					Usart1Send[6]=IRLocation.FarMid;
					Usart1Send[7]=IRLocation.FarPreRight;
					Usart1Send[8]=IRLocation.FarPreLeft;
					Usart1Send[9]=IRLocation.FarRight;
					Usart1Send[10]=IRLocation.FarLeft;
					Usart1Send[11]=RunNoIRsenorLastStep;
					Usart1Send[12]=RunStep;
					SendCount=1;
					SBUF=Usart1Send[SendCount];
				}
				#endif 
				if(IRLocation.FarMid>0 )
				{
                    if(Mid_ReadIR.ReadIR[0] ==0x11|| Mid_ReadIR.ReadIR[0] ==0x86||Mid_ReadIR.ReadIR[0] ==0x84 \
						  ||Mid_ReadIR.ReadIR[0] ==0x18  ||Mid_ReadIR.ReadIR[0] ==0xA8|| Mid_ReadIR.ReadIR[0]==0X44\
							||Mid_ReadIR.ReadIR[0] ==0x8A)
					        InitMotorForwardSlow();
							RunNoIRsenorTime=0;
							RunNoIRsenorLastStep=1;
					        RunStep=0x50;
				}
		
				else if(IRLocation.FarPreRight>0 ||IRLocation.FarRight>0 )
				{
                   if(Mid_ReadIR.ReadIR[0] ==0xAA){
				   	 
						 RunStep=0x50;
				         
						
                   	}
				    else{
					RunStep=0x50; //CCW
					InitMotorForwardSlow();
					RunNoIRsenorTime=0;
					RunNoIRsenorLastStep=2;
				   	}
				
				}
				else if(IRLocation.FarLeft>0 ||IRLocation.FarPreLeft>0)
				{
					if(Mid_ReadIR.ReadIR[0] ==0xA1){
				     InitMotorForwardSlow();// InitMotorForwardRightSlow();
					  RunStep=0x50;
					}
					else{
						  RunStep=0x50; //CW
						  InitMotorForwardSlow();
						RunNoIRsenorTime=0;
						RunNoIRsenorLastStep=3;
							
					
				}
			  }
				else if (Mid_ReadIR.ReadIR[0] !=0){
					
						 InitMotorForwardSlow();
						RunStep=0x50;


					
				}
				else if (Mid_ReadIR.ReadIR[0] ==0){

						Mid_ReadIR.ReadIR[0]=0;
		   
						 RunStep=0x43; //CCW
						//RunNoIRsenorTime=0;
						//RunNoIRsenorLastStep=3;
						RunMs = 0;
				

				}
				ClearAllIR();
			}
		}
		break;
		
		break;
		

		case 0x43 ://CCW
               if(RunMs< 6){

				InitMotorLeft();//CCW 


			   }
			   else {

					RunMs =0 ;
					RunStep = 0x44;


			   }


		break;

		case 0x44 :

	          j++ ;
			 SetStop();
			 Delay_ms(500);
		  
			
			   IRLocation.CloseList[0]=Mid_ReadIR.ReadIR[0];
			
			 
			 if(IRLocation.CloseList[0] >0){

			 			RunStep = 0x45;//line run 
						RunMs = 0;


			 }
		     else if(IRLocation.CloseList[0] ==0){

					    RunStep = 0x47;
						RunMs = 0;
			 }
			            
                  


		break;

		case 45:  //line
			
		      if(z==1){
				  if(RunMs< 3)
						InitMotorForwardSlow();//line run 
					z=0;
			  }
		      else if(RunMs< 5){

                InitMotorForwardSlow();//line run 


			   }
			   else {

					RunMs =0 ;
					RunStep = 0x46;

               }


		break;

		case 0x46:
			 
			 SetStop();
			 Delay_ms(500);
		   
			 
			   IRLocation.CloseList[2]=Mid_ReadIR.ReadIR[0];
			
			 if(IRLocation.CloseList[2] >0){

			 			RunStep = 0x45;
						RunMs = 0;
			 }
		
			 else if(IRLocation.CloseList[2] ==0){

					    RunStep = 0x1;
						RunMs = 0;
			           
			 }
			            



		break;
		
		case 0x47 : //cw
			
		       if(left_Circular ==1){
				   if(RunMs<100)

                    InitMotorRight();//CW 
				 
				   z =1;
				   
				   
			   }
               else if(RunMs< 3){

                  InitMotorRight();//CW 


			   }
			   else {

					RunMs =0 ;
					RunStep = 0x48;

               }


		break;




		case 0x48:
			
			 SetStop();
			 Delay_ms(500);
			
			     IRLocation.CloseList[5]=Mid_ReadIR.ReadIR[0];
		
		      if(z ==1){
			        RunStep = 0x45; //line 
						RunMs = 0;
				 
			  
			  }
			
			 else if(IRLocation.CloseList[5] >0){

			 			RunStep = 0x45; //line 
						RunMs = 0;

             }
			 else if(IRLocation.CloseList[5] ==0){

					    RunStep = 0x43;
						RunMs = 0;
			 }
			

		break;

       case 0x50:
		{
            i=0;
			if(RunMs>30)
			{
				RunMs=0;
				#if 0
				if(SendCount>=12)
				{
					Usart1Send[0]=12;
					Usart1Send[1]=IRLocation.NearMid;
					Usart1Send[2]=IRLocation.NearPreRight;
					Usart1Send[3]=IRLocation.NearPreLeft;
					Usart1Send[4]=IRLocation.NearRight;
					Usart1Send[5]=IRLocation.NearLeft;
					Usart1Send[6]=IRLocation.FarMid;
					Usart1Send[7]=IRLocation.FarPreRight;
					Usart1Send[8]=IRLocation.FarPreLeft;
					Usart1Send[9]=IRLocation.FarRight;
					Usart1Send[10]=IRLocation.FarLeft;
					Usart1Send[11]=IMP;
					Usart1Send[12]=RunStep;
					SendCount=1;
					SBUF=Usart1Send[SendCount];
				}
				#endif 
				if(IRLocation.NearMid>0)
				{
					InitMotorForwardSlow();
					RunNoIRsenorTime=0;
					RunNoIRsenorLastStep=1;					
				}
				else if(IRLocation.NearPreRight>0)
				{

					InitMotorForwardLeftSlow();
					RunNoIRsenorTime=0;
					RunNoIRsenorLastStep=2;					
				}
				else if(IRLocation.NearPreLeft>0)
				{
					InitMotorForwardRightSlow();
					RunNoIRsenorTime=0;
					RunNoIRsenorLastStep=3;					
				}
				else if(IRLocation.NearRight>0)
				{
					InitMotorForwardLeftSlow();
					RunNoIRsenorTime=0;
					RunNoIRsenorLastStep=2;					
				}
				else if(IRLocation.NearLeft>0)
				{
					InitMotorForwardRightSlow();
					RunNoIRsenorTime=0;
					RunNoIRsenorLastStep=3;					
				}
				else if(IRLocation.FarMid>0)
				{
					//RunStep=0x50;
					InitMotorForwardSlow();
					RunNoIRsenorTime=0;
					RunNoIRsenorLastStep=1;					
				}
				else if(IRLocation.FarPreRight>0)
				{
					//RunStep=0x53;
					InitMotorForwardLeftSlow();
					RunNoIRsenorTime=0;
					RunNoIRsenorLastStep=2;					
				}
				else if(IRLocation.FarPreLeft>0)
				{
					//RunStep=0x56;
					InitMotorForwardRightSlow();
					RunNoIRsenorTime=0;
					RunNoIRsenorLastStep=3;					
				}
				else if(IRLocation.FarRight>0)
				{
					//RunStep=0x59;
					InitMotorForwardLeftSlow();
					RunNoIRsenorTime=0;
					RunNoIRsenorLastStep=2;					
				}
				else if(IRLocation.FarLeft>0)
				{
					//RunStep=0x5c;
					//RunStep =0x47;
					//RunMs =0;
					//left_Circular = 1;
					#if 1
					i++;
					if(i<10){
						RunMs =0 ;
						RunStep=1;
					}
					else{
						i=0;
					    // InitMotorForwardRightSlow_left();
						RunStep =0x47;
					    RunMs =0;
					    left_Circular = 1;
					}
				    #endif 
				//	InitMotorForwardRightSlow();	
					RunNoIRsenorTime=0;
					RunNoIRsenorLastStep=2;	
								
				}
				else
				{
					RunNoIRsenorTime++;
					if(RunNoIRsenorTime>4)
					{

						RunNoIRsenorTime=0;
						if(RunNoIRsenorLastStep==1)
						{

						}
						else	if(RunNoIRsenorLastStep==2)
						{
							InitMotorForwardRightSlow();
							RunNoIRsenorTime=0;
							RunStep=0x1;
						}
						else	if(RunNoIRsenorLastStep==3)
						{
							InitMotorForwardLeftSlow();
							RunNoIRsenorTime=0;
							RunStep=0x1;
						}


					}
				}
				ClearAllIR();
			}
		}
		break;
		}
}
/***********************************************************************
 * ***
 *Function Name:void ReChargeBattery(void) 
 *Function :void CleanMode_BOW(void)
 * 
 * 
 * 
 * 
************************************************************************/
void CleanMode_BOW(void)
{

// 弓形
	
		
		switch(RunStep)
		{
		case 0:
		{

		}
		break;
		case 1:
		{
		   //InitMotorLeft();
			InitMotorForward();
			RunStep=2;
		}
		break;
		case 2:
		{
			if((WallDp[0]>WallMin)||(WallDp[1]>WallMin)||(WallDp[2]>WallMin)||(WallDp[3]>WallMin))
			{

				NoImpSecond=0;
				RunStep=0x4;
				InitMotorRetreat();
				RunMs=30;
				CurrentMax++;
			}
            else if(IMP>0)
			{
				NoImpSecond=0;
				RunStep=0x4;
				InitMotorRetreat();
				RunMs=0;
				CurrentMax++;			
			}
			else if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
			{
				CurrentMax++;
				NoImpSecond=0;
				RunStep=0x3;
				SetStop();
				RunMs=0;
			}
			else  if(RunMs>500)
			{
				CurrentMax=0;
			}
		}
			break;
		case 3:
		{
			if(RunMs>90)
			{
				InitMotorRetreat();
				RunMs=0;
				RunStep=4;
			}
			break;
        }
		case 4:
		{
			if(RunMs>90)
			{
				SetStop();
				RunMs=0;
				RunStep=5;
			}
		}
			break;
		case 5:
		{
			if(RunMs>20)
			{
				InitMotorLeft();
				RunMs=0;
				RunStep=6;
			}
		}
			break;

		case 6:
		{
			if(RunMs>readRunTime())
			{
				SetStop();
				//InitMotorForward();
				RunMs=0;
				RunStep=7;
				LCurrent=0;
				RCurrent=0;
			}
			else if((WallDp[0]>WallMin)||(WallDp[1]>WallMin)||(WallDp[2]>WallMin)||(WallDp[3]>WallMin))
			{

				NoImpSecond=0;
				RunStep=4;
				InitMotorRetreat();
				RunMs=30;

			}
            else if(IMP>0)
			{
				NoImpSecond=0;
				RunStep=0x4;
				InitMotorRetreat();
				RunMs=0;
				CurrentMax++;			
			}

        }
			break;
		case 7:
		{
			if(RunMs>40)
			{
				InitMotorForward();
				RunMs=0;
				RunStep=8;
				LCurrent=0;
				RCurrent=0;
			}
		}
		break;
		case 8:
		{
			if(RunMs>150)
			{
				SetStop();
				RunMs=0;
				RunStep=9;

			}
			else if((WallDp[0]>WallMin)||(WallDp[1]>WallMin)||(WallDp[2]>WallMin)||(WallDp[3]>WallMin))
			{
				NoImpSecond=0;
				RunStep=9;
				InitMotorRetreat();
				RunMs=0;
				CurrentMax++;
			}
			else if(IMP>0)
			{

				NoImpSecond=0;
				RunStep=9;
				InitMotorLeftMax();
				RunMs=0;
				CurrentMax++;
			}

			else if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
			{

				CurrentMax++;
				InitMotorRetreat();
				RunMs=0;
				RunStep=9;
			}
		}
			break;
		case 9:
		{
			if(RunMs>90)
			{
				InitMotorLeft();
				RunMs=0;
				RunStep=10;
			}
		}
			break;

		case 10:
			if(RunMs>readRunTime())
			{

				{
					//InitMotorForward();
					SetStop();
					RunMs=0;
					RunStep=11;
					LCurrent=0;
					RCurrent=0;
				}
			}

			else if((WallDp[0]>WallMin)||(WallDp[1]>WallMin)||(WallDp[2]>WallMin)||(WallDp[3]>WallMin))
			{

				NoImpSecond=0;
				RunStep=4;
				InitMotorRetreat();
				RunMs=20;

			}
			else if(IMP>0)
			{

				NoImpSecond=0;
				RunStep=4;
				InitMotorLeftMax();
				RunMs=0;

			}


			break;
		case 11:
			if(RunMs>20)
			{
				InitMotorForward();
				RunMs=0;
				RunStep=0x12;
				ImpSecond=0;
				LCurrent=0;
				RCurrent=0;
			}
			else if((WallDp[0]>WallMin)||(WallDp[1]>WallMin)||(WallDp[2]>WallMin)||(WallDp[3]>WallMin))
			{

				NoImpSecond=0;
				RunStep=9;
				InitMotorRetreat();
				RunMs=0;

			}
			else if(IMP>0)
			{

				NoImpSecond=0;
				RunStep=9;
				InitMotorRetreat();
				RunMs=0;

			}
			break;
		case 0x12:
		{
			if((WallDp[0]>WallMin)||(WallDp[1]>WallMin)||(WallDp[2]>WallMin)||(WallDp[3]>WallMin))
			{
				CurrentMax++;
				NoImpSecond=10;
				RunStep=0x14;
				InitMotorRetreat();
				RunMs=20;

			}
			else if(IMP>0)
			{
				CurrentMax++;
				NoImpSecond=0;
				RunStep=0x14;
				InitMotorRetreat();
				RunMs=0;
			
			}
			else if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
			{

				CurrentMax++;
				EdgeTime=0;
				NoImpSecond=0;
				RunStep=0x13;
				SetStop();
				RunMs=0;
			}
			else  if(RunMs>500)
			{
				CurrentMax=0;
			}
		}
		break;
		case 0x13:
		{
			if(RunMs>30)
			{
				InitMotorRetreat();
				RunMs=0;
				RunStep=0x14;
			}
			break;
		}
		case 0x14:
		{
			if(RunMs>90)
			{
				SetStop();
				RunMs=0;
				RunStep=0x15;
			}
		}
			break;
		case 0x15:
		{
			if(RunMs>10)
			{
				InitMotorRight();
				RunMs=0;
				RunStep=0x16;
			}
		}
			break;

		case 0x16:
		{
			if(RunMs>readRunTime())
			{
				SetStop();
				//InitMotorForward();
				RunMs=0;
				RunStep=0x17;
				LCurrent=0;
				RCurrent=0;
			}
			else if((WallDp[0]>WallMin)||(WallDp[1]>WallMin)||(WallDp[2]>WallMin)||(WallDp[3]>WallMin))
			{
				CurrentMax++;
				NoImpSecond=0;
				RunStep=0x14;
				InitMotorRetreat();
				RunMs=0;

			}
 			else if(IMP>0)
			{
				CurrentMax++;
				NoImpSecond=0;
				RunStep=0x14;
				InitMotorRetreat();
				RunMs=0;
			
			}
			else if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
			{
				CurrentMax++;
				NoImpSecond=0;
				RunStep=0x14;
				InitMotorRetreat();
				RunMs=0;

			}

	   }
			break;
		case 0x17:
		{
			if(RunMs>20)
			{
				InitMotorForward();
				RunMs=0;
				RunStep=0x18;
				LCurrent=0;
				RCurrent=0;
			}
		}
		break;
		case 0x18:
		{
			if(RunMs>150)
			{
				SetStop();
				RunMs=0;
				RunStep=0x19;

			}
			else  if((WallDp[0]>WallMin)||(WallDp[1]>WallMin)||(WallDp[2]>WallMin)||(WallDp[3]>WallMin))
			{
				CurrentMax++;
				NoImpSecond=0;
				RunStep=0x19;
				InitMotorRetreat();
				RunMs=0;

			}
		   else if(IMP>0)
		   {
				CurrentMax++;
				NoImpSecond=0;
				RunStep=0x19;
				InitMotorRetreat();
				RunMs=0;		   
		   }
			else if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
			{
				CurrentMax++;
				InitMotorRetreat();
				RunMs=0;
				RunStep=0x19;
			}
		}
			break;
		case 0x19:
		{
			if(RunMs>20)
			{
				InitMotorRight();
				RunMs=0;
				RunStep=0x1a;
			}
			}
			break;

		case 0x1a:
		{
			if(RunMs>readRunTime())
			{
				//InitMotorForward();
				SetStop();
				RunMs=0;
				RunStep=0x1b;
				LCurrent=0;
				RCurrent=0;

			}
			else if((WallDp[0]>WallMin)||(WallDp[1]>WallMin)||(WallDp[2]>WallMin)||(WallDp[3]>WallMin))
			{
				CurrentMax++;
				NoImpSecond=0;
				RunStep=0x19;
				InitMotorRetreat();
				RunMs=0;

			}
		   else if(IMP>0)
		   {
				CurrentMax++;
				NoImpSecond=0;
				RunStep=0x19;
				InitMotorRetreat();
				RunMs=0;		   
		   }
			else if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
			{
				CurrentMax++;
				InitMotorRetreat();
				RunMs=0;
				RunStep=0x19;
			}
		}
			break;
		case 0x1b:
		{
			if(RunMs>20)
			{
				InitMotorForward();
				RunMs=0;
				RunStep=0x2;
				ImpSecond=0;
				LCurrent=0;
				RCurrent=0;
			}
			else if((WallDp[0]>WallMin)||(WallDp[1]>WallMin)||(WallDp[2]>WallMin)||(WallDp[3]>WallMin))
			{
				CurrentMax++;
				NoImpSecond=0;
				RunStep=0x19;
				InitMotorRetreat();
				RunMs=0;

			}
		   else if(IMP>0)
		   {
				CurrentMax++;
				NoImpSecond=0;
				RunStep=0x19;
				InitMotorRetreat();
				RunMs=0;		   
		   }
			else if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
			{
				CurrentMax++;
				InitMotorRetreat();
				RunMs=0;
				RunStep=0x19;
			}
		   }
			break;

		}
		
	
}
/***********************************************************************
 * ***
 *Function Name:void CleanMode_Random(void)
 *Function :void CleanMode_BOW(void)
 * 
 * 
 * 
 * 
************************************************************************/
void CleanMode_Random(void)
{
	   
	  	switch(RunStep)
		{
		case 0:
		{

		}
		break;
		case 1:
		{

			InitMotorForward();
			RunStep=2;
		}
		break;
		case 2:
		{
			if((WallDp[0]>WallMin)||(WallDp[1]>WallMin)||(WallDp[2]>WallMin)||(WallDp[3]>WallMin))
			{

				NoImpSecond=0;
				RunStep=0x3;
				InitMotorRetreat();
				RunMs=10;
				CurrentMax++;
			}
            else if(IMP>0)
			{
				NoImpSecond=0;
				RunStep=0x3;
				InitMotorRetreat();
				RunMs=0;
				CurrentMax++;			
			}
			else if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
			{
				CurrentMax++;
				NoImpSecond=0;
				RunStep=0x3;
				SetStop();
				RunMs=0;
			}
			else  if(RunMs>500)
			{
				CurrentMax=0;
			}
		}
			break;
		case 3:
		{
			if(RunMs>30)
			{
				InitMotorRetreat();
				RunMs=0;
				RunStep=4;
			}
			break;
        }
		case 4:
		{
			if(RunMs>30)
			{
				SetStop();
				RunMs=0;
				RunStep=5;
			}
		}
			break;
		case 5:
		{
			if(RunMs>20)
			{
				InitMotorLeft();
				RunMs=0;
				RunStep=6;
			}
		}
			break;

		case 6:
		{
			if(RunMs>readRunTime())
			{
				//SetStop();
				InitMotorForward();
				RunMs=0;
				RunStep=2;
				LCurrent=0;
				RCurrent=0;
			}
			else if((WallDp[0]>WallMin)||(WallDp[1]>WallMin)||(WallDp[2]>WallMin)||(WallDp[3]>WallMin))
			{

				NoImpSecond=0;
				RunStep=3;
				InitMotorRetreat();
				RunMs=10;

			}
            else if(IMP>0)
			{
				NoImpSecond=0;
				RunStep=0x3;
				InitMotorRetreat();
				RunMs=0;
				CurrentMax++;			
			}

        }
			break;			
			}
}
/**********************************************************************
 * 	*
    *Function Name:void  CheckRun()
	*Function: 
	*Input Ref:NO
	*Return Ref: NO
	*
***********************************************************************/
void  CheckRun()
{
   
   
   switch(RunMode) {
      
	case 1 : // clean random Mode 
         CleanMode_Random();

	break;

	case 2: //clean zMode --edge line Mode
		wallMode();
	break; 

	case 3: //clean bow Mode
		CleanMode_BOW();
	break;

	case 4: //fixpoint clean Mode
		circleMode();
	break;

	case 5:
	     Auto_ReChargeBattery();

	break;


   }
}


/****************************************************************
 * *
 * * * Function Name:void circleMode(void)
 *     Function: 
 * 
 * 
*****************************************************************/
void circleMode(void)
{
 		switch(cleanWorks.Clean_fixpointMode)
		{
			case 0:
			{

			}
				break;

			case 1:  //初始原地右转圈
			{								
				InitMotorRightCircle();
				RunStep=2;
				RunMs=0;
			}
				break;

			case 2:  //normal run
			{
				if((WallDp[0]>WallMin)||(WallDp[1]>WallMin)||(WallDp[2]>WallMin)||(WallDp[3]>WallMin))
				{
					NoImpSecond=0;
					RunStep=0x3;
					InitMotorRetreat();
					RunMs=10;
					CurrentMax++;
				}
				else if(IMP>0)
				{
					NoImpSecond=0;
					RunStep=0x3;
					InitMotorRetreat();
					RunMs=0;
					CurrentMax++;			
				}
				else 
					if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
				{
					CurrentMax++;
					NoImpSecond=0;
					RunStep=0x3;
					SetStop();
					RunMs=0;
				}
				else if(RunMs>600)
				{
					InitMotorForwardRightUp1();
					RunStep = 0x10;
					RunMs = 0;
					CurrentMax = 0;
				}
			}
				break;
			
			case 3:   //后退
			{
				if(RunMs>30)
				{
					InitMotorRetreat();
					RunMs=0;
					RunStep=4;
				}
			}
				break;
			
			case 4:  //停止
			{
				if(RunMs>40)
				{
					SetStop();
					RunMs=0;
					RunStep=5;
				}
			}
				break;

			case 5:  //转弯
			{
				if(RunMs>20)
				{
					InitMotorLeftCircle();
					RunMs=0;
					RunStep=6;
				}
			}
				break;

			case 6:  //直走
			{			
				if(RunMs>80)
				{
					InitMotorForward();
					RunMs=0;
					RunStep=7;
				}	
			}
				break;			
					
			case 7:
			{
			if(RunMs>300)  //直走一段距离，然后换转向
				{
					SetStop();				
					RunStep=1;				
					RunMs=0;
					LCurrent=0;
					RCurrent=0;
				}
				else if((WallDp[0]>WallMin)||(WallDp[1]>WallMin)||(WallDp[2]>WallMin)||(WallDp[3]>WallMin))
				{
					NoImpSecond=0;
					RunStep=3;
					InitMotorRetreat();
					RunMs=10;

				}
				else if(IMP>0)
				{
					NoImpSecond=0;
					RunStep=0x3;
					InitMotorRetreat();
					RunMs=0;
					CurrentMax++;			
				}			
			}
				break;
			
						
			//右内圈
			case 0x10:{
				if((WallDp[0]>WallMin)||(WallDp[1]>WallMin)||(WallDp[2]>WallMin)||(WallDp[3]>WallMin))
				{
					NoImpSecond=0;
					RunStep=0x3;
					InitMotorRetreat();
					RunMs=10;
					CurrentMax++;
				}
				else if(IMP>0)
				{
					NoImpSecond=0;
					RunStep=0x3;
					InitMotorRetreat();
					RunMs=0;
					CurrentMax++;			
				}
				else if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
				{
					CurrentMax++;
					NoImpSecond=0;
					RunStep=0x3;
					SetStop();
					RunMs=0;
				}
				else  if(RunMs>2000)
				{
					InitMotorForwardRightUp2();
					RunStep = 0x11;
					CurrentMax = 0;
				}
			}
				break;
			
			//右中圈
			case 0x11:{
				if((WallDp[0]>WallMin)||(WallDp[1]>WallMin)||(WallDp[2]>WallMin)||(WallDp[3]>WallMin))
				{
					NoImpSecond=0;
					RunStep=0x3;
					InitMotorRetreat();
					RunMs=10;
					CurrentMax++;
				}
				else if(IMP>0)
				{
					NoImpSecond=0;
					RunStep=0x3;
					InitMotorRetreat();
					RunMs=0;
					CurrentMax++;			
				}
				else if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
				{
					CurrentMax++;
					NoImpSecond=0;
					RunStep=0x3;
					SetStop();
					RunMs=0;
				}
				else  if(RunMs>2200)
				{
					InitMotorForwardRightUp3();
					RunStep = 0x12;
					CurrentMax = 0;
					RunMs=0;
				}
			}
				break;	

			//右外圈
			case 0x12:{
				if((WallDp[0]>WallMin)||(WallDp[1]>WallMin)||(WallDp[2]>WallMin)||(WallDp[3]>WallMin))
				{
					NoImpSecond=0;
					RunStep=0x3;
					InitMotorRetreat();
					RunMs=10;
					CurrentMax++;
				}
				else if(IMP>0)
				{
					NoImpSecond=0;
					RunStep=0x3;
					InitMotorRetreat();
					RunMs=0;
					CurrentMax++;			
				}
				else if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
				{
					CurrentMax++;
					NoImpSecond=0;
					RunStep=0x3;
					SetStop();
					RunMs=0;
				}
				else  if(RunMs>1600)
				{
					SetStop();
					RunStep=0x06;
					RunMs= 75;
					CurrentMax = 0;
				}
			}
				break;	

#if 0   
			case 0x08:   //原地左转
			{
				InitMotorLeftCircle();
				RunStep= 0x02;
				rightLeftFlag = 0;
				RunMs=0;				
			}
				break;			
			
			
			//左内圈
			case 0x20:{
				if((WallDp[0]>WallMin)||(WallDp[1]>WallMin)||(WallDp[2]>WallMin)||(WallDp[3]>WallMin))
				{
					NoImpSecond=0;
					RunStep=0x3;
					InitMotorRetreat();
					RunMs=10;
					CurrentMax++;
				}
				else if(IMP>0)
				{
					NoImpSecond=0;
					RunStep=0x3;
					InitMotorRetreat();
					RunMs=0;
					CurrentMax++;			
				}
				else if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
				{
					CurrentMax++;
					NoImpSecond=0;
					RunStep=0x3;
					SetStop();
					RunMs=0;
				}
				else  if(RunMs>1000)
				{
					InitMotorForwardLeftUp2();
					RunStep = 0x21;
					CurrentMax = 0;
					RunMs=0;
				}
			}
				break;
			
			//左中圈
			case 0x21:{
				if((WallDp[0]>WallMin)||(WallDp[1]>WallMin)||(WallDp[2]>WallMin)||(WallDp[3]>WallMin))
				{
					NoImpSecond=0;
					RunStep=0x3;
					InitMotorRetreat();
					RunMs=10;
					CurrentMax++;
				}
				else if(IMP>0)
				{
					NoImpSecond=0;
					RunStep=0x3;
					InitMotorRetreat();
					RunMs=0;
					CurrentMax++;			
				}
				else if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
				{
					CurrentMax++;
					NoImpSecond=0;
					RunStep=0x3;
					SetStop();
					RunMs=0;
				}
				else  if(RunMs>2000)
				{
					RunMs=0;
					InitMotorForwardLeftUp3();
					RunStep = 0x22;
					CurrentMax = 0;
				}
			}
				break;	

			//左外圈
			case 0x22:{
				if((WallDp[0]>WallMin)||(WallDp[1]>WallMin)||(WallDp[2]>WallMin)||(WallDp[3]>WallMin))
				{
					NoImpSecond=0;
					RunStep=0x3;
					InitMotorRetreat();
					RunMs=10;
					CurrentMax++;
				}
				else if(IMP>0)
				{
					NoImpSecond=0;
					RunStep=0x3;
					InitMotorRetreat();
					RunMs=0;
					CurrentMax++;			
				}
				else if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
				{
					CurrentMax++;
					NoImpSecond=0;
					RunStep=0x3;
					SetStop();
					RunMs=0;
				}
				else  if(RunMs>2500)
				{
					SetStop();
					RunStep=0x1;
					RunMs=0;
					CurrentMax = 0;
				}
			}
				break;	
	#endif		
	}	
}
/****************************************************************
 * *
 * * * Function Name:void wallMode(void)
 *     Function: 
 * 
 * 
*****************************************************************/
void wallMode(void)
{
	
	switch(cleanWorks.Clean_wallMode){
		case 0:
			break;
		
		case 1:   //init
			InitMotorForwardLeft();
			RunStep=2;				
			RunMs = 0;
		  WallDp[0] = 0;
			WallDp[1] = 0;
			WallDp[2] = 0;
			WallDp[3] = 0;
			break;

		case 2:  // run normal 
			if((WallDp[0]>WallMin)||(WallDp[2]>WallMin)||(WallDp[3]>WallMin)){			
				NoImpSecond=0;
				RunStep=0x3;
				InitMotorRetreat();
				RunMs=10;
				CurrentMax++;
			}
			else if(IMP>0){		
				NoImpSecond=0;
				RunStep=0x3;
				InitMotorRetreat();
				RunMs=0;
				CurrentMax++;			
				if(IMP == 1){
					RunStep=10;
				}
			}
			else	if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax)){			
				CurrentMax++;
				NoImpSecond=0;
				RunStep=0x3;
				SetStop();
				RunMs=0;
			}
			else	if((WallDp[1]>WallModeMin)){  //right IR detection
				NoImpSecond=0;
				InitMoterAdjustLeft();
				RunStep=0x8;
				RunMs = 0;
			}
			else if(RunMs>1000){			//往右前方走，一直打圈检测不到，则向直走一段距离，重新检测
				RunStep = 0x09;
				RunMs = 0;
				InitMotorForward();
				CurrentMax = 0;			
			}
			break;
		
		case 3: 		//后退 retreat
			if(RunMs>30){
				InitMotorRetreat();
				RunMs=0;
				RunStep=4;
			}			
			break;

			case 4:  		//停止 stop
				if(RunMs>40){	
					SetStop();
					RunMs=0;
					RunStep=5;
				}
				break;

			case 5:  //转弯 turn
				if(RunMs>20){			
					InitMotorLeft();
					RunMs=0;
					RunStep=6;
				}
				break;

			case 6:  //直走	
				if(RunMs>80){
					InitMotorForward();
					RunMs=0;
					RunStep=7;
				}	
				break;			
					
			case 7:  //直走一段小距离，然后换转向			
				if(RunMs>100){  			
					RunStep=1;				
					RunMs=0;
					LCurrent=0;
					RCurrent=0;
				}
				else if((WallDp[0]>WallMin)||(WallDp[2]>WallMin)||(WallDp[3]>WallMin))
				{
					NoImpSecond=0;
					RunStep=3;
					InitMotorRetreat();
					RunMs=10;
				}
				else if(IMP>0)
				{
					NoImpSecond=0;
					RunStep=0x3;
					InitMotorRetreat();
					RunMs=0;
					CurrentMax++;			
					if(IMP == 1){
						RunStep=10;
					}
				}	
				else if(WallDp[1]>WallModeMin){
					RunMs = 0;
					RunStep = 8;
				}				
				break;
						
			case 8:   //right IR check 采样
				if(RunMs>10){
					RunMs = 0;
					if(WallDp[1]<WallModeMin){
						RunStep = 0x01;
						RunMs = 0;
					}
					else if(WallDp[1]<WallModeNormal){ //全速直走
						RunMs = 0;
						InitMoterAdjustForward();
					}					
					else if(WallDp[1]<WallModeMax){  
						InitMoterAdjustLeft();
						RunMs = 0;
					}
					else{
						InitMoterAdjustLeftMore();
						RunMs = 0;
					}
						
					if((WallDp[0]>WallMin)||(WallDp[2]>WallMin)||(WallDp[3]>WallMin))
					{
						NoImpSecond=0;
						RunStep=3;
						InitMotorRetreat();
						RunMs=10;
					}
					else if(IMP>0)
					{
						NoImpSecond=0;
						RunStep=0x3;
						InitMotorRetreat();
						RunMs=0;
						CurrentMax++;			
						if(IMP == 1){
							RunStep=10;
						}
					}	
				}
				break;
				
			case 9:		//向前走一段长距离，重新寻找墙
				if(RunMs>500){
					RunMs = 0;
					RunStep = 1;
				}
				break;

			
		case 10: 		//后退 retreat
			if(RunMs>10){
				InitMotorRetreat();
				RunMs=0;
				RunStep=11;
			}			
			break;

			case 11:  		//停止 stop
				if(RunMs>40){	
					SetStop();
					RunMs=0;
					RunStep=12;
				}
				break;

			case 12:  //转小弯 turn
				if(RunMs>20){			
					InitMotorLeft();
					RunMs=0;
					RunStep=13;
				}
				break;
				
			case 13:  //小曲线右转	
				if(RunMs>40){
					InitMotorRightLittle();
					RunMs= 80;
					RunStep=7;
				}	
				break;	
				
				
		default:
			break;	
	}
	return;
}
/************************************************************************************
 * 	*
    *Function Name:void CheckMode(INT8U Key)
	*Function : motor run of mode three 3 modes
	*           mode 0ne :
	*Input Ref:NO
	*Return Ref:NO
	*
*************************************************************************************/
void CheckMode(INT8U Key)
{
if(Key==1)
 {
   Mode =0; 
   cleanWorks.pressPowerKey++;
   if(cleanWorks.pressPowerKey>4)cleanWorks.pressPowerKey=0;
   Step=cleanWorks.pressPowerKey;
   SBUF =  Step;
 }
  else if(Key==2){ //works mode ----cleaning button        
         Mode =1;
       cleanWorks.worksNumber++;
     if(cleanWorks.worksNumber>4)cleanWorks.worksNumber=0;
      Step=cleanWorks.worksNumber  ;
      SBUF =  Step;
 }
    ////power on of initial: Mode=2;Step=0;RunMode=1;RunStep=0;
	switch(Mode)
	{
	    case 0 :
		{
		
		switch(Step)
		{
	        
			//power On and power key press status 
			case 1: //power on 
			{
				cleanWorks.iPowerFlag =1;
				SetStop();
				LedGreenOff();
				LedRedON();
				SetBuzzerTime(5);
				Delay_ms(10);
				SetBuzzerTime(0);
				Delay_ms(10);
				SetBuzzerTime(5);
				Delay_ms(10);
				BuzzerOff();
				Mode = 0x65;
				Step = 0x64;
			

			}
			break;

        
		case 2:  //input standby mode
	            SetBuzzerTime(4);
			    Delay_ms(10);
				BuzzerOff();
                Mode =0x66;
			    LedGreenON();
				LedRedOff();
				
				Step = 0x19 ;

			
			break;
		case 3: //input recharge status 
               
				Mode =0x66;
			   
				SetBuzzerTime(4);
			    Delay_ms(10);
				BuzzerOff();

				LedGreenOff();
				LedRedOff();

				RunMode =5;
				RunStep=0;
				RunMs = 0;
		
				
				

			
			break;
			case  4: //power off 
				 Mode =0x66;
				SetStop();
				SetBuzzerTime(4);
			    Delay_ms(10);
				BuzzerOff();
                LedGreenOff();
				LedRedON();
			

				Step = 0x19 ;

			
			break;
		
		
		  

		
		case 0x19:
		//if(cleanWorks.CleanMode == standbyMode)  //  Mode=2;Step=0;RunMode=1;RunStep=0; ---default power on don't press key
		{
			if(Step==0)
			{
				//20
				Step=1;
				ADCtl=1;
				RunSecond=0;
			}
			else if(Step<0x20)
			{
				//LedBlueON();
				Mode=1;
				Step=0;
				RunSecond=0;
				SetStop();
				SetFan(0);
				SetEdge(0);
				RunStep=0;
				//SetBuzzerTime(2);
			}
		  }
		
		}//Mode =0 END
	}
	   break;
	/*************************Mode 0 END**************************/
	/**********Mode 1 start******************/
	//power on key =1
	//  Mode=2;Step=0;RunMode=1;RunStep=0; ---default power on don't press key
	case 1:
	{
		switch(Step)
		{
			//锟斤拷锟斤拷锟斤拷示锟斤拷1锟斤拷锟斤拷2锟斤拷
		case 0:
		{
			
		}
		break;
		case 1://prepare clean mode 
		{
		      
			    Mode =0x66;
				SetBuzzerTime(4);
			    Delay_ms(10);
				BuzzerON();
				LedRedON();
		}
		break;
		case 2://randomMode
		{
                RunMode =1; //
				RunStep =1;
			    Mode =0x66;
				SetBuzzerTime(4);
			    Delay_ms(10);
				BuzzerOff();
				LedRedOff();
				
		  }
		break;
		//锟斤拷锟斤拷锟斤拷锟斤拷时锟斤拷锟狡癸拷锟斤拷频锟斤拷2Hz

		case 3://zMode ---wall edge mode 
		        RunMode =2;
				RunStep=1;
		        Mode =0x66;
				SetBuzzerTime(4);
				Delay_ms(10);
				SetBuzzerTime(0);
				Delay_ms(10);
				SetBuzzerTime(4);
				BuzzerOff();
			
			
				LedGreenON();
				LedRedON();
		break;

		case 4: //bowMode
		         RunMode =3;
				 RunStep =1;
                Mode =0x66;   
		        SetBuzzerTime(4);
				Delay_ms(10);
				SetBuzzerTime(0);
				Delay_ms(10);
				SetBuzzerTime(4);
				Delay_ms(10);
				SetBuzzerTime(0);
				Delay_ms(10);
				SetBuzzerTime(4);
				BuzzerOff();
		
				
                LedGreenOff();
				LedRedOff();

				
	
		break;
		// 锟斤拷锟斤拷械乒锟狡碉拷锟�?0.5Hz
		case 5: //fixPoint Mode
			    RunMode =4;
				RunStep =1;
			    Mode =0x66;
				SetBuzzerTime(4);
				Delay_ms(10);
				SetBuzzerTime(0);
				Delay_ms(10);
				SetBuzzerTime(4);
				Delay_ms(10);
				SetBuzzerTime(0);
				Delay_ms(10);
				SetBuzzerTime(4);
				Delay_ms(10);
				SetBuzzerTime(0);
			    Delay_ms(10);
				SetBuzzerTime(4);
				BuzzerOff();
				LedGreenON();
				LedRedON();
		break;

		case 6:
		{
			if(RunSecond>9)
			{
				LedRedOff();
				Step=5;
				RunSecond=0;
			}
			else if(Voltage>840)
			{
				Step=7;
			}
			else if((0==ReadPowerAutoIn())&&(0==ReadPowerDCIn()))
			{
				Step=0;
				Mode=1;
				//SetBuzzerTime(1);
			}
		}
		break;
		//锟斤拷锟界不锟斤拷
		case 7:
		{
			if((0==ReadPowerAutoIn())&&(0==ReadPowerDCIn()))
			{
				Step=0;
				Mode=0;
			}

			else if(Voltage<650)
			{
				Step=5;

				//SetBuzzerTime(3);
			}
			break;
		}
		case 8:
		{
			if(RunSecond>0)
			{
				LedRedON();

				Step=9;
				RunSecond=0;
			}
		}
		break;

		case 9:
		{
			if(RunSecond>0)
			{

				LedRedOff();
				Step=8;
				RunSecond=0;
			}
		}
		break;
		case 20:
		{
			if((WallDp[0]>WallMin)&&(WallDp[1]>WallMin)&&(WallDp[2]>WallMin))
				LedRedON();
			else
				LedRedOff();
		}
		break;

		}
	}
	break;
	/**********************Mode 1 END***********************************/
	/*************Mode 2 start Battery recharge ***********************/
	// Mode=2;Step=0;RunMode=1;RunStep=0; ---default power on don't press key
	//power on of initial:	Mode=2;Step=0;RunMode=1;RunStep=0;
	//Mode =2 start 
	case 2:
	{
		switch(Step)
		{
			case 0:
			{
				RunMode=2;
				RunStep=0;
				Step=1;
			}
			break;
			case 1:
			{
				if(P2_1 ==1|| P1_0 ==1)
				{
					RunStep=0x60;
					SetStop();
					LedGreenON();
					Step=2;
				}
			}
			break;
            //battery recharge status
           
			case 2:
				if(P2_1 ==1|| P1_0 ==1){
	                SetStop() ;// AllStop();
					LedGreenON();
					Delay_ms(500);
					LedGreenOff();
					Delay_ms(500);
					Step =2;
					Mode =2;

				}
			break;
		
		}

	}
	break;
	/*******************Mode 2 END **********************************/
	/**********************************************************/
	/*********************************************************/

    }
}
	
