/*
 * Document Dependency:
 * - Device: STM32F407
 * - Datasheet: RM0090 Reference manual
 */


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

// RCC register definition struct
typedef struct{
    volatile uint32_t CR;
    volatile uint32_t PLLCFGR;
    volatile uint32_t CFGR;
    volatile uint32_t CIR;
    volatile uint32_t AHB1RSTR;
    volatile uint32_t AHB2RSTR;
    volatile uint32_t AHB3RSTR;
             uint32_t RESERVED0;
    volatile uint32_t APB1RSTR;
    volatile uint32_t APB2RSTR;
             uint32_t RESERVED1[2];
    volatile uint32_t AHB1ENR;
    volatile uint32_t AHB2ENR;
    volatile uint32_t AHB3ENR;
             uint32_t RESERVED2;
    volatile uint32_t APB1ENR;
    volatile uint32_t APB2ENR;
             uint32_t RESERVED3[2];
    volatile uint32_t AHB1LPENR;
    volatile uint32_t AHB2LPENR;
    volatile uint32_t AHB3LPENR;
             uint32_t RESERVED4;
    volatile uint32_t APB1LPENR;
    volatile uint32_t APB2LPENR;
             uint32_t RESERVED5[2];
    volatile uint32_t BDCR;
    volatile uint32_t CSR;
    volatile uint32_t SSCGR;
    volatile uint32_t PLLI2SCFGR;

}RCC_RegDef_t;

// SYSCFG register definition struct
typedef struct{
    volatile uint32_t MEMRMP;
    volatile uint32_t PMC;
    volatile uint32_t EXTICR[4];
    volatile uint32_t CMPCR;
}SYSCFG_RegDef_t;

typedef struct{
    volatile uint32_t IMR;
    volatile uint32_t EMR;
    volatile uint32_t RTSR;
    volatile uint32_t FTSR;
    volatile uint32_t SWIER;
    volatile uint32_t PR;
}EXTI_RegDef_t;


/* peripheral base addresses */
// AHB1 peripheral base addresses
#define AHB1_BASEADDR (0x40020000UL)
// APB2 peripheral base addresses
#define APB2_BASEADDR (0x40010000UL)
#define GPIOA ((GPIO_RegDef_t *) (AHB1_BASEADDR + 0x0000UL))    // GPIO A base address
#define GPIOB ((GPIO_RegDef_t *) (AHB1_BASEADDR + 0x0400UL))    // GPIO B base address
#define GPIOC ((GPIO_RegDef_t *) (AHB1_BASEADDR + 0x0800UL))    // GPIO C base address
#define GPIOD ((GPIO_RegDef_t *) (AHB1_BASEADDR + 0x0C00UL))    // GPIO D base address
#define GPIOE ((GPIO_RegDef_t *) (AHB1_BASEADDR + 0x1000UL))    // GPIO E base address
#define GPIOF ((GPIO_RegDef_t *) (AHB1_BASEADDR + 0x1400UL))    // GPIO F base address
#define GPIOG ((GPIO_RegDef_t *) (AHB1_BASEADDR + 0x1800UL))    // GPIO G base address
#define GPIOH ((GPIO_RegDef_t *) (AHB1_BASEADDR + 0x1C00UL))    // GPIO H base address
#define GPIOI ((GPIO_RegDef_t *) (AHB1_BASEADDR + 0x2000UL))    // GPIO I base address
#define GPIOJ ((GPIO_RegDef_t *) (AHB1_BASEADDR + 0x2400UL))    // GPIO J base address
#define GPIOK ((GPIO_RegDef_t *) (AHB1_BASEADDR + 0x2800UL))    // GPIO K base address

// RCC base address
#define RCC ((RCC_RegDef_t * ) (AHB1_BASEADDR + 0x3800UL))
// SYSCFG base address
#define SYSCFG ((SYSCFG_RegDef_t *) (APB2_BASEADDR + 0x3800UL))
// EXTI base address
#define EXTI ((EXTI_RegDef_t *) (APB2_BASEADDR + 0x3C00UL))
// GPIO clock enable
#define GPIOA_CLK_ENB() (RCC->AHB1ENR |= (0x01U << 0U)) // GPIO A CLOCK ENABLE
#define GPIOB_CLK_ENB() (RCC->AHB1ENR |= (0x01U << 1U)) // GPIO B CLOCK ENABLE
#define GPIOC_CLK_ENB() (RCC->AHB1ENR |= (0x01U << 2U)) // GPIO C CLOCK ENABLE
#define GPIOD_CLK_ENB() (RCC->AHB1ENR |= (0x01U << 3U)) // GPIO D CLOCK ENABLE
#define GPIOE_CLK_ENB() (RCC->AHB1ENR |= (0x01U << 4U)) // GPIO E CLOCK ENABLE
#define GPIOF_CLK_ENB() (RCC->AHB1ENR |= (0x01U << 5U)) // GPIO F CLOCK ENABLE
#define GPIOG_CLK_ENB() (RCC->AHB1ENR |= (0x01U << 6U)) // GPIO G CLOCK ENABLE
#define GPIOH_CLK_ENB() (RCC->AHB1ENR |= (0x01U << 7U)) // GPIO H CLOCK ENABLE
#define GPIOI_CLK_ENB() (RCC->AHB1ENR |= (0x01U << 8U)) // GPIO I CLOCK ENABLE
// SYSCFG clock enable
#define SYSCFG_CLK_ENB() (RCC->APB2ENR |= (0x01U << 14U)) // SYSCFG CLOCK ENABLE

#define GPIOA_CLK_DIS() (RCC->AHB1ENR &= ~(0x01U << 0U)) // GPIO A CLOCK DISABLE
#define GPIOB_CLK_DIS() (RCC->AHB1ENR &= ~(0x01U << 1U)) // GPIO B CLOCK DISABLE
#define GPIOC_CLK_DIS() (RCC->AHB1ENR &= ~(0x01U << 2U)) // GPIO C CLOCK DISABLE
#define GPIOD_CLK_DIS() (RCC->AHB1ENR &= ~(0x01U << 3U)) // GPIO D CLOCK DISABLE
#define GPIOE_CLK_DIS() (RCC->AHB1ENR &= ~(0x01U << 4U)) // GPIO E CLOCK DISABLE
#define GPIOF_CLK_DIS() (RCC->AHB1ENR &= ~(0x01U << 5U)) // GPIO F CLOCK DISABLE
#define GPIOG_CLK_DIS() (RCC->AHB1ENR &= ~(0x01U << 6U)) // GPIO G CLOCK DISABLE
#define GPIOH_CLK_DIS() (RCC->AHB1ENR &= ~(0x01U << 7U)) // GPIO H CLOCK DISABLE
#define GPIOI_CLK_DIS() (RCC->AHB1ENR &= ~(0x01U << 8U)) // GPIO I CLOCK DISABLE



#include "stm32f407xx_gpio_driver.h"

#endif