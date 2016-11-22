#include <PID_v1.h>
#include "DHT.h"

// 45, then 27, then 31
int temperatures[4] = {45, 27, 31, 0};
long temps[3] = {1000, 2000, 3000, 4000};
 
#define DHTPIN 2     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
#define heater 5 // Sortie pour le soleil
#define jour 76032 // Facteur .88

DHT dht(DHTPIN, DHTTYPE);

//Define Variables we'll be connecting to
double Setpoint, Input, Output;

//Specify the links and initial tuning parameters
PID myPID(&Input, &Output, &Setpoint,250,5,1, DIRECT);

int WindowSize = 5000;
unsigned long windowStartTime;
long seconds = 0;
int etape = 0;
  
void setup() {
  pinMode(heater, OUTPUT);
  Serial.begin(9600); 
  dht.begin();
  

  
  //initialize the variables we're linked to
  Input = analogRead(0);
  Setpoint = 45;

  //turn the PID on
  myPID.SetMode(AUTOMATIC);

  //tell the PID to range between 0 and the full window size
  myPID.SetOutputLimits(0, WindowSize);
}
 
void loop() {
  // Wait a few seconds between measurements.
  delay(1000);
 
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius
  float t = dht.readTemperature();
  
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Input = t;
  myPID.Compute();

  unsigned long now = millis();
  if(now - windowStartTime>WindowSize)
  { //time to shift the Relay Window
    windowStartTime += WindowSize;
  }
  if(Output > now - windowStartTime) digitalWrite(heater,HIGH);
  else digitalWrite(heater,LOW);
  
  ++seconds;
  if(seconds>temps[0] && seconds<temps[1])
    etape = 0;
  else if(seconds>temps[1] && seconds<temps[2])
    etape = 1;
  else if(seconds>temps[2] && seconds<temps[3])
    etape = 2;
  else
    etape = 3;
  
  Setpoint = temperature[etape];
  
  Serial.print(seconds);
  Serial.print(",");
  Serial.print(Setpoint);
  Serial.print(",");
  Serial.print(Output);
  Serial.print(",");  
  Serial.println(t);
}
