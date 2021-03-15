// Adafruit IO Publish Example
//
// Adafruit invests time and resources providing this open source code.
// Please support Adafruit and open source hardware by purchasing
// products from Adafruit!
//
// Written by Todd Treece for Adafruit Industries
// Copyright (c) 2016 Adafruit Industries
// Licensed under the MIT license.
//
// All text above must be included in any redistribution.

/************************** Configuration ***********************************/

// edit the config.h tab and enter your Adafruit IO credentials
// and any additional configuration needed for WiFi, cellular,
// or ethernet clients.
#include "config.h"

/************************ Example Starts Here *******************************/


#define IO_LOOP_DELAY 15000
unsigned long lastUpdate;

char data_sen0;
int count;

char data_sen[6];

char *val1;
char *val2;

float x_out;
float y_out;
float z_out;

// set up the 'counter' feed
AdafruitIO_Feed *xaxis = io.feed("xaxis");
AdafruitIO_Feed *yaxis = io.feed("yaxis");
AdafruitIO_Feed *zaxis = io.feed("zaxis");

AdafruitIO_Feed *boton1 = io.feed("boton1");
AdafruitIO_Feed *boton2 = io.feed("boton2");

void setup() {
  // Note the format for setting a serial port is as follows: Serial2.begin(baud-rate, protocol, RX pin, TX pin);
  Serial.begin(9600);

  // wait for serial monitor to open
  while(! Serial);

  // connect to io.adafruit.com
  io.connect();

  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    delay(500);
  } 
}

void loop() {

  //Leo los valores enviados por el PIC
  for(int i = 0; i <= 5; i++){
    if(Serial.available()){
      data_sen[i] = Serial.read();
    }
  }

  //Reviso si ya paso el tiempo mminimo para actualizar los datos en adafruit
  if (millis() > (lastUpdate + IO_LOOP_DELAY)) {
    io.run();

    Serial.println(data_sen[0], DEC);
    xaxis->save(data_sen[0]);

    Serial.println(data_sen[2], DEC);
    yaxis->save(data_sen[2]);

    Serial.println(data_sen[4], DEC);
    zaxis->save(data_sen[4]);

    //Tomo el dato actualizado
    boton1->get();
    boton2->get();
    
    boton1->onMessage(Boton1);
    boton2->onMessage(Boton2);
    
    // update timer
    lastUpdate = millis();
  }
}

//Funciones para encender luces
void Boton1(AdafruitIO_Data *data){
  val1 =  data->value();
  if(*val1 == '1'){
    Serial.write(1); 
  }
  else{
    Serial.write(2);
  }
  return;
}

void Boton2(AdafruitIO_Data *data){
  val2 =  data->value();
  if(*val2 == '1'){
    Serial.write(3); 
  }
  else {
    Serial.write(4);
  }
  return;
}
