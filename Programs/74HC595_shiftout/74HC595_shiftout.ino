int _datapin = 4;
int _clockpin = 6;
int _latchpin = 5;
void setup() {
  pinMode(_datapin, OUTPUT);
   pinMode(_clockpin, OUTPUT);
   pinMode(_latchpin, OUTPUT);
  digitalWrite(_latchpin, LOW);
    shiftOut(_datapin, _clockpin, MSBFIRST, B11111001);  
    digitalWrite(_latchpin, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:

}

void shift595()
{
    digitalWrite(_latchpin, LOW);
    shiftOut(_datapin, _clockpin, MSBFIRST, B11111001);  
    digitalWrite(_latchpin, HIGH);
}
