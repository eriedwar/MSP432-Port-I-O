# MSP432-Port-I-O
Using the MSP432 to design and implement a two-bit adder and display the output values using LED's

This code is written in C language and intended to run on a Texas Instruments MSP432 microcontroller. Here is a breakdown of what the code does:
1.	It includes the header file "msp.h" which provides definitions for the MSP432 microcontroller.
2.	It defines a function TwoBitAdder which takes four integer inputs A1, B1, A2, and B2. This function computes the sum of two two-bit numbers and carry-out bit using bitwise operators.
3.	It defines two functions read_input and write_output which read input from a pin and write output to a pin respectively. These functions use bitwise operations to manipulate the values of the input/output pins.
4.	In the main function, it disables the watchdog timer and initializes the input and output pins of the microcontroller.
5.	It enters a while loop which runs indefinitely.
6.	Inside the loop, it turns on an LED, writes 0 to the output pins, and reads input from the pins using the read_input function.
7.	It turns off the LED and computes the sum of the two two-bit numbers and carry-out bit using the TwoBitAdder function.
8.	It writes the output to the pins using the write_output function and delays for some time using the __delay_cycles function.
9.	If the sum is 7, it enters an automated mode where it repeatedly writes 0 and 7 to the output pins with a delay between each write.
10.	The program continues to loop indefinitely until it is manually stopped or an error occurs.
In summary, this code implements a two-bit adder circuit on a MSP432 microcontroller and outputs the result to a set of output pins. If the sum of the two two-bit numbers and carry-out bit is 7, it enters an automated mode where it repeatedly writes a value of 7 to the output pins with a delay between each write.
