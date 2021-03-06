/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "MKL25Z4.h"
#include "TSI.h"
#include "UART.h"
#include "ADC.h"
#include "log.h"
#include "LED.h"
#include "I2C.h"
#include "timer.h"
#include "TSL2561.h"
#include "humidity.h"
#include "Message.h"

CI_Msg msg;

int main(void)
{
	uint32_t i;
	uint8_t id1,id2;
	uint16_t touch_val;

	led_pwm_init();
	tsi_init();
	UART0_init();
	i2c_init();
	ADC_Init();
	tsl_init();

	init_buff(&tx_buff,2000);//initialize TX buffer of 100 bytes
	init_buff(&rx_buff,2000);//initialize RX buffer of 100 bytes
	//log0("Welcome");

	while(1){
		if(rx_buff .num_items == 5){
			__asm("cpsid i");
			Read_CI_Msg(&msg);
			__asm("cpsie i");
			Decode_CI_Msg(&msg);
		}
		touch_val=scan_touch();
		if(touch_val>80)
			LED_select(BLUE,(touch_val-70)*10);
	}

    return 0;
}
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
