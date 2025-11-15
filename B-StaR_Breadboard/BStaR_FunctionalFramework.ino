/*
NAME:         INNES MCCLAIR
CREATED:      14/11/2025
EDITED:       ""
PROJECT:      B-StaR Avionics board
DESCRIPTION:  testing top file

TO DO:        IMPLEMENT ALL PERIPHERALS
              CHANGE DELAY IN LOOP? MESS ABOUT AND FIND MAX SAMPLE RATE
*/

#define SERIAL_PORT   Serial
#define WIRE_PORT     Wire

/**** INCLUDE LIBRARIES ****/
#include "esp.hpp"
#include "dps310.hpp"
#include "SEN15335.hpp"
#include "LoRa9x.hpp"
#include <Wire.h>
#include <SPI.h>

/**** INSTANTIATE ALL PERIPHERALS ****/
DPS310 dps;
IMU_SF imu;
LoRa9x rfm;

/**** INITIALISATION ****/
void setup() {
  Serial.begin(115200);
  while (!SERIAL_PORT) { ; }

  WIRE_PORT.begin();
  WIRE_PORT.setClock(400000);

  dps.init();
  imu.init();
  rfm.init();
}

/**** ACTIVE LOOP ****/
/*** ALL BASIC TESTING, NEED INTEGRATION ***/
void loop() {
  dps.serialOut();
  imu.serialOut();
  rfm.transmit("Hi");  

  SERIAL_PORT.println(" ");
  delay(200);       //CHANGE AS REQUIRED
}