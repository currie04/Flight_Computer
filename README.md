# Flight Computer

This repository contains code and documentation related to the [NAME HERE] flight computer. The flight computer is currently built using breakouts for simplicity and cost-effectiveness, but will later be updated. 

## Parts
- ESP32 Microcontroller
- DPS310 Pressure Sensor
- RFM95W LoRa radio
- NEO6M72 GPS Module
- W25Q64 Flash
- MicroSD breakout
- ICM-20948 IMU
- DFR0570 Buck

## Block Diagram
![Block Diagram of the Flight Computer](Images/FC_Block_Diagram.png)

## Structure
In the esp32_fc folder, a [PlatformIO](https://platformio.org/platformio-ide) project has been created. This will allow us to use VSCode for programming.

The project can still run in the Arduino IDE with [these instructions](https://runningdeveloper.com/blog/platformio-project-to-arduino-ide/). We can also still utilise the arduino libraries for our breakouts, as PlatformIO will import them

## Dependencies


