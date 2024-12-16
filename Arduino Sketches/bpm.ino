const int pin_ppg = A0;
int value_ppg = 0;
int threshold = 500;
bool peak = false;
unsigned long last_peak = 0;
unsigned long current_time = 0;
int bpm = 0;

void setup() 
{
  pinMode(A0, INPUT);
  Serial.begin(9600);
}

void loop()
{
  value_ppg = analogRead(pin_ppg);
  //Serial.println(value_ppg); //descomentar para ver o plot no serial plotter (comentar os outros serial print)
  current_time = millis();
  
  // Detect a peak
  if (value_ppg > threshold && !peak) 
  {
    peak= true;
    if (last_peak > 0) 
    {
      // Calculate time between peaks
      unsigned long time_interval = current_time - last_peak;
      // Calculate BPM
      bpm = 60000.0 / time_interval;
      
      if (bpm < 180 && bpm>40)
      {
        Serial.print("BPM: ");
        Serial.println(bpm);    
      }
    }
    last_peak = current_time;
  }
  // Reset peak detection flag
  if (value_ppg < threshold)
  {
    peak = false;
  }

}

  
