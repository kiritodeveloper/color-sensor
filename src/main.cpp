#include <Arduino.h>
// Define constants
#define LED_R 11
#define LED_G 12
#define LED_B 13
#define RGBLED_R 6
#define RGBLED_G 9
#define RGBLED_B 10
#define LED_CALIBRATION 3
#define LED_SENSING 4
#define LED_CALIBRATION_WHITE 7
#define LED_CALIBRATION_BLACK 8
#define LDR A0
#define BUTTON_MODE 2
#define STATE_CALIBRATION 0
#define STATE_READ_COLOR 1

// Declare variables
int current_state = STATE_CALIBRATION;
int previous_button_state = 1; // This variable is initialized 1, as the pin will be configured as INPUT_PULLUP
int white_r;
int white_g;
int white_b;
int black_r;
int black_g;
int black_b;

// Function declaration
void initialize();
void calibrate();
void read_color();
void read_rgb_values(int *r, int *g, int *b);
void print_color(int r, int g, int b);


void setup() {
    initialize();
}

void loop() {
    switch(current_state){
        case STATE_READ_COLOR:
        read_color();
        case STATE_CALIBRATION:
        calibrate();
    }
}

// Function implementation
void initialize(){
    pinMode(LED_R, OUTPUT);
    pinMode(LED_G, OUTPUT);
    pinMode(LED_B, OUTPUT);
    pinMode(LED_CALIBRATION, OUTPUT);
    pinMode(LED_SENSING, OUTPUT);
    pinMode(LDR, OUTPUT);
    pinMode(BUTTON_MODE, INPUT_PULLUP);
}

int white_calibration_count = 0;
int black_calibration_count = 0;
int average_white_r=0, average_white_g=0, average_white_b=0;
int average_black_r=0, average_black_g=0, average_black_b=0;
void calibrate(){
    if(white_calibration_count<5){
        int r, g, b;
        read_rgb_values(&r, &g, &b);
        average_white_r = (average_white_r + r)/(white_calibration_count + 1);
        average_white_g = (average_white_g + g)/(white_calibration_count + 1);
        average_white_b = (average_white_b + b)/(white_calibration_count + 1);
        white_calibration_count++;
    }else if(black_calibration_count<5){
        int r, g, b;
        read_rgb_values(&r, &g, &b);
        average_black_r = (average_black_r + r)/(black_calibration_count + 1);
        average_black_g = (average_black_g + g)/(black_calibration_count + 1);
        average_black_b = (average_black_b + b)/(black_calibration_count + 1);
        black_calibration_count++;
    }else{
        white_r = average_white_r;
        white_g = average_white_g;
        white_b = average_white_b;
        black_r = average_black_r;
        black_g = average_black_g;
        black_b = average_black_b;
        current_state = STATE_READ_COLOR;
    }
}

void read_color(){
    int r, g, b;
    read_rgb_values(&r, &g, &b);
    if(r>black_r) r=black_r;
    if(g>black_g) g=black_g;
    if(b>black_b) b=black_b;
    if(r<white_r) r=white_r;
    if(g<white_g) g=white_g;
    if(b<white_b) b=white_b;
    int current_r = map(r, white_r, black_r, 255, 0);
    int current_g = map(g, white_g, black_g, 255, 0);
    int current_b = map(b, white_b, black_b, 255, 0);
}

void read_rgb_values(int *r, int *g, int *b){
    // Read red value
    digitalWrite(LED_R, HIGH);
    delay(25);
    *r = analogRead(LDR);
    delay(25);
    digitalWrite(LED_R, LOW);

    // Read green value
    digitalWrite(LED_G, HIGH);
    delay(25);
    *g = analogRead(LDR);
    delay(25);
    digitalWrite(LED_G, LOW);
    
    // Read blue value
    digitalWrite(LED_B, HIGH);
    delay(25);
    *b = analogRead(LDR);
    delay(25);
    digitalWrite(LED_B, LOW);
}

void print_color(int r, int g, int b){
    //Still to implement
}

void send_rgb_code(int r, int g, int b){
    
}