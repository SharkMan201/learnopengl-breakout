#ifndef TEXTURE_H
#define TEXTURE_H

namespace core {
class Texture2D {
 public:
  Texture2D(const Texture2D&) = delete;
  Texture2D& operator=(const Texture2D&) = delete;

  unsigned int id;
  unsigned int width, height;
  unsigned int internal_format;
  unsigned int image_format;
  unsigned int wrap_s;
  unsigned int wrap_t;
  unsigned int filter_min;
  unsigned int filter_max;

  Texture2D();
  void Generate(unsigned int width, unsigned int height, unsigned char* data);
  void Bind() const;
};
}  // namespace core

#endif