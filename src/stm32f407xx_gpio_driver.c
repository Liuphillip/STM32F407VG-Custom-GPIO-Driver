/*
 * Document Dependency:
 * - Device: STM32F407
 * - Datasheet: RM0090 Reference manual
 */

#include "stm32f407xx.h"

void GPIO_Init(GPIO_RegDef_t * GPIOx, GPIO_PinConf_t GPIOPinConf){

    // ------------------------------------------------------------------------
    // Configure Pin Mode
    // Datasheet Ref: Section 8.4.1 GPIO port mode register (GPIOx_MODER) 
    // 00: Input (reset state)
    // 01: General purpose output mode
    // 10: Alternate function mode
    // 11: Analog mode
    // ------------------------------------------------------------------------

    // clear bits first to ensure clean slate
    GPIOx->MODER &= ~(0x03U << GPIOPinConf.GPIO_PinNumber * 2);
    // set bit
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

void GPIO_WritePin(GPIO_RegDef_t * GPIOx, uint8_t PinNumber, GPIO_PinState_e PinState){

    // if (PinState == GPIO_PIN_LOW){
    //     //clear the output pin
    //     GPIOx->ODR &= ~(0x01U << PinNumber);
    // }
    // else{
    //     // set the output pin
    //     GPIOx->ODR |= (0x01U << PinNumber);
    // }

    /*
        the above code can trigger race condition so im rewriting it
    */

    //This new code uses the BSRR which just writes to the reg in one go 
    /*
        the previous method requires read-modify-write which can be interupted by an isr
        and during the isr it can also write to the odr.
        when exiting the isr and I GO BACK  and rewrite what the isr did, this will cause bugs.
    */
    if (PinState == GPIO_PIN_LOW){
        GPIOx->BSRR = (0x01U << (PinNumber + 16)); // reset pin via BSRR
    }
    else{
        GPIOx->BSRR = (0x01U << PinNumber); // set pin via BSRR
    }
    
   
}

uint8_t GPIO_ReadPin(GPIO_RegDef_t * GPIOx, uint8_t PinNumber){
    uint8_t ret;
    /*
        bit shift the bit in question to the LSB position then mask
        it to clean the rest of the register so that
        only the bit in question is the only one left.
    */
    ret = (GPIOx->IDR >> PinNumber) & 0x01U;
    return ret;
}

void GPIO_TogglePin(GPIO_RegDef_t * GPIOx, uint8_t PinNumber){
    // so i need to find a register that keeps track of whether the gpio is outputtting or not
    // the register is ODR

    uint16_t OutputData = GPIOx->ODR;
    // next i need to mask this register with the PinNUmber parameter
    /*
        instead of the doing that i will resuse code from above
        this shifts the bit to the lsb position and we apply the AND function
        to isolate the lsb.
    */
    uint16_t OutputBit = (OutputData >> PinNumber) & 0x01U;

    if(OutputBit){
        GPIOx->ODR &= ~(0x01U << PinNumber); // clear output pin
    }
    else{
        GPIOx->ODR |= (0x01U << PinNumber); // set output pin
    }
}

void GPIO_LockPin(GPIO_RegDef_t * GPIOx, uint8_t PinNumber){
    uint32_t LockKey = (0x01 << 16U);
    uint32_t PortPin = (0x01 << PinNumber);

    LockKey |= PortPin;

    // Lock Key write sequence
    GPIOx->LCKR = LockKey | PortPin;
    GPIOx->LCKR = PortPin;
    GPIOx->LCKR = LockKey | PortPin;
    (void)GPIOx->LCKR;

}