#include "buttonDebounce.h"

void debounceButton(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, struct button_debounce_parametrs* parametr, button_state* butt_state ){
	if (parametr->butt_counter == parametr->butt_count_to) {
        parametr->butt_counter = 0;
        
					if (GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == 0) {
            if (*butt_state == BTN_UNPUSH) {
                *butt_state = BTN_POLL;
            } else if (*butt_state == BTN_POLL) {
                *butt_state = BTN_PUSHED;
            }
				} else if (*butt_state == BTN_POLL) {
					*butt_state = BTN_UNPUSH;
				} else if (*butt_state == BTN_PUSHED) {
					*butt_state = BTN_POLL;
				}					
			} 
	else{
		parametr->butt_counter++;
			}
}

