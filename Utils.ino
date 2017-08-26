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

uint32_t randomColor() {
  return hsvToRgb(random(255) / 255.0f);
}

uint32_t hsvToRgb(double h) {
  return hsvToRgb(h, 1.0, 0.5);
}

uint32_t hsvToRgb(double h, double s, double v) {
    double r, g, b;

    double q = v < 0.5 ? v * (1 + s) : v + s - v * s;
    double p = 2 * v - q;
    r = hue2rgb(p, q, h + 1/3.0);
    g = hue2rgb(p, q, h);
    b = hue2rgb(p, q, h - 1/3.0);

    return strip.Color(r * 255, g * 255, b * 255);
}

double hue2rgb(double p, double q, double t) {
  if(t < 0) t += 1;
  if(t > 1) t -= 1;
  if(t < 1/6.0) return p + (q - p) * 6 * t;
  if(t < 1/2.0) return q;
  if(t < 2/3.0) return p + (q - p) * (2/3.0 - t) * 6;
  return p;
}
