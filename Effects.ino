
void setColor(uint32_t color)
{
  for (uint16_t i; i < strip.numPixels(); i++)
  {
    setPixelColor(i, color);
  }
  show();
}

void randomColors(uint16_t wait)
{
  for (uint16_t i = 0; i < 100; i++)
  {
    setPixelColor(i, randomColor());
    show();
    delay(10);
  }
}

// Fill the dots one after the other with a color
boolean colorWipe(uint32_t c, uint8_t wait)
{
  for (uint16_t i = 0; i < strip.numPixels(); i++)
  {
    setPixelColor(i, c);
    show();
    if (beforeDelay())
    {
      return false;
    }
    delay(wait);
  }
  return true;
}

void rippleEdge(uint8_t r, uint8_t g, uint8_t b)
{
  float f[] = {0.2f, 0.1f, 0.05f, 0.0f};
  int len = sizeof(f) / sizeof(f[0]);
  setColor(CLEAR);

  for (uint8_t i = 0; i < 35; i++)
  {
    for (uint8_t j = 0; j < 35; j++)
    {
      setEdgeColor(i, strip.Color(r, g, b));
      for (uint8_t k = 0; k < len; k++)
      {
        if (i >= k)
        {
          setEdgeColor(i - k, strip.Color(r * f[k], g * f[k], b * f[k]));
        }
        if (i <= 34 - k)
        {
          setEdgeColor(i + k, strip.Color(r * f[k], g * f[k], b * f[k]));
        }
      }
    }
    show();
    delay(100);
  }
}

void stepThrough()
{
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    setPixelColor(i, 255, i % 10 == 0 ? 255 : 0, i % 50 == 0 ? 255 : 0);
    show();
    if (i % 10 == 0) {
      delay(1000);
    }
    delay(10);
  }
}

void blink(uint16_t wait, uint32_t color)
{
  for (uint16_t i; i < strip.numPixels(); i++)
  {
    setPixelColor(i, color);
  }
  show();
  delay(wait);
  for (uint16_t i; i < strip.numPixels(); i++)
  {
    setPixelColor(i, 0);
  }
  strip.show();
  delay(wait);
}

void fullRainbow()
{
  for (uint16_t i = 0; i <= 255; i += 3)
  {
    setColor(Wheel(i));
  }
  show();
  if (beforeDelay())
  {
    return false;
  }
}

boolean rainbow(uint8_t wait)
{
  uint16_t i, j;

  for (j = 0; j < 256; j++)
  {
    for (i = 0; i < strip.numPixels(); i++)
    {
      setPixelColor(i, Wheel((i + j) & 255));
    }
    show();
    if (beforeDelay())
    {
      return false;
    }
    delay(wait);
  }
  return true;
}

// Slightly different, this makes the rainbow equally distributed throughout
boolean rainbowCycle(uint8_t wait)
{
  uint16_t i, j;

  for (j = 0; j < 256 * 5; j++)
  { // 5 cycles of all colors on wheel
    for (i = 0; i < strip.numPixels(); i++)
    {
      setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    show();
    if (beforeDelay())
    {
      return false;
    }
    delay(wait);
  }
  return false;
}

// disco ball, every 50ms
// rotation

// Only
boolean spiralMiddle() // LOL
{
  for (uint8_t i = 0; i < 100; i++) {
    uint8_t oldX = (int)((i - 5) / 100.0 * 6);
    uint8_t oldY = (int)((i - 5) / 100.0 * 34);
    if (oldX > 0 && oldY > 0) {
      setVerticalEdgeRange(oldY, 3, oldX, 0);
    }

    uint8_t x = (int)(i / 100.0 * 6);
    uint8_t y = (int)(i / 100.0 * 34);
    int color = Wheel((int)(y / 35.0 * 255));
    setVerticalEdgeRange(y, 3, x, color);

    show();
    delay(10);
  }
}

boolean mellowPumpItUp() {
  int delayMs = 50;
  int totalCount = 10;
  for (int count = 0; count < totalCount; count++) {
    delayMs = (int)(delayMs * .6);
    for (int i = 0; i < 35; i++) {
      // int color = Wheel((int)((i / 35.0) * 255 + (count % 6) / 5.0 * 255.0) % 255);
      int color = Wheel((int) count / (double) totalCount * 255.0);
      setEdgeColor(i, color, false);
      show();
      delay(delayMs);
    }
  }
  for (int i = 0; i < 5; i++) {
    setColor(0xffffff);
    show();
    delay(50);
    setColor(0);
    show();
    delay(50);
  }
}

boolean edgeRainbowCycle()
{
  uint16_t i, j;

  float periods = 0.5;
  float speed = 5;

  for (j = 0; j < 256 * 5; j += speed)
  { // 5 cycles of all colors on wheel
    for (i = 0; i <= 35; i++)
    {
      setEdgeColor(i, Wheel(((int)(i * 256 / (35 / periods) + j)) & 255));
    }
    show();
    //    if (beforeDelay()) {
    //      return false;
    //    }
  }
  return false;
}

boolean middleOutRainbowCycle()
{
  uint16_t i, j;

  for (j = 0; j < 256 * 5; j += 3)
  { // 5 cycles of all colors on wheel
    for (i = 0; i <= 17; i++)
    {
      setEdgeColor(i, Wheel(((i * 256 / 35) + j) & 255));
      setEdgeColor(35 - i, Wheel(((i * 256 / 35) + j) & 255));
    }
    show();
    //    if (beforeDelay()) {
    //      return false;
    //    }
  }
  return false;
}

boolean theaterChase(uint32_t c, uint8_t wait)
{
  for (int j = 0; j < 10; j++)
  { //do 10 cycles of chasing
    for (int q = 0; q < 3; q++)
    {
      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3)
      {
        setPixelColor(i + q, c); //turn every third pixel on
      }
      show();
      if (beforeDelay())
      {
        return false;
      }
      delay(wait);

      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3)
      {
        setPixelColor(i + q, 0); //turn every third pixel off
      }
    }
  }
  return true;
}

void wipeEdge(uint32_t color, int wait)
{
  setColor(strip.Color(0, 0, 0));
  for (int i = 0; i <= 35; i++)
  {
    setEdgeColor(i, color);
    strip.show();
    //    if (beforeDelay()) {
    //      return;
    //    }
    delay(wait);
  }
}

void wipeRing(uint32_t color)
{
  for (int i = 0; i < 15; i++)
  {
    setRingColorSymmetrical(i, color);
    show();
    delay(50);
  }
  // delay(1000);
}

void wipeFromTopRightVertex(uint32_t color)
{
  // setEdgeColor(color, false);
  for (int i = 0; i < 8; i++)
  {
    setEdgeColor(8 + (i * 2), color);
    setEdgeColor(9 + (i * 2), color);
    if (i <= 7) {
      setEdgeColor(7 - (i * 2), color);
      setEdgeColor(6 - (i * 2), color);
    }
    setEdgeColor(35 - (i * 2), color);
    setEdgeColor(34 - (i * 2), color);
    setRingColorSymmetrical(i, color);
    show();
    delay(50);
  }
}

void rainbowWaveFromTopRightVertex()
{
  uint8_t i = 0;
  while (true) {
    i += 3;
    for (int j = 0; j < 16; j++)
    {
      uint32_t color = Wheel(255 / 16 * j + i);
      setEdgeColor(8 + j, color);
      if (j <= 7) {
        setEdgeColor(7 - j, color);
      }
      setEdgeColor(35 - j, color);
      if (j % 2 == 0) {
        setRingColorSymmetrical(j / 2, color);
      }
    }
    show();
  }
}

void rainbowBounceWaveFromTopRightVertex()
{
  // Lower numbers make tighter colors
  uint8_t min = 16;
  uint8_t max = 32;
  uint8_t delta = max - min;
  for (float i = 0.0; i <= delta; i += 0.2) {
    float divisor = i <= delta / 2 ? min + i : max - i;
    for (int j = 0; j < 16; j++)
    {
      uint32_t color = Wheel(255 / divisor * j);
      setEdgeColor(8 + j, color);
      if (j <= 7) {
        setEdgeColor(7 - j, color);
      }
      setEdgeColor(35 - j, color);
      if (j % 2 == 0) {
        setRingColorSymmetrical(j / 2, color);
      }
    }
    show();
  }
}

//Theatre-style crawling lights with rainbow effect
boolean theaterChaseRainbow(uint8_t wait)
{
  for (int j = 0; j < 256; j++)
  { // cycle all 256 colors in the wheel
    for (int q = 0; q < 3; q++)
    {
      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3)
      {
        setPixelColor(i + q, Wheel((i + j) % 255)); //turn every third pixel on
      }
      show();
      if (beforeDelay())
      {
        return false;
      }
      delay(wait);

      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3)
      {
        setPixelColor(i + q, 0); //turn every third pixel off
      }
    }
  }
  return true;
}

void disco(uint32_t color, int numPixels, int turnOffPercentage, int wait) {
  int numPixelsSet = 0;
  for (int i = 0; i <= 357; i++) {
    if (strip.getPixelColor(i) != 0 && random(0, 100) < turnOffPercentage) {
      strip.setPixelColor(i, CLEAR);
    }
  }

  for (int i = numPixelsSet; i < numPixels; i++) {
    strip.setPixelColor(random(0, 357), color);
  }
  strip.show();
  delay(wait);
}

void pulseAccelerate(uint32_t maxDelay) {
  for (int i = 0; i < 35; i++) {
    uint32_t color = Wheel(255 / 35);
    setEdgeColor(i, color, false);
    if (i < 7) {
      setBottomRingColorSymmetrical(i, color);
    }
    if (i >= 7 && 1 < 17) {
      setTopRingColorSymmetrical(i - 7, color);
    }
    show();
    delay(maxDelay - 3 * i);
  }
}

boolean beforeDelay()
{
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