#pragma once

#include <glad/gl.h>
#include <cstddef>
#include <cstdint>
#include <vector>


auto RegularCheckerboard(size_t rows, size_t columns) -> std::vector<uint8_t>;


class Texture {
public:

  enum class GridType {
    Regular,
    Random
  };

  Texture(std::size_t n_rows, std::size_t n_columns);
  Texture(std::size_t n_rows, std::size_t n_columns, GridType grid);
  Texture();
  Texture(Texture &&) = default;
  Texture(const Texture &) = default;
  Texture &operator=(Texture &&) = default;
  Texture &operator=(const Texture &) = default;
  ~Texture();

  auto ID() -> std::uint32_t { return m_ID; }
  auto InitialTexture() -> void;
  auto MakeCheckerboard(size_t rows, size_t columns, GridType grid) -> std::vector<uint8_t>;
  auto RandomCheckerboard(size_t rows, size_t columns) -> std::vector<uint8_t>;
  auto PixelData() -> std::uint8_t* { return m_data.data(); }
  auto Rows() -> std::size_t { return m_rows; }
  auto SetRows(std::size_t rows) -> void { m_rows = rows; }
  auto Columns() -> std::size_t { return m_columns; }
  auto SetColumns(std::size_t cols) -> void { m_columns = cols; }
  auto Update() -> void;

private:
  std::uint32_t m_ID;
  std::size_t m_rows;
  std::size_t m_columns;
  std::vector<uint8_t> m_data;

  
};

