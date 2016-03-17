/*
 * Stepper Motor Library for Stellaris/Tiva launchpads
 * Supports 28BYJ-48 Motor
 * All rights reserved.
 * Distributed under the BSD License
 * Copyright (c) 2015, Manolis Kiagias
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * --/COPYRIGHT--*/
 /*******************************************************************************/


#include <stepper.h>
int states[]={0b0001,0b0011,0b0010,0b0110,0b0100,0b1100,0b1000,0b1001};
int currentstate=0;

void initStepper(void)
{
	SysCtlPeripheralEnable(STEPPER_PERIPH);
	GPIOPinTypeGPIOOutput(STEPPER_PORT_BASE,  ALLINPINS);
	GPIOPinWrite(STEPPER_PORT_BASE, ALLINPINS ,0);
}

void stopStepper(void) {
	GPIOPinWrite(STEPPER_PORT_BASE, ALLINPINS, 0);
	if (--currentstate<0)
		currentstate=7;
}


void stepForward(int steps) {
	int n;
	for (n=0; n<steps; n++) {
		GPIOPinWrite(STEPPER_PORT_BASE, ALLINPINS,  states[currentstate++]);
		if (currentstate>7) currentstate=0;
		SysCtlDelay(10000);
	}
}

void stepBackward(int steps) {
	int n;
	for (n=steps; n>=0; n--) {
		GPIOPinWrite(STEPPER_PORT_BASE, ALLINPINS,  states[currentstate--]);
		if (currentstate<0) currentstate=7;
		SysCtlDelay(10000);
	}
}
