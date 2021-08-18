#include "startup.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "Sound/midiMessage.h"
#include "main.h"
#include "stm32f1xx_hal_tim.h"

// Possible key states
typedef enum {
  KEY_IS_UP,
  KEY_IS_DOWN,
  KEY_IS_GOING_UP,    // We increment the timer in this state
  KEY_IS_GOING_DOWN,  // We increment the timer in this state
} state_t;

// Possible events
typedef enum {
  KEY_PRESSED,    // Key is pressed
  KEY_DOWN,       // Key reached bottom
  KEY_RELEASED,   // Key was released
  KEY_UP,         // Key reached top
} event_t;

typedef struct {
  char			midi_note	:8;
  state_t       state		:4; // Bit fields
  unsigned int  t    		:7; // Lines up nicely to 16bits, t overflows at 4096
} midikey_t;

typedef struct {
  uint8_t top;
  uint8_t bottom;
} bank_t;
#define NUM_KEYS 61

midikey_t keys[NUM_KEYS];

#define NUM_BANKS 8

// For scanning banks
bank_t banks[NUM_BANKS];
bank_t prev_banks[NUM_BANKS];

void initialize()
{
	printf("%s\n", __func__);

	// Init keys
	for ( int key = 0; key < NUM_KEYS; key++) {
		keys[key].midi_note = 24 + key;
		keys[key].t = 0;
	}

	memset(banks, 0xff, sizeof(banks));

	HAL_TIM_Base_Start(&htim1);

}

void trigger(midikey_t *key, event_t event) {
	if(event == KEY_PRESSED) {
		key->state = KEY_IS_GOING_DOWN;

	} else if (event == KEY_DOWN) {
		key->state = KEY_IS_DOWN;
		// note pressed
		midiMessage(MIDI_NOTE_ON, 0, key->midi_note, 127- key->t);
//		printf("ON %d %d\n", key->midi_note, 127- key->t);
		key->t = 0;
	} else if (event == KEY_RELEASED) {
		key->state = KEY_IS_GOING_UP;
	} else if ( event == KEY_UP) {
		key->state = KEY_IS_UP;
		// note released
		midiMessage(MIDI_NOTE_OFF, 0, key->midi_note, 127- key->t);
//		printf("OFF %d %d\n", key->midi_note, 127- key->t);
		key->t = 0;
	}
}

void increment() {
	// Advance timers
	for(int key = 0; key < NUM_KEYS; key++) {
		state_t state = keys[key].state;
		if(state == KEY_IS_GOING_UP || state == KEY_IS_GOING_DOWN) {
			keys[key].t++;
		}
	}
}

void delay_us (uint16_t us)
{
	__HAL_TIM_SET_COUNTER(&htim1,0);  // set the counter value a 0
	while (__HAL_TIM_GET_COUNTER(&htim1) < us);  // wait for the counter to reach the us input in the parameter
}

uint32_t IDR[NUM_BANKS];
void scan() {

	// Scan and store
	for(int bank = 0; bank < NUM_BANKS; bank++) {
		prev_banks[bank] = banks[bank]; // Store previous state so we can look for changes

		GPIOA->ODR |= (1<<bank)&0xff; // Selects bottom row
		delay_us(10); // Debounce
		IDR[bank] = GPIOB->IDR;
		banks[bank].bottom    = IDR[bank] & 0xff;
		banks[bank].top = IDR[bank] >> 8;
		GPIOA->ODR &=  ~((1<<bank)&0xff); // Selects bottom row
	}

	// Process
	for(int bank = 0; bank < NUM_BANKS; bank++) {

		uint8_t diff;

		// Check top switches and fire events
		diff = banks[bank].top ^ prev_banks[bank].top;
		if(diff) {
			for(int key = 0; key < 8; key++) {
				if(diff & (1<<key)) {
					event_t event = banks[bank].top & (1<<key) ? KEY_UP : KEY_PRESSED;
					trigger(&keys[bank + 8 * key], event);
				}
			}
		}

		// Check bottom switches and fire events
		diff = banks[bank].bottom ^ prev_banks[bank].bottom;
		if(diff) {
			for(int key = 0; key < 8; key++) {
				if(diff & (1<<key)) {
					event_t event = banks[bank].bottom & (1<<key) ? KEY_DOWN : KEY_RELEASED;
					trigger(&keys[bank + 8 * key], event);
				}
			}
		}

	}

}

void loop()
{
	static uint32_t oldTick = 0;
	scan();
	increment();
	if(HAL_GetTick() - oldTick >= 1000) {
		oldTick = HAL_GetTick();
		HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
	}

	//	   footpedal();
}

