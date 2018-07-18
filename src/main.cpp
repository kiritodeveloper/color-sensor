#include <Arduino.h>

// Define constants
#define LED_R 11
#define LED_G 12
#define LED_B 13
#define LED_SENSING 4
#define LED_CALIBRATION_WHITE 7
#define LED_CALIBRATION_BLACK 8
#define LDR A0
#define BUTTON_CALIBRATE 2
#define STATE_CALIBRATION 0
#define STATE_READ_COLOR 1

//Used: 2,3,4,7,8,11,12,13

// Declare variables
int current_state = STATE_CALIBRATION;
int white_r;
int white_g;
int white_b;
int black_r;
int black_g;
int black_b;
int white_calibration_count = 0;
int black_calibration_count = 0;
int button_status = 0;
int last_button_status = 1; // Initialized with a value of 1 as the button's pin is configured as INPUT_PULLUP
int average_white_r = 0, average_white_g = 0, average_white_b = 0;
int average_black_r = 0, average_black_g = 0, average_black_b = 0;
bool calibration_white_started = false;
bool calibration_black_started = false;

// Function declaration
void initialize();
void calibrate();
void read_color();
void read_rgb_values(int *r, int *g, int *b);
void print_color(int r, int g, int b);
void send_rgb_code(int r, int g, int b);
void blinkLed(int led);

void setup()
{
    initialize();
}

void loop()
{
    button_status = digitalRead(BUTTON_CALIBRATE);
    if (button_status == 0 and last_button_status == 1)
        current_state = STATE_CALIBRATION;
    switch (current_state)
    {
    case STATE_READ_COLOR:
        blinkLed(LED_SENSING);
        read_color();
        break;
    case STATE_CALIBRATION:
        digitalWrite(LED_SENSING, LOW);
        calibrate();
        break;
    }
}

// Function implementation
void initialize()
{
    Serial.begin(9600);
    pinMode(LED_R, OUTPUT);
    pinMode(LED_G, OUTPUT);
    pinMode(LED_B, OUTPUT);
    pinMode(LED_CALIBRATION_WHITE, OUTPUT);
    pinMode(LED_SENSING, OUTPUT);
    pinMode(BUTTON_CALIBRATE, INPUT_PULLUP);
    current_state = STATE_CALIBRATION;
}

void calibrate()
{
    if (white_calibration_count < 5)
    {
        if (!calibration_white_started)
        {
            delay(3000);
            calibration_white_started = true;
        }
        digitalWrite(LED_CALIBRATION_WHITE, HIGH);
        int r, g, b;
        read_rgb_values(&r, &g, &b);
        average_white_r += r;
        average_white_g += g;
        average_white_b += b;
        white_calibration_count++;
        delay(50);
    }
    else if (black_calibration_count < 5)
    {
        digitalWrite(LED_CALIBRATION_WHITE, LOW);
        if (!calibration_black_started)
        {
            delay(3000);
            calibration_black_started = true;
        }
        digitalWrite(LED_CALIBRATION_BLACK, HIGH);
        int r, g, b;
        read_rgb_values(&r, &g, &b);
        average_black_r += r;
        average_black_g += g;
        average_black_b += b;
        black_calibration_count++;
        delay(50);
    }
    else
    {
        digitalWrite(LED_CALIBRATION_BLACK, LOW);
        white_r = average_white_r / 5;
        white_g = average_white_g / 5;
        white_b = average_white_b / 5;
        //Serial.println("White");
        //send_rgb_code(white_r,white_g,white_b);
        //Serial.println();
        black_r = average_black_r / 5;
        black_g = average_black_g / 5;
        black_b = average_black_b / 5;
        //Serial.println("Black");
        //send_rgb_code(black_r,black_g,black_b);
        //Serial.println();
        current_state = STATE_READ_COLOR;
        calibration_black_started = false;
        calibration_white_started = false;
    }
}

void read_color()
{
    int r, g, b;
    read_rgb_values(&r, &g, &b);
    if (r > black_r)
        r = black_r;
    if (g > black_g)
        g = black_g;
    if (b > black_b)
        b = black_b;
    if (r < white_r)
        r = white_r;
    if (g < white_g)
        g = white_g;
    if (b < white_b)
        b = white_b;
    int current_r = map(r, white_r, black_r, 255, 0);
    int current_g = map(g, white_g, black_g, 255, 0);
    int current_b = map(b, white_b, black_b, 255, 0);
    send_rgb_code(current_r, current_g, current_b);
}

void read_rgb_values(int *r, int *g, int *b)
{
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

void print_color(int r, int g, int b)
{
    //Still to implement
}

void send_rgb_code(int r, int g, int b)
{
    if (r < 10)
        Serial.print("0");
    if (r < 100)
        Serial.print("0");
    Serial.print(r);
    Serial.print(";");
    if (g < 10)
        Serial.print("0");
    if (g < 100)
        Serial.print("0");
    Serial.print(g);
    Serial.print(";");
    if (b < 10)
        Serial.print("0");
    if (b < 100)
        Serial.print("0");
    Serial.print(b);
    delay(100);
}

long blink_start = millis();
int blink_status = 0;
void blinkLed(int pin_led)
{
    long current_millis = millis();
    long millis_difference = current_millis - blink_start;
    if (millis_difference >= 1000)
    {
        blink_start = current_millis;
        blink_status = 1 - blink_status;
        digitalWrite(pin_led, blink_status);
    }
}