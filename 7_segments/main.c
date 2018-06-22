#define F_CPU 1000000

#include <avr/io.h>
#include <util/delay.h>

#define dotPIN PINB2

uint8_t digitCodeMap[] = {
	  //     GFEDCBA  Segments      7-segment map:
	  0b00111111, // 0   "0"          AAA
	  0b00000110, // 1   "1"         F   B
	  0b01011011, // 2   "2"         F   B
	  0b01001111, // 3   "3"          GGG
	  0b01100110, // 4   "4"         E   C
	  0b01101101, // 5   "5"         E   C
	  0b01111101, // 6   "6"          DDD
	  0b00000111, // 7   "7"
	  0b01111111, // 8   "8"
	  0b01101111, // 9   "9"
	  0b01110111, // 10  'A'
	  0b01111100, // 11  'B'
	  0b00111001, // 12  'C'
	  0b01011110, // 13  'D'
	  0b01111001, // 14  'E'
	  0b01110001, // 15  'F'
	  0b01000000, // 16  '-'  DASH
	  0b00000000  // 17  ' '  BLANK
};

struct DigitDisplay {
	uint8_t rightDigit;
	uint8_t rightDot;
	uint8_t leftDigit;
	uint8_t leftDot;
};

void SEGMENT_display(struct DigitDisplay* digitDisplay);
void SEGMENT_clear();


int main(void){
	
	struct DigitDisplay digitDisplay;
	
	digitDisplay.rightDigit = digitCodeMap[17];
	digitDisplay.rightDot = 0;
	digitDisplay.leftDigit = digitCodeMap[17];
	digitDisplay.leftDot = 0;
	
	DDRA |= 0b01111111;
	PORTA &=~(0b01111111);
	DDRB |= (1<<dotPIN)|(1 << PINB0)|(1<<PINB1);
	PORTB |= (1 << PINB1);
	PORTB &=~((1 << PINB0)|(1<<dotPIN));
	int i=0;
	
	while(1) {
		int number = 0;
		for (number=0; number<50; number++) {
			digitDisplay.rightDigit = digitCodeMap[number%10];
			if ((number/10)==0) {
				digitDisplay.leftDigit = digitCodeMap[17];
			} else {
				digitDisplay.leftDigit = digitCodeMap[number/10];
			}
			int j = 0;
			for (j=0; j<50; j++) {
				SEGMENT_display(&digitDisplay);
			}
		}
	}
	return 0;
}

void SEGMENT_display(struct DigitDisplay* digitDisplay) {
	PORTA &=~(0b01111111);
	PORTA |= digitDisplay->rightDigit;
	PORTB &=~((1 << PINB0)|(1 << PINB1)|(1 << PINB2));
	PORTB |= (1 << PINB0)|(digitDisplay->leftDot << PINB2);
	_delay_ms(10);
	PORTA &=~(0b01111111);
	PORTA |= digitDisplay->leftDigit;
	PORTB &=~((1 << PINB0)|(1 << PINB1)|(1 << PINB2));
	PORTB |= (1 << PINB1)|(digitDisplay->leftDot << PINB2);
	_delay_ms(10);
}

void SEGMENT_clear() {
	PORTA &=~(0b01111111);
	PORTB &=~(1 << PINB0)|(1 << PINB1)|(1 << PINB2);
}