#include "main.h"
#include "sevenSegmentDisplay.h"



static volatile uint8_t num = 1;
static volatile unsigned int numbers[10] = { 0x3f, 0x6, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x7, 0x7f, 0x6f};
static volatile unsigned int numbers_with_dot[10] = { 
    0xBF,
    0x86, 
    0xDB,
    0xCF, 
    0xE6,
    0xED, 
    0xFD,
    0x87, 
    0xFF,
    0xEF 
};

 uint8_t out7SegDisplay[4] = {1,2,3,4};
uint8_t animationCount = 0;


void initSevenSegmentDisplayPins(void) {
    RCC_APB2PeriphClockCmd(SEGMENT_A_RCC, ENABLE);
    RCC_APB2PeriphClockCmd(SEGMENT_B_RCC, ENABLE);
    RCC_APB2PeriphClockCmd(SEGMENT_C_RCC, ENABLE);
    RCC_APB2PeriphClockCmd(SEGMENT_D_RCC, ENABLE);
    RCC_APB2PeriphClockCmd(SEGMENT_E_RCC, ENABLE);
    RCC_APB2PeriphClockCmd(SEGMENT_F_RCC, ENABLE);
    RCC_APB2PeriphClockCmd(SEGMENT_G_RCC, ENABLE);
    RCC_APB2PeriphClockCmd(SEGMENT_DP_RCC, ENABLE);
    RCC_APB2PeriphClockCmd(DIGIT_1_RCC, ENABLE);
    RCC_APB2PeriphClockCmd(DIGIT_2_RCC, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Pin = SEGMENT_A_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(SEGMENT_A_GPIO, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = SEGMENT_B_PIN;
    GPIO_Init(SEGMENT_B_GPIO, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = SEGMENT_C_PIN;
    GPIO_Init(SEGMENT_C_GPIO, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = SEGMENT_D_PIN;
    GPIO_Init(SEGMENT_D_GPIO, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = SEGMENT_E_PIN;
    GPIO_Init(SEGMENT_E_GPIO, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = SEGMENT_F_PIN;
    GPIO_Init(SEGMENT_F_GPIO, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = SEGMENT_G_PIN;
    GPIO_Init(SEGMENT_G_GPIO, &GPIO_InitStructure);
		
    GPIO_InitStructure.GPIO_Pin = SEGMENT_DP_PIN;
    GPIO_Init(SEGMENT_DP_GPIO, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = DIGIT_1_PIN;
    GPIO_Init(DIGIT_1_GPIO, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = DIGIT_2_PIN;
    GPIO_Init(DIGIT_2_GPIO, &GPIO_InitStructure);
		
		GPIO_InitStructure.GPIO_Pin = DIGIT_3_PIN;
    GPIO_Init(DIGIT_3_GPIO, &GPIO_InitStructure);
		
		GPIO_InitStructure.GPIO_Pin = DIGIT_4_PIN;
    GPIO_Init(DIGIT_4_GPIO, &GPIO_InitStructure);
}

void write_number(uint8_t number) {
    GPIO_WriteBit(SEGMENT_A_GPIO, SEGMENT_A_PIN, TST_BIT(~numbers[number], 0));
    GPIO_WriteBit(SEGMENT_B_GPIO, SEGMENT_B_PIN, TST_BIT(~numbers[number], 1));
    GPIO_WriteBit(SEGMENT_C_GPIO, SEGMENT_C_PIN, TST_BIT(~numbers[number], 2));
    GPIO_WriteBit(SEGMENT_D_GPIO, SEGMENT_D_PIN, TST_BIT(~numbers[number], 3));
    GPIO_WriteBit(SEGMENT_E_GPIO, SEGMENT_E_PIN, TST_BIT(~numbers[number], 4));
    GPIO_WriteBit(SEGMENT_F_GPIO, SEGMENT_F_PIN, TST_BIT(~numbers[number], 5));
    GPIO_WriteBit(SEGMENT_G_GPIO, SEGMENT_G_PIN, TST_BIT(~numbers[number], 6));
		GPIO_WriteBit(SEGMENT_DP_GPIO, SEGMENT_DP_PIN, TST_BIT(~numbers[number], 7));
}

void write_number_with_dot(uint8_t number) {
    GPIO_WriteBit(SEGMENT_A_GPIO, SEGMENT_A_PIN, TST_BIT(~numbers_with_dot[number], 0));
    GPIO_WriteBit(SEGMENT_B_GPIO, SEGMENT_B_PIN, TST_BIT(~numbers_with_dot[number], 1));
    GPIO_WriteBit(SEGMENT_C_GPIO, SEGMENT_C_PIN, TST_BIT(~numbers_with_dot[number], 2));
    GPIO_WriteBit(SEGMENT_D_GPIO, SEGMENT_D_PIN, TST_BIT(~numbers_with_dot[number], 3));
    GPIO_WriteBit(SEGMENT_E_GPIO, SEGMENT_E_PIN, TST_BIT(~numbers_with_dot[number], 4));
    GPIO_WriteBit(SEGMENT_F_GPIO, SEGMENT_F_PIN, TST_BIT(~numbers_with_dot[number], 5));
    GPIO_WriteBit(SEGMENT_G_GPIO, SEGMENT_G_PIN, TST_BIT(~numbers_with_dot[number], 6));
	  GPIO_WriteBit(SEGMENT_DP_GPIO, SEGMENT_DP_PIN, TST_BIT(~numbers_with_dot[number], 7));

}

void write_minus(void) {
    GPIO_WriteBit(SEGMENT_A_GPIO, SEGMENT_A_PIN, 1);
    GPIO_WriteBit(SEGMENT_B_GPIO, SEGMENT_B_PIN, 1);
    GPIO_WriteBit(SEGMENT_C_GPIO, SEGMENT_C_PIN, 1);
    GPIO_WriteBit(SEGMENT_D_GPIO, SEGMENT_D_PIN, 1);
    GPIO_WriteBit(SEGMENT_E_GPIO, SEGMENT_E_PIN, 1);
    GPIO_WriteBit(SEGMENT_F_GPIO, SEGMENT_F_PIN, 1);
    GPIO_WriteBit(SEGMENT_G_GPIO, SEGMENT_G_PIN, 0);
	  GPIO_WriteBit(SEGMENT_DP_GPIO, SEGMENT_DP_PIN, 1);
}

void write_o(void) {
    GPIO_WriteBit(SEGMENT_A_GPIO, SEGMENT_A_PIN, 0);
    GPIO_WriteBit(SEGMENT_B_GPIO, SEGMENT_B_PIN, 0);
    GPIO_WriteBit(SEGMENT_C_GPIO, SEGMENT_C_PIN, 1);
    GPIO_WriteBit(SEGMENT_D_GPIO, SEGMENT_D_PIN, 1);
    GPIO_WriteBit(SEGMENT_E_GPIO, SEGMENT_E_PIN, 1);
    GPIO_WriteBit(SEGMENT_F_GPIO, SEGMENT_F_PIN, 0);
    GPIO_WriteBit(SEGMENT_G_GPIO, SEGMENT_G_PIN, 0);
	  GPIO_WriteBit(SEGMENT_DP_GPIO, SEGMENT_DP_PIN, 1);
}
void write_nothing(void) {
    GPIO_WriteBit(SEGMENT_A_GPIO, SEGMENT_A_PIN, 1);
    GPIO_WriteBit(SEGMENT_B_GPIO, SEGMENT_B_PIN, 1);
    GPIO_WriteBit(SEGMENT_C_GPIO, SEGMENT_C_PIN, 1);
    GPIO_WriteBit(SEGMENT_D_GPIO, SEGMENT_D_PIN, 1);
    GPIO_WriteBit(SEGMENT_E_GPIO, SEGMENT_E_PIN, 1);
    GPIO_WriteBit(SEGMENT_F_GPIO, SEGMENT_F_PIN, 1);
    GPIO_WriteBit(SEGMENT_G_GPIO, SEGMENT_G_PIN, 1);
	  GPIO_WriteBit(SEGMENT_DP_GPIO, SEGMENT_DP_PIN, 1);
}

void dynamicIndication(void) {
    switch (num) {
        case 1:
            GPIO_SetBits(DIGIT_4_GPIO, DIGIT_4_PIN);
            GPIO_ResetBits(DIGIT_1_GPIO, DIGIT_1_PIN);
            write_number(out7SegDisplay[0]);
            break;

        case 2:
						GPIO_SetBits(DIGIT_1_GPIO, DIGIT_1_PIN);
            GPIO_ResetBits(DIGIT_2_GPIO, DIGIT_2_PIN);
            write_number(out7SegDisplay[1]);
            break;
				
        case 3:
            GPIO_SetBits(DIGIT_2_GPIO, DIGIT_2_PIN);
            GPIO_ResetBits(DIGIT_3_GPIO, DIGIT_3_PIN);
            write_number(out7SegDisplay[2]);
            break;
				
        case 4:
            GPIO_SetBits(DIGIT_3_GPIO, DIGIT_3_PIN);
            GPIO_ResetBits(DIGIT_4_GPIO, DIGIT_4_PIN);
            write_number(out7SegDisplay[3]);
            break;
    }
    num++;
    if (num > 4) num = 1;
}

void dynamicIndicationForTemperature(int32_t temperarute) {
    switch (num) {
        case 1:
            GPIO_SetBits(DIGIT_4_GPIO, DIGIT_4_PIN);
            GPIO_ResetBits(DIGIT_1_GPIO, DIGIT_1_PIN);
				
				
						if(temperarute<100&&temperarute>0){
							write_number_with_dot(out7SegDisplay[0]);
						}else if(temperarute<0){
							write_minus();
						}else if(temperarute<10 && temperarute>0){
							write_number_with_dot(out7SegDisplay[0]);
						}
						else{
							write_number(out7SegDisplay[0]);
						}						
						
            break;

        case 2:
						GPIO_SetBits(DIGIT_1_GPIO, DIGIT_1_PIN);
            GPIO_ResetBits(DIGIT_2_GPIO, DIGIT_2_PIN);
						if(temperarute>100){
							write_number_with_dot(out7SegDisplay[1]);
						}else if(temperarute < 0 && temperarute > (-100)){
							write_number_with_dot(out7SegDisplay[0]);							
						}else if(temperarute < (-100)){
							write_number(out7SegDisplay[0]);					
						}else{
							write_number(out7SegDisplay[1]);
						}

            break;
				
        case 3:
            GPIO_SetBits(DIGIT_2_GPIO, DIGIT_2_PIN);
            GPIO_ResetBits(DIGIT_3_GPIO, DIGIT_3_PIN);
						if(temperarute < 0 && temperarute > (-100)){
						write_number(out7SegDisplay[1]);
						}else if(temperarute < (-100)){
							write_number_with_dot(out7SegDisplay[1]);
						}else if(temperarute<100 && temperarute>=0){
							write_o();
						}else{
							write_number(out7SegDisplay[2]);
						}
            break;
				
        case 4:
            GPIO_SetBits(DIGIT_3_GPIO, DIGIT_3_PIN);
            GPIO_ResetBits(DIGIT_4_GPIO, DIGIT_4_PIN);
						if (temperarute<(-100)){
            write_number(out7SegDisplay[2]);
						}else if(temperarute>0 && temperarute<100){
							write_nothing();
						}else{
							write_o();
						}
            break;
    }
    num++;
    if (num > 4) num = 1;
}


void writeTo7SegDisplay(int32_t number) {
    convBinToDec((uint32_t)number, out7SegDisplay, 4);
}

void convBinToDec(uint32_t value, uint8_t *digits_array, uint8_t array_size) {
    for (int i = (array_size - 1); (i >= 0); i--) {
        digits_array[i] = 0;
    }
    for (int i = (array_size - 1); (i >= 0) && (value != 0); i--) {
        digits_array[i] = value % 10;
        value = value / 10;
    }
}

void waitForCalibrationAnimation(void){
	if(animationCount<=10)
	{
	GPIO_SetBits(DIGIT_2_GPIO, DIGIT_2_PIN);
  GPIO_ResetBits(DIGIT_1_GPIO, DIGIT_1_PIN);
	GPIO_WriteBit(SEGMENT_A_GPIO, SEGMENT_A_PIN, 0);
  GPIO_WriteBit(SEGMENT_B_GPIO, SEGMENT_B_PIN, 1);
	GPIO_WriteBit(SEGMENT_C_GPIO, SEGMENT_C_PIN, 0);
  GPIO_WriteBit(SEGMENT_D_GPIO, SEGMENT_D_PIN, 0);
	GPIO_WriteBit(SEGMENT_E_GPIO, SEGMENT_E_PIN, 0);
  GPIO_WriteBit(SEGMENT_F_GPIO, SEGMENT_F_PIN, 0);
	GPIO_WriteBit(SEGMENT_G_GPIO, SEGMENT_G_PIN, 0);
		animationCount++;
	}
	else if(animationCount<=20)
	{
	GPIO_SetBits(DIGIT_1_GPIO, DIGIT_1_PIN);
  GPIO_ResetBits(DIGIT_2_GPIO, DIGIT_2_PIN);
	GPIO_WriteBit(SEGMENT_A_GPIO, SEGMENT_A_PIN, 1);
  GPIO_WriteBit(SEGMENT_B_GPIO, SEGMENT_B_PIN, 0);
	GPIO_WriteBit(SEGMENT_C_GPIO, SEGMENT_C_PIN, 0);
  GPIO_WriteBit(SEGMENT_D_GPIO, SEGMENT_D_PIN, 0);
	GPIO_WriteBit(SEGMENT_E_GPIO, SEGMENT_E_PIN, 0);
  GPIO_WriteBit(SEGMENT_F_GPIO, SEGMENT_F_PIN, 0);
	GPIO_WriteBit(SEGMENT_G_GPIO, SEGMENT_G_PIN, 0);
		animationCount++;
	}
	else if(animationCount<=30)
	{
	GPIO_SetBits(DIGIT_1_GPIO, DIGIT_1_PIN);
  GPIO_ResetBits(DIGIT_2_GPIO, DIGIT_2_PIN);
	GPIO_WriteBit(SEGMENT_A_GPIO, SEGMENT_A_PIN, 0);
  GPIO_WriteBit(SEGMENT_B_GPIO, SEGMENT_B_PIN, 0);
	GPIO_WriteBit(SEGMENT_C_GPIO, SEGMENT_C_PIN, 0);
  GPIO_WriteBit(SEGMENT_D_GPIO, SEGMENT_D_PIN, 0);
	GPIO_WriteBit(SEGMENT_E_GPIO, SEGMENT_E_PIN, 1);
  GPIO_WriteBit(SEGMENT_F_GPIO, SEGMENT_F_PIN, 0);
	GPIO_WriteBit(SEGMENT_G_GPIO, SEGMENT_G_PIN, 0);
		animationCount++;
	}else if(animationCount<=40)
	{
	GPIO_SetBits(DIGIT_2_GPIO, DIGIT_2_PIN);
  GPIO_ResetBits(DIGIT_1_GPIO, DIGIT_1_PIN);
	GPIO_WriteBit(SEGMENT_A_GPIO, SEGMENT_A_PIN, 0);
  GPIO_WriteBit(SEGMENT_B_GPIO, SEGMENT_B_PIN, 0);
	GPIO_WriteBit(SEGMENT_C_GPIO, SEGMENT_C_PIN, 0);
  GPIO_WriteBit(SEGMENT_D_GPIO, SEGMENT_D_PIN, 1);
	GPIO_WriteBit(SEGMENT_E_GPIO, SEGMENT_E_PIN, 0);
  GPIO_WriteBit(SEGMENT_F_GPIO, SEGMENT_F_PIN, 0);
	GPIO_WriteBit(SEGMENT_G_GPIO, SEGMENT_G_PIN, 0);
		animationCount++;
	}

	if(animationCount >=41){
		animationCount = 0;
	}

}
