#include <PID_v1.h>
#include "DHT.h"
 
#define DHTPIN 2     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
#define plancherChauffant 4 // Sortie relais pour le plancher
#define soleil 5 // Sortie pour le soleil
#define jour 76032 // Facteur .88
DHT dht(DHTPIN, DHTTYPE);

//Define Variables we'll be connecting to
double Setpoint, Input, Output;

//Specify the links and initial tuning parameters
PID myPID(&Input, &Output, &Setpoint,250,5,1, DIRECT);

int WindowSize = 5000;
long temps, secondes;
unsigned long windowStartTime;

void setup() {
  pinMode(plancherChauffant, OUTPUT);  
  pinMode(soleil, OUTPUT);
  Serial.begin(9600); 
  dht.begin();
  
  //initialize the variables we're linked to
  Input = analogRead(0);
  Setpoint = 24;

  // Variables pour le temps
  secondes = 38000L; // 12 heures *0.88

  //turn the PID on
  myPID.SetMode(AUTOMATIC);

  temps = 37995;

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
  if(Output > now - windowStartTime) digitalWrite(plancherChauffant,HIGH);
  else digitalWrite(plancherChauffant,LOW);

  temps += 1;
  if (temps < secondes){
    digitalWrite(soleil,HIGH);
  }
  else {
    digitalWrite(soleil,LOW);
    if (Setpoint != 18)
      Setpoint = 18;
  }

  // La journée est terminée .. on recommence
  if (temps > jour) {
    Setpoint = 25;
    temps = 0;
  }
  
  Serial.print(Output);
  Serial.print(","); 
  Serial.print(t);
  Serial.print(",");
  Serial.println(temps);
}
