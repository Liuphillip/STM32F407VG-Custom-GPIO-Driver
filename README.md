# STM32F407 Bare-Metal GPIO Driver

A custom GPIO peripheral driver written from scratch in C for the STM32F407VGT6 microcontroller, targeting the STM32F4-Discovery board. No HAL, no CMSIS peripheral abstractions — register access only.

## What I Built

- **Device header** (`header/stm32f407xx.h`) — memory-mapped register structs and base addresses for the GPIO and RCC peripherals, plus clock enable/disable macros for GPIO ports A–I
- **GPIO driver** (`header/stm32f407xx_gpio_driver.h` / `src/stm32f407xx_gpio_driver.c`) — a clean API over the raw GPIO registers
- **Demo application** (`src/main.c`) — button-triggered LED toggle running on real hardware

## GPIO Driver API

```c
void    GPIO_Init(GPIO_RegDef_t *GPIOx, GPIO_PinConf_t conf);
void    GPIO_WritePin(GPIO_RegDef_t *GPIOx, uint8_t pin, GPIO_PinState_e state);
uint8_t GPIO_ReadPin(GPIO_RegDef_t *GPIOx, uint8_t pin);
void    GPIO_TogglePin(GPIO_RegDef_t *GPIOx, uint8_t pin);
```

### Pin Configuration

`GPIO_Init` accepts a `GPIO_PinConf_t` struct that covers every option exposed by the STM32F4 GPIO peripheral:

| Field | Options |
|---|---|
| Mode | Input, Output, Alternate Function, Analog |
| Output type | Push-pull, Open-drain |
| Output speed | Low, Medium, High, Very High |
| Pull-up/Pull-down | None, Pull-up, Pull-down |
| Alternate function | AF0–AF15 |

## Design Decisions Worth Noting

**Atomic pin writes via BSRR** — `GPIO_WritePin` uses the Bit Set/Reset Register instead of read-modify-write on ODR. A read-modify-write sequence can be interrupted by an ISR that also writes to ODR, corrupting the pin state. BSRR is a write-only register that sets or clears a pin in a single bus cycle, eliminating the race condition.

**Register struct layout** — GPIO and RCC peripherals are mapped by casting a base address pointer to a `volatile` struct. Each register field is `volatile uint32_t` to prevent the compiler from optimizing out hardware accesses. Reserved fields are included as non-volatile padding to keep struct offsets aligned with the reference manual.

## Demo: Button-Toggled LED

The application initializes all four Discovery board LEDs (PD12–PD15) and the onboard user button (PA0). Pressing the button toggles the blue LED (PD15) with a 20 ms debounce delay and waits for release before re-arming.

```c
if (GPIO_ReadPin(GPIOA, GPIO_PIN_NUM_0) == GPIO_PIN_HIGH) {
    delay_ms(20);
    GPIO_TogglePin(GPIOD, GPIO_PIN_NUM_15);
    while (GPIO_ReadPin(GPIOA, GPIO_PIN_NUM_0) == 1);
}
```

## Hardware

- **MCU:** STM32F407VGT6 (Cortex-M4, 168 MHz)
- **Board:** STM32F4-Discovery
- **Toolchain:** Keil MDK (µVision)

## Project Structure

```
├── header/
│   ├── stm32f407xx.h              # Device register map and clock macros
│   └── stm32f407xx_gpio_driver.h  # GPIO driver interface
└── src/
    ├── stm32f407xx_gpio_driver.c  # GPIO driver implementation
    └── main.c                     # Demo application
```
