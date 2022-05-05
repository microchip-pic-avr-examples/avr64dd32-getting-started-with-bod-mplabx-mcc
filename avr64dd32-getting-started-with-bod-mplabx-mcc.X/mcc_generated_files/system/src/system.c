/**
 * System Driver Source File
 * 
 * @file system.c
 * 
 * @ingroup systemdriver
 * 
 * @brief This is the generated driver implementation file for the System Driver.
 *
 * @version Driver Version 1.0.1
*/
/*
© [2022] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/

 /**
   Section: Included Files
 */
#include "../system.h"

/**
 * Initializes MCU, drivers and middleware in the project
**/

static bod_vlm_cb_t bod_vlm_callback;

int8_t BOD_Initialize();

void SYSTEM_Initialize(void)
{
    PIN_MANAGER_Initialize();
    BOD_Initialize();
    CLOCK_Initialize();
    CPUINT_Initialize();
}

int8_t BOD_Initialize()
{
    //SLEEP Disabled; 
    ccp_write_io((void*)&(BOD.CTRLA),0x4);
    //
    BOD.CTRLB = 0x1;
    //VLMCFG VDD crosses VLM threshold; VLMIE enabled; 
    BOD.INTCTRL = 0x5;
    //VLMIF disabled; 
    BOD.INTFLAGS = 0x0;
    //
    BOD.STATUS = 0x0;
    //VLMLVL VLM threshold 25% above BOD level; 
    BOD.VLMCTRLA = 0x3;

    return 0;
}

void BOD_VLM_Set_Callback(bod_vlm_cb_t pcb)
{
    bod_vlm_callback = pcb;
}

ISR(BOD_VLM_vect)
{
	if(bod_vlm_callback != NULL)
    {
        bod_vlm_callback();
    }

	/* The interrupt flag has to be cleared manually */
	BOD.INTFLAGS = BOD_VLMIE_bm;
}

