#include "main.h"
#define TST_BIT( REG, OFFSET ) (((REG) & (0x01 << (OFFSET))) >> OFFSET)

#define SEGMENT_A_PIN GPIO_Pin_14
#define SEGMENT_B_PIN GPIO_Pin_10
#define SEGMENT_C_PIN GPIO_Pin_12
#define SEGMENT_D_PIN	GPIO_Pin_8
#define SEGMENT_E_PIN GPIO_Pin_15
#define SEGMENT_F_PIN GPIO_Pin_13
#define SEGMENT_G_PIN GPIO_Pin_12
#define SEGMENT_DP_PIN GPIO_Pin_11

#define SEGMENT_A_GPIO GPIOB
#define SEGMENT_B_GPIO GPIOA
#define SEGMENT_C_GPIO GPIOA
#define SEGMENT_D_GPIO GPIOA
#define SEGMENT_E_GPIO GPIOB
#define SEGMENT_F_GPIO GPIOB
#define SEGMENT_G_GPIO GPIOB
#define SEGMENT_DP_GPIO GPIOA

#define SEGMENT_A_RCC RCC_APB2Periph_GPIOB
#define SEGMENT_B_RCC RCC_APB2Periph_GPIOA
#define SEGMENT_C_RCC RCC_APB2Periph_GPIOA
#define SEGMENT_D_RCC RCC_APB2Periph_GPIOA
#define SEGMENT_E_RCC RCC_APB2Periph_GPIOB
#define SEGMENT_F_RCC RCC_APB2Periph_GPIOB
#define SEGMENT_G_RCC RCC_APB2Periph_GPIOB
#define SEGMENT_DP_RCC RCC_APB2Periph_GPIOA


#define DIGIT_1_PIN GPIO_Pin_11
#define DIGIT_2_PIN GPIO_Pin_10
#define DIGIT_3_PIN GPIO_Pin_1
#define DIGIT_4_PIN GPIO_Pin_0

#define DIGIT_1_GPIO GPIOB
#define DIGIT_2_GPIO GPIOB
#define DIGIT_3_GPIO GPIOB
#define DIGIT_4_GPIO GPIOB

#define DIGIT_1_RCC RCC_APB2Periph_GPIOB
#define DIGIT_2_RCC RCC_APB2Periph_GPIOB
#define DIGIT_3_RCC RCC_APB2Periph_GPIOB
#define DIGIT_4_RCC RCC_APB2Periph_GPIOB

void write_number(uint8_t number);
void initSevenSegmentDisplayPins(void);
void dynamicIndication(void);
void convBinToDec( uint32_t value, uint8_t *digits_array,uint8_t array_size );
void writeTo7SegDisplay(int32_t number);
void waitForCalibrationAnimation(void);
void dynamicIndicationForTemperature(int32_t temperarute);
void write_number_with_dot(uint8_t number);
