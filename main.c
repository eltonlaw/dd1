#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#define F_CPU 1000000UL

#define SR_SRCLR_PIN  PIND5
#define SR_SRCLR_DDR  DDRD
#define SR_SRCLR_PORT PORTD

#define SR_SRCLK_PIN  PIND6
#define SR_SRCLK_DDR  DDRD
#define SR_SRCLK_PORT PORTD

#define SR_RCLK_PIN  PIND7
#define SR_RCLK_DDR  DDRD
#define SR_RCLK_PORT PORTD

#define SR_SER_PIN  PINB0
#define SR_SER_DDR  DDRB
#define SR_SER_PORT PORTB

void sr_sn74hc595n_init() {
	/* Sets all pins as output and set as low */
    SR_SRCLR_DDR |= (1 << SR_SRCLR_PIN);

	SR_SER_DDR |= (1 << SR_SER_PIN);
	SR_SER_PORT &= ~(1 << SR_SER_PIN);

	SR_SRCLK_DDR |= (1 << SR_SRCLK_PIN);
	SR_SRCLK_PORT &= ~(1 << SR_SRCLK_PIN);

    SR_RCLK_DDR |= (1 << SR_RCLK_PIN);
	SR_RCLK_PORT &= ~(1 << SR_RCLK_PIN);

	/* debugging led */
	DDRC |= (1 << PINC4);
}

void sr_clear_registers() {
	/* SRCLR active low resets all shift registers to low */
	SR_SRCLR_PORT &= ~(1 << SR_SRCLR_PIN);
	_delay_ms(1000); /* Deactivate by setting to high */
	SR_SRCLR_PORT |= (1 << SR_SRCLR_PIN);
}

int main() {
	sr_sn74hc595n_init();
	sr_clear_registers();
	SR_SER_PORT |= (1 << SR_SER_PIN);
	while (1) {
		/* debug led on  */
		PORTC |= (1 << PINC4);

		for (int i=0; i < 8; i++) {
			/* toggles SRCLK, on rising edge, SER stored in first register and
			 * previous 7 bits bumped up*/
			SR_SRCLK_PORT &= ~(1 << SR_SRCLK_PIN);
			SR_SRCLK_PORT |= (1 << SR_SRCLK_PIN);
			/* toggles RCLK, on rising edge, values of register copied out */
			SR_RCLK_PORT &= ~(1 << SR_RCLK_PIN);
			SR_RCLK_PORT |= (1 << SR_RCLK_PIN);
		}

		/* debug led off */
		_delay_ms(3000);
		sr_clear_registers();
		PORTC &= ~(1 << PINC4);
		_delay_ms(5000);
	}
    return 0;
}
