/**************************************************************************//**
 * @file     power_api.h
 * @brief    Power Profile API Interface Header for LPC11xxL Microcontrollers.
 * @version  V1.0
 * @author   Tymm Twillman
 * @date     1. January 2012
 ******************************************************************************
 * @section Overview
 * This file gives a basic interface to NXP LPC11xxL microcontroller
 * Power Profile API (ROM based interface to power control on the
 * chips).  It allows setting of the microcontroller's PLL and performance.
 ******************************************************************************
 * @section License
 * Licensed under a Simplified BSD License:
 *
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

#ifndef POWER_API_H_
#define POWER_API_H_


#ifdef __cplusplus
extern "C" {
#endif

/* Includes -----------------------------------------------------------------*/

#include <stdint.h>
#include "lpc11xx.h"
#include "lpclib_assert.h"


/**
  * @defgroup PowerAPI Power Profile API Interface
  * @ingroup  ROM
  * @{
  */

/* Defines ------------------------------------------------------------------*/

/** @defgroup PowerAPI_Definitions Power Profile API Interface Definitions
  * @{
  */

#define POWERAPI_ENTRY_POINT     (0x1fff2004UL)     /*!< Power API entry location in ROM */

/** @} */


/* Types & Type-Related Definitions -----------------------------------------*/

/** @defgroup PowerAPI_Types Power API Interface Types and Type-Related Definitions
  * @ingroup  PowerAPI
  * @{
  */

typedef enum {
    PowerAPI_PLLMode_Equal = 0,
    PowerAPI_PLLMode_LessOrEqual,
    PowerAPI_PLLMode_GreaterOrEqual,
    PowerAPI_PLLMode_Approximate
} PowerAPI_PLLMode_Type;

typedef enum {
    PowerAPI_Status_Success = 0,
    PowerAPI_Status_InvalidFrequency,
    PowerAPI_Status_InvalidMode,
    PowerAPI_Status_FreqNotFound,
    PowerAPI_Status_PLLNotLocked
} PowerAPI_Status_Type;

typedef enum {
    PowerAPI_PowerMode_Default = 0,
    PowerAPI_PowerMode_Performance,
    PowerAPI_PowerMode_Efficiency,
    PowerAPI_PowerMode_LowCurrent
} PowerAPI_PowerMode_Type;

/**
  * @}
  */


/* Exported Functions -------------------------------------------------------*/

/** @defgroup POWER_Exported_Functions Power Profile Exported Functions
  * @{
  */

/** @brief Set the system PLL to a something like the given frequency via Power Profile interface
  * @param[in]  desired_sysclock  The desired clock rate at which to run the CPU
  * @param[in]  pll_match_mode        The
  * @param[in]  max_tries
  * @return PowerAPI_Status_Type value giving success or the reason the call failed.
  */
PowerAPI_Status_Type PowerAPI_SetPLLFreq(uint32_t desired_sysclock,
                                                 PowerAPI_PLLMode_Type pll_mode,
                                                 uint32_t max_tries);

/** @brief  Set the system power mode to the desired setting via Power Profile interface
  * @param  power_mode           The desired power mode (performance, efficiency, etc.)
  * @return PowerAPI_Status_Type value giving success or the reason the call failed.
  */
PowerAPI_Status_Type PowerAPI_SetPowerMode(PowerAPI_PowerMode_Type power_mode);

/** @} */

#ifdef __cplusplus
};
#endif

#endif /* #ifndef POWER_API_H_ */
