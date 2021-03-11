/* 
 * File:   adxl345.h
 * Author: emili
 *
 * Created on 10 de marzo de 2021, 05:40 PM
 */

#ifndef ADXL345_H
#define	ADXL345_H

#include "i2c.h"

void adxl345_write(int add, int data);
int adxl345_read(int add);
void adxl345_init();

#endif	/* ADXL345_H */

