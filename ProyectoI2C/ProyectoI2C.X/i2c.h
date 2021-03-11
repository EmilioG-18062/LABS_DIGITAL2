/* 
 * File:   i2c.h
 * Author: emili
 *
 * Created on 10 de marzo de 2021, 03:33 PM
 */

#ifndef I2C_H
#define	I2C_H

#include <xc.h>
#include <stdint.h>
#include <stdio.h>

void I2C_Master_Init(const unsigned long c);
void I2C_Master_Wait(void);
void I2C_Master_Start(void);
void I2C_Master_RepeatedStart(void);
void I2C_Master_Stop(void);
void I2C_Master_Write(unsigned d);
unsigned short I2C_Master_Read(unsigned short a);

#endif	/* I2C_H */

