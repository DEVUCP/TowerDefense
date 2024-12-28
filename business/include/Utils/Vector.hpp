#pragma once

#include <cassert>
#include <cmath>

static constexpr double EPS = 1e-9;

template <typename T, typename D = T>
class Vector {
public:
  Vector(T x, T y) : x{x}, y{y} {}

  /*
   * @brief the Basic Operations on the vector: addition, subtracion,
   * reverse_direction, and scalar product
   */
  Vector operator+(Vector other) const { return {x + other.x, y + other.y}; }
  Vector operator-(Vector other) const { return {x - other.x, y - other.y}; }
  Vector operator-() const { return {-x, -y}; }
  T operator*(Vector other) const { return x * other.x + y * other.y; }

  /*
   * @brief Check Equality by comparing x's and y's
   */
  bool operator==(Vector other) const { return x == other.x && y == other.y; }

  /*
   * @brief Normalize a vector
   *
   * @note Must check length is not equal to 0
   */
  Vector normalize() {
    assert(has_direction());
    T len = length();

    return {x / len, y / len};
  }

  /*
   * @brief Get the length of a vector
   */
  float length() { return std::sqrt(x * x + y * y); }

  /**
   * @brief Return The distance between two vectors using vector arithmetic
   */
  float get_distance_to(Vector<T> destination) {
    return std::sqrt(std::pow(destination.x - x, 2) +
                     std::pow(destination.y - y, 2));
  }

  /**
   * @brief Return true if two vectors are in the same direction
   *
   * @brief
   * Make sure neither is the origin point
   */
  bool is_same_direction_as(Vector<T> other) {
    assert(has_direction());
    assert(other.has_direction());
    return this->normalize() == other.normalize();
  }

  /**
   * @brief Return true if a vector is the same as the origin point (same as has
   * no direction)
   */
  bool is_origin() { return x == 0 && y == 0; }

  /**
   * @brief Return true if the vector has direction
   */
  bool has_direction() { return !is_origin(); };

public:
  T x;
  T y;
};

template <typename T>
Vector<T> operator*(Vector<T> vec, T value) {
  return Vector<T>(vec.x * value, vec.y * value);
}
template <typename T>
Vector<T> operator*(T value, Vector<T> vec) {
  return vec * value;
}
