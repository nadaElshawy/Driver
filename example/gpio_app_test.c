/*
 * main.c
 */
#include "../APP/app_gpio.h"
#include "../APP/app_uart.h"
#include "../SL/NVICInterruptHandler.h"
#define SCB_CPAC (*(( volatile unsigned int*)0xE000ED88))
void EnableInterrupts(void);
void DisableInterrupts(void);
gUARTObj_t UART;
gUARTInterrConfig_t UARTINT;
void interr(void) {
	//while(1);
	}

int main(void) {
	EnableInterrupts();
	//init
	UART.base=BASE_UART1;
  UART.BaudRate=115200;
	UART.UARTClkSource=System_clock;
  UART.DataFormate.Fifos_En=TRUE;
	UART.DataFormate.PariyType=PARITY_NONE;
	UART.DataFormate.word_Lenght=WordLength_8;
	UART.DataFormate.stop_bits=1;
	initUART(&UART);

//interrupt	
	UARTINT.BreakError =TRUE;
	UARTINT.ClearToSend=TRUE;
	UARTINT.FramingError=TRUE;
	UARTINT.Mode_9BIT=TRUE;
	UARTINT.OverrunError=TRUE;
	UARTINT.ParityError=TRUE;
	UARTINT.ReceiveTimeOutError=TRUE;
	UARTINT.RXFIFILevelSel=RX_FIFO_1_8;
	UARTINT.TXFIFILevelSel=TX_FIFO_7_8;	
	UARTInterruptConfig(BASE_UART1 , &UARTINT);
	installNIVCISRFunction(UART1, &interr);
	NVICInterruptEnable(UART1, 0, FALSE);
	
	//FlowControl
	UART1FlowControlSet( HW_RequestToSend, TRUE );
	while (1) {


	}
}


void SystemInit(){
SCB_CPAC |=0x00F00000;}
