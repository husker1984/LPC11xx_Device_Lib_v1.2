/** ***************************************************************************
 * @file     lpc11xx_crt0.c
 * @brief    Low-level memory initialization code for LPC11xx CPUs
 * @version  V1.0
 * @author   Tymm Twillman
 * @date     3. January 2012
 * @license  Simplified BSD License
 ******************************************************************************
 * Copyright (c) 2012, Timothy Twillman
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *
 *    1. Redistributions of source code must retain the above copyright notice,
 *        this list of conditions and the following disclaimer.
 *
 *    2. Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED ''AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL
 * TIMOTHY TWILLMAN OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * The views and conclusions contained in the software and documentation are
 * those of the authors and should not be interpreted as representing official
 * policies, either expressed or implied, of Timothy Twillman.
 *****************************************************************************/

/* Includes -----------------------------------------------------------------*/

#include "lpc11xx.h"
#include "lpc11xx/isr_vector.h"


/* External Declarations ----------------------------------------------------*/

/* A basic definition for main() to allow us to call it. */
int main();

/* These are provided by the linker */
extern unsigned long _bss_start, _bss_end;
extern unsigned long _data_start, _data_src_start, _data_end;
extern unsigned long _stack;
extern unsigned long __checksum__;
extern unsigned long _init_array_start;
extern unsigned long _init_array_end;
extern unsigned long _fini_array_start;
extern unsigned long _fini_array_end;


/* System Global Variables --------------------------------------------------*/

/*! @brief System Exception & Interrupt Vectors */
__attribute__ ((section(".boot_isr_vector")))
const ISRVector_Type BootISRVector = {
    .Stack_Addr                      = &_stack,
    .Reset_Handler_Vect              = Reset_Handler,
    .HardFault_Handler_Vect          = HardFault_Handler,
    .Checksum                        = &__checksum__,
    .SVC_Handler_Vect                = SVC_Handler,
    .PendSV_Handler_Vect             = PendSV_Handler,
    .SysTick_Handler_Vect            = SysTick_Handler,
    .PIO0_0_Wakeup_IRQHandler_Vect   = PIO0_0_Wakeup_IRQHandler,
    .PIO0_1_Wakeup_IRQHandler_Vect   = PIO0_1_Wakeup_IRQHandler,
    .PIO0_2_Wakeup_IRQHandler_Vect   = PIO0_2_Wakeup_IRQHandler,
    .PIO0_3_Wakeup_IRQHandler_Vect   = PIO0_3_Wakeup_IRQHandler,
    .PIO0_4_Wakeup_IRQHandler_Vect   = PIO0_4_Wakeup_IRQHandler,
    .PIO0_5_Wakeup_IRQHandler_Vect   = PIO0_5_Wakeup_IRQHandler,
    .PIO0_6_Wakeup_IRQHandler_Vect   = PIO0_6_Wakeup_IRQHandler,
    .PIO0_7_Wakeup_IRQHandler_Vect   = PIO0_7_Wakeup_IRQHandler,
    .PIO0_8_Wakeup_IRQHandler_Vect   = PIO0_8_Wakeup_IRQHandler,
    .PIO0_9_Wakeup_IRQHandler_Vect   = PIO0_9_Wakeup_IRQHandler,
    .PIO0_10_Wakeup_IRQHandler_Vect  = PIO0_10_Wakeup_IRQHandler,
    .PIO0_11_Wakeup_IRQHandler_Vect  = PIO0_11_Wakeup_IRQHandler,
    .PIO1_0_Wakeup_IRQHandler_Vect   = PIO1_0_Wakeup_IRQHandler,
    .SSP1_IRQHandler_Vect            = SSP1_IRQHandler,
    .I2C0_IRQHandler_Vect             = I2C0_IRQHandler,
    .CT16B0_IRQHandler_Vect          = CT16B0_IRQHandler,
    .CT16B1_IRQHandler_Vect          = CT16B1_IRQHandler,
    .CT32B0_IRQHandler_Vect          = CT32B0_IRQHandler,
    .CT32B1_IRQHandler_Vect          = CT32B1_IRQHandler,
    .SSP0_IRQHandler_Vect            = SSP0_IRQHandler,
    .UART0_IRQHandler_Vect           = UART0_IRQHandler,
    .ADC0_IRQHandler_Vect            = ADC0_IRQHandler,
    .WDT_IRQHandler_Vect             = WDT_IRQHandler,
    .BOD_IRQHandler_Vect             = BOD_IRQHandler,
    .PIO3_IRQHandler_Vect            = PIO3_IRQHandler,
    .PIO2_IRQHandler_Vect            = PIO2_IRQHandler,
    .PIO1_IRQHandler_Vect            = PIO1_IRQHandler,
    .PIO0_IRQHandler_Vect            = PIO0_IRQHandler,
};


/* Functions ----------------------------------------------------------------*/

/** @brief Undefined Exception Handler (infinite loop)
  * @param None.
  *
  * @return None.
  */
void UndefinedException_Handler(void) __attribute__((weak, section(".startup") ));
void UndefinedException_Handler(void)
{
    while(1);
}


/** @brief Function for iterating through & calling global / static constructors
  * @param None.
  *
  * @return None.
  *
  * Called on system bring-up.
  */
void __libc_init_array(void) __attribute__((weak, section(".startup") ));
void __libc_init_array()
{
    unsigned long iptr;


    for (iptr = (unsigned long)&_init_array_start;
         iptr < (unsigned long)&_init_array_end;
         iptr++)
    {
        (*((void (*)())iptr))();
    }
}


/** @brief Function for iterating through & calling global / static destructors
  * @param None.
  *
  * @return None.
  *
  * Called on exit from main()
  */
void __libc_fini_array(void) __attribute__((weak, section(".startup") ));
void __libc_fini_array()
{
    unsigned long fptr;


    for (fptr = (unsigned long)&_fini_array_start;
         fptr < (unsigned long)&_fini_array_end;
         fptr++)
    {
        (*((void (*)())fptr))();
    }
}


/** @brief  Initial entry point for bringing system up.
  *
  * @return None.
  *
  * Calls _sysinit() to prep hardware (core clocks, etc), then initializes BSS and
  * DATA segments, calls global / static constructors, then calls main().
  * If main() returns, calls global / static destructors then goes into an
  * infinite loop.
  */
void _start(void) __attribute__((section (".startup") )) __attribute__((naked));
void _start()
{
    unsigned long *x;
    unsigned long *y;

	/* Clear BSS area */
    for (x = &_bss_start; x < &_bss_end; x++) {
        *x = 0;
    }

	/* Copy data area from flash */
    for (x = &_data_start,y = &_data_src_start; x < &_data_end; x++,y++) {
        *x = *y;
    }

    SystemInit();

    /* Do after copying data, since SystemInit modifies some variables...
     * Call global / static constructors
     */
    __libc_init_array();

	/* Call main() function... */
    main();

    /* Call global / static destructors */
    __libc_fini_array();

_main_exited: /* Loop forever. */
    goto _main_exited;
}

