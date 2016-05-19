

#define RELE_1 9
#define RELE_2 8

#define ON 0
#define OFF 1

void setup() {                
  digitalWrite(RELE_1, OFF); 
  digitalWrite(RELE_2, OFF);   
  pinMode(RELE_1, OUTPUT);   
  pinMode(RELE_2, OUTPUT);  
}

void loop() {
  digitalWrite(RELE_1, ON); 
  delay(10000);             
  digitalWrite(RELE_1, OFF); 
  delay(10000);            
  digitalWrite(RELE_2, ON); 
  delay(10000);             
  digitalWrite(RELE_2, OFF); 
  delay(10000); 
  digitalWrite(RELE_1, ON); 
  digitalWrite(RELE_2, ON); 
  delay(10000);             
  digitalWrite(RELE_1, OFF);
  digitalWrite(RELE_2, OFF); 
  delay(10000);            
}

