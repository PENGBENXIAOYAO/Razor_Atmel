/**********************************************************************************************************************
File: user_app1.c                                                                

----------------------------------------------------------------------------------------------------------------------
To start a new task using this user_app1 as a template:
 1. Copy both user_app1.c and user_app1.h to the Application directory
 2. Rename the files yournewtaskname.c and yournewtaskname.h
 3. Add yournewtaskname.c and yournewtaskname.h to the Application Include and Source groups in the IAR project
 4. Use ctrl-h (make sure "Match Case" is checked) to find and replace all instances of "user_app1" with "yournewtaskname"
 5. Use ctrl-h to find and replace all instances of "UserApp1" with "YourNewTaskName"
 6. Use ctrl-h to find and replace all instances of "USER_APP1" with "YOUR_NEW_TASK_NAME"
 7. Add a call to YourNewTaskNameInitialize() in the init section of main
 8. Add a call to YourNewTaskNameRunActiveState() in the Super Loop section of main
 9. Update yournewtaskname.h per the instructions at the top of yournewtaskname.h
10. Delete this text (between the dashed lines) and update the Description below to describe your task
----------------------------------------------------------------------------------------------------------------------

Description:
This is a user_app1.c file template 

------------------------------------------------------------------------------------------------------------------------
API:

Public functions:


Protected System functions:
void UserApp1Initialize(void)
Runs required initialzation for the task.  Should only be called once in main init section.

void UserApp1RunActiveState(void)
Runs current task state.  Should only be called once in main loop.


**********************************************************************************************************************/

#include "configuration.h"

/***********************************************************************************************************************
Global variable definitions with scope across entire project.
All Global variable names shall start with "G_UserApp1"
***********************************************************************************************************************/
/* New variables */
volatile u32 G_u32UserApp1Flags;                       /* Global state flags */


/*--------------------------------------------------------------------------------------------------------------------*/
/* Existing variables (defined in other files -- should all contain the "extern" keyword) */
extern volatile u32 G_u32SystemFlags;                  /* From main.c */
extern volatile u32 G_u32ApplicationFlags;             /* From main.c */

extern volatile u32 G_u32SystemTime1ms;                /* From board-specific source file */
extern volatile u32 G_u32SystemTime1s;                 /* From board-specific source file */

extern u8 G_u8DebugScanfCharCount;
bool   bRunFlag=TRUE;
/***********************************************************************************************************************
Global variable definitions with scope limited to this local application.
Variable names shall start with "UserApp1_" and be declared as static.
***********************************************************************************************************************/
static fnCode_type UserApp1_StateMachine;            /* The state machine function pointer */
//static u32 UserApp1_u32Timeout;                      /* Timeout counter used across states */


/**********************************************************************************************************************
Function Definitions
**********************************************************************************************************************/

/*--------------------------------------------------------------------------------------------------------------------*/
/* Public functions                                                                                                   */
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/
/* Protected functions                                                                                                */
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------
Function: UserApp1Initialize

Description:
Initializes the State Machine and its variables.

Requires:
  -

Promises:
  - 
*/
void UserApp1Initialize(void)
{
 	LedOff(WHITE);
	LedOff(PURPLE);
	LedOff(BLUE);
	LedOff(CYAN);
	LedOff(GREEN);
	LedOff(YELLOW);
	LedOff(ORANGE);
	LedOff(RED);
	PWMAudioSetFrequency(BUZZER1,200);
	PWMAudioOff(BUZZER1);
 
  /* If good initialization, set state to Idle */
  if( 1 )
  {
    UserApp1_StateMachine = UserApp1SM_Idle;
  }
  else
  {
    /* The task isn't properly initialized, so shut it down and don't run */
    UserApp1_StateMachine = UserApp1SM_Error;
  }

} /* end UserApp1Initialize() */

  
/*----------------------------------------------------------------------------------------------------------------------
Function UserApp1RunActiveState()

Description:
Selects and runs one iteration of the current state in the state machine.
All state machines have a TOTAL of 1ms to execute, so on average n state machines
may take 1ms / n to execute.

Requires:
  - State machine function pointer points at current state

Promises:
  - Calls the function to pointed by the state machine function pointer
*/
void UserApp1RunActiveState(void)
{
  UserApp1_StateMachine();

} /* end UserApp1RunActiveState */


/*--------------------------------------------------------------------------------------------------------------------*/
/* Private functions                                                                                                  */
/*--------------------------------------------------------------------------------------------------------------------*/
void UserApp1_state1(void)
{
	u8 u8String1[]="Entering state 1";

	DebugPrintf(u8String1);
	DebugLineFeed();
	u8 au8Message[] = "STATE 1";
	LCDCommand(LCD_CLEAR_CMD);
	LCDMessage(LINE1_START_ADDR, au8Message);
	LedOn(WHITE);
	LedOn(PURPLE);
	LedOn(BLUE);
	LedOn(CYAN);
	LedOff(GREEN);
	LedOff(YELLOW);
	LedOff(ORANGE);
	LedOff(RED);
	LedPWM(LCD_RED, LED_PWM_100);
	LedPWM(LCD_BLUE, LED_PWM_100);
	LedPWM(LCD_GREEN, LED_PWM_0);
	
	PWMAudioOff(BUZZER1);
    bRunFlag=TRUE;




	UserApp1_StateMachine=UserApp1SM_Idle;
}

void UserApp1_state2(void)
{
     
    u8 u8String2[]="Entering state 2";
	
	static u32 u32Time=0;
	
	u32Time++;
	
    if(bRunFlag)
	{
		DebugPrintf(u8String2);
		DebugLineFeed();
		u8 au8Message[] = "STATE 2";
		LCDCommand(LCD_CLEAR_CMD);
		LCDMessage(LINE1_START_ADDR, au8Message);
		LedBlink(GREEN, LED_2HZ);
		LedBlink(YELLOW, LED_2HZ);
		LedBlink(ORANGE, LED_4HZ);
		LedBlink(RED, LED_2HZ);
		LedOff(WHITE);
		LedOff(PURPLE);
		LedOff(BLUE);
		LedOff(CYAN);
	
		LedPWM(LCD_RED, LED_PWM_100);
		LedPWM(LCD_BLUE, LED_PWM_0);
		LedPWM(LCD_GREEN, LED_PWM_50);
		
		bRunFlag=FALSE;
	}
    
	if(u32Time==100)
	{
      PWMAudioOff(BUZZER1);
	}
	
	if(u32Time==1000)
	{
      PWMAudioOn(BUZZER1);
	  u32Time=0;
	}
    
	
	UserApp1_StateMachine=UserApp1SM_Idle;
   
}

/**********************************************************************************************************************
State Machine Function Definitions
**********************************************************************************************************************/

/*-------------------------------------------------------------------------------------------------------------------*/
/* Wait for ??? */
static void UserApp1SM_Idle(void)
{
	static bool bFlag1=FALSE;
	static bool bFlag2=FALSE;
	static u8 u8Count1=0;
	static u8 u8Count2=0;
	
	static u8 au8buffer[1]=0;
	
	
	
	if(G_u8DebugScanfCharCount==1)
	{
	  DebugScanf(au8buffer);
	  u8Count1++;
	  u8Count2++;
	}
	
	if(u8Count1==1)
	{
	  if(au8buffer[0]!='1')
	  {
		u8Count1=0;
		bFlag1=FALSE;
	  }	
	}
	
	if(u8Count1==2)
	{
	  if(au8buffer[0]!='\r')
	  {
		u8Count1=0;
		bFlag1=FALSE;
	  }
	  else
	  {
		bFlag1=TRUE;
		u8Count1=0;
	  }
	}
	
	if(u8Count2==1)
	{
	  if(au8buffer[0]!='2')
	  {
		u8Count2=0;
		bFlag2=FALSE;
	  }	
	}
	
	if(u8Count2==2)
	{
	  if(au8buffer[0]!='\r')
	  {
		u8Count2=0;
		bFlag2=FALSE;
	  }
	  else
	  {
		bFlag2=TRUE;
		u8Count2=0;
	  }
	}
	
	
	
    
    if(WasButtonPressed(BUTTON1)||bFlag1)
	{
		ButtonAcknowledge(BUTTON1);
		UserApp1_StateMachine=UserApp1_state1;
		bFlag1=FALSE;
		bFlag2=FALSE;
	}
	
	if(WasButtonPressed(BUTTON2))
	{
	  ButtonAcknowledge(BUTTON2);
	  bFlag2=TRUE;
	}

	if(bFlag2)
	{
		UserApp1_StateMachine=UserApp1_state2;
	}
} /* end UserApp1SM_Idle() */
		

/*-------------------------------------------------------------------------------------------------------------------*/
/* Handle an error */
static void UserApp1SM_Error(void)          
{
	
} /* end UserApp1SM_Error() */



/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */
/*--------------------------------------------------------------------------------------------------------------------*/
