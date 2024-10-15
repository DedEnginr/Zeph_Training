
#include <zephyr/irq.h>
#include <zephyr/arch/arm/cortex_m/nvic.h>

void

typedef uint32_t IRQn_Type;

#define PendSV_IRQn -2

/* Need to keep the remaining from cmsis.h, as Zephyr expects these. 
typedef enum {
	//Reset_IRQn                    = -15,
	//NonMaskableInt_IRQn           = -14,
	//HardFault_IRQn                = -13,
	//MemoryManagement_IRQn         = -12,
	//BusFault_IRQn                 = -11,
	//UsageFault_IRQn               = -10,
	//SVCall_IRQn                   =  -5,
	//DebugMonitor_IRQn             =  -4,
	//PendSV_IRQn                   =  -2,
	//SysTick_IRQn                  =  -1,
} CMSIS_IRQn_Type;
*/
#define __NVIC_PRIO_BITS               NUM_IRQ_PRIO_BITS

#include <core_cm0plus.h>
