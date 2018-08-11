int pir = 4;

void setup() {
  Serial.begin(9600);
  pinMode(pir, INPUT);
}

void loop() {
  int pirState = digitalRead(pir);
  Serial.println(pirState);
  delay(10);
}
