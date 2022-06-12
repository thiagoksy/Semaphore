#include <stdint.h>

//**********************************Assembly Function Prototype**********************************
void PLL_Init(void);
void SysTick_Init(void);
void SysTick_Wait1ms(uint32_t delay);
void GPIO_Init(void);

//*********************************Port Functions Prototype**********************************
uint32_t PortJ_Input(void);
void PortN_Output(uint32_t leds);
void PortF_Output(uint32_t leds);

#define temp1 1000 //1s
#define temp2 2000 //2s
#define temp6 6000 //6s

#define tempPisca 5000 //5s
#define tempLed 100 //0.1s


//**************************DEFINES S1**************************
#define S1_yellow 0x01// 0001
#define S1_green 0x02 // 0010
#define S1_red 0x03   // 0011


//**************************DEFINES S2**************************
#define S2_yellow 0x01// 00 0001
#define S2_green 0x010 // 1 0000
#define S2_red 0x11   // 1 0001


typedef enum states
{
	OFF,
	ON
}stt;
int flag = OFF;

void acende_led(int S1, int S2, int delay_1)
{
	PortN_Output(S1);
	PortF_Output(S2);
	SysTick_Wait1ms(delay_1);
}

void change_flag()
{
	 flag = ON;
}

void pisca_leds()
{
	for(int i=0; i<((tempPisca/tempLed)/2);i++)
	{
		//Led1 e Led3
		PortN_Output(S1_yellow); 				 //0001
		PortF_Output(S2_yellow); 				 //00 0001
		SysTick_Wait1ms(tempLed);
		
		
		//Led2 e Led4
		PortN_Output(S1_green);   		//0010
		PortF_Output(S2_green);       //10 0000
		SysTick_Wait1ms(tempLed);
	}
}


int main(void)
{
	PLL_Init();
	SysTick_Init();
	GPIO_Init();
	int state = 1;

	
	while(1)
	{
		switch (state)
		{
			case 1:
			{
				if(flag == ON)
				{
					pisca_leds();
					break;
				}
				else
				{
					acende_led(S1_red, S2_red, temp1);
					break;
				}
			}
		  case 2:
			{
				flag = OFF;
				acende_led(S1_red,S2_green,temp6);
				break;
			}	
			case 3:
			{
				acende_led(S1_red, S2_yellow,temp2);
				break;
			}	
			case 4:
			{
				acende_led(S1_red, S2_red, temp1);
				break;
			}	
			case 5:
			{
				acende_led(S1_green, S2_red, temp6);
				break;
			}	
			case 6:
		  {
				acende_led(S1_yellow,S2_red, temp2);
				state = 0;
				break;
			}
		}
		state++;
		
	}
}
