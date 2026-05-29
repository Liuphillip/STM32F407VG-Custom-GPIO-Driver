#ifndef STM32F407XX_H
#define STM32F407XX_H

#include <stdint.h>

typedef struct 
{
    volatile uint32_t MODER;
    volatile uint32_t OTYPER;
    volatile uint32_t OSPEEDR;
    volatile uint32_t PUPDR;
    volatile uint32_t IDR;
    volatile uint32_t ODR;
    volatile uint32_t BSRR;
    volatile uint32_t LCKR;
    volatile uint32_t AFRL;
    volatile uint32_t AFRH;
}GPIO_RegDef_t;

/* peripheral base addresses */
#define AHB1_BASEADDR (0x40020000UL)
#define GPIOA ((GPIO_RegDef_t *) (AHB1_BASEADDR + 0x0000UL))
#define GPIOB ((GPIO_RegDef_t *) (AHB1_BASEADDR + 0x0400UL))
#define GPIOC ((GPIO_RegDef_t *) (AHB1_BASEADDR + 0x0800UL))
#define GPIOD ((GPIO_RegDef_t *) (AHB1_BASEADDR + 0x0C00UL))
#define GPIOE ((GPIO_RegDef_t *) (AHB1_BASEADDR + 0x1000UL))
#define GPIOF ((GPIO_RegDef_t *) (AHB1_BASEADDR + 0x1400UL))
#define GPIOG ((GPIO_RegDef_t *) (AHB1_BASEADDR + 0x1800UL))
#define GPIOH ((GPIO_RegDef_t *) (AHB1_BASEADDR + 0x1C00UL))
#define GPIOI ((GPIO_RegDef_t *) (AHB1_BASEADDR + 0x2000UL))
#define GPIOJ ((GPIO_RegDef_t *) (AHB1_BASEADDR + 0x2400UL))
#define GPIOK ((GPIO_RegDef_t *) (AHB1_BASEADDR + 0x2800UL))

#include "stm32f407xx_gpio_driver.h"

#endif