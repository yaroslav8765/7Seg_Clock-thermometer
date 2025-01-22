#include "main.h"
#include "sevenSegmentDisplay.h"
#include "rtc.h"
#include "buttonDebounce.h"
//#include "I2C.h"
static RTC_DateTimeTypeDef	RTC_DateTime;
static uint32_t RTC_Counter = 0;
static button_state butt_state_time_plus = BTN_UNPUSH;
static button_state butt_state_time_minus = BTN_UNPUSH;
static button_state butt_state_time_select = BTN_UNPUSH;
static button_state butt_state_switch_mode = BTN_UNPUSH;

long temperature = 0;
long pressure = 0;  //unused

typedef enum{
	TIME = 1,
	DATE = 2,
	YEAR = 3,
	TEMPERATURE = 4,
	PRESSURE = 5,
}clockMode;

struct button_debounce_parametrs butt_parametrs_time_plus;
clockMode Mode = TIME;


int main(){
	initSevenSegmentDisplayPins();
	tim2Init();
	tim3init();
	init_buttons();
	RTC_init();
	

//	I2C1_Init();
//	BMP280_Init();
	butt_parametrs_time_plus.butt_count_to_min = 10;
	butt_parametrs_time_plus.butt_count_to_max = 50;
	butt_parametrs_time_plus.butt_counter = 0;
	butt_parametrs_time_plus.butt_count_to = 10;  //Zaulupa, peredelat
	RTC_DateTime.RTC_Date = 22;
		RTC_DateTime.RTC_Month = 9;
		RTC_DateTime.RTC_Year = 2016;

		RTC_DateTime.RTC_Hours = 14;
		RTC_DateTime.RTC_Minutes = 30;
		RTC_DateTime.RTC_Seconds = 00;

		// ????? ????????????? ???????? ????????. ??? ??? ??? ?? ??????????????.
		delay_ms(500);
		RTC_SetCounter(RTC_GetRTC_Counter(&RTC_DateTime));
	while(1){

		RTC_Counter = RTC_GetCounter();
		RTC_GetDateTime(RTC_Counter, &RTC_DateTime);
	}
}


void TIM2_IRQHandler(void) { 
	debounceButton(GPIOA, GPIO_Pin_0,&butt_parametrs_time_plus, &butt_state_time_plus);
	debounceButton(GPIOA, GPIO_Pin_1,&butt_parametrs_time_plus, &butt_state_time_minus);
	debounceButton(GPIOA, GPIO_Pin_4,&butt_parametrs_time_plus, &butt_state_time_select);
	debounceButton(GPIOA, GPIO_Pin_2,&butt_parametrs_time_plus, &butt_state_switch_mode);
	switch (Mode){
		case TIME:
			writeTo7SegDisplay(((RTC_DateTime.RTC_Minutes*100) + (RTC_DateTime.RTC_Seconds)));
			//writeTo7SegDisplay(4567);
			dynamicIndication();
		break;
		
		case DATE:
			writeTo7SegDisplay(((RTC_DateTime.RTC_Date*100) + (RTC_DateTime.RTC_Month)));
			dynamicIndication();
		break;
		
		case YEAR:
			writeTo7SegDisplay(RTC_DateTime.RTC_Year);
			dynamicIndication();
		break;
		
		case TEMPERATURE:
			if(temperature>100){
				writeTo7SegDisplay((int32_t)temperature*10);
			}
			else if(temperature<100 && temperature > 0){
				writeTo7SegDisplay((int32_t)temperature*100);
			}
			else if(temperature<=(-1) && temperature > (-10)){
				writeTo7SegDisplay((int32_t)temperature*(-100));
			}
			else if(temperature<(-10) && temperature > (-100)){
				writeTo7SegDisplay((int32_t)temperature*(-100));
			}
			else if(temperature<(-100)){
				writeTo7SegDisplay((int32_t)temperature*(-10));
			}
			else{
				writeTo7SegDisplay((int32_t)abs(temperature));
			}
			dynamicIndicationForTemperature((int32_t)temperature);
		break;
			
		case PRESSURE:
			Mode = TIME;
		break;
		}    

	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
}

void TIM3_IRQHandler(void) { 
	if((butt_state_time_plus == BTN_PUSHED)||(butt_state_time_minus == BTN_PUSHED)||(butt_state_switch_mode == BTN_PUSHED)){
	TIM3->ARR = 18000;
		if(butt_state_time_plus == BTN_PUSHED && butt_state_time_select == BTN_PUSHED){
			switch (Mode){
				case TIME:
					RTC_DateTime.RTC_Hours ++;
					RTC_DateTime.RTC_Seconds = 0;
					RTC_SetCounter(RTC_GetRTC_Counter(&RTC_DateTime));
				break;
				
				case DATE:
					RTC_DateTime.RTC_Date ++;
					RTC_SetCounter(RTC_GetRTC_Counter(&RTC_DateTime));
				break;
				
				case YEAR:
					RTC_DateTime.RTC_Year ++;
					RTC_SetCounter(RTC_GetRTC_Counter(&RTC_DateTime));
				break;
				
				case TEMPERATURE:
					//change PWM
				break;
				
				case PRESSURE:
					//change PWM
				break;		
				
				}
		}else if(butt_state_time_minus == BTN_PUSHED && butt_state_time_select == BTN_PUSHED){
			switch (Mode){
				case TIME:
					if(RTC_DateTime.RTC_Hours ==0){
						RTC_DateTime.RTC_Hours = 23;
						RTC_DateTime.RTC_Seconds = 0;
					}else{
						RTC_DateTime.RTC_Hours --;
						RTC_DateTime.RTC_Seconds = 0;
						RTC_SetCounter(RTC_GetRTC_Counter(&RTC_DateTime));
					}
				break;
				
				case DATE:
					RTC_DateTime.RTC_Date --;
					RTC_SetCounter(RTC_GetRTC_Counter(&RTC_DateTime));
				break;
				
				case YEAR:
					RTC_DateTime.RTC_Year --;
					RTC_SetCounter(RTC_GetRTC_Counter(&RTC_DateTime));
				break;
				
				case TEMPERATURE:
					//change PWM
				break;
				
				case PRESSURE:
					//change PWM
				break;			
				
			}
		}else if(butt_state_time_plus == BTN_PUSHED && butt_state_time_select == BTN_UNPUSH){
			switch (Mode){
				case TIME:
					RTC_DateTime.RTC_Minutes ++;
					RTC_DateTime.RTC_Seconds = 0;
					RTC_SetCounter(RTC_GetRTC_Counter(&RTC_DateTime));
				break;
				
				case DATE:
					RTC_DateTime.RTC_Month ++;
					RTC_SetCounter(RTC_GetRTC_Counter(&RTC_DateTime));
				break;
				
				case YEAR:
					RTC_DateTime.RTC_Year ++;
					RTC_SetCounter(RTC_GetRTC_Counter(&RTC_DateTime));
				break;
				
				case TEMPERATURE:
					//change PWM
				break;
				
				case PRESSURE:
					//change PWM
				break;			
				
			}
		}else if(butt_state_time_minus == BTN_PUSHED && butt_state_time_select == BTN_UNPUSH){
			switch (Mode){
				case TIME:
					RTC_DateTime.RTC_Minutes --;
					RTC_DateTime.RTC_Seconds = 0;
					RTC_SetCounter(RTC_GetRTC_Counter(&RTC_DateTime));
				break;
				
				case DATE:
					RTC_DateTime.RTC_Month --;
					RTC_SetCounter(RTC_GetRTC_Counter(&RTC_DateTime));
				break;
				
				case YEAR:
					RTC_DateTime.RTC_Year --;
					RTC_SetCounter(RTC_GetRTC_Counter(&RTC_DateTime));
				break;
				
				case TEMPERATURE:
					//change PWM
				break;
				
				case PRESSURE:
					//change PWM
				break;	
				
			}
		}else if(butt_state_switch_mode == BTN_PUSHED){
			if (Mode >= PRESSURE) {
				Mode = TIME;
			}else{
				Mode ++;
			}
		}
	}
	else{ 
		TIM3->ARR = 1500;
	}
  TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
}

void RTC_IRQHandler(void){
	if (RTC_GetITStatus(RTC_IT_SEC) != RESET) {
      RTC_ClearITPendingBit(RTC_IT_SEC); 
			//bmp280Convert(&temperature, &pressure);
		if(Mode == TIME){
			GPIO_TogglePin(GPIOA, GPIO_Pin_3);
		}
		else{
			GPIO_SetBits(GPIOA, GPIO_Pin_3);
		}
	}
    RTC_WaitForLastTask(); 
}




void GPIO_TogglePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin) {
    if (GPIO_ReadOutputDataBit(GPIOx, GPIO_Pin)) {
        GPIO_ResetBits(GPIOx, GPIO_Pin);
    } else {
        GPIO_SetBits(GPIOx, GPIO_Pin);
    }
}


void init_buttons(void) {
    GPIO_InitTypeDef pin;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    pin.GPIO_Mode = GPIO_Mode_IPU;
    pin.GPIO_Pin = GPIO_Pin_0;
    pin.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOA, &pin);
    pin.GPIO_Pin = GPIO_Pin_1;
    GPIO_Init(GPIOA, &pin);
	  pin.GPIO_Pin = GPIO_Pin_2;
    GPIO_Init(GPIOA, &pin);
	  pin.GPIO_Pin = GPIO_Pin_4;
    GPIO_Init(GPIOA, &pin);
}


void tim2Init(void){
		TIM_TimeBaseInitTypeDef timer;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    TIM_TimeBaseStructInit(&timer);
    timer.TIM_Prescaler = 720 - 1;
    timer.TIM_Period = 300;
    TIM_TimeBaseInit(TIM2, &timer);
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
    TIM_Cmd(TIM2, ENABLE);
    
    NVIC_EnableIRQ(TIM2_IRQn);
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}


void tim3init(void) {
    TIM_TimeBaseInitTypeDef timer;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    TIM_TimeBaseStructInit(&timer);
    timer.TIM_Prescaler = 720 - 1; // 100,000
    timer.TIM_Period = 1500;
    TIM_TimeBaseInit(TIM3, &timer);
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
    TIM_Cmd(TIM3, ENABLE);
    
    NVIC_EnableIRQ(TIM3_IRQn);
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

