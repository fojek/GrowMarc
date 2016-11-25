#include <PID_v1.h>

// 45, then 27, then 31
int temperatures[4] = {45, 27, 31, 0};
long temps[3] = {1000, 4500, 8000};
 
#define RTDPIN A0     // what pin we're connected to
#define heater 5 // Sortie pour le soleil


//Define Variables we'll be connecting to
double Setpoint, Input, Output;

//Specify the links and initial tuning parameters
PID myPID(&Input, &Output, &Setpoint,250,5,1, DIRECT);

int WindowSize = 5000;
unsigned long windowStartTime;
long seconds = 990;
int etape = 2;
float resConnue = 99.1;

float in[] = { 100.00, 100.39, 100.78, 101.17, 101.56, 101.95, 102.34, 102.73, 103.12, 103.51,
               103.90, 104.29, 104.68, 105.07, 105.46, 105.85, 106.24, 106.63, 107.02, 107.40,
               107.79, 108.18, 108.57, 108.96, 109.35, 109.73, 110.12, 110.51, 110.90, 111.29,
               111.67, 112.06, 112.45, 112.83, 113.22, 113.61, 114.00, 114.38, 114.77, 115.15,
               115.54, 115.93, 116.31, 116.70, 117.08, 117.47, 117.86, 118.24, 118.63, 119.01,
               119.40, 119.78, 120.17, 120.55, 120.94, 121.32, 121.71, 122.09, 122.47, 122.86,
               123.24, 123.63, 124.01, 124.39, 124.78, 125.16, 125.54, 125.93, 126.31, 126.69,
               127.08, 127.46, 127.84, 128.22, 128.61, 128.99, 129.37, 129.75, 130.13, 130.52 };

// known resistance in voltage divider
int R1 = 984;

float MultiMap(float val, float* _in, uint8_t size)
{
  // calculate if value is out of range 
  if (val < _in[0] ) return -99.99;
  if (val > _in[size-1] ) return 99.99;

  //  search for 'value' in _in array to get the position No.
  uint8_t pos = 0;
  while(val > _in[pos]) pos++;  

  // handles the 'rare' equality case
  if (val == _in[pos]) return pos;

  float r1 = _in[pos-1];
  float r2 = _in[pos];
  int c1 = pos-1;
  int c2 = pos;

 return c1 + (val - r1) / (r2-r1) * (c2-c1);
}


void setup() {
  pinMode(heater, OUTPUT);
  Serial.begin(9600); 
  
  analogReference(INTERNAL);

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
  float Vin = 5.05;
 
  // Température
  int pt100 = analogRead(A0);

  float Vout = pt100 * (1.1 / 1023.0);
  
  float R2 = R1/(Vin/Vout - 1);
  
  float c =  MultiMap(R2,in,80) - 2;
  
  int t = c;//resRTD;

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
  if(seconds>=0 && seconds<temps[0])
    etape = 0;
  else if(seconds>temps[0] && seconds<temps[1])
    etape = 1;
  else if(seconds>temps[1] && seconds<temps[2])
    etape = 2;
  else
    etape = 3;
  
  Setpoint = temperatures[etape];
  
  Serial.print(seconds);
  Serial.print(",");
  Serial.print(Setpoint);
  Serial.print(",");  
  Serial.print(etape);
  Serial.print(",");
  Serial.print(Output);
  Serial.print(",");  
  Serial.print(analogRead(A0));
  Serial.print(",");  
  Serial.println(c);
}
