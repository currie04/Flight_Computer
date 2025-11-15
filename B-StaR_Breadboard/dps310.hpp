/*
NAME:         INNES MCCLAIR
CREATED:      14/11/2025
EDITED:       ""
PROJECT:      B-StaR Avionics board
DESCRIPTION:  dps310 pressure sensor header file
              DPS310 object
              basic serial datalogging

TO DO:        CHANGE FORMATTING?
              MEANINGFUL DATA OUT
*/

#ifndef dps310
#define dps310
#include <Adafruit_DPS310.h>

class DPS310 {
  public:
  void init() {
    if (!dps.begin_I2C(DPS_ADDR, &WIRE_PORT)){
      Serial.println("B-StaR DPS not connected, please check :)");
      while (1) yield();
    }
    SERIAL_PORT.println("DPS is functional xox");
    dps.configurePressure(DPS310_64HZ, DPS310_64SAMPLES);
    dps.configureTemperature(DPS310_64HZ, DPS310_64SAMPLES);
  }

  void serialOut() {  //BASIC SERIAL OUT FOR DEBUG
    sensors_event_t temp_event, pressure_event;
    if (dps.temperatureAvailable() && dps.pressureAvailable())
    {
      dps.getEvents(&temp_event, &pressure_event);
      SERIAL_PORT.print(F("DPS310 Temp = "));
      SERIAL_PORT.print(temp_event.temperature);
      SERIAL_PORT.print(" *C, Pressure = ");
      SERIAL_PORT.print(pressure_event.pressure);
      SERIAL_PORT.println(" hPa");
    }
  }
  private:
    Adafruit_DPS310 dps;
};
#endif



