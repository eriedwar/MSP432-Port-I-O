// include the header file for MSP432 device
#include "msp.h"

// function for two-bit adder logic
int TwoBitAdder(int A1, int B1, int A2, int B2)
{
    int S1 = A1 ^ B1;
    int S2 = ((A2 ^ B2) ^ (A1 & B1));
    int C2 = (((A1 & B1) & (A2 ^ B2))|(A2 & B2));

    // return the sum of two two-bit numbers and carry out bit
    return S1 | (S2 << 1) | (C2 << 2);
}

// function to read input from a pin
int read_input(int pin)
{
    // read the input from a pin
    return P5->IN & pin ? 0 : 1;
}

// function to write output to a pin
void write_output(int pin, int value)
{
    // if the value is high, set the corresponding pin to high
    if (value) {
        P2->OUT |= pin;
    }
    // if the value is low, set the corresponding pin to low
    else {
        P2->OUT &= ~pin;
    }
}

void main(void)
{
    // disable the watchdog timer
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;

    // initialize the input and output pins
    int a1 = 0, b1 = 0, a2 = 0, b2 = 0, c0 = 0;
    P1->DIR |= BIT0;
    P1->OUT |= BIT0;
    P1->OUT &= ~BIT0;
    P5->DIR |= 0x07;
    P5->REN |= 0xF8;
    P5->OUT |= 0xFF;
    P5->OUT &= ~0x07;

    // main loop
    while (1)
    {
        // turn on the LED
        P1->OUT |= BIT0;

        // write 0 to the output pins
        write_output(0xF8, 0);

        // read input from the pins
        int i;
        for (i = 0; i < 200000; i++)
        {
            a1 |= read_input(BIT4);
            b1 |= read_input(BIT5);
            a2 |= read_input(BIT6);
            b2 |= read_input(BIT7);
            c0 |= read_input(BIT3);
        }

        // turn off the LED
        P1->OUT &= ~BIT0;

        // compute the sum of two two-bit numbers and carry out bit
        int Sum = TwoBitAdder(a1, b1, a2, b2) + c0;

        // write the output to the pins
        write_output(0xF8, Sum | 0xF8);

        // delay for some time
        __delay_cycles(6000000);

        // if the sum is 7, enter automated mode
        if (Sum == 7)
        {
            while (1)
            {
                // write 0 to the output pins
                write_output(0xF8, 0);

                // delay for some time
                __delay_cycles(6000000);

                // write 7 to the output pins
                write_output(0xF8, 7);

                // delay for some time
                __delay_cycles(6000000);
            }
        }
    }
}
