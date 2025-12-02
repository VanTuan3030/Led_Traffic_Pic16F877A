#include <16f877a.h>
#fuses HS, NOWDT, NOPROTECT, NOLVP
#use delay(clock=20000000) // 20 MHz
#use rtos(timer=0, minor_cycle=10ms) // Chu k? nh? 10ms

// Các chân k?t n?i LED 7-segment
#define SEG_A PIN_B0
#define SEG_B PIN_B1
#define SEG_C PIN_B2
#define SEG_D PIN_B3
#define SEG_E PIN_B4
#define SEG_F PIN_B5
#define SEG_G PIN_B6

#define DIGIT_1_LED1 PIN_D0
#define DIGIT_2_LED1 PIN_D1
#define DIGIT_1_LED2 PIN_C4
#define DIGIT_2_LED2 PIN_D3

#define d1 PIN_A0  // Ðèn d? giao thông 1
#define v1 PIN_A1  // Ðèn vàng giao thông 1
#define x1 PIN_A2  // Ðèn xanh giao thông 1
#define d2 PIN_A3  // Ðèn d? giao thông 2
#define v2 PIN_D4  // Ðèn vàng giao thông 2
#define x2 PIN_A5  // Ðèn xanh giao thông 2

#define BUTTON_MODE1 PIN_D6 // Nút ch? d? 1
#define BUTTON_MODE2 PIN_D7 // Nút ch? d? 2

// Mã hóa s? trên LED 7-segment
unsigned int8 SEGMENT_CODES[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};

// Bi?n tr?ng thái
int1 mode = 1; // M?c d?nh ch? d? 1
static int8 i1 = 10, i2 = 7; // Bi?n luu tr? giá tr? LED 7-segment
static int8 state = 0;       // Tr?ng thái c?a dèn giao thông
static int16 counter_traffic = 0; // B? d?m th?i gian cho dèn giao thông

// Hàm hi?n th? ch? s? trên LED 7-segment
void display_digit(int8 digit, int8 value, int8 led) {
    // T?t t?t c? các digit
    output_low(DIGIT_1_LED1);
    output_low(DIGIT_2_LED1);
    output_low(DIGIT_1_LED2);
    output_low(DIGIT_2_LED2);

    // Hi?n th? giá tr? tuong ?ng trên LED 7-segment
    output_b(SEGMENT_CODES[value]);

    // B?t digit c?n hi?n th?
    if (led == 1) {
        if (digit == 0) output_high(DIGIT_1_LED1);
        else output_high(DIGIT_2_LED1);
    } else if (led == 2) {
        if (digit == 0) output_high(DIGIT_1_LED2);
        else output_high(DIGIT_2_LED2);
    }

    // Delay d? nhìn th?y hi?n th?
    delay_us(500);

    // T?t t?t c? các digit sau khi hi?n th?
    output_low(DIGIT_1_LED1);
    output_low(DIGIT_2_LED1);
    output_low(DIGIT_1_LED2);
    output_low(DIGIT_2_LED2);
}

#task(rate=10ms)
void taskLED7() {
    if (mode) {
        static int16 counter = 0;    // B? d?m 10ms d? tính th?i gian
        static int flag = 0;

        counter++;

        if (counter >= 100) { // M?i 1 giây (100 * 10ms)
            counter = 0;

            if (i1 > 0) i1--;
            if (i2 > 0) i2--;
            if (i2 == 0 && i1 == 3) i2 = 3;
            if (i2 == 3 && i1 == 0) i1 = 3;
            if (i1 == 0 && i2 == 0) {
                flag = 1 - flag;
                if (flag == 1) { i2 = 10; i1 = 7;} 
                else { i2 = 7; i1 = 10;}
            }   
        }
        // Hi?n th? các giá tr? trên LED 7-segment
        display_digit(0, i1 / 10, 1); // Hi?n th? ch? s? hàng ch?c c?a LED 1
        display_digit(1, i1 % 10, 1); // Hi?n th? ch? s? hàng don v? c?a LED 1
        display_digit(0, i2 / 10, 2); // Hi?n th? ch? s? hàng ch?c c?a LED 2
        display_digit(1, i2 % 10, 2); // Hi?n th? ch? s? hàng don v? c?a LED 2
    }
    else { // Ch? d? 2
        // T?t LED 7-segment
        output_low(DIGIT_1_LED1); 
        output_low(DIGIT_2_LED1); 
        output_low(DIGIT_1_LED2); 
        output_low(DIGIT_2_LED2); 

    } 
}

#task(rate=100ms)
void taskLEDGT() {
    if (mode) { // Ch? d? 1: Ðèn giao thông ho?t d?ng bình thu?ng
        counter_traffic++;
        switch (state) {
            case 0:
                output_high(d1);
                output_low(v1);
                output_low(x1);
                output_low(d2);
                output_low(v2);
                output_high(x2);
                if (counter_traffic >= 70) { // 7 giây th?c hi?n
                    counter_traffic = 0;
                    state = 1;
                }
                break;
            case 1:
                output_high(d1);
                output_low(v1);
                output_low(x1);
                output_low(d2);
                output_high(v2);
                output_low(x2);
                if (counter_traffic >= 30) { // 3 giây th?c hi?n
                    counter_traffic = 0;
                    state = 2;
                }
                break;
            case 2:
                output_low(d1);
                output_low(v1);
                output_high(x1);
                output_high(d2);
                output_low(v2);
                output_low(x2);
                if (counter_traffic >= 70) { // 7 giây th?c hi?n
                    counter_traffic = 0;
                    state = 3;
                }
                break;
            case 3:
                output_low(d1);
                output_high(v1);
                output_low(x1);
                output_high(d2);
                output_low(v2);
                output_low(x2);
                if (counter_traffic >= 30) { // 3 giây th?c hi?n
                    counter_traffic = 0;
                    state = 0;
                }
                break;
        }
    } else { // Ch? d? 2: Nháy dèn vàng
        counter_traffic++;
        if (counter_traffic >= 5) { // Nháy dèn vàng 0.5s
            counter_traffic = 0;
            output_toggle(v1);
            output_toggle(v2);
        }
        // T?t các dèn khác
        output_low(d1);
        output_low(x1);
        output_low(d2);
        output_low(x2);
    }
}

#task(rate=10ms)
void taskBUTTON() {
    static int1 last_button_mode1 = 1;
    static int1 last_button_mode2 = 1;

    if (!input(BUTTON_MODE1) && last_button_mode1) {
        mode = 1;
        i1 = 10; // Gán LED 1 = 10 khi chuy?n sang ch? d? 1
        i2 = 7;  // Gán LED 2 = 7 khi chuy?n sang ch? d? 1
        state = 0; // Reset tr?ng thái dèn giao thông
        counter_traffic = 0; // Reset b? d?m th?i gian
    }

    if (!input(BUTTON_MODE2) && last_button_mode2) {
        mode = 0;
    }

    last_button_mode1 = input(BUTTON_MODE1);
    last_button_mode2 = input(BUTTON_MODE2);
}

void main() {
    set_tris_d(0xC0); // C?u hình RD6, RD7 là INPUT
    set_tris_b(0x00); // Các chân di?u khi?n LED 7-segment là OUTPUT
    set_tris_a(0x00); // Các chân di?u khi?n dèn giao thông là OUTPUT
    output_b(0x00);   // T?t t?t c? các chân B
    output_a(0x00);   // T?t t?t c? các chân A
    rtos_run();       // Ch?y RTOS
}
