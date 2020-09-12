#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define __AVR_ATmega328P__ 1
#ifndef F_CPU
#define F_CPU 16000000UL
#endif

int main() {
    // Initialize indicator LED
    DDRB |= (1 << PINB0);

    while (1) {
		// Initialize Direction of Wheels
		PORTB |= (1 << PINB0);
		_delay_ms(1000);
		PORTB &= ~(1 << PINB0);
		_delay_ms(1000);
    }
    return 0;
}
