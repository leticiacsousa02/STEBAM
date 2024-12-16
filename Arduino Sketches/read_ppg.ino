const int pin_ppg = A0;
int value_ppg = 0;
int threshold = 500;

void setup() {
  pinMode(A0,INPUT);
  Serial.begin(9600);
}

void loop()
{
  value_ppg = analogRead(pin_ppg);
  if (value_ppg > threshold){
    digitalWrite(LED_BUILTIN, HIGH); 
  }
  else{
    digitalWrite(LED_BUILTIN, LOW); 
  }
  Serial.println(value_ppg);
  Serial.print(",");
  Serial.print(550);
  Serial.print(",");
  Serial.print(490);
  Serial.print("\r");
  Serial.print("\n");

Serial.print(threshold);
Serial.print("\r");
  Serial.print("\n");
}


