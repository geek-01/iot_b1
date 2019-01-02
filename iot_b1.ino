#define BLYNK_PRINT SwSerial



#include <SoftwareSerial.h>

SoftwareSerial SwSerial(10, 11); // RX, TX

    

#include <BlynkSimpleStream.h>

#include <dht.h>



// You should get Auth Token in the Blynk App.

// Go to the Project Settings (nut icon).

char auth[] = "3eb376e410074d9ba3a6877db256271a"; 



#define DHTPIN 4         // What digital pin we're connected to



dht DHT;

BlynkTimer timer;



// In the app, Widget's reading frequency should be set to PUSH. This means

// that you define how often to send data to Blynk App.

void sendSensor()

{
  

  float h = DHT.humidity;

  float t = DHT.temperature; // or dht.readTemperature(true) for Fahrenheit



  if (isnan(h) || isnan(t)) {

    SwSerial.println("Failed to read from DHT sensor!");

    return;

  }

  // You can send any value at any time.

  // Please don't send more that 10 values per second.

  Blynk.virtualWrite(V5, h);

  Blynk.virtualWrite(V6, t);

}



void setup()

{

  // Debug console

  SwSerial.begin(9600);



  // Blynk will work through Serial

  // Do not read or write this serial manually in your sketch

  Serial.begin(9600);

  Blynk.begin(Serial, auth);




  // Setup a function to be called every second

  timer.setInterval(1000L, sendSensor);

}



void loop()

{
  int chk=DHT.read11(DHTPIN);

  Blynk.run();

  timer.run();

}

