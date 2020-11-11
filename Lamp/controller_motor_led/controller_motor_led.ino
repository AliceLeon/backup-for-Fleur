//lamp final
#include <PS4Controller.h>
#include <FastLED.h>
#include <Servo.h>

#define NUM_LEDS 24
#define DATA_PIN 25

static const int headPin = 12;
static const int bottomPin = 14;

Servo head;
Servo bottom;

CRGB leds[NUM_LEDS];
CHSV colors[] = {CHSV(160, 255, 100), CHSV(0, 0, 0), CHSV(60, 255, 100)};

bool isUpdating = false; // yellow looping motion triangle button.

int readLeftY;
int readLeftX;
int readRightY;
int prevLeftY;
int prevLeftX;
int prevRightY;

int posBottom = 90;
int posHead = 90;

int brightness = 100;
int current = 0; // color control
int counter = 0;

int timeSpan1 = 0;
int timeSpan2 = 0;


void setup()
{
  Serial.begin(115200);
  head.attach(headPin);
  bottom.attach(bottomPin);
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);  // GRB ordering is assumed

  PS4.begin("e8:61:7e:70:9f:52");
  Serial.println("Ready.");

}

void loop()
{
  if (PS4.isConnected()) {
    
    if ( PS4.data.button.triangle ) {
      Serial.println("trangle pressed");
      if (timeSpan1 > 30) {
        isUpdating = !isUpdating;
        timeSpan1 = 0;
        Serial.println("updating");
      }
    }
    if ( PS4.data.button.cross ) {
      Serial.print("Battey Percent : ");
      Serial.println(PS4.data.status.battery, DEC);
    }
    if ( PS4.data.button.square ) {
      Serial.println("square pressed");
      if (timeSpan2 > 30) {
        timeSpan2 = 0;
        current = (current + 1) % 3;
        Serial.println("not updating");
      }
    }

    // brightness
    if ( PS4.data.button.up )
      brightness = constrain(brightness += 1, 0, 255);
    if ( PS4.data.button.down )
      brightness = constrain(brightness -= 1, 0, 255);

    if ( PS4.event.analog_move.stick.lx ) {
      readLeftX = PS4.data.analog.stick.lx;
      int gap2 = readLeftX - prevLeftX;
      if (abs(gap2) > 10) {
        if (readLeftX > 0) {
          posBottom = constrain(posBottom += 1/*abs(gap)*/, 0, 180);
        } else if (readLeftX < 0) {
          posBottom = constrain(posBottom -= 1, 0, 180);
        }
      }
    }


    if ( PS4.event.analog_move.stick.ry ) {
      readRightY = PS4.data.analog.stick.ry;
      int gap3 = readRightY - prevRightY;
      if (abs(gap3) > 10) {
        if (readRightY > 0) {
          posHead = constrain(posHead += 1, 0, 180);
        } else if (readRightY < 0) {
          posHead = constrain(posHead -= 1, 0, 180);
        }
      }
    }
  }

  head.write(posHead);
  bottom.write(posBottom);
  FastLED.setBrightness(brightness);

  for (int i = 0; i < NUM_LEDS; i++) {
    if (isUpdating) {
      leds[i].setHSV( 64, 255, constrain((23 - (i + counter) % 24) * 10, 0, 255));
    } else {
      colors[current].val = brightness;
      leds[i] = colors[current];
    }
    FastLED.show();
  }
  counter = int(millis() / 100.);
  timeSpan1 += 1;
  timeSpan2 += 1;
}
