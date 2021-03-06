#include <RH_ASK.h>
#include <SPI.h>

RH_ASK driver;
int sensorPin = 0;

// const int sensorMin = 0;     // sensor minimum
// const int sensorMax = 1024;  // sensor maximum

int firePin = 1;

void setup()
{
  pinMode(5, INPUT);
    if (!driver.init())
         Serial.println("init failed");
}

void loop()
{
  int sensorReading = digitalRead(5);
  
  // map the sensor range (four options):
  // ex: 'long int map(long int, long int, long int, long int, long int)'
  // int range = map(sensorReading, sensorMin, sensorMax, 0, 3);

  char message[16];
  String str;
  // range value:
  switch (sensorReading) {
  case 0:    // A fire is close.
    str = "Close Fire!    ";
    str.toCharArray(message, 16);
    tone(8, 1000);
    break;
  case 1:    // No fire detected.
    int reading = analogRead(sensorPin);
    float voltage = reading * 5.0;
    voltage /= 1024.0;
    float temperatureC = (voltage - 0.5) * 100 ;
    float temperatureF = (temperatureC * 9.0 / 5.0) + 32.0;
    dtostrf(temperatureF, 6, 2, message);
    char ending[9] = " F       ";
    sprintf(message,"%s%s",message,ending);
    noTone(8);
    break;
  }
    const char *msg = message;
    driver.send((uint8_t *)msg, strlen(msg));
    driver.waitPacketSent();
    delay(500);
}
