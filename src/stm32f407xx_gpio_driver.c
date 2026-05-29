#include "stm32f407xx.h"

void GPIO_Init(GPIO_RegDef_t * GPIOx, GPIO_PinConf_t GPIOPinConf){
    // configure pin mode
    GPIOx->MODER &= ~(0x03U << GPIOPinConf.GPIO_PinNumber * 2);
    GPIOx->MODER |= (GPIOPinConf.GPIO_PinMode << GPIOPinConf.GPIO_PinNumber * 2);

    if(GPIOPinConf.GPIO_PinMode == GPIO_MODE_ALT || GPIOPinConf.GPIO_PinMode == GPIO_MODE_OUTPUT){
        // configure output type
        GPIOx->OTYPER &= ~(0x01U << GPIOPinConf.GPIO_PinNumber);
        GPIOx->OTYPER |= (GPIOPinConf.GPIO_OutType << GPIOPinConf.GPIO_PinNumber);
        // configure output speed
        GPIOx->OSPEEDR &= ~(0x03U << GPIOPinConf.GPIO_PinNumber * 2);
        GPIOx->OSPEEDR |= (GPIOPinConf.GPIO_OutSpeed << GPIOPinConf.GPIO_PinNumber * 2);
    }
    
    // configure pull up pull down
    GPIOx->PUPDR &= ~(0x03U << GPIOPinConf.GPIO_PinNumber * 2);
    GPIOx->PUPDR |= (GPIOPinConf.GPIO_PUPD << GPIOPinConf.GPIO_PinNumber * 2);
    // configure the altnernate function
    if(GPIOPinConf.GPIO_PinMode == GPIO_MODE_ALT){
        if(GPIOPinConf.GPIO_PinNumber < 8){
            // config for low reg
            GPIOx->AFRL &= ~(0x0FU << GPIOPinConf.GPIO_PinNumber * 4);
            GPIOx->AFRL |= (GPIOPinConf.GPIO_AltFnc << GPIOPinConf.GPIO_PinNumber * 4);
        }
        else{
            // config for high reg
            GPIOx->AFRL &= ~(0x0FU << GPIOPinConf.GPIO_PinNumber * 4);
            GPIOx->AFRL |= (GPIOPinConf.GPIO_AltFnc << GPIOPinConf.GPIO_PinNumber * 4);
        }
    }

}