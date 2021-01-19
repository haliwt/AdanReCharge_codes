#include "lb_key.h"
#include "lb_ir.h"
#include "..\lib\LB_Run.h"
#include "..\lib\LB_Led.h"
#include "..\lib\LB_Motor.h"
#include "..\lib\LB_AD.h"
xdata struct _CleanMode cleanWorks;
/****************************************************
	*
	*Function Name: INT8U AutoDC_ReChargeStatus(void)
	*Function :
	*Inpute Ref: NO
	*Return Ref: battery is full electric quantiy value
	*            1 --full quantiy  0- no full
	*
*****************************************************/
INT8U AutoDC_ReChargeStatus(void)
{
    static INT8U full=0;
	if(Auto_DCCharge ==1 || DC_Recharge  ==1 ){//�س�͵�Դ������DC�����⣬û������??
	     
		 	SysFlag = 0xff;	
            SetStop();
			RunMode = 1;
			RunStep = 0;
		    SetFan(0);
			SetEdge(0);	
		    	     
       if(BatteryRechargStatus ==1){
			   LedRedOff();
			   LedGreenON();
	           Delay_ms(1000);
               full ++ ;
			   if(full > 250)full =11;
               if(full==10){
			   	    InitMotorRetreat();
				    Delay_ms(500);
					SetStop();
					RunMode = 0;
					RunStep = 0;
					SetBuzzerTime(4);
					Delay_ms(10);
					BuzzerOff();
		            SetFan(0);  //WT.EDIT 
					SetEdge(0);	 //WT.EDIT 	
					ADCtl=0;
					SysFlag = IDEL;

                }
			   
	          return 1;
		}
		else if(twinkle < 1 ){
				 LedRedOff();
				 LedGreenOff();
				 full=0;
		}
		else{
				 if(twinkle > 2)twinkle =0;
				 LedGreenOff();
				 LedRedON();
				 ful=0;
		}			
		return 1;
	}
	else 
		return 0;
}

/****************************************************
	*
	*Function Name: INT8U AutoDC_ReChargeStatus(void)
	*Function :
	*Inpute Ref: NO
	*Return Ref: battery is full electric quantiy value
	*            1 --full quantiy  0- no full
	*
*****************************************************/
void ItselfChecking(void)
{
   
      	switch(RunStep)
		{
		case 0:
		{
              RunStep =1;
			  RunMs =0 ;
		}
		break;
		case 1:
		{
			if(RunMs<20){

				InitMotorForward();
				RunMs=0;
				RunStep=6;
			}
		}
		break;

		case 2:
			if(RunMs>500)
			{
				InitMotorLeft();
				RunMs=0;
				RunStep=3;
			}

		break;

		case 3:
			if(RunMs>500)
			{
				InitMotorRight();
				RunMs=0;
				RunStep=3;
			}

		break;

		default:

		break;

}
		}


