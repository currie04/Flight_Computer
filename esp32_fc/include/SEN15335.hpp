/*
NAME:         INNES MCCLAIR
CREATED:      14/11/2025
EDITED:       ""
PROJECT:      B-StaR Avionics board
DESCRIPTION:  SEN-15335 IMU sensor header file
              IMU object
              basic serial datalogging

TO DO:        IMPLEMENT SHIMU?
              MEANINGFUL DATA OUT
                         
*/

#ifndef SEN15335
#define SEN15335
#include <ICM_20948.h>

//SPARKFUN IMU -> ICM_20948
class IMU_SF {  
  public:
  void init() {
    ICM.begin(WIRE_PORT);  //ad0 val default = 1
  }

  void serialOut() {  //BASIC SERIAL OUT FOR DEBUG
    if (ICM.dataReady()){
      ICM.getAGMT();
      printScaledAGMT(&ICM);
    }
  }
  
  private:
    ICM_20948_I2C ICM;    //SPARKFUN LIBRARY OBJECT

    /* --------------- ORLENA HELPER FUNCTIONS ----------------- */
    void printFormattedFloat(float val, uint8_t leading, uint8_t decimals)
    {
      float aval = abs(val);
      if (val < 0) SERIAL_PORT.print("-");
      else SERIAL_PORT.print(" ");
      for (uint8_t indi = 0; indi < leading; indi++)
      {
        uint32_t tenpow = 0;
        if (indi < (leading - 1)) tenpow = 1;
        for (uint8_t c = 0; c < (leading - 1 - indi); c++) tenpow *= 10;
        if (aval < tenpow) SERIAL_PORT.print("0");
        else break;
      }
      SERIAL_PORT.print(val, decimals);
    }

    void printScaledAGMT(ICM_20948_I2C *sensor)
    {
      SERIAL_PORT.print("ICM-20948 Acc (mg) [ ");
      printFormattedFloat(sensor->accX(), 5, 2);
      SERIAL_PORT.print(", ");
      printFormattedFloat(sensor->accY(), 5, 2);
      SERIAL_PORT.print(", ");
      printFormattedFloat(sensor->accZ(), 5, 2);
      SERIAL_PORT.print(" ], Gyr (DPS) [ ");
      printFormattedFloat(sensor->gyrX(), 5, 2);
      SERIAL_PORT.print(", ");
      printFormattedFloat(sensor->gyrY(), 5, 2);
      SERIAL_PORT.print(", ");
      printFormattedFloat(sensor->gyrZ(), 5, 2);
      SERIAL_PORT.print(" ], Mag (uT) [ ");
      printFormattedFloat(sensor->magX(), 5, 2);
      SERIAL_PORT.print(", ");
      printFormattedFloat(sensor->magY(), 5, 2);
      SERIAL_PORT.print(", ");
      printFormattedFloat(sensor->magZ(), 5, 2);
      SERIAL_PORT.print(" ], Tmp (C) [ ");
      printFormattedFloat(sensor->temp(), 5, 2);
      SERIAL_PORT.print(" ]");
      SERIAL_PORT.println();
    }
};
#endif