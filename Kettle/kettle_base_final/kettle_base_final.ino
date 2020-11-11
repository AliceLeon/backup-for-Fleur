// nobody fucking touches this
#define BLYNK_PRINT Serial
#define FASTLED_ESP8266_RAW_PIN_ORDER
#include "FastLED.h"
#define NUM_LEDS 17
#define DATA_PIN D7

CRGB leds[NUM_LEDS];

int counter = 0;

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>


char auth[] = "eb1HVy6tShgUJ3GCQWC0fQutvQLtwQlO";

char ssid[] = "BT-7RAFR5";
char pass[] = "q4mrtkEvRyeUmP";

int brightness = 0;
int normalB = 0;
boolean isBoiling = false;
boolean isNormal = false;

BLYNK_WRITE(V0) {
  int pinValue = param.asInt();
  if (pinValue == 1) {
    isBoiling = true;
  } else {
    isBoiling = false;
  }
}
BLYNK_WRITE(V1) {
  int pinValue = param.asInt();
  if (pinValue == 1) {
    isNormal = true;
  } else {
    isNormal = false;
    normalB = 0;
  }
}


void setup()
{
  // Debug console
  Serial.begin(9600);
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 8080);
}

void loop()
{
  Blynk.run();
  if (isBoiling) {
    if (brightness >= 150) {
      brightness = 0;
    } else {
      brightness += 5;
    }
  } else {
    if (brightness >= 3) {
      brightness -= 3;
    } else {
      brightness = 0;
    }
  }
  if (isNormal) {
    normalB = constrain(normalB + 10, 0, 150);
    FastLED.setBrightness(normalB);
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB::White;
      FastLED.show();
    }
  } else {
    FastLED.setBrightness(255);
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i].setHSV( 255, 255, brightness);
      FastLED.show();
    }
  }
}
