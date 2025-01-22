#include "main.h"
typedef enum 
{ 
 	BTN_UNPUSH 		= 0x00,
	BTN_POLL	= 0x01,
	BTN_PUSHED		= 0x02,
} button_state;

struct button_debounce_parametrs{
	uint16_t butt_count_to_min;
	uint16_t butt_count_to_max;
	uint16_t butt_counter;
	uint16_t butt_count_to;  //Zalupa, peredelat
};
void debounceButton(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, struct button_debounce_parametrs* parametr, button_state* butt_state );
