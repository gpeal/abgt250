#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

// typedef uint32_t u32
// typedef uint16_t u16
// typedef uint8_t u8

#define DEBOUNCE_COUNT 1
#define BRIGHTNESS_PIN A4
#define MODE_BUTTON_PIN 2
#define LED_PIN 2
#define INTEGRATED_LED_PIN 13
Adafruit_NeoPixel strip = Adafruit_NeoPixel(357, 3, NEO_GRB + NEO_KHZ800);

uint32_t RED = 0xFF0000;
uint32_t GREEN = 0x00FF00;
uint32_t BLUE = 0x0000FF;
uint32_t CLEAR = 0;
boolean integratedLedOn = false;

int modeButtonDebounce = 0;
void setup()
{
  Serial.begin(9600);
  pinMode(MODE_BUTTON_PIN, INPUT);
  strip.begin();
  strip.show();
  setBrightness(20);  
}

int counter = 0;

void loop()
{
  integratedLedOn = !integratedLedOn;
  digitalWrite(INTEGRATED_LED_PIN, integratedLedOn ? HIGH : LOW);

  // wipeRing(RED);
  // delay(100);
  // wipeRing(GREEN);
  // delay(100);
  // wipeRing(BLUE);
  // delay(100);

  // stepThrough();
  // blink(1000, RED);
  // rippleEdge(255, 0, 0);
  // sunRise();
  counter = (counter + random(50, 200)) % 255;
  wipeFromMiddle(Wheel(counter), 10);
  // setColor(RED);
  // wipeEdge(strip.Color(255, 0, 0), 50);
  // rainbowBounceWaveFromTopRightVertex();
  // rainbowWaveFromTopRightVertex();
  // spiralMiddle();
  mellowPumpItUp();

  // middleOutRainbowCycle();
  // colorWipe(strip.Color(255, 0, 0), wipeSpeed);
  // blink(1000, strip.Color(0, 0, 255));
  // theaterChase(strip.Color(127, 127, 127), 75);
  // fullRainbow();
  // rainbow(10);
  // rainbowCycle(10);
  // edgeRainbowCycle();
  // theaterChaseRainbow(10);
  // randomColors(10);
  // disco(0xD3FCFF, 150, 75, 25);
<<<<<<< HEAD
  // pulseAccelerate(120);
=======
  // pulseAccelerate(150);
  // setColor(CLEAR);
>>>>>>> Added sunrise and wipeFromMidle
}

void setBrightness(int brightness)
{
  strip.setBrightness(brightness);
}

void show()
{
  strip.show();
}