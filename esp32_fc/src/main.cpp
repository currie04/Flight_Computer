/****************************************************************
 * Integrated Example: ICM-20948 IMU + DPS310 Pressure/Temp
 * I2C only
 ***************************************************************/
#include <Arduino.h>
#include "ICM_20948.h"       // SparkFun ICM-20948 library
#include <Adafruit_DPS310.h> // Adafruit DPS310 library

#define SERIAL_PORT Serial
#define WIRE_PORT Wire
#define AD0_VAL 1   // ICM-20948 I2C address bit (default 1)

ICM_20948_I2C myICM;   // ICM-20948 object (I2C)
Adafruit_DPS310 dps;   // DPS310 object

// -------------------- SETUP --------------------
void setup()
{
  SERIAL_PORT.begin(115200);
  while (!SERIAL_PORT) { ; }

  WIRE_PORT.begin();
  WIRE_PORT.setClock(400000);

  // ---- Initialize ICM-20948 ----
  bool initialized = false;
  while (!initialized)
  {
    myICM.begin(WIRE_PORT, AD0_VAL);

    SERIAL_PORT.print(F("ICM-20948 init: "));
    SERIAL_PORT.println(myICM.statusString());
    if (myICM.status != ICM_20948_Stat_Ok)
    {
      SERIAL_PORT.println("Retrying ICM...");
      delay(500);
    }
    else
    {
      initialized = true;
    }
  }

  // ---- Initialize DPS310 ----
  SERIAL_PORT.println("Initializing DPS310...");
  if (!dps.begin_I2C()) {
    SERIAL_PORT.println("Failed to find DPS310!");
    while (1) yield();
  }
  SERIAL_PORT.println("DPS310 OK!");

  dps.configurePressure(DPS310_64HZ, DPS310_64SAMPLES);
  dps.configureTemperature(DPS310_64HZ, DPS310_64SAMPLES);
}

// -------------------- HELPER FUNCTIONS --------------------
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


// -------------------- LOOP --------------------
void loop()
{
  // ---- ICM-20948 ----
  if (myICM.dataReady())
  {
    myICM.getAGMT();
    printScaledAGMT(&myICM);
  }
  else
  {
    SERIAL_PORT.println("Waiting for IMU data...");
  }

  // ---- DPS310 ----
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

  SERIAL_PORT.println();
  delay(200); // Adjust rate as needed
}