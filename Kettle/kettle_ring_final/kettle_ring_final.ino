// nobody fucking touches this either
#define BLYNK_PRINT Serial
#define FASTLED_ESP8266_RAW_PIN_ORDER
#include "FastLED.h"
#define NUM_LEDS 24
#define DATA_PIN D6

CRGB leds[NUM_LEDS];
int counter = 0;
int num = 0;

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>


char auth[] = "4ILIWxktr00nfIfEFtOVCNUBwh7LFOw1";

char ssid[] = "BT-7RAFR5";
char pass[] = "q4mrtkEvRyeUmP";

int brightness = 0;
int normalB = 0;
boolean isUpdating = false;

BLYNK_WRITE(V0) {
  int pinValue = param.asInt();
  if (pinValue == 1) {
    isUpdating = true;
  } else {
    isUpdating = false;
  }
}

BLYNK_WRITE(V1) {
  int pinValue = param.asInt();
  num = pinValue;
}

void setup()
{
  Serial.begin(9600);
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(150);
  Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 8080);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
}

void loop()
{
  Blynk.run();
  if (isUpdating) {
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i].setHSV( 64, 255, constrain((23 - (i + counter) % 24) * 10, 0, 255));
      FastLED.show();
    }
  } else {
    FastLED.setBrightness(10);
    for (int i = 0; i <  NUM_LEDS; i++) {
      if (((i + 1 ) <= num) || (i >= 24 - num)) {
        leds[i] = CRGB::White;
      } else {
        leds[i] = CRGB::Black;
      }
      FastLED.show();
    }
  }
  counter = int(millis() / 100.);
}
