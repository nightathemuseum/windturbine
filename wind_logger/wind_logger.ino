#include <ArduinoLowPower.h>
#include <SPI.h>
#include <SD.h>

//initialize logging file
File data;

//initialize I/O pins
int pinCS = 13; // Chip select pin
// Pin 14: MOSI
// Pin 15: MISO
// Pin 16: SCK
int pinFET = 12; // controls power supply to anemometer
int pinSpeed = 26; // anemometer signal
int pinDirection = 25; // wind vane signal


//initialize variables & constants
int SamplePeriod = 10; // Sample period measured in s
int vel; // anemometer output converted to mm/s
int dir; // wind direction output converted to deg
long int n = 0; // sample timestamp in seconds

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(pinCS, OUTPUT);
  
  // SD Card Initialization
  if (SD.begin(pinCS))
  {
    data.println("SD card successfully initialized.");
  }

}

void loop() {
  // put your main code here, to run repeatedly:
  vel = analogRead(pinSpeed)*20.25*4.9 - 8100;
  dir = analogRead(pinDir)*0.0049;
  data = SD.open("logfiles.txt", FILE_WRITE);
  if (data) {    
    data.print(n);
    data.print(",");    
    data.print(vel);
    data.print(",");    
    data.println(dir);
    data.close(); // close the file
  }
  // if the file didn't open, print an error:
  else {
    Serial.println("error opening test.txt");
  }
  n = n + SamplePeriod;
  deepSleep(SamplePeriod*1000);
}
