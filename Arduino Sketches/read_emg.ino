// define sampling frequency :
int fs = 50 , period = 0 ;
unsigned long currentTime = 0 , previousTime = 0 ;
// select the input pin :
int readPin = A0 ;
int ledPin = 7 ;
// variable to store the value coming from the sensor :
int sensorValue = 0 ;
float x=0.0, x1=0.0, x2=0.0;
int y=0;

int filter(float x, float x1, float x2)
{
int out;
out=int((x+x1+x2)/3);
return(out);
}

void setup(){
Serial.begin(9600) ;
// compute waiting time from sampling f r e q u e n c y :
period = int(1000*1/(float)fs);
// Initialize LED pin as an output:
pinMode(ledPin, OUTPUT);
}

void loop() {
currentTime = millis() ;
if(currentTime - previousTime >= period) {
  //Serial.println(currentTime - previousTime);
previousTime = currentTime ;
// read t h e i n p u t on a n al og p in 0 :
float emgValue = analogRead(A0); // Read EMG data from analog pin A0
sensorValue = emgValue * 3300 / 1023;
//Serial.println(emgValue); 
x2=x1;
x1=x;
x = float(sensorValue); // read values (0 to 1023) from the input pin
// Digital signal processing (Filtering)
y=filter(x,x1,x2);
delay(0.02);

//Check if the sensor value exceeds 1150:
if (y > 1150) {
  digitalWrite(ledPin, HIGH); // Turn on the LED
} else {
  digitalWrite(ledPin, LOW); // Turn off the LED
}
// p r i n t ou t t h e v a l u e you read :
Serial.print(0); // To freeze the lower limit
Serial.print(" ");
Serial.print(1150); // To freeze the upper limit
Serial.print(" ");
//Serial.println(sensorValue);
Serial.println(y); 
}
}


