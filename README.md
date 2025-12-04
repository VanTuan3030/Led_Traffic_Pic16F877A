# Automatic Traffic Light Control System (PIC16F877A)

An embedded system project simulating and controlling a 4-way traffic light system using the PIC16F877A microcontroller. The system features a countdown timer displayed on 7-segment LEDs and flexible control modes for different traffic scenarios.

## 🚀 Key Features

* **Automatic Mode (Auto Mode):** The system operates on a standard traffic light cycle (Green -> Yellow -> Red) with pre-set timings for two intersecting lanes.
* **Countdown Display:** Uses four 7-segment LEDs to show the remaining time for the current signal, helping commuters stay informed.
* **Warning Mode:** A continuous blinking Yellow light mode (0.5s) for night-time warnings or when the signal requires maintenance/priority.
* **Flexible Mode Switching:** Uses physical push buttons to instantly switch between Automatic Mode (Mode 1) and Warning Mode (Mode 2).

## 🛠️ Hardware Requirements

* **Microcontroller:** PIC16F877A.
* **Display:**
    * 7-Segment LEDs (Common Anode) x4 (2 digits per lane).
    * Single LEDs (Red, Yellow, Green) simulating traffic signals.
* **Control:** Push Buttons for mode switching.
* **Power & Circuitry:**
    * 20MHz Crystal Oscillator.
    * Ceramic Capacitors, Current Limiting Resistors.
    * 5V Power Supply.

## 🔌 Pinout Diagram

| Device | PIC16F877A Pin | Symbol (Code) | Function |
| :--- | :--- | :--- | :--- |
| **Traffic Light 1** | PIN_A0 | `d1` | Red Light Lane 1 |
| | PIN_A1 | `v1` | Yellow Light Lane 1 |
| | PIN_A2 | `x1` | Green Light Lane 1 |
| **Traffic Light 2** | PIN_A3 | `d2` | Red Light Lane 2 |
| | PIN_D4 | `v2` | Yellow Light Lane 2 |
| | PIN_A5 | `x2` | Green Light Lane 2 |
| **LED 7-Segment (Data)** | PORT B (B0-B6) | `SEG_A`...`SEG_G` | Digit Data Segments |
| **LED 7-Segment (Scan)**| PIN_D0, D1, C4, D3 | `DIGIT_x_LEDx` | Digit Control Pins (Scan) |
| **Button (Control)** | PIN_D6 | `BUTTON_MODE1` | Switch to Auto Mode |
| | PIN_D7 | `BUTTON_MODE2` | Switch to Warning Mode |

## 💻 Installation and Usage

1.  **Software:**
    * Compiler: **CCS C Compiler** (PIC C).
    * Simulation: **Proteus** or **Altium**.

2.  **Code Configuration:**
    * Open the `.c` source file.
    * Verify crystal frequency: `#use delay(clock=20000000)` (20MHz).
    * RTOS Configuration: `#use rtos(timer=0, minor_cycle=10ms)`.

3.  **Operation:**
    * **Default:** System runs in Auto Mode (Countdown and signal cycling).
    * **Press Button 1 (GPIO D6):** Reset to Auto Mode (if currently in another mode).
    * **Press Button 2 (GPIO D7):** Switch to Warning Mode (Blinking Yellow), 7-segment display turns off.

## 👤 Author

* **Student:** Vo Van Tuan
* **Student ID:** 6251020094
* **Class:** Electronics and Telecommunications Engineering (Course 62)
* **University:** University of Transport and Communications - HCMC Campus

---
*Project for the Embedded Systems course final report.*
