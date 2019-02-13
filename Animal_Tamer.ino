/*********************************************************
This is a library for the MPR121 12-channel Capacitive touch sensor

Designed specifically to work with the MPR121 Breakout in the Adafruit shop 
  ----> https://www.adafruit.com/products/

These sensors use I2C communicate, at least 2 pins are required 
to interface

Adafruit invests time and resources providing this open source code, 
please support Adafruit and open-source hardware by purchasing 
products from Adafruit!

Written by Limor Fried/Ladyada for Adafruit Industries.  
BSD license, all text above must be included in any redistribution
**********************************************************/

//This is a modified version of the MPR121 example file provided by Adafruit. 
//Additions were made to interface with the Cytron MP3 shield. Modified by Willy P Feb 2019

#include <Wire.h>
#include "Adafruit_MPR121.h"

#ifndef _BV
#define _BV(bit) (1 << (bit)) 
#endif

// This includes the library needed to run the MP3 Shield
#include <CytronEZMP3.h>
CytronEZMP3 mp3;

boolean toggle = true;

// You can have up to 4 on one i2c bus but one is enough for testing!
Adafruit_MPR121 cap = Adafruit_MPR121();

// Keeps track of the last pins touched
// so we know when buttons are 'released'
uint16_t lasttouched = 0;
uint16_t currtouched = 0;

void setup() {
  Serial.begin(9600);

  while (!Serial) { // needed to keep leonardo/micro from starting too fast!
    delay(10);
  }
  
  Serial.println("Adafruit MPR121 Capacitive Touch sensor test"); 
  
  // Default address is 0x5A, if tied to 3.3V its 0x5B
  // If tied to SDA its 0x5C and if SCL then 0x5D
  if (!cap.begin(0x5A)) {
    Serial.println("MPR121 not found, check wiring?");
    while (1);
  }
  Serial.println("MPR121 found!");
  
  if (!mp3.begin(2, 3));
  mp3.setDevice(2);
  mp3.setVolume(10);
}

void loop() {
  // Get the currently touched pads
  currtouched = cap.touched();
  
  for (uint8_t i=0; i<12; i++) {
    // it if *is* touched and *wasnt* touched before, alert!
    if ((currtouched & _BV(i)) && !(lasttouched & _BV(i)) ) {
      Serial.print(i); Serial.println(" touched");
    }
    // if it *was* touched and now *isnt*, alert!
    if (!(currtouched & _BV(i)) && (lasttouched & _BV(i)) ) {
      Serial.print(i); Serial.println(" released");
    }
  }

//This is the code that recognizes touch inputs from the conductive thread and plays
//the corrisponding sound from the SD card in the MP3 Shield
  if (cap.touched() & (1 << 1)) {
    if (toggle){
      mp3.playTrack(1);
      while (cap.touched() & (1 << 1));
      delay(20); 
      }
    }
  if (cap.touched() & (1 << 3)) {
    if (toggle){
      mp3.playTrack(2);
      while (cap.touched() & (1 << 1));
      delay(20);
      }
    }
  if (cap.touched() & (1 << 5)) {
    if (toggle){
      mp3.playTrack(3);
      while (cap.touched() & (1 << 1));
      delay(20);
      }
    }
  if (cap.touched() & (1 << 7)) {
    if (toggle){
      mp3.playTrack(4);
      while (cap.touched() & (1 << 1));
      delay(20);
      }
    }
  if (cap.touched() & (1 << 9)) {
    if (toggle){
      mp3.playTrack(5);
      while (cap.touched() & (1 << 1));
      delay(20);
      }
    }
  if (cap.touched() & (1 << 11)) {
    if (toggle){
      mp3.playTrack(6);
      while (cap.touched() & (1 << 1));
      delay(20);
      }
    }
  
  // reset our state
  lasttouched = currtouched;

  // comment out this line for detailed data from the sensor!
  return;
  
  // debugging info, what
  Serial.print("\t\t\t\t\t\t\t\t\t\t\t\t\t 0x"); Serial.println(cap.touched(), HEX);
  Serial.print("Filt: ");
  for (uint8_t i=0; i<12; i++) {
    Serial.print(cap.filteredData(i)); Serial.print("\t");
  }
  Serial.println();
  Serial.print("Base: ");
  for (uint8_t i=0; i<12; i++) {
    Serial.print(cap.baselineData(i)); Serial.print("\t");
  }
  Serial.println();
  
  // put a delay so it isn't overwhelming
  delay(100);
}
