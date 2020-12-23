/*

---------- file information -----------------------------------------------
file name:
define   : <�ļ�˵��>
version  : ���ļ�β��
---------------------------------------------------------------------------
*/

//ȫ�ֱ�������
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

#endif
#include "..\lib\LB_Key.h"
/*******************************************************
  * @?|¨¬???  	?¡§?¡§o?¨¤o?£¤¡§oy
  * @2?¡§oy  	fui_i : ?¡§?¡§o?¨¤¡§o?¨¤??
  * @?¡è|¨¬???|¨¬ ?T
  * @?¨¢?¨¦ 	Fcpu = 16MHz?¨º?fui_i = 1¡§o?¨¤?¨º??¡§?¡§o?¨¤¡§o?¨¤?????a1Ms
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
  * @?|¨¬???  	?¡§?¡§o?¨¤o?£¤¡§oy
  * @2?¡§oy  	fui_i : ?¡§?¡§o?¨¤¡§o?¨¤??
  * @?¡è|¨¬???|¨¬ ?T
  * @?¨¢?¨¦ 	Fcpu = 16MHz?¨º?fui_i = 1¡§o?¨¤?¨º??¡§?¡§o?¨¤¡§o?¨¤?????a1Ms
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
    static INT16U i,j,z,w ;

	switch(RunMode)
	{
		/********************Mode =1 END***********************************/
	/******************************************************/
	//Mode =2 start recharge battery
	case 2:
	{

		/*
		NearMid;
		NearPreLeft;
		NearPreRight;
		NearLeft;
		NearRight;
		FarMid;
		FarLeft;
		FarRight;
		FarPreLeft;
		FarPreRight;
		*/

		switch(RunStep)
		{
		case 0:
		{
           if(RunMs < 70)
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
							||Mid_ReadIR.ReadIR[0] ==0x8A||Mid_ReadIR.ReadIR[0] ==0xAA)
					        InitMotorForwardSlow();
							RunNoIRsenorTime=0;
							RunNoIRsenorLastStep=1;
					        RunStep=0x50;
				}
		
				else if(IRLocation.FarPreRight>0 ||IRLocation.FarRight>0 )
				{
                   if(Mid_ReadIR.ReadIR[0] ==0xAA || Mid_ReadIR.ReadIR[0]==0xA8 || Mid_ReadIR.ReadIR[0]==0x18){				   	     InitMotorForwardSlow();
						 RunStep=0x50;
				         InitMotorForwardSlow();
						
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
					if(Mid_ReadIR.ReadIR[0] ==0xA1 || Mid_ReadIR.ReadIR[0]==0X86||Mid_ReadIR.ReadIR[0]==0X58){
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
					
						 
						RunStep=0x47;
						RunMs = 0;

					
				}
				else if (Mid_ReadIR.ReadIR[0] ==0){

						Mid_ReadIR.ReadIR[0]=0;
		                w ++ ;
				        if(w==1){
							 RunStep=0x43; //CCW
							RunMs = 0;
				        }
						else{
							 RunStep=0x47; //CW
							RunMs = 0;
							w=0;
						}
				

				}
				ClearAllIR();
			}
		}
		break;
		
		break;
		

		case 0x43 ://CCW
               if(RunMs< 3){

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
		  
			 if(j ==1)
			   IRLocation.CloseList[0]=Mid_ReadIR.ReadIR[0];
			 else {
			     IRLocation.CloseList[1]=Mid_ReadIR.ReadIR[0];
				 j=0;
              }

             

			 if(IRLocation.irRightValue==1 && (IRLocation.CloseList[0]==0 && IRLocation.CloseList[1]==0))
			 {
				RunStep = 0x45; //line 
				RunMs = 0;
				IRLocation.irRightValue=0;

			 }
			 else {
			 if(IRLocation.CloseList[1] >IRLocation.CloseList[0]){

			 			RunStep = 0x45;//line run 
						RunMs = 0;
			           IRLocation.irLeftValue =1 ;
			   }
			 else if(IRLocation.CloseList[1] < IRLocation.CloseList[0]){

			 			RunStep = 0x47;//CW
						RunMs = 0;
             }
			 else if(IRLocation.CloseList[1] ==IRLocation.CloseList[0] && IRLocation.CloseList[0]!=0 ){
						RunStep = 0x45; //line 
						RunMs = 0;

			 }
			 
			 else if(IRLocation.CloseList[5] ==IRLocation.CloseList[1] && IRLocation.CloseList[1]!=0){
						RunStep = 0x45; //line 
						RunMs = 0;

			 }
			 else{

			     	  RunMs =0 ;
				      RunStep = 0x01;

				 }
			 	}        
                  


		break;

		case 45:  //line
			 if(RunMs< 10){

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
		      i++;
			 if(i ==1)
			   IRLocation.CloseList[2]=Mid_ReadIR.ReadIR[0];
			 else {
			     IRLocation.CloseList[3]=Mid_ReadIR.ReadIR[0];
				 i=0;
              }

                


			 if(IRLocation.CloseList[3] >IRLocation.CloseList[2]){

			 			RunStep = 0x45;
						RunMs = 0;
			 }
			 else if(IRLocation.CloseList[3] ==IRLocation.CloseList[2] && IRLocation.CloseList[2]!=0 ){
                    
                        IRLocation.NearMid++;
					    RunStep = 0x45;
						RunMs = 0;
						
			 }
			else{

			
			      RunMs =0 ;
				  RunStep = 0x01;//WT.EDIT 
			 
			}

		break;
		
		case 0x47 : //cw
               if(RunMs< 3){

                InitMotorRight();//CW 


			   }
			   else {

					RunMs =0 ;
					RunStep = 0x46;

               }


		break;




		case 0x48:
			   z++ ;
			 SetStop();
			 Delay_ms(500);
			 if(z ==1)
			   IRLocation.CloseList[4]=Mid_ReadIR.ReadIR[0];
			 else {
			     IRLocation.CloseList[5]=Mid_ReadIR.ReadIR[0];
				 z=0;
              }
			 
			 if(IRLocation.irLeftValue ==1 && (IRLocation.CloseList[4]==0||IRLocation.CloseList[5]==0 )){

                        RunStep = 0x45; //line 
						RunMs = 0;
			            IRLocation.irLeftValue =0;



			 }
             else {
			 if(IRLocation.CloseList[5] >IRLocation.CloseList[4]){

			 			RunStep = 0x45; //line 
						RunMs = 0;

             }
			
			 else if(IRLocation.CloseList[5] ==IRLocation.CloseList[4] && IRLocation.CloseList[4]!=0 ){
						RunStep = 0x45; //line 
						RunMs = 0;

			 }
		
			 else if(IRLocation.CloseList[5] <IRLocation.CloseList[4]){
			 	        RunStep = 0x43; //CW
						RunMs = 0;
			 			IRLocation.irRightValue=1;

			 }
			 else if(IRLocation.CloseList[5] ==IRLocation.CloseList[1] && IRLocation.CloseList[1]!=0){
						RunStep = 0x45; //line 
						RunMs = 0;

			 }
              else {
			            RunMs =0 ;
				        RunStep = 0x01;
             
                }
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
					InitMotorForwardRightSlow();
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
	
	
}
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
	static INT8U n;
  //  Mode=2;Step=0;RunMode=1;RunStep=0; ---default power on don't press key
	if(Key==1)
	{

		if(n!=1)
		{
			n=1;
			Mode =0; 
			cleanWorks.pressPowerKey++;
			Step=cleanWorks.pressPowerKey;
			SBUF =  Step;
			if(cleanWorks.pressPowerKey>5)cleanWorks.pressPowerKey=0;
		}

	
	}
    else if(Key==2){ //works mode ----cleaning button

          
               Mode =1;
		       cleanWorks.worksNumber++;
			   Step=cleanWorks.worksNumber  ;
			   SBUF =  Step;
			   if(cleanWorks.worksNumber>5)cleanWorks.worksNumber=0;
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
				n=0;

			}
			break;

        
		case 2:  //input standby mode
	            SetBuzzerTime(4);
			    Delay_ms(10);
				BuzzerOff();
                Mode =0x66;
			    LedGreenON();
				LedRedOff();
				n=0;

			
			break;
		case 3: //input recharge status 
               
				Mode =0x66;
			   
				SetBuzzerTime(4);
			    Delay_ms(10);
				BuzzerOff();

				LedGreenOff();
				LedRedOff();

				RunMode =2;
				RunStep=0;
				RunMs = 0;
				n=0;
				
				

			
			break;
			case  4: //power off 
				 Mode =0x66;
			
				SetBuzzerTime(4);
			    Delay_ms(10);
				BuzzerOff();
               LedGreenOff();
				LedRedON();
				n=0;


			
			break;
		
		
		  

		
		case 0x19:
		if(cleanWorks.CleanMode == standbyMode)  //  Mode=2;Step=0;RunMode=1;RunStep=0; ---default power on don't press key
		{
			if(Step==0)
			{
				//20
				Step=1;
				ADCtl=1;
				RunSecond=0;
			}
			else if(Step<20)
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
			//������ʾ��1����2��
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
             
			    Mode =0x66;
				SetBuzzerTime(4);
			    Delay_ms(10);
				BuzzerOff();
				LedRedOff();
				
		  }
		break;
		//��������ʱ���ƹ���Ƶ��2Hz

		case 3://zMode
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
		// ����еƹ�Ƶ�ￄ1�7?0.5Hz
		case 5: //fixPoint Mode
			
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
		//���粻��
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
	
