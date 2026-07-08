.syntax unified
.cpu cortex-m4
.thumb

.global _vectors
.global _reset_handler

/* The Vector Table (Placed at the very beginning of Flash Memory) */
.section .isr_vector, "a", %progbits
_vectors:
    .word   0x20014000      /* 1. Initial Stack Pointer (Top of 80KB SRAM) */
    .word   _reset_handler  /* 2. Reset Vector (Address where execution starts) */

/* The Reset Handler Code */
.section .text
_reset_handler:
    /* Jump directly to main() function in main.c */
    bl      main
    
    /* Trap the processor if main ever returns */
_infinite_loop:
    b       _infinite_loop
