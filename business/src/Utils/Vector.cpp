#pragma once

#include "Utils/Vector.hpp"

// Epsilon for floating-point comparisons
static constexpr double EPS = 1e-9;

template <typename T, typename D>
Vector<T, D>::Vector(T x, T y) : x{x}, y{y} {}

template <typename T, typename D>
Vector<T, D> Vector<T, D>::operator+(Vector other) const {
  return {x + other.x, y + other.y};
}

template <typename T, typename D>
Vector<T, D> Vector<T, D>::operator-(Vector other) const {
  return {x - other.x, y - other.y};
}

template <typename T, typename D>
Vector<T, D> Vector<T, D>::operator-() const {
  return {-x, -y};
}

template <typename T, typename D>
T Vector<T, D>::operator*(Vector other) const {
  return x * other.x + y * other.y;
}

template <typename T, typename D>
bool Vector<T, D>::operator==(Vector other) const {
  return x == other.x && y == other.y;
}

template <typename T, typename D>
Vector<T, D> Vector<T, D>::normalize() {
  T len = length();
  assert(std::fabs(len) > EPS); // Ensure the length is non-zero
  return {x / len, y / len};
}

template <typename T, typename D>
T Vector<T, D>::length() {
  return std::sqrt(x * x + y * y);
}

template <typename T>
Vector<T> operator*(Vector<T> vec, T value) {
  return {vec.x * value, vec.y * value};
}

template <typename T>
Vector<T> operator*(T value, Vector<T> vec) {
  return vec * value;
}
