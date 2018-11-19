/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial
// #define BLYNK_DEBUG        // Optional, this enables more detailed prints

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <TroykaLight.h> // библиотека для работы с датчиком освещённости (Troyka-модуль)
#include <OneWire.h> // необходимые библиотеки для работы с датчиком температуры
#include <DallasTemperature.h> // необходимые библиотеки для работы с датчиком температуры

// реле с лампочкой подключено к пину 1
#define RELAY_PIN 1

// сигнальный провод датчика температуры подключен к 2 пину на Arduino
#define ONE_WIRE_BUS 2
// настроим библиотеку 1-Wire для связи с датчиком
OneWire oneWire(ONE_WIRE_BUS);
// создадим объект для работы с библиотекой DallasTemperature
DallasTemperature sensorTemp(&oneWire);

// создаём объект для работы с датчиком освещённости
// и передаём ему номер пина выходного сигнала
TroykaLight sensorLight(A0);

// Токен авторизации из приложения (Auth Token)
char auth[] = "31340d84e905466daad8dcbc2f1d0ada";

// Данные точки доступа WiFi
char ssid[] = "Rus";
char pass[] = "12345670";

BlynkTimer timer;

void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);

  // каждую 1сек отправляем данные через sendSensorsData
  timer.setInterval(1000L, sendSensorsData);
}


void sendSensorsData()
{
  // This function sends Arduino up time every 1 second to Virtual Pin (V5)
  // In the app, Widget's reading frequency should be set to PUSH
  // You can send nything with any interval using this construction
  // Don't send more that 10 values per second

  // считывание данных с датчика освещённости
  sensorLight.read();
  // вывод показателей сенсора освещённости в люксах
  Serial.print("Light is ");
  Serial.print(sensorLight.getLightLux());
  Serial.print(" Lx\n");

  // отправка данных сенсора на пин V1
  Blynk.virtualWrite(V1, sensorLight.getLightLux());

  // отправляем запрос на измерение температуры
  sensorTemp.requestTemperatures();
  // покажем температуру в мониторе Serial порта
  Serial.print("Temp: ");
  Serial.print(sensorTemp.getTempCByIndex(0));
  Serial.print(" C\n");

  // отправка данных сенсора на пин V2
  Blynk.virtualWrite(V2, sensorTemp.getTempCByIndex(0));
}

void loop()
{
  Blynk.run();
  timer.run(); // BlynkTimer is working...
}
