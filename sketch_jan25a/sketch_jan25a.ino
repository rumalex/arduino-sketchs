void setup () {
pinMode(A2,INPUT); //A2 пин — на вход сигнала

Serial.begin(9600); //связь с компьютером 9600 бит/с
}
void loop () {
int t = analogRead(A2); //читаем значение с A2
Serial.println(t); //пишем это значение в //последовательный порт (для нас это USB)

delay(500); // немного ждём
}
