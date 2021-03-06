# For Fleur

Taking things down before I forget.

#### Toaster

- [Fadecandy tutorial](https://www.instructables.com/How-to-Control-Addressable-LEDs-With-Fadecandy-and/) by Amy Goodchild.
- [How to set up Fadecandy Mac server](https://groups.google.com/g/fadecandy/c/FvVmTFIXn5A)
- For some reason, my processing doesn't detect the microphone, so I switched to P5.js. 

#### Kettle

- For the base, HM-10 Bluetooth module + Arduino UNO + easy driver + stepper motor, [Dabble](https://github.com/STEMpedia/Dabble).
- For two LEDs, [Blynk](https://github.com/blynkkk/blynk-library) + ESP8266 + ws2812. 
- I couldn't get the motor and the LEDs working together. I probably could have if I had bought the expensive RGB LEDs. It turns out with Dabble, the Bluetooth chip we bought can't run led strips with libraries like FastLed or NeoPixel. Bluetooth won't be able to work with them. With Blynk, the virtual output refreshes very slow, and the motor loses all its steadiness; with the analog output, it triggers the led strips to blink randomly, and I won't be able to control its speed. Eventually, I used one Blynk app for two chips and two led strips (one for the base and one for the body).

#### Lamp

- A tiny robotic arm with two servos controlled by a [PS4 controller](https://github.com/aed3/PS4-esp32/blob/master/README.md), driven by an ESP32 chip.

#### Others

- Make sure you have `#define COLOR_ORDER RGB` on ESP8266. Or it will all go **green**.

- Added some photos



I thank the open-source community with all of my heart.

Link to the final project:  https://aliceleon.org/post/conterproductive/