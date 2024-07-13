#include "Texture.h"
#include <cstdint>
#include <iostream>
#include <random>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"


auto RegularCheckerboard(size_t rows, size_t columns) -> std::vector<uint8_t> {
  std::vector<uint8_t> data;
  data.resize(rows*columns);
  std::cout << "Data Size: " << data.size() << "\n";
  for(size_t j = 0; j < columns; ++j) {
    for(size_t i = 0; i < rows; ++i) {
      if ((j % 2 == 0 && i % 2 == 0) || (j % 2 == 1 && i % 2 == 1)) {
        data[i + j * rows] = 0xFF;
      } else {
        data[i + j * rows] = 0x00;
      }
    }
  }

  return data;
}

auto LoadTexture(const std::string& name) -> uint32_t {
  int width, height, num_channels;
  unsigned char* data = stbi_load(name.c_str(), &width, &height, &num_channels, 0);

  uint32_t texture;
  glGenTextures(1, &texture);

  glBindTexture(GL_TEXTURE_2D, texture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  if (data) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  } else {
    std::cout << "Failed to load texture\n";
  }

  stbi_image_free(data);

  return texture;
}

auto Texture::Update() -> void {
  glTextureSubImage2D(m_ID,
                      0,
                      0, 0,
                      m_rows, m_columns,
                      GL_RED, GL_UNSIGNED_BYTE,
                      m_data.data());

}

Texture::Texture(size_t n_rows, size_t n_columns) {
  // stbi_set_flip_vertically_on_load(true);
  m_rows = n_rows;
  m_columns = n_columns;
  m_data = RegularCheckerboard(m_rows, m_columns);
}

Texture::Texture(size_t n_rows, size_t n_columns, GridType grid) {
  m_rows = n_rows;
  m_columns = n_columns;
  m_data = MakeCheckerboard(m_rows, m_columns, grid);
}

auto Texture::MakeCheckerboard(size_t rows, size_t columns, GridType grid) -> std::vector<uint8_t> {
  if (grid == GridType::Regular) {
    return RegularCheckerboard(rows, columns); 
  } else if (grid == GridType::Random) {
    return RandomCheckerboard(rows, columns);
  } else {
    return std::vector<uint8_t> {};
  }
}

auto Texture::RandomCheckerboard(size_t rows, size_t columns) -> std::vector<uint8_t> {

  std::mt19937 generator{std::random_device{}()};
  std::uniform_real_distribution<float> up_or_down(0.0, 1.0);

  std::vector<uint8_t> data;
  data.resize(rows*columns);
  for(size_t j = 0; j < columns; ++j) {
    for(size_t i = 0; i < rows; ++i) {
      if (up_or_down(generator) < 0.5) {
        data[i + j * rows] = 0xFF;
      } else {
        data[i + j * rows] = 0x00;
      }
    }
  }

  return data;
}

Texture::Texture() {
}

auto Texture::InitialTexture() -> void {

  glCreateTextures(GL_TEXTURE_2D, 1, &m_ID);
  glTextureStorage2D(m_ID, 1, GL_R8, m_rows, m_columns);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glTextureSubImage2D(m_ID,
                      0,
                      0, 0,
                      m_rows, m_columns,
                      GL_RED, GL_UNSIGNED_BYTE,
                      m_data.data());

  glBindTexture(GL_TEXTURE_2D, m_ID);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

Texture::~Texture() {
}
