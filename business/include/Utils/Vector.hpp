#pragma once

#include <cassert>
#include <cmath>

/**
 * @brief Represents a 2D vector with basic operations like addition, subtraction, normalization, and more.
 *
 * @tparam T Type for the vector components.
 * @tparam D Type for derived calculations (defaults to T).
 */
template <typename T, typename D = T>
class Vector {
public:
  /**
   * @brief Constructor to initialize a vector with x and y components.
   * 
   * @param x The x-component of the vector.
   * @param y The y-component of the vector.
   */
  Vector(T x, T y);

  /**
   * @brief Basic vector operations.
   */
  Vector operator+(Vector other) const;
  Vector operator-(Vector other) const;
  Vector operator-() const;
  T operator*(Vector other) const;

  /**
   * @brief Equality check by comparing components.
   *
   * @param other The vector to compare.
   * @return True if the vectors are equal, otherwise false.
   */
  bool operator==(Vector other) const;

  /**
   * @brief Normalize the vector.
   *
   * @note Asserts that the length of the vector is not zero.
   * @return The normalized vector.
   */
  Vector normalize();

  /**
   * @brief Get the length (magnitude) of the vector.
   * 
   * @return The length of the vector.
   */
  T length();

public:
  T x; ///< The x-component of the vector.
  T y; ///< The y-component of the vector.
};

/**
 * @brief Scalar multiplication of a vector.
 */
template <typename T>
Vector<T> operator*(Vector<T> vec, T value);

/**
 * @brief Scalar multiplication of a vector (reverse order).
 */
template <typename T>
Vector<T> operator*(T value, Vector<T> vec);
