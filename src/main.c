// Inspired from - https://github.com/OpenNuvoton/M031BSP/blob/master/SampleCode/Template/main.c

#include <stdio.h>
#include "NuMicro.h"

void UART_Open(UART_T *uart, uint32_t u32baudrate);

void SYS_Init(void)
{
    SYS_UnlockReg();

    CLK_EnableXtalRC(CLK_PWRCTL_HIRCEN_Msk);

    CLK_WaitClockReady(CLK_STATUS_HIRCSTB_Msk);

    CLK_SetHCLK(CLK_CLKSEL0_HCLKSEL_HIRC, CLK_CLKDIV0_HCLK(1));

    CLK_EnableModuleClock(UART0_MODULE);

    CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UART0SEL_HIRC, CLK_CLKDIV0_UART0(1));

    SystemCoreClockUpdate();

    SYS->GPB_MFPH = (SYS->GPB_MFPH & ~(SYS_GPB_MFPH_PB12MFP_Msk | SYS_GPB_MFPH_PB13MFP_Msk))    |       \
                    (SYS_GPB_MFPH_PB12MFP_UART0_RXD | SYS_GPB_MFPH_PB13MFP_UART0_TXD);

    SYS_LockReg();
}

int main()
{
    SYS_Init();

    UART_Open(UART0, 9600);

    printf("Hello World\n");

    while(1);
}
