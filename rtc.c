#include "rtc.h"

void RTC_init(void){
	
	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);
    PWR_BackupAccessCmd(ENABLE);
    
    RCC_LSEConfig(RCC_LSE_ON);
    while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET);

    RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
    RCC_RTCCLKCmd(ENABLE);

    RTC_WaitForSynchro();
    RTC_WaitForLastTask();

    RTC_ITConfig(RTC_IT_SEC, ENABLE);
    RTC_WaitForLastTask();
		
    RTC_EnterConfigMode();
    RTC_SetPrescaler(32767);
    RTC_WaitForLastTask();
    RTC_ExitConfigMode();
		NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
	
		GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
} 

void delay_ms(uint32_t milliseconds) {
    uint32_t i, j;
    for (i = 0; i < milliseconds; i++) {
        for (j = 0; j < 24000; j++) {
        }
    }
}

uint32_t RTC_GetRTC_Counter(RTC_DateTimeTypeDef* RTC_DateTimeStruct) {
	uint8_t a;
	uint16_t y;
	uint8_t m;
	uint32_t JDN;

	a=(14-RTC_DateTimeStruct->RTC_Month)/12;
	y=RTC_DateTimeStruct->RTC_Year+4800-a;
	m=RTC_DateTimeStruct->RTC_Month+(12*a)-3;

	JDN=RTC_DateTimeStruct->RTC_Date;
	JDN+=(153*m+2)/5;
	JDN+=365*y;
	JDN+=y/4;
	JDN+=-y/100;
	JDN+=y/400;
	JDN = JDN -32045;
	JDN = JDN - JULIAN_DATE_BASE;
	JDN*=86400;
	JDN+=(RTC_DateTimeStruct->RTC_Hours*3600);
	JDN+=(RTC_DateTimeStruct->RTC_Minutes*60);
	JDN+=(RTC_DateTimeStruct->RTC_Seconds);

	return JDN;
}

void RTC_GetDateTime(uint32_t RTC_Counter, RTC_DateTimeTypeDef* RTC_DateTimeStruct) {
	unsigned long time;
	unsigned long t1, a, b, c, d, e, m;
	int year = 0;
	int mon = 0;
	int wday = 0;
	int mday = 0;
	int hour = 0;
	int min = 0;
	int sec = 0;
	uint64_t jd = 0;
	uint64_t jdn = 0;

	jd = ((RTC_Counter+43200)/(86400>>1)) + (2440587<<1) + 1;
	jdn = jd>>1;

	time = RTC_Counter;
	t1 = time/60;
	sec = time - t1*60;

	time = t1;
	t1 = time/60;
	min = time - t1*60;

	time = t1;
	t1 = time/24;
	hour = time - t1*24;

	wday = jdn%7;

	a = jdn + 32044;
	b = (4*a+3)/146097;
	c = a - (146097*b)/4;
	d = (4*c+3)/1461;
	e = c - (1461*d)/4;
	m = (5*e+2)/153;
	mday = e - (153*m+2)/5 + 1;
	mon = m + 3 - 12*(m/10);
	year = 100*b + d - 4800 + (m/10);

	RTC_DateTimeStruct->RTC_Year = year;
	RTC_DateTimeStruct->RTC_Month = mon;
	RTC_DateTimeStruct->RTC_Date = mday;
	RTC_DateTimeStruct->RTC_Hours = hour;
	RTC_DateTimeStruct->RTC_Minutes = min;
	RTC_DateTimeStruct->RTC_Seconds = sec;
	RTC_DateTimeStruct->RTC_Wday = wday;
}
