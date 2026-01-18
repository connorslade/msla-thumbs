#include <qimage.h>

float lightness(unsigned int color) {
  return static_cast<float>((color & 0xFF) + ((color >> 8) & 0xFF) +
                            ((color >> 16) & 0xFF)) /
         3.0;
}

float invLerp(float a, float b, float value) { return (value - a) / (b - a); }
float saturate(float value) { return std::fmin(std::fmax(value, 0.0), 1.0); }

void removeBackground(QImage &img) {
  for (int y = 0; y < img.height(); y++) {
    for (int x = 0; x < img.width(); x++) {
      auto color = img.pixel(x, y);
      auto shade = lightness(color);
      auto alpha =
          static_cast<unsigned int>(saturate(invLerp(16, 24, shade)) * 255);

      auto newColor = (color & 0xFFFFFF) | alpha << 24;
      img.setPixel(x, y, newColor);
    }
  }
}
