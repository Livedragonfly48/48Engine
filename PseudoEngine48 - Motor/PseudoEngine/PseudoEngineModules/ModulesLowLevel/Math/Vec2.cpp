#include "Vec2.h"
#include "MathUtils.h"
#include <iostream>

/// <summary>
/// Constructor por defecto, inicializa el vector en (0,0).
/// </summary>
Vec2::Vec2() : x(0), y(0) {}

/// <summary>
/// Constructor que inicializa el vector con valores especificos.
/// </summary>
/// <param name="x">Valor inicial de la componente x.</param>
/// <param name="y">Valor inicial de la componente y.</param>
Vec2::Vec2(float x, float y) : x(x), y(y) {}

/// <summary>
/// Suma dos vectores y devuelve el resultado.
/// </summary>
/// <param name="other">Vector a sumar.</param>
/// <returns>Un nuevo vector que es la suma de este vector y <paramref name="other"/>.</returns>
Vec2 Vec2::operator+(const Vec2& other) const {
    return Vec2(x + other.x, y + other.y);
}

/// <summary>
/// Suma otro vector a este vector (operador compuesto).
/// </summary>
/// <param name="other">Vector a sumar.</param>
/// <returns>Referencia a este vector despues de la suma.</returns>
Vec2& Vec2::operator+=(const Vec2& other) {
    x += other.x;
    y += other.y;
    return *this;
}

/// <summary>
/// Resta otro vector de este vector y devuelve el resultado.
/// </summary>
/// <param name="other">Vector a restar.</param>
/// <returns>Un nuevo vector que es la resta de este vector y <paramref name="other"/>.</returns>
Vec2 Vec2::operator-(const Vec2& other) const {
    return Vec2(x - other.x, y - other.y);
}

/// <summary>
/// Resta otro vector de este vector (operador compuesto).
/// </summary>
/// <param name="other">Vector a restar.</param>
/// <returns>Referencia a este vector despues de la resta.</returns>
Vec2& Vec2::operator-=(const Vec2& other) {
    x -= other.x;
    y -= other.y;
    return *this;
}

/// <summary>
/// Multiplica el vector por un escalar y devuelve el resultado.
/// </summary>
/// <param name="scalar">Valor escalar.</param>
/// <returns>Un nuevo vector escalado.</returns>
Vec2 Vec2::operator*(float scalar) const {
    return Vec2(x * scalar, y * scalar);
}

/// <summary>
/// Multiplica este vector por un escalar (operador compuesto).
/// </summary>
/// <param name="scalar">Valor escalar.</param>
/// <returns>Referencia a este vector despues de la multiplicacion.</returns>
Vec2& Vec2::operator*=(float scalar) {
    x *= scalar;
    y *= scalar;
    return *this;
}

/// <summary>
/// Divide el vector por un escalar y devuelve el resultado.
/// </summary>
/// <param name="scalar">Valor escalar.</param>
/// <returns>Un nuevo vector dividido por <paramref name="scalar"/>.</returns>
Vec2 Vec2::operator/(float scalar) const {
    return Vec2(x / scalar, y / scalar);
}

/// <summary>
/// Divide este vector por un escalar (operador compuesto).
/// </summary>
/// <param name="scalar">Valor escalar.</param>
/// <returns>Referencia a este vector despues de la division.</returns>
Vec2& Vec2::operator/=(float scalar) {
    x /= scalar;
    y /= scalar;
    return *this;
}

/// <summary>
/// Compara si dos vectores son iguales.
/// </summary>
/// <param name="other">Vector a comparar.</param>
/// <returns>True si las componentes x e y son iguales, false en otro caso.</returns>
bool Vec2::operator==(const Vec2& other) const {
    return (x == other.x) && (y == other.y);
}

/// <summary>
/// Devuelve la magnitud (longitud) del vector.
/// </summary>
/// <returns>Valor de la magnitud del vector. Devuelve NaN si ocurre un error.</returns>
float Vec2::magnitude() const {
    float mag_sq = x * x + y * y;
    if (mag_sq < 0) {
        std::cerr << "Error: Magnitud negativa detectada!" << std::endl;
        return std::nan("");
    }
    return sqrt_approx(mag_sq);
}

/// <summary>
/// Devuelve una version normalizada del vector (longitud = 1).
/// </summary>
/// <returns>Un nuevo vector normalizado. Si la magnitud es 0, devuelve (0,0).</returns>
Vec2 Vec2::normalized() const {
    float mag = magnitude();
    if (mag == 0.0f) return Vec2(0, 0);
    return (*this) / mag;
}

/// <summary>
/// Calcula el producto punto con otro vector.
/// </summary>
/// <param name="other">Vector con el cual calcular el producto punto.</param>
/// <returns>El resultado del producto punto.</returns>
float Vec2::dot(const Vec2& other) const {
    return x * other.x + y * other.y;
}

/// <summary>
/// Devuelve la magnitud al cuadrado del vector.
/// </summary>
/// <returns>Valor de la magnitud al cuadrado.</returns>
float Vec2::lengthSquared() const {
    return x * x + y * y;
}
