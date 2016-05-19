#include <PS2Keyboard.h>

const int DataPin = 3;
const int IRQpin =  4;

PS2Keyboard keyboard;

void setup() {
  delay(1000);
  keyboard.begin(DataPin, IRQpin);
  Serial.begin(9600);
  Serial.println("Keyboard Test:");
}

void loop() {
  if (keyboard.available()) {
    
    // read the next key
    char c = keyboard.read();
    
        
      // otherwise, just print all normal characters
      Serial.print(c);
    
  }
}
