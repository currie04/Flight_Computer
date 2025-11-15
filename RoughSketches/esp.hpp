/*
NAME:         INNES MCCLAIR
CREATED:      14/11/2025
EDITED:       ""
PROJECT:      B-StaR Avionics board
DESCRIPTION:  header file containing esp data inc pinout
*/

#ifndef esp_pinout
#define esp_pinout

//I2C PINOUT
#define SDA         21
#define SCL         22

//I2C ADDRESSES
#define DPS_ADDR    0x77
//#define IMU_AD0_VAL 1   //NOT REQ, DEFAULT TO 1 IN DEFINITION


//SPI PINOUT
#define MISO        19
#define MOSI        23
#define SCK         18

//SPI CHIP SELECT
#define CS_LORA     5
#define CS_FLASH    16
#define CS_SD       17

//EXTRA LORA PINOUT
#define G0_LORA     26
#define RST_LORA    14

#endif