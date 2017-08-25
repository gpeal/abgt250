// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos)
{
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85)
  {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170)
  {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

byte* randomColor() {
  byte RGB[] = {0, 0, 0};
  hsvToRgb(random(256) / 255.0f, RGB);
  return RGB;
}

void hsvToRgb(double h, byte rgb[]) {
  hsvToRgb(h, 1.0, 0.5, rgb);
}

void hsvToRgb(double h, double s, double v, byte rgb[]) {
    double r, g, b;

    double q = v < 0.5 ? v * (1 + s) : v + s - v * s;
    double p = 2 * v - q;
    r = hue2rgb(p, q, h + 1/3.0);
    g = hue2rgb(p, q, h);
    b = hue2rgb(p, q, h - 1/3.0);

    Serial.print(h);
    Serial.print(" ");
    Serial.print(r);
    Serial.print(" ");
    Serial.print(g);
    Serial.print(" ");
    Serial.print(b);
    Serial.println();

    rgb[0] = r * 255;
    rgb[1] = g * 255;
    rgb[2] = b * 255;
}

double hue2rgb(double p, double q, double t) {
  if(t < 0) t += 1;
  if(t > 1) t -= 1;
  if(t < 1/6.0) return p + (q - p) * 6 * t;
  if(t < 1/2.0) return q;
  if(t < 2/3.0) return p + (q - p) * (2/3.0 - t) * 6;
  return p;
}
