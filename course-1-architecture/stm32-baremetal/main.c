/* 
 * Bare-metal UART2 Driver for STM32F401RE
 * Target: NUCLEO-F401RE with XNUCLEO IQS4A1A attached
 * Speeds: 115200 Baud, 8 Data Bits, 1 Stop Bit
 */

#include <stdint.h>
#include <stdbool.h>

/* Base Memory Boundaries (From RM0368 Reference Manual) */
#define PERIPHERAL_BASE 0x40000000U
#define AHB1_BASE       (PERIPHERAL_BASE + 0x00020000U)
#define APB1_BASE       PERIPHERAL_BASE

/* Specific Peripheral Addresses */
#define RCC_BASE        (AHB1_BASE + 0x3800U)
#define USART2_BASE     (APB1_BASE + 0x4400U)
#define GPIOA_BASE      (AHB1_BASE + 0x0000U)

/* Register Offsets */
#define RCC_AHB1ENR     (*(volatile uint32_t*)(RCC_BASE + 0x30U))
#define RCC_APB1ENR     (*(volatile uint32_t*)(RCC_BASE + 0x40U))

#define GPIOA_MODER     (*(volatile uint32_t*)(GPIOA_BASE + 0x00U))
#define GPIOA_AFRL      (*(volatile uint32_t*)(GPIOA_BASE + 0x20U))

#define USART2_SR       (*(volatile uint32_t*)(USART2_BASE + 0x00U))
#define USART2_DR       (*(volatile uint32_t*)(USART2_BASE + 0x04U))
#define USART2_BRR      (*(volatile uint32_t*)(USART2_BASE + 0x08U))
#define USART2_CR1      (*(volatile uint32_t*)(USART2_BASE + 0x0CU))

/* Transmission Function */
void uart2_write(int ch) {
    // Wait until transmit data register is empty (TXE bit 7)
    while (!(USART2_SR & (1 << 7))) {
        // Spin-lock
    }
    // Write character to data register
    USART2_DR = (ch & 0xFF);
}

/* Helper function to transmit whole strings */
void uart2_write_string(const char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        uart2_write(str[i]);
    }
}

int main(void) {
    /* ========================================= */
    /* STEP 1: ROUTE PERIPHERAL POWER (CLOCKS)   */
    /* ========================================= */
    
    // Enable GPIOA clock (Bit 0)
    RCC_AHB1ENR |= (1 << 0); 

    // Enable USART2 clock (Bit 17)
    RCC_APB1ENR |= (1 << 17);

    /* ========================================= */
    /* STEP 2: CONFIGURE PIN MODES (MODER)       */
    /* ========================================= */

    // Clear mode bits for PA2 (bits 4-5) and PA3 (bits 6-7) to guarantee 00
    GPIOA_MODER &= ~(3 << 4); 
    GPIOA_MODER &= ~(3 << 6); 

    // Set PA2 and PA3 to 10 (Alternate Function Mode)
    GPIOA_MODER |= (2 << 4);  
    GPIOA_MODER |= (2 << 6);  

    /* ========================================= */
    /* STEP 3: ASSIGN SPECIFIC FUNCTIONS (AFRL)  */
    /* ========================================= */

    // Clear 4-bit slots for PA2 (bits 8-11) and PA3 (bits 12-15)
    GPIOA_AFRL &= ~(15 << 8); 
    GPIOA_AFRL &= ~(15 << 12); 

    // Write Alternate Function 7 (USART2) to PA2 and PA3 slots
    GPIOA_AFRL |= (7 << 8);
    GPIOA_AFRL |= (7 << 12);

    /* ========================================= */
    /* STEP 4: CONFIGURE USART2 COMMUNICATIONS   */
    /* ========================================= */
    
    // Set Baud Rate Divider to 139 (16,000,000Hz / 115,200 baud)
    USART2_BRR = 139; 

    // Enable Transmitter (Bit 3) and Enable USART Peripheral (Bit 13)
    USART2_CR1 |= (1 << 3) | (1 << 13); 

    /* ========================================= */
    /* STEP 5: APPLICATION LOOP                  */
    /* ========================================= */
    
    // Transmit a welcome message once to signal success
    uart2_write_string("\r\n--- USART2 Bare-Metal Active ---\r\n");
    uart2_write_string("Hardware Setup: NUCLEO-F401RE + XNUCLEO IQS4A1A\r\n\r\n");

    while (true) {
        // Repeatedly send a pulse character to verify connection
        uart2_write_string("Nucleo Heartbeat (XNUCLEO IQS4A1A attached)...\r\n");
        
        // Software Delay to prevent terminal flooding
        for (volatile int i = 0; i < 1000000; i++) {
            // Spin-lock
        }
    }
    
    return 0;
}
