#include <avr/io.h>
#include <avr/interrupt.h>

// Number of PWM cycles before the ramp starts
#define DELAY       31250
// Final duty cycle of the PWM ramp
#define DUTY_CYCLE  128
// Number of PWM cycles between steps of the ramp
#define RAMP_TIME   100

// Delay time (s) = DELAY/31250
// Total ramp time (s) = (255 - DUTY_CYCLE)*RAMP_TIME/31250

volatile uint32_t countdown = DELAY;
volatile uint16_t ramp_divider = 0;


ISR(TIM0_OVF_vect) {
    if (countdown == 0) {
        if (OCR0A > DUTY_CYCLE) {
            ramp_divider++;
            if (ramp_divider >= RAMP_TIME) {
                ramp_divider = 0;
                OCR0A--;
            }
        }
    }
    else countdown--;
}

int main() {
    DDRB   = 0b00000001;
    TCCR0A = 0b10000011;
    TCCR0B = 0b00000001;
    OCR0A  = 255;
    TIMSK  = 0b00000010;
    sei();
    while (1);
}
