/*
NAME:         INNES MCCLAIR
CREATED:      14/11/2025
EDITED:       ""
PROJECT:      B-StaR Avionics board
DESCRIPTION:  900MHz RFM9x LoRa BREAKOUT BOARD

TO DO:        FIX TRANSMIT FOR FULL DATA OUT
              LORA OUTPUT TIMINGS, REDUCE TO ONE TRANSMISSION ~5s
              DECLARE PARAMETERS 
              NEED RECIEVER           
*/

#ifndef LoRa9x
#define LoRa9x

#include <LoRa.h>


class LoRa9x {
  public:
  void init() {
    LoRa.setPins(CS_LORA, RST_LORA, G0_LORA);  //OVERWRITE PIN DEFAULTS
    if (!LoRa.begin(BAND_LORA)){               //IF NOT AT LEGAL FREQ BAND
      Serial.println("B-StaR LoRa not connected?!?");
      while (1) yield();
    }
    SERIAL_PORT.println("LoRa is functional xox");

     //SPACE FOR PARAMETER SETTING
    LoRa.setTxPower(20);
  }

  /*** FIX FOR ACTUAL DATA ***/
  void transmit(const String& message ) {
    LoRa.beginPacket();
    LoRa.print(message);
    LoRa.endPacket(); //BOOL FOR SUCCESS
  }
};

#endif