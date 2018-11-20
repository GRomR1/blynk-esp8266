/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial
// #define BLYNK_DEBUG        // Optional, this enables more detailed prints

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <TroykaLight.h> // библиотека для работы с датчиком освещённости (Troyka-модуль)
#include <OneWire.h> // необходимые библиотеки для работы с датчиком температуры


// реле с лампочкой подключено к пину 0 (GP16)
#define RELAY_PIN 0
// красный светодиод подключен к пину 1 (GP5)
#define RED_PIN 1
// желтый светодиод подключен к пину 2 (GP4)
#define YELLOW_PIN 2
// зеленый светодиод подключен к пину 3 (GP0)
#define GREEN_PIN 2


// Токен авторизации из приложения (Auth Token)
char auth[] = "31340d84e905466daad8dcbc2f1d0ada";

// Данные точки доступа WiFi
char ssid[] = "Rus";
char pass[] = "12345670";

// создаём объект для работы с датчиком освещённости
// и передаём ему номер пина выходного сигнала
TroykaLight sensorLight(A0);
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
  // считывание данных с датчика освещённости
  sensorLight.read();
  Serial.print("Light is ");   // вывод показателей сенсора освещённости в люксах
  Serial.print(sensorLight.getLightLux());
  Serial.print(" Lx\n");

  // отправка данных сенсора на пин V1
  Blynk.virtualWrite(V1, sensorLight.getLightLux());
}

void loop()
{
  Blynk.run();
  timer.run(); 
}
