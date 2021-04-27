// Electronica Digital - Laboratorio 4
//  Seccion 20
//  Emilio Gordillo, 18062

void setup_GPIOs();
void main()
{
 setup_GPIOs();
 while(1)
 {
 GPIO_PORTF_DATA1_bit = 1;
 GPIO_PORTF_DATA2_bit = 0;
 GPIO_PORTF_DATA3_bit = 0;
 delay_ms(900);
 GPIO_PORTF_DATA1_bit = 1;
 GPIO_PORTF_DATA2_bit = 1;
 GPIO_PORTF_DATA3_bit = 0;
 delay_ms(900);
 GPIO_PORTF_DATA1_bit = 0;
 GPIO_PORTF_DATA2_bit = 1;
 GPIO_PORTF_DATA3_bit = 0;
 delay_ms(900);
 GPIO_PORTF_DATA1_bit = 0;
 GPIO_PORTF_DATA2_bit = 1;
 GPIO_PORTF_DATA3_bit = 1;
 delay_ms(900);
 GPIO_PORTF_DATA1_bit = 0;
 GPIO_PORTF_DATA2_bit = 0;
 GPIO_PORTF_DATA3_bit = 1;
 delay_ms(900);
 GPIO_PORTF_DATA1_bit = 1;
 GPIO_PORTF_DATA2_bit = 0;
 GPIO_PORTF_DATA3_bit = 1;
 delay_ms(900);
 GPIO_PORTF_DATA1_bit = 1;
 GPIO_PORTF_DATA2_bit = 1;
 GPIO_PORTF_DATA3_bit = 1;
 delay_ms(900);
 }
}
void setup_GPIOs()
{ delay_ms(2000);
 
 GPIO_Clk_Enable(&GPIO_PORTF);
 
 GPIO_Config(&GPIO_PORTF,
 (_GPIO_PINMASK_1 | _GPIO_PINMASK_2 | _GPIO_PINMASK_3),
 _GPIO_DIR_OUTPUT,
 (_GPIO_CFG_DIGITAL_ENABLE | _GPIO_CFG_DRIVE_8mA),
 _GPIO_PINCODE_NONE);
}
