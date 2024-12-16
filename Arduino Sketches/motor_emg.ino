#include <Servo.h>

Servo servo;  // Create a servo object

// define sampling frequency :
int fs = 50 , period = 0 ;
unsigned long currentTime = 0 , previousTime = 0 ;
int readPin = A0 ; // input pin from the emg
int ledPin = 7 ;
int resetButtonPin = 4;   // Pin for the reset button
int sensorValue = 0 ; // variable to store the value coming from the sensor
float x=0.0, x1=0.0, x2=0.0;
int y=0;
bool open;
int angleclos = 180;
int angleopen = 0;

// auxiliar functions --------------------------------------------------
int filter(float x, float x1, float x2)
{
int out;
out=int((x+x1+x2)/3);
return(out);
}

void servopen(){
  servo.write(angleopen);
  digitalWrite(ledPin, HIGH);
  open = true;
  delay(300);
}

void servoclos(){
  servo.write(angleclos);
  digitalWrite(ledPin, LOW);
  open = false;
  delay(300);
}
//----------------------------------------------------------------------

void setup(){
Serial.begin(9600) ;
period = int(1000*1/(float)fs);
pinMode(ledPin, OUTPUT);
servo.attach(9);
servopen();
pinMode(resetButtonPin, INPUT_PULLUP); // Enable internal pull-up resistor for the button

}

void loop() {
currentTime = millis() ;
if(currentTime - previousTime >= period) {
  previousTime = currentTime ;

  float emgValue = analogRead(A0);
  sensorValue = emgValue * 3300 / 1023;
  //Serial.println(emgValue); 

  x2=x1;
  x1=x;
  x = float(sensorValue); // read values (0 to 1023) from the input pin
  y=filter(x,x1,x2);
  delay(0.02);

  //Check if the sensor value exceeds 1150:
  if (!open && y > 2300){
    servopen();
  }

  // Check if the reset button is pressed
  int resetButtonState = digitalRead(resetButtonPin);
  if (resetButtonState == LOW) {
    servoclos();
  }

  //Serial.print(0); // To freeze the lower limit
  //Serial.print(" ");
  Serial.print(2300); // To freeze the upper limit
  Serial.print(" ");
  //Serial.println(sensorValue);
  Serial.println(y); 
}
}


