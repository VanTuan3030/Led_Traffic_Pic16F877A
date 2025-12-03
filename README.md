This embedded systems project implements an automatic traffic light control system using the PIC16F877A microcontroller. The system simulates real-world traffic signals with countdown timers, supports multiple operating modes, and can be extended with sensors for smart traffic management.

🚀 Key Features
Automatic Traffic Light Control: Red, Yellow, Green LEDs switch according to fixed cycles.

Countdown Display: Dual 7-segment LEDs show remaining time for each signal.

Multiple Modes:

Mode 1: Normal traffic light operation (Red → Green → Yellow).

Mode 2: Warning mode with blinking Yellow lights.

Button Input: Simulates pedestrian crossing or mode switching.

Expandable: Can integrate sensors (e.g., vehicle detection) or RTC modules for advanced scheduling.

🛠️ Hardware Requirements
Microcontroller: PIC16F877A (40-pin, 20MHz crystal).

LEDs: Red, Yellow, Green traffic LEDs.

Display: Dual 7-segment LED modules (common anode).

Passive Components: Resistors, capacitors, push buttons.

Oscillator: 20MHz crystal + capacitors.

Power Supply: 9V battery with LM2596/LM7805 regulator (output 5V).

Optional: RTC DS1307/DS3231 for precise timing.

🔌 Wiring Diagram (Pinout Overview)
Device	PIC16F877A Pin	Notes
Traffic LEDs	PORTA (RA0–RA5), PORTD	Red/Yellow/Green signals
7-Segment Display	PORTB, PORTC, PORTD	Digit control + segment pins
Buttons	PORTD (RD6, RD7)	Mode selection
Oscillator	OSC1/OSC2	20MHz crystal
Power	VDD/VSS	5V regulated
💻 Software Design
Language: C (CCS C Compiler / MPLAB / MikroC).

RTOS Timer: Minor cycle 10ms for precise scheduling.

Main Tasks:

taskLED7: Controls countdown display on 7-segment LEDs.

taskLEDGT: Manages traffic light states and timing.

Modes:

Normal cycle: Red (7s) → Green (7s) → Yellow (3s).

Warning cycle: Blinking Yellow (0.5s interval).

📚 Applications
Educational project for Embedded Systems course.

Demonstrates integration of hardware + software in real-time control.

Can be extended to smart traffic systems with sensors and IoT modules.

👤 Author
Student: Võ Văn Tuấn

Student ID: 6251020094

Class: Kỹ thuật Điện tử - Viễn thông (CQ.62.KTDTVT)

University:
