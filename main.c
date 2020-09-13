#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define __AVR_ATmega328P__ 1
#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#define SR_SRCLR_PIN  PIND5
#define SR_SRCLR_DDR  DDRD
#define SR_SRCLR_PORT PORTD

#define SR_SER_PIN  PIND6
#define SR_SER_DDR  DDRD
#define SR_SER_PORT PORTD

#define SR_SRCLK_PIN  PIND7
#define SR_SRCLK_DDR  DDRD
#define SR_SRCLK_PORT PORTD

#define SR_RCLK_PIN  PINB0
#define SR_RCLK_DDR  DDRB
#define SR_RCLK_PORT PORTB

void sr_sn74hc595n_init() {
	/* Sets all pins as output */
    SR_SRCLR_DDR |= (1 << SR_SRCLR_PIN);
	SR_SER_DDR |= (1 << SR_SER_PIN);
	SR_SRCLK_DDR |= (1 << SR_SRCLK_PIN);
    SR_RCLK_DDR |= (1 << SR_RCLK_PIN);
}

void sr_clear_registers() {
	/* SRCLR active low resets all shift registers to low */
	SR_SRCLR_PORT &= ~(1 << SR_SRCLR_PIN);
	/* Deactivate by setting to high */
	SR_SRCLR_PORT |= (1 << SR_SRCLR_PIN);
}

int main() {
	sr_sn74hc595n_init();
	sr_clear_registers();

    while (1) {}
    return 0;
}
