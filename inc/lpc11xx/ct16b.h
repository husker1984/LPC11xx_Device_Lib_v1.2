/*****************************************************************************
 * @file:    ct16b.h
 * @purpose: 16 Bit Counter/Timer Interface Header for NXP LPC Microcontrollers
 * @version: V1.0
 * @author:  Tymm Twillman
 * @date:    1. January 2012
 * @license: Simplified BSD License
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

#ifndef NXP_LPC_CT16B_H_
#define NXP_LPC_CT16B_H_

#ifdef __cplusplus
extern "C" {
#endif


/* Includes -----------------------------------------------------------------*/

#include <stdint.h>

#include "lpc11xx.h"
#include "lpc11xx/lib_assert.h"


/**
  * @defgroup CT16B_Access_Interface Counter/Timer (16-bit) Access-level Interface
  * @ingroup  LPC_Peripheral_Access_Layer
  * @{
  */

/* Typedefs -----------------------------------------------------------------*/

/**
  * @defgroup CT16B_Types CT16B Access-level Interface Types and Definitions
  * @{
  */

/** @defgroup CT16B_Interrupt_Types CT16B Interrupt Sources
  * NOTE: LPC11xx doesn't support captures 1-3.
  * @{
  */

#if !defined(LPC11XX)
# define CT16B_IT_Mask                       (0xff)        /*!< All Valid Bits in Interrupt Reg  */
#else
# define CT16B_IT_Mask                       (0x1f)        /*!< All Valid Bits in Interrupt Reg  */
#endif

#define CT16B_IT_MR0                        (1 << 0)       /*!< Match on Match Register 0        */
#define CT16B_IT_MR1                        (1 << 1)       /*!< Match on Match Register 1        */
#define CT16B_IT_MR2                        (1 << 2)       /*!< Match on Match Register 2        */
#define CT16B_IT_MR3                        (1 << 3)       /*!< Match on Match Register 3        */
#define CT16B_IT_CR0                        (1 << 4)       /*!< Trigger of Capture Input 0       */

#if !defined(LPC11XX)
# define CT16B_IT_CR1                       (1 << 5)       /*!< Trigger of Capture Input 1       */
# define CT16B_IT_CR2                       (1 << 6)       /*!< Trigger of Capture Input 2       */
# define CT16B_IT_CR3                       (1 << 7)       /*!< Trigger of Capture Input 3       */
#endif

/** @} */

/** @defgroup CT16B_Match_Control_Types CT16B Actions to take on a match
  * @{
  */

/* Note: these are actions per match register.  Actions can be ORed together. */
#define CT16B_MatchControl_Mask             (0x07)         /*!< All valid Match Control bits     */

#define CT16B_MatchControl_None             (0x00)         /*!< Do nothing on match              */
#define CT16B_MatchControl_Interrupt        (1 << 0)       /*!< Generate IRQ on match            */
#define CT16B_MatchControl_Reset            (1 << 1)       /*!< Reset the timer/counter on match */
#define CT16B_MatchControl_Stop             (1 << 2)       /*!< Stop the timer/counter on match  */

/** @} */

/** @defgroup CT16B_Capture_Control_Types CT16B External Capture Settings
  * @{
  */

/* Note: these are actions per capture control register.  Actions can be ORed together. */
#define CT16B_CaptureControl_Mask           (0x07)         /*!< All valid Capture Control bits   */

#define CT16B_CaptureControl_None           (0x00)         /*!< Do not monitor capture pin       */
#define CT16B_CaptureControl_RisingEdges    (1 << 0)       /*!< Capture count on rising edges    */
#define CT16B_CaptureControl_FallingEdges   (1 << 1)       /*!< Capture count on falling edges   */
#define CT16B_CaptureControl_Interrupt      (1 << 2)       /*!< Generate an interrupt on capture */

/** @} */

/** @defgroup CT16B_Ext_Match_Control_Types CT16B External Match Output Controls
  * @{
  */

/*! CT16B External Match Control Configurations */
typedef enum {
    CT16B_ExtMatchControl_None = 0x00,                     /*!< No output on timer/ctr match     */
    CT16B_ExtMatchControl_Clear,                           /*!< Set output lo on timer/ctr match */
    CT16B_ExtMatchControl_Set,                             /*!< Set output hi on timer/ctr match */
    CT16B_ExtMatchControl_Toggle,                          /*!< Toggle output on timer/ctr match */
} CT16B_ExtMatchControl_Type;

/*! Macro to test whether parameter is a valid Counter / Timer External Match Control setting */
#define CT16B_IS_EXT_MATCH_CONTROL(Control) (((Control) == CT16B_ExtMatchControl_None)  \
                                          || ((Control) == CT16B_ExtMatchControl_Clear) \
                                          || ((Control) == CT16B_ExtMatchControl_Set)   \
                                          || ((Control) == CT16B_ExtMatchControl_Toggle))

/** @} */

/** @defgroup CT16B_Mode_Types CT16B Mode Configuration Controls
  * @{
  */

/*! CT16B Mode Configurations */
typedef enum {
    CT16B_Mode_Timer = 0x00,                               /*!< Timer Mode                       */
    CT16B_Mode_CountRisingEdges,                           /*!< Count mode; count Rising Edges   */
    CT16B_Mode_CountFallingEdges,                          /*!< Count mode; count falling edges  */
    CT16B_Mode_CountAllEdges,                              /*!< Count mode; count all edges      */
} CT16B_Mode_Type;

/*! Macro to test whether parameter is a valid Counter / Timer Mode setting */
#define CT16B_IS_MODE(Mode)  (((Mode) == CT16B_Mode_Timer)             \
                           || ((Mode) == CT16B_Mode_CountRisingEdges)  \
                           || ((Mode) == CT16B_Mode_CountFallingEdges) \
                           || ((Mode) == CT16B_Mode_CountAllEdges))

/** @} */

/**
  * @}
  */

/* Inline Functions ---------------------------------------------------------*/

/**
  * @defgroup CT16B_INLINE_Functions CT16B Access-level Inline Functions
  *
  * @{
  */

/** @brief  Enable a Timer
  * @param  Timer      The Timer to Enable
  * @return The "Match" Value of the Match Channel
  */
__INLINE static void CT16B_Enable(CT16B_Type *Timer)
{
    Timer->TCR |= CT16B_CE;
}

/** @brief  Disable a Timer
  * @param  Timer      The Timer to Disable
  * @return The "Match" Value of the Match Channel
  */
__INLINE static void CT16B_Disable(CT16B_Type *Timer)
{
    Timer->TCR &= ~CT16B_CE;
}

/** @brief  Determine Whether a Timer Is Enabled
  * @param  Timer     The Timer
  * @return 1 if the TImer is Enabled, 0 Otherwise
  */
__INLINE static uint8_t CT16B_IsEnabled(CT16B_Type *Timer)
{
    return (Timer->TCR & CT16B_CE) ? 1:0;
}

/** @brief  Set the Operation Mode for a Timer
  * @param  Timer     The Timer
  * @param  Mode      The Timer's Mode Configuration
  * @return None.
  *
  * Mode can be one of:
  * - CT16B_Mode_Timer             -- Timer mode
  * - CT16B_Mode_CountRisingEdges  -- Counter mode, Count Rising Edges on CAP Input
  * - CT16B_Mode_CountFallingEdges -- Counter mode, Count Falling Edges on CAP Input
  * - CT16B_Mode_CountAllEdges     -- Counter mode, Count All Edges on CAP Input
  */
__INLINE static void CT16B_SetMode(CT16B_Type *Timer, CT16B_Mode_Type Mode)
{
    lpclib_assert(CT16B_IS_MODE(Mode));
    Timer->CTCR = Mode;
}

/** @brief  Get the Currently Configured Mode for a Timer
  * @param  Timer     The Timer
  * @return The Currently Active Mode for the Timer
  */
__INLINE static CT16B_Mode_Type CT16B_GetMode(CT16B_Type *Timer)
{
    return Timer->CTCR;
}

/** @brief  Reset a Timer (stays reset until cleared)
  * @param  Timer      The Timer
  * @return None.
  */
__INLINE static void CT16B_AssertReset(CT16B_Type *Timer)
{
    Timer->TCR |= CT16B_CR;
}

/** @brief  Clear a Timer's RESET State
  * @param  Timer      The Timer
  * @return None.
  */
__INLINE static void CT16B_DeassertReset(CT16B_Type *Timer)
{
    Timer->TCR &= ~CT16B_CR;
}

/** @brief Determine Whether a Timer is Being Held in Reset
  * @return 1 if the Reset Line is Set, 0 Otherwise.
  */
__INLINE static uint8_t CT16B_ResetIsAsserted(CT16B_Type *Timer)
{
    return (Timer->TCR & CT16B_CR) ? 1:0;
}

/** @brief  Get the Pending Interrupts for a Timer
  * @param  Timer
  * @return Bit mask of Pending Interrupts
  */
__INLINE static uint8_t CT16B_GetPendingIT(CT16B_Type *Timer)
{
    return Timer->IR;
}

/** @brief  Clear Pending Interrupts on a Timer
  * @param  Timer      The Timer
  * @param  Interrupts Bits Specifying which Interrupts to clear
  * @return None.
  */
__INLINE static void CT16B_ClearPendingIT(CT16B_Type *Timer, uint8_t Interrupts)
{
    lpclib_assert((Interrupts & ~CT16B_IT_Mask) == 0);
    Timer->IR = Interrupts;
}

/** @brief  Set the Count Value of a Timer
  * @param  Timer      The Timer
  * @param  Count      The New Count Value
  * @return None.
  */
__INLINE static void CT16B_SetCount(CT16B_Type *Timer, uint16_t Count)
{
    Timer->TC = Count;
}

/** @brief  Get the Current Count Value of a Timer
  * @param  Timer      The Timer
  * @return The Timer's Current Count
  */
__INLINE static uint16_t CT16B_GetCount(CT16B_Type *Timer)
{
    return Timer->TC;
}

/** @brief  Set the Prescaler of a Timer
  * @param  Timer      The Timer
  * @param  Prescaler  The New Prescaler
  * @return None.
  *
  * Prescaler of a Timer is the # of input clocks or counts before
  *  the timer increments.  Changing this changes the number of
  *  counts before each increment of the timer/counter.
  */
__INLINE static void CT16B_SetPrescaler(CT16B_Type *Timer, uint16_t Prescaler)
{
    Timer->PR = Prescaler;
}

/** @brief  Get the Prescaler of a Timer
  * @param  Timer      The Timer
  * @return The Timer's Current Prescaler
  *
  * Prescaler of a Timer is the # of input clocks or counts before
  *  the timer increments.  Changing this changes the number of
  *  counts before each increment of the timer/counter.
  */
__INLINE static uint16_t CT16B_GetPrescaler(CT16B_Type *Timer)
{
    return Timer->PR;
}

/** @brief  Set the Prescaler Count Value of a Timer
  * @param  Timer      The Timer
  * @param  Count  The New Prescaler Count
  * @return None.
  *
  * This is the number of prescaler "ticks" thus far on the way to the
  *  next count increment.
  */
__INLINE static void CT16B_SetPrescalerCount(CT16B_Type *Timer, uint16_t Count)
{
    Timer->PC = Count;
}

/** @brief  Get the Current Prescaler Count Value of a Timer
  * @param  Timer      The Timer
  * @return The Timer's Current Prescaler Count Value
  *
  * This is the number of prescaler "ticks" thus far on the way to the
  *  next count increment.
  */
__INLINE static uint16_t CT16B_GetPrescalerCount(CT16B_Type *Timer)
{
    return Timer->PC;
}

/** @brief  Set the Actions that will Happen when the Count Equals a "Match" Channel
  * @param  Timer      The Timer on which to operate
  * @param  Channel    The Channel on that Timer for which to Configure Actions
  * @param  Control    The Action(s) to be Taken, ORed Together
  * @return None.
  *
  * Valid Actions (OR together):
  * - CT16B_MatchControl_None
  * - CT16B_MatchControl_Interrupt (Interrupt on match)
  * - CT16B_MatchControl_Reset     (Reset counter to 0 on match)
  * - CT16B_MatchControl_Stop      (Stop counter on match)
  */
__INLINE static void CT16B_SetChannelMatchControl(CT16B_Type *Timer, unsigned int Channel, uint8_t Control)
{
    lpclib_assert(Channel <= 3);
    lpclib_assert((Control & ~CT16B_MatchControl_Mask) == 0);

    Timer->MCR = (Timer->MCR & ~(0x07 << (Channel * 3))) | (Control << (Channel * 3));
}

/** @brief  Get the Actions that are Configured to Occur when a Channel Matches a Timer's Count
  * @param  Timer      The Timer
  * @param  Channel    The Channel on the Timer
  * @return The Currently Configured Action Control Bits, ORed together
  */
__INLINE static uint8_t CT16B_GetChannelMatchControl(CT16B_Type *Timer, unsigned int Channel)
{
    lpclib_assert(Channel <= 3);

    return (Timer->MCR >> (Channel * 3)) & 0x07;
}

/** @brief  Set the "Match" Value on one Channel of a Timer
  * @param  Timer      The Timer
  * @param  Channel    The Channel on the Timer on which to Configure the "Match" Value
  * @param  Count      The Count Value on which the Match Channel should Trigger
  * @return None.
  */
__INLINE static void CT16B_SetChannelMatchValue(CT16B_Type *Timer, unsigned int Channel, uint16_t Count)
{
    lpclib_assert(Channel <= 3);

    ((__IO uint32_t *)&Timer->MR0)[Channel] = Count;
}

/** @brief  Get the "Match" Value of a Timer's Channel
  * @param  Timer      The Timer
  * @param  Channel    The Channel on the Timer for which to get the Match Value
  * @return The "Match" Value Configured on the given Channel
  */
__INLINE static uint16_t CT16B_GetChannelMatchValue(CT16B_Type *Timer, unsigned int Channel)
{
    lpclib_assert(Channel <= 3);

    return ((__IO uint32_t *)&Timer->MR0)[Channel];
}

/** @brief Set the Functionality of an External Match Pin / Bit
  * @param  Timer    The Timer
  * @param  Channel  The Channel on the Timer for which to Configure the External Match Function
  * @param  Control  The Functionality of the External Match Pin / Bit
  * @return None.
  *
  * Note that regardless of whether a pin is configured for external match duty,
  *  there is a bit that reflects the state of the External Match value.
  *
  * Control can be:
  * - CT16B_ExtMatchControl_None
  * - CT16B_ExtMatchControl_Clear  - Clear the pin / bit on match of channel
  * - CT16B_ExtMatchControl_Set    - Set the pin / bit on match of channel
  * - CT16B_ExtMatchControl_Toggle - Toggle the pin / bit on match of channel
  */
__INLINE static void CT16B_SetChannelExtMatchControl(CT16B_Type *Timer, unsigned int Channel, CT16B_ExtMatchControl_Type Control)
{
    lpclib_assert(Channel <= 3);
    lpclib_assert(CT16B_IS_EXT_MATCH(Control));

    Timer->EMR = (Timer->EMR & ~(0x03 << ((Channel * 2) + 4))) | (Control << ((Channel * 2) + 4));
}

/** @brief Get the Configured Functionality of an External Match Pin / Bit
  * @param  Timer    The Timer
  * @param  Channel  The Channel on the Timer for which to get the External Match Configuration
  * @return The Configuration of the External Match Pin / Bit
  */
__INLINE static CT16B_ExtMatchControl_Type CT16B_GetChannelExtMatchControl(CT16B_Type *Timer, unsigned int Channel)
{
    lpclib_assert(Channel <= 3);

    return (Timer->EMR >> ((Channel * 2) + 4)) & 0x03;
}

/** @brief Set the Value of a Timer Channel's External Match bit
  * @param  Timer    The Timer
  * @param  Channel  The Timer's Channel on which to set the External Match Bit's Value
  * @param  Value    Whether to Set or Clear the Bit (Zero means Clear, Non-Zero means Set)
  * @return None.
  */

__INLINE static void CT16B_SetChannelExtMatchBit(CT16B_Type *Timer, unsigned int Channel, unsigned int Value)
{
    lpclib_assert(Channel <= 3);

    if (Value) {
        Timer->EMR |= (1 << Channel);
    } else {
        Timer->EMR &= ~(1 << Channel);
    }
}

/** @brief Get the Value of the Given Timer Channel's External Match Bit
  * @param  Timer    The Timer
  * @param  Channel  The Timer's Channel for which to get the External Match Bit
  * @return The Value of the Timer's Channel's External Match Bit
  */
__INLINE static uint8_t CT16B_GetChannelExtMatchBit(CT16B_Type *Timer, unsigned int Channel)
{
    lpclib_assert(Channel <= 3);

    return (Timer->EMR & (1 << Channel)) ? 1:0;
}

/** @brief  Enable a PWM Channel on a Timer
  * @param  Timer      The Timer
  * @param  Channel    The Timer's Channel on which to enable PWM
  * @return None.
  *
  * If enabled, a PWM channel controls the External Match pin / bit; if disabled,
  *  it's under external match control.
  */
__INLINE static void CT16B_EnableChannelPWM(CT16B_Type *Timer, unsigned int Channel)
{
    lpclib_assert(Channel <= 3);

    Timer->PWMC |= (1 << Channel);
}

/** @brief  Disable a PWM Channel on a Timer
  * @param  Timer      The Timer
  * @param  Channel    The Timer's Channel on which to disable PWM
  * @return None.
  *
  * If enabled, a PWM channel controls the External Match pin / bit; if disabled,
  *  it's under external match control.
  */
__INLINE static void CT16B_DisableChannelPWM(CT16B_Type *Timer, unsigned int Channel)
{
    lpclib_assert(Channel <= 3);

    Timer->PWMC &= ~(1 << Channel);
}

/** @brief  Determine Whether a Timer's Channel is Configured for PWM Operation
  * @param  Timer      The Timer
  * @param  Channel    The Timer's Channel for which to get PWM Configuration
  * @return 1 if the channel is Configured for PWM operation, 0 if not.
  *
  * If enabled, a PWM channel controls the External Match pin / bit; if disabled,
  *  it's under external match control.
  */
__INLINE static uint8_t CT16B_ChannelPWMIsEnabled(CT16B_Type *Timer, unsigned int Channel)
{
    lpclib_assert(Channel <= 3);

    return (Timer->PWMC & (1 << Channel)) ? 1:0;
}

/** @brief  Configure the Capture Input on a Timer/Counter
  * @param  Timer      The Timer for which to Configure a Capture Input
  * @param  Channel    The Channel for which to Configure the Capture Input
  * @param  Control    The capture input configuration bits (ORed together)
  * @return None.
  *
  * Control can be:
  * - CT16B_CaptureControl_None
  * - CT16B_CaptureControl_RisingEdges  (capture on rising edges)
  * - CT16B_CaptureControl_FallingEdges (capture on falling edges)
  * - CT16B_CaptureControl_Interrupt    (interrupt on capture)
  *
  * MUST be CT16B_CaptureControl_None if counter mode is selected on timer.
  */
__INLINE static void CT16B_SetCaptureControl(CT16B_Type *Timer, unsigned int Channel, uint8_t Control)
{
#ifdef LPC11XX
    /* LPC11xx has only one capture channel */
    lpclib_assert(Channel == 0);
#else
    lpclib_assert(Channel <= 3);
#endif

    lpclib_assert((Control & ~CT16B_CaptureControl_Mask) == 0);

    Timer->CCR = Control;
}

/** @brief  Get the Capture Input Configuration for a Timer's Channel
  * @param  Timer      The Timer
  * @return The Configured Control Bits (Capture on Rising / Falling / Both, Whether to Raise IRQ, etc)
  */
__INLINE static uint8_t CT16B_GetCaptureControl(CT16B_Type *Timer)
{
    return Timer->CCR;
}

/** @brief  Get the Captured Count Value from the Given Timer Channel
  * @param  Timer      The Timer
  * @param  Channel    The timer channel for which to get the capture value
  * @return Captured Count Value for the Timer Channel.
  * NOTE: (only 1 count capture channel -- Channel 0 -- on LPC11xx)
  */
__INLINE static uint16_t CT16B_GetCaptureValue(CT16B_Type *Timer, unsigned int Channel)
{
#ifdef LPC11XX
    /* LPC11xx has only one capture channel */
    lpclib_assert(Channel == 0);
#else
    lpclib_assert(Channel <= 3);
#endif

    return ((uint16_t *)&(Timer->CR0))[Channel];
}

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
};
#endif

#endif /* #ifndef NXP_LPC_CT16B_H_ */
