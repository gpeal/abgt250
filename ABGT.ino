#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define MODE_BUTTON_PIN 8
#define DEBOUNCE_COUNT 1
#define BRIGHTNESS_PIN A4
#define MIC_PIN A5
Adafruit_NeoPixel strip = Adafruit_NeoPixel(357, 2, NEO_GRB + NEO_KHZ800);

uint32_t RED = 0xFF0000;
uint32_t GREEN = 0x00FF00;
uint32_t BLUE = 0x0000FF;

int modeButtonDebounce = 0;
void setup() {
  Serial.begin(9600);
  pinMode(MODE_BUTTON_PIN, INPUT);
  strip.begin();
  strip.show();
  setBrightness(30);
}

void loop() {
//  wipeEdge(RED, 10);
//  delay(200);
//  wipeEdge(GREEN, 10);
//  delay(200);
//  wipeEdge(BLUE, 10);
//  delay(200);



  
//  setColor(strip.Color(0, 0, 255));
//  wipeEdge(strip.Color(255, 0, 0), wipeSpeed);
//  colorWipe(strip.Color(255, 0, 0), wipeSpeed);
//  blink(1000, strip.Color(0, 0, 255));
//  int theaterChaseSpeed = 75;
//  theaterChase(strip.Color(127, 127, 127), theaterChaseSpeed);
//  rainbow(rainbowSpeed);
//  rainbowCycle(rainbowSpeed);
  edgeRainbowCycle(0);
//  theaterChaseRainbow(rainbowSpeed);
//  randomColors(10);
}

void setColor(uint32_t color) {
  for(uint16_t i; i < strip.numPixels(); i++) {
    setPixelColor(i, color);
  }
  show();
}

void randomColors(uint16_t wait) {
  for (uint16_t i = 0; i < 100; i++) {
    strip.setPixelColor(i, random(0, 255), random(0, 255), random(0, 255));
    show();
    delay(10);
  }
}

// Fill the dots one after the other with a color
boolean colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    setPixelColor(i, c);
    show();
    if (beforeDelay()) {
      return false;
    }
    delay(wait);
  }
  return true;
}

void blink(uint16_t wait, uint32_t color) {
  for(uint16_t i; i < strip.numPixels(); i++) {
    setPixelColor(i, color);
  }
  show();
  delay(wait);
  for(uint16_t i; i < strip.numPixels(); i++) {
    setPixelColor(i, 0);
  }
  strip.show();
  delay(wait);

}

boolean rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      setPixelColor(i, Wheel((i+j) & 255));
    }
    show();
    if (beforeDelay()) {
      return false;
    }
    delay(wait);
  }
  return true;
}

// Slightly different, this makes the rainbow equally distributed throughout
boolean rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    show();
    if (beforeDelay()) {
      return false;
    }
    delay(wait);
  }
  return false;
}

boolean edgeRainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j = 0; j < 256 * 5; j++) { // 5 cycles of all colors on wheel
    for(i = 0; i <= 35; i++) {
      setEdgeColor(i, Wheel(((i * 256 / 35) + j) & 255));
    }
    show();
    if (beforeDelay()) {
      return false;
    }
    delay(wait);
  }
  return false;
}

boolean theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        setPixelColor(i+q, c);    //turn every third pixel on
      }
      show();
      if (beforeDelay()) {
        return false;
      }
      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
  return true;
}

void wipeEdge(uint32_t color, int wait) {
  setColor(strip.Color(0, 0, 0));
  for (int i = 0; i <= 35; i++) {
    setEdgeColor(i, color);
    strip.show();
//    if (beforeDelay()) {
//      return;
//    }
    delay(wait);
  }
}

void micEdge(uint32_t color, int wait) {
  for (int i = 0; i <= 35; i++) {
    setEdgeColor(i, strip.Color(0, 0, 0));
  }

  float amount = max(analogRead(MIC_PIN) / (float) 1024.0 * 33.0 - 15, 0) * 2;
  for (int i = 0; i <= amount; i++) {
    setEdgeColor(i, color);
    if (beforeDelay()) {
      return;
    }
  }
  strip.show();
}

//Theatre-style crawling lights with rainbow effect
boolean theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      show();
      if (beforeDelay()) {
        return false;
      }
      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
  return true;
}

boolean beforeDelay() {
//  int brightness = analogRead(BRIGHTNESS_PIN) / 1023.0 * 100;
//  if (digitalRead(MODE_BUTTON_PIN) == HIGH) {
//    modeButtonDebounce++;
//  } else {
//    if (modeButtonDebounce >= DEBOUNCE_COUNT) {
//      modeButtonDebounce = 0;
//      return true;
//    }
//  }
  return false;
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

void setPixelColor(int pixel, uint32_t color) {
  strip.setPixelColor(pixel, color);
}

void setEdgeColor(int index, uint32_t color) {
  if (index <= 32) {
    strip.setPixelColor(index, color);
    strip.setPixelColor(66 - index, color);
  }
  if (index <= 35) {
    strip.setPixelColor(67 + index, color);
    strip.setPixelColor(135 - index, color);
    strip.setPixelColor(136 + index, color);
    strip.setPixelColor(198 - index, color);
  }
  if (index == 0) {
    for (int i = 199; i <= 274; i++) {
      strip.setPixelColor(i, color);
    }
  } else if (index == 7) {
    for (int i = 275; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, color);
    }
  }
}

void setBrightness(int brightness) {
   strip.setBrightness(brightness);
}

void show() {
  strip.show();
}


