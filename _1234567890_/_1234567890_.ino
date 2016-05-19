/*
 * IRremote: IRrecvDemo - demonstrates receiving IR codes with IRrecv
 * An IR detector/demodulator must be connected to the input RECV_PIN.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */

#include <IRremote.h>

int RECV_PIN = 11;

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
}

void loop() {
  if (irrecv.decode(&results)) {
    //Serial.println(results.value, HEX);
    
    switch ( results.value ) {
    case 0xFF6897:
        Serial.println("1");
        break;
    case 0xFF9867:
        Serial.println("2");
        break;
    case 0xFFB04F:
        Serial.println("3");
        break;
    case 0xFF30CF:
        Serial.println("4");
        break;
    case 0xFF18E7:
        Serial.println("5");
        break;
    case 0xFF7A85:
        Serial.println("6");
        break;
    case 0xFF10EF:
        Serial.println("7");
        break;
    case 0xFF38C7:
        Serial.println("8");
        break;
    case 0xFF5AA5:
        Serial.println("9");
        break;
    case 0xFF4AB5:
        Serial.println("0");
        break;
    case 0xFF02FD:
        Serial.println("ok");
        break;
    case 0xFF42BD:
        Serial.println("*");
        break;
    case 0xFF52AD:
        Serial.println("#");
        break;
    case 0xFF629D:
        Serial.println("u");
        break;
    case 0xFFA857:
        Serial.println("d");
        break;
    case 0xFF22DD:
        Serial.println("l");
        break;
    case 0xFFC23D:
        Serial.println("r");
        break;
    default: 
        Serial.println("-");
        break;   
    }     
    
    
    irrecv.resume(); // Receive the next value
  }
  delay(100);
}
