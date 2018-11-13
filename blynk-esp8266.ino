/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************

  You’ll need:
   - Blynk App (download from AppStore or Google Play)
   - ESP8266 board
   - Decide how to connect to Blynk
     (USB, Ethernet, Wi-Fi, Bluetooth, ...)

  There is a bunch of great example sketches included to show you how to get
  started. Think of them as LEGO bricks  and combine them as you wish.
  For example, take the Ethernet Shield sketch and combine it with the
  Servo example, or choose a USB sketch and add a code from SendData
  example.
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
// библиотека для работы с датчиком освещённости (Troyka-модуль)
#include <TroykaLight.h>

// подключим необходимые библиотеки
#include <OneWire.h>
#include <DallasTemperature.h>
 
// сигнальный провод подключен к 2 пину на Arduino
#define ONE_WIRE_BUS 2
 
// настроим библиотеку 1-Wire для связи с датчиком
OneWire oneWire(ONE_WIRE_BUS);
 
// создадим объект для работы с библиотекой DallasTemperature
DallasTemperature sensors(&oneWire);

// создаём объект для работы с датчиком освещённости
// и передаём ему номер пина выходного сигнала
TroykaLight sensorLight(A0);

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
  char auth[] = "cae89ee037194e0a97a6522bb97392d0";

// Your WiFi credentials.
// Set password to "" for open networks.
//char ssid[] = "Rus";
//char pass[] = "12345670";

char ssid[] = "Unit_WiFi";
char pass[] = "rMW4tAux9U5H";

BlynkTimer timer; // Create a Timer object called "timer"! 

void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
  
  timer.setInterval(1000L, sendUptime); //  Here you set interval (1sec) and which function to call 
}


void sendUptime()
{
  // This function sends Arduino up time every 1 second to Virtual Pin (V5)
  // In the app, Widget's reading frequency should be set to PUSH
  // You can send anything with any interval using this construction
  // Don't send more that 10 values per second

//  Blynk.virtualWrite(V5, millis() / 1000);
  
  // считывание данных с датчика освещённости
  sensorLight.read();
  // вывод показателей сенсора освещённости в люксах
  Serial.print("Light is ");
  Serial.print(sensorLight.getLightLux());
  Serial.print(" Lx\n");

  Blynk.virtualWrite(V6, sensorLight.getLightLux());

  
  // отправляем запрос на измерение температуры
  sensors.requestTemperatures();
  // покажем температуру в мониторе Serial порта
  Serial.print("Temp: ");
  Serial.print(sensors.getTempCByIndex(0));
  Serial.print(" C\n");
  
  Blynk.virtualWrite(V2, sensors.getTempCByIndex(0));
}

void loop()
{
  Blynk.run();
  // You can inject your own code or combine it with other sketches.
  // Check other examples on how to communicate with Blynk. Remember
  // to avoid delay() function!
  timer.run(); // BlynkTimer is working...
}
