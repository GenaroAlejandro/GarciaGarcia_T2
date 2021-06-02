#include <stdio.h>
#include "fsl_clock.h"
#include "fsl_gpio.h"
#include "fsl_port.h"
#include "fsl_common.h"

void SW2 (void);
void SW3 (void);

gpio_pin_config_t led_config = {
        kGPIO_DigitalOutput,
        1,
    };

gpio_pin_config_t sw_config = {
        kGPIO_DigitalInput,
        0,
    };
#define DELAY 1000000u
#define waiting 50000u
#define CORE_FREQ 21000000u
#define PIN26      26u
#define PIN22      22u
#define PIN21      21u
#define PIN6        6u
#define PIN4        4u



int main(void) {
	//Función de la API para habilitar el reloj del multiplexor
	//kCLOCK_Portx: Macro con el valor en el registro SCGC5 del PORTA, PORTB, PORTC y PORTE
	 CLOCK_EnableClock(kCLOCK_PortA);
	 CLOCK_EnableClock(kCLOCK_PortB);
	 CLOCK_EnableClock(kCLOCK_PortC);
	 CLOCK_EnableClock(kCLOCK_PortE);
	 //Activación del pin como GPIO en el registro PCR para el puerto PORTA, PORTB, PORTC y PORTC
	 //PORTx: Puerto (base)/ PINn: Macro con el número del pin del Puerto A, B, C y E/kPORT_MuxAsGpio: Macro para activación del pin como GPIO
	 PORT_SetPinMux(PORTE, PIN26, kPORT_MuxAsGpio);
	 PORT_SetPinMux(PORTB, PIN22, kPORT_MuxAsGpio);
	 PORT_SetPinMux(PORTB, PIN21, kPORT_MuxAsGpio);
	 PORT_SetPinMux(PORTC, PIN6, kPORT_MuxAsGpio);
	 PORT_SetPinMux(PORTA, PIN4, kPORT_MuxAsGpio);


	 //Función para la configuración del pin como entrada o salida
	 GPIO_PinInit(GPIOE, PIN26, &led_config);
	 GPIO_PinInit(GPIOB, PIN22, &led_config);
	 GPIO_PinInit(GPIOB, PIN21, &led_config);
	 GPIO_PinInit(GPIOC, PIN6, &sw_config);
	 GPIO_PinInit(GPIOA, PIN4, &sw_config);



    while(1) {
    	//SDK_DelayAtLeastUs(waiting,CORE_FREQ);
    	if((!GPIO_PinRead(GPIOC,PIN6))&&(!GPIO_PinRead(GPIOC,PIN6)))
    	{
  		  //Blanco
      	  GPIO_PortClear(GPIOB, 1u << PIN22);
      	  GPIO_PortClear(GPIOB, 1u << PIN21);
      	  GPIO_PortClear(GPIOE, 1u << PIN26);
      	  SDK_DelayAtLeastUs(DELAY,CORE_FREQ);

    	}
		if(!GPIO_PinRead(GPIOA,PIN4))
        {
			GPIO_PortSet(GPIOB, 1u << PIN22);
			GPIO_PortSet(GPIOB, 1u << PIN21);
			GPIO_PortSet(GPIOE, 1u << PIN26);
      	    SW3();
        }

        else if(!GPIO_PinRead(GPIOC,PIN6))
        {
			GPIO_PortSet(GPIOB, 1u << PIN22);
			GPIO_PortSet(GPIOB, 1u << PIN21);
			GPIO_PortSet(GPIOE, 1u << PIN26);
        	SW2();
        }


    }
    return 0 ;
}

void SW2 (void)
{
	//Amarillo
	GPIO_PortClear(GPIOB, 1u << PIN22);
	GPIO_PortClear(GPIOE, 1u << PIN26);
	SDK_DelayAtLeastUs(DELAY,CORE_FREQ);
	GPIO_PortSet(GPIOB, 1u << PIN22);
	GPIO_PortSet(GPIOE, 1u << PIN26);

	//Rojo
	GPIO_PortClear(GPIOB, 1u << PIN22);
	SDK_DelayAtLeastUs(DELAY,CORE_FREQ);
	GPIO_PortSet(GPIOB, 1u << PIN22);

	//Morado
	GPIO_PortClear(GPIOB, 1u << PIN22);
	GPIO_PortClear(GPIOB, 1u << PIN21);
	SDK_DelayAtLeastUs(DELAY,CORE_FREQ);
	GPIO_PortSet(GPIOB, 1u << PIN22);
	GPIO_PortSet(GPIOB, 1u << PIN21);

	//Azúl
	GPIO_PortClear(GPIOB, 1u << PIN21);
	SDK_DelayAtLeastUs(DELAY,CORE_FREQ);
	GPIO_PortSet(GPIOB, 1u << PIN21);

	//VERDE
	GPIO_PortClear(GPIOE, 1u << PIN26);
	SDK_DelayAtLeastUs(DELAY,CORE_FREQ);
	GPIO_PortSet(GPIOE, 1u << PIN26);
}

void SW3 (void)
{
	//VERDE
	GPIO_PortClear(GPIOE, 1u << PIN26);
    SDK_DelayAtLeastUs(DELAY,CORE_FREQ);
    GPIO_PortSet(GPIOE, 1u << PIN26);

    //Azúl
	GPIO_PortClear(GPIOB, 1u << PIN21);
	SDK_DelayAtLeastUs(DELAY,CORE_FREQ);
	GPIO_PortSet(GPIOB, 1u << PIN21);

	//Morado
	GPIO_PortClear(GPIOB, 1u << PIN22);
	GPIO_PortClear(GPIOB, 1u << PIN21);
	SDK_DelayAtLeastUs(DELAY,CORE_FREQ);
	GPIO_PortSet(GPIOB, 1u << PIN22);
	GPIO_PortSet(GPIOB, 1u << PIN21);

	//Rojo
	GPIO_PortClear(GPIOB, 1u << PIN22);
	SDK_DelayAtLeastUs(DELAY,CORE_FREQ);
	GPIO_PortSet(GPIOB, 1u << PIN22);


    //Amarillo
	GPIO_PortClear(GPIOB, 1u << PIN22);
	GPIO_PortClear(GPIOE, 1u << PIN26);
	SDK_DelayAtLeastUs(DELAY,CORE_FREQ);
	GPIO_PortSet(GPIOB, 1u << PIN22);
	GPIO_PortSet(GPIOE, 1u << PIN26);

}

//Función para establecer un valor lógico de 1 en el PINn, configurado como salida (con registro PCOR)
//GPIOx: Periferico x/ 1u << PINn: Máscara para poner a 1 el valor de salida del PINn
//Función para establecer un valor lógico de 1 en el pin 22, configurado como salida (con registro PSOR)
