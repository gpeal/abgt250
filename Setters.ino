#include "Setters.h"
/**
0-32    = [32] edge 1 (7 middle anchor, up)
33      = exactly the top
34      = covered, near the top
34-67   = [33] edge 2 (60 middle anchor, down)
68-101  = [33] edge 3 (75 middle anchor, up, 215 bottom anchor)
102     = top
103-134 = [31] edge 4 (128 middle anchor, down)
135-167 = [32] edge 5 (141 middle anchor, up, 238 bottom anchor)
168     = REAL top
169-202 = [33] edge 6 (195 middle anchor, down, 203 bottom anchor, 283 hidden anchor)

203     = bottom anchor (edge 6)
204-214 = bottom edge 1
215     = bottom anchor (edge 3)
216-226 = bottom edge 2
227     = bottom anchor (edge 1)
228-237 = bottom edge 3
238     = bottom anchor (edge 5)
239-249 = bottom edge 4
250     = bottom anchor (edge 4)
251-261 = bottom edge 5
262     = bottom anchor (edge 2)
263-272 = bottom edge 6

354-356, 273-282  = middle edge 1
283           = hidden anchor 1 (edge 6)
284-294       = middle edge 2
295 (296ish)  = hidden anchor 2 (edge )
297-310       = middle edge 3
311           = hidden anchor 3
312-324       = middle edge 4
325           = hidden anchor 4
326-337       = middle edge 5
338           = hidden anchor 5
339-352       = middle edge 6
353           = hidden anchor 6
**/

void setPixelColor(uint16_t i, uint32_t color) {
  strip.setPixelColor(i, color);
}

void setPixelColor(uint16_t i, uint8_t r, uint8_t g, uint8_t b) {
  strip.setPixelColor(i, r, g, b);
}

void setEdgeColor(uint32_t color, bool withRing) {
  for (int i = 0; i <= 35; i++) {
    setEdgeColor(i, color, withRing);
  }
}

void setEdgeColor(int index, uint32_t color)
{
  setEdgeColor(index, color, true);
}

void setEdgeColor(int index, uint32_t color, bool withRing)
{
  if (index <= 31)
  {
    setPixelColor(134 - index, color); // Edge 4
  }
  if (index <= 32)
  {
    setPixelColor(index, color); // Edge 1
    setPixelColor(135 + index, color); // Edge 5
  }
  if (index <= 33)
  {
    setPixelColor(67 - index, color); // Edge 2
    setPixelColor(68 + index, color); // Edge 3
    setPixelColor(202 - index, color); // Edge 6
  }
  if (index == 34) {
    setPixelColor(33, color);
    setPixelColor(34, color);
    setPixelColor(102, color);
    setPixelColor(168, color);
  }
  if (withRing) {
    if (index == 0)
    {
      for (int i = 203; i <= 272; i++)
      {
        setPixelColor(i, color);
      }
    }
    else if (index == 7)
    {
      for (int i = 273; i <= 356; i++)
      {
        setPixelColor(i, color);
      }
    }
  }
}

void setRingColor(int i, uint32_t color)
{
  setTopRingColor(i, color);
  setBottomRingColor(i, color);
}

void setBottomRingColor(int i, uint32_t color)
{
  if (i > 11)
  {
    return;
  }
  if (i == 0)
  {
    // This is actually at the other end of the strip
    setPixelColor(203 - i, color);
  }
  else
  {
    setPixelColor(273 - i, color);
  }
  setPixelColor(262 - i, color);
  setPixelColor(250 - i, color);
  setPixelColor(238 - i, color);
  setPixelColor(227 - i, color);
  setPixelColor(215 - i, color);
}

void setTopRingColor(int i, uint32_t color)
{
  setPixelColor(283 + i, color);
  setPixelColor(296 + i, color);
  setPixelColor(311 + i, color);
  setPixelColor(325 + i, color);
  setPixelColor(339 + i, color);
  if (i < 4)
  {
    setPixelColor(353 + i, color);
  }
  else
  {
    setPixelColor(269 + i, color);
  }
}

void setRingColorSymmetrical(int i, uint32_t color)
{
  setTopRingColorSymmetrical(i, color);
  setBottomRingColorSymmetrical(i, color);
}

void setBottomRingColorSymmetrical(int i, uint32_t color)
{
  if (i > 6)
  {
    return;
  }
  setPixelColor((i == 0 ? 203 : 273) - i, color);
  setPixelColor(263 + i, color);

  setPixelColor(262 - i, color);
  setPixelColor(251 + i, color);

  setPixelColor(250 - i, color);
  setPixelColor(239 + i, color);

  setPixelColor(238 - i, color);
  setPixelColor(228 + i, color);

  setPixelColor(227 - i, color);
  setPixelColor(216 + i, color);

  setPixelColor(215 - i, color);
  setPixelColor(204 + i, color);
}

void setTopRingColorSymmetrical(int i, uint32_t color)
{
  setPixelColor(283 + i, color);
  setPixelColor(295 - i, color);

  setPixelColor(296 + i, color);
  setPixelColor(310 - i, color);

  setPixelColor(311 + i, color);
  setPixelColor(324 - i, color);

  setPixelColor(325 + i, color);
  setPixelColor(338 - i, color);

  setPixelColor(339 + i, color);
  setPixelColor(352 - i, color);

  setPixelColor((i < 4 ? 353 : 269) + i, color);
  setPixelColor(282 - i, color);
}