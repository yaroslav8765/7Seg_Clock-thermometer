#include "stm32f10x.h"
#include "stm32f10x_conf.h"

#include "stdio.h"
#include <stdlib.h>
#include "misc.h"
#include "math.h"
#include <stdint.h>
#include "string.h"


void TIM3_IRQHandler(void);
void TIM2_IRQHandler(void);
void RTC_IRQHandler(void);
void tim2Init(void);
void tim3init(void);
void GPIO_TogglePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void init_buttons(void);
