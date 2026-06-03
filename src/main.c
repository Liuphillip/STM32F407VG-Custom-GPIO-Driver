#include "stm32f407xx.h"

GPIO_PinConf_t Blinky_LED;

void BlueLED_Init(void){

    Blinky_LED.GPIO_PinNumber   = GPIO_PIN_NUM_15;
    Blinky_LED.GPIO_PinMode     = GPIO_MODE_OUTPUT;
    Blinky_LED.GPIO_OutType     = GPIO_OUTPUT_PP;
    Blinky_LED.GPIO_OutSpeed    = GPIO_LOW_SPEED;
    Blinky_LED.GPIO_PUPD        = GPIO_NO_PUPD;

    GPIO_Init(GPIOD, Blinky_LED);
}

void GreenLED_Init(void){

    Blinky_LED.GPIO_PinNumber   = GPIO_PIN_NUM_12;
    Blinky_LED.GPIO_PinMode     = GPIO_MODE_OUTPUT;
    Blinky_LED.GPIO_OutType     = GPIO_OUTPUT_PP;
    Blinky_LED.GPIO_OutSpeed    = GPIO_LOW_SPEED;
    Blinky_LED.GPIO_PUPD        = GPIO_NO_PUPD;

    GPIO_Init(GPIOD, Blinky_LED);
}

void RedLED_Init(void){

    Blinky_LED.GPIO_PinNumber   = GPIO_PIN_NUM_14;
    Blinky_LED.GPIO_PinMode     = GPIO_MODE_OUTPUT;
    Blinky_LED.GPIO_OutType     = GPIO_OUTPUT_PP;
    Blinky_LED.GPIO_OutSpeed    = GPIO_LOW_SPEED;
    Blinky_LED.GPIO_PUPD        = GPIO_NO_PUPD;

    GPIO_Init(GPIOD, Blinky_LED);
}

void OrangeLED_Init(void){

    Blinky_LED.GPIO_PinNumber   = GPIO_PIN_NUM_13;
    Blinky_LED.GPIO_PinMode     = GPIO_MODE_OUTPUT;
    Blinky_LED.GPIO_OutType     = GPIO_OUTPUT_PP;
    Blinky_LED.GPIO_OutSpeed    = GPIO_LOW_SPEED;
    Blinky_LED.GPIO_PUPD        = GPIO_NO_PUPD;

    GPIO_Init(GPIOD, Blinky_LED);
}



volatile uint8_t Flag = 0;

int main(void){
    
    GPIOD_CLK_ENB();
    BlueLED_Init();
    GreenLED_Init();
    OrangeLED_Init();
    RedLED_Init();

    // turn on the blue led
    GPIO_WritePin(GPIOD, GPIO_PIN_NUM_15, GPIO_PIN_HIGH);
    // turn on the green led
    GPIO_WritePin(GPIOD, GPIO_PIN_NUM_12, GPIO_PIN_HIGH);
    // turn on the orange led
    GPIO_WritePin(GPIOD, GPIO_PIN_NUM_13, GPIO_PIN_HIGH);
    // turn on the red led
    GPIO_WritePin(GPIOD, GPIO_PIN_NUM_14, GPIO_PIN_HIGH);
    
    return 0;
}