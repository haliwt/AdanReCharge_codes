#include "lb_key.h"
#include "lb_ir.h"
#include "..\lib\LB_Run.h"
#include "..\lib\LB_Led.h"
#include "..\lib\LB_Motor.h"
/****************************************************
	*
	*Function Name: uint8_t HDKey_Scan(uint8_t mode)
	*Function :
	*Inpute Ref: 0 ---不支持连续按键
	*Return Ref: 0 --没有按键按下， 1---有按键按下
	*
*****************************************************/
INT8U HDKey_Scan(INT8U mode)
{
	
		static INT8U key_up=1;	 //°´¼üËÉ¿ª±êÖ¾
		if(mode==1)key_up=1;	// 支持连续按键
    if(key_up&&(Power_Key==1||Cleaning_Key==1)){
       Delay_ms(20);
       key_up =0 ;
       if((Power_Key== 0) && Cleaning_Key ==0)  return GROUP_PRES ;
	    else if (Cleaning_Key ==0) return CLEANING_PRES;
		
        else if(Power_Key== 0)  return POWER_PRES;

       }
     else if(Power_Key==0 && Cleaning_Key==0 )key_up=1;
		return 0;	//没有按键按下
}


/*****************************************************************************/
void Decoder_KEY(INT8U value)
{
   static INT8U keyLock;
	switch(value){

		       case 0:


			   break; 
			   case 1: 
			        SetStop();
					LedGreenON();
					SetBuzzerTime(10);
					Delay_ms(200);
					SetBuzzerTime(0);
					Delay_ms(200);
					SetBuzzerTime(10);
					Delay_ms(20);
					BuzzerOff();
					cleanWorks.iPowerFlag =1;

			   break;
 
			   case 2: 
			            keyLock++ ;
						if(keyLock ==1)cleanWorks.CleanMode=runWoksStatus;
						else if(keyLock ==2)cleanWorks.CleanMode=randomMode;
			           else if(keyLock ==3)cleanWorks.CleanMode=3;
					   else if(keyLock ==4)cleanWorks.CleanMode=4;
					   if(keyLock ==5)keyLock =0;
						
			   break;

			  
			  
		   }
}


void CleanMode_Run(void)
{
     
	if(cleanWorks.iPowerFlag ==1){
	 switch(cleanWorks.CleanMode){

        case 0:

			cleanWorks.CleanMode= 0x64;

		break;
	    
		
		case runWoksStatus :  //1

			SetBuzzerTime(4);
			Delay_ms(50);
			BuzzerOff();
			LedGreenON();
		  
cleanWorks.CleanMode= 0x64;
		break;

       case randomMode: //2
	      SetBuzzerTime(4);
		Delay_ms(50);
		BuzzerOff();
		LedGreenON();
cleanWorks.CleanMode= 0x64;
	   break;

	   case zMode ://3

	      	SetBuzzerTime(4);
			Delay_ms(50);
			SetBuzzerTime(0);
			Delay_ms(50);
			SetBuzzerTime(4);
			BuzzerOff();
			LedGreenOff();
			cleanWorks.CleanMode= 0x64;

	   break;

	   case bowMode: //4
	      SetBuzzerTime(4);
							Delay_ms(50);
							SetBuzzerTime(0);
							Delay_ms(50);
							SetBuzzerTime(4);
							Delay_ms(50);
							SetBuzzerTime(0);
							Delay_ms(50);
							SetBuzzerTime(4);
							BuzzerOff();
							 LedGreenON();
							 cleanWorks.CleanMode= 0x64;

	   break;

	   case fixpointMode:  //5
	       SetBuzzerTime(4);
							Delay_ms(50);
							SetBuzzerTime(0);
							Delay_ms(50);
							SetBuzzerTime(4);
							Delay_ms(50);
							SetBuzzerTime(0);
							Delay_ms(50);
							SetBuzzerTime(4);
							Delay_ms(50);
							SetBuzzerTime(0);
							Delay_ms(50);
							SetBuzzerTime(4);
							BuzzerOff();
			
							LedGreenOff();
							Delay_ms(200);
							LedGreenON();
							cleanWorks.CleanMode= 0x64;
						
	       break;




	 }
 }
	 else{
       BuzzerOff();


	 }





}