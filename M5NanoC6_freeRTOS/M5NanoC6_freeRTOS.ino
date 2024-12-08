// An example of how to use freeRTOS with 3 tasks.
// - https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/system/freertos.html
// - https://github.com/DiegoPaezA/ESP32-freeRTOS
// - https://www.freertos.org/index.html

//-------------------------------------------------------------------
#include <Adafruit_NeoPixel.h>

//-------------------------------------------------------------------
// blaue led
const int PIN_LED = 7;

//-------------------------------------------------------------------
// neopixel rgb-led
const int PIN_POWER_RGB_ENABLE = 19;
const int PIN_DATA_RGB = 20;

const int NUM_LEDS = 1;

Adafruit_NeoPixel rgb(NUM_LEDS, PIN_DATA_RGB, NEO_GRB + NEO_KHZ800);

//-------------------------------------------------------------------
void setup() 
{
  //---
  Serial.begin(115200);

  //---
  // Task 2 erzeugen und starten
  xTaskCreate(Task_2, NULL, 8192, NULL, 1, NULL);

  //---
  // Task 3 erzeugen und starten
  xTaskCreate(Task_3, NULL, 8192, NULL, 2, NULL);
}

//-------------------------------------------------------------------
void loop()
{
  Serial.println("Hallo Welt...");
  delay(1000);
}

//-------------------------------------------------------------------
void Task_2(void *pvParameters)
{
  //---
  // blaue led ausschalten
  analogWrite(PIN_LED, 0);

  //---
  // endlos loop
  while (true) {
    // blaue led einblenden (0..100%)
    for (int tg = 0; tg <= 255; tg++) {
      analogWrite(PIN_LED, tg);
      delay(2);
    }

    // blaue led ausblenden (100..0%)
    for (int tg = 255; tg >= 0; tg--) {
      analogWrite(PIN_LED, tg);
      delay(2);
    }
  }
}

//-------------------------------------------------------------------
void Task_3(void *pvParameters)
{
  //---
  pinMode(PIN_POWER_RGB_ENABLE, OUTPUT);
  digitalWrite(PIN_POWER_RGB_ENABLE, HIGH);

  rgb.begin();
  rgb.show();

  //---
  // endlos loop
  while (true) {
    // rot 100%
    rgb.setPixelColor(0, rgb.Color(255, 0, 0));
    rgb.show();
    delay(500);

    // grün 100%
    rgb.setPixelColor(0, rgb.Color(0, 255, 0));
    rgb.show();
    delay(500);

    // blau 100%
    rgb.setPixelColor(0, rgb.Color(0, 0, 255));
    rgb.show();
    delay(500);

    // weiss 100%
    rgb.setPixelColor(0, rgb.Color(255, 255, 255));
    rgb.show();
    delay(500);
  }
}
