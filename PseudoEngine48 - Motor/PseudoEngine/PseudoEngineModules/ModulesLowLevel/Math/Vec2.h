#pragma once

/// <summary>
/// Representa un vector en 2 dimensiones con componentes <c>x</c> e <c>y</c>.
/// </summary>
struct Vec2 {
    float x, y;

    /// <summary>
    /// Constructor por defecto, inicializa el vector en (0,0).
    /// </summary>
    Vec2();

    /// <summary>
    /// Constructor que inicializa el vector con valores especificos.
    /// </summary>
    /// <param name="x">Valor inicial de la componente x.</param>
    /// <param name="y">Valor inicial de la componente y.</param>
    Vec2(float x, float y);

    /// <summary>
    /// Suma dos vectores y devuelve el resultado.
    /// </summary>
    /// <param name="other">Vector a sumar.</param>
    /// <returns>Un nuevo vector que es la suma de este vector y <paramref name="other"/>.</returns>
    Vec2 operator+(const Vec2& other) const;

    /// <summary>
    /// Suma otro vector a este vector (operador compuesto).
    /// </summary>
    /// <param name="other">Vector a sumar.</param>
    /// <returns>Referencia a este vector despues de la suma.</returns>
    Vec2& operator+=(const Vec2& other);

    /// <summary>
    /// Resta otro vector de este vector y devuelve el resultado.
    /// </summary>
    /// <param name="other">Vector a restar.</param>
    /// <returns>Un nuevo vector que es la resta de este vector y <paramref name="other"/>.</returns>
    Vec2 operator-(const Vec2& other) const;

    /// <summary>
    /// Resta otro vector de este vector (operador compuesto).
    /// </summary>
    /// <param name="other">Vector a restar.</param>
    /// <returns>Referencia a este vector despues de la resta.</returns>
    Vec2& operator-=(const Vec2& other);

    /// <summary>
    /// Multiplica el vector por un escalar y devuelve el resultado.
    /// </summary>
    /// <param name="scalar">Valor escalar.</param>
    /// <returns>Un nuevo vector escalado.</returns>
    Vec2 operator*(float scalar) const;

    /// <summary>
    /// Multiplica este vector por un escalar (operador compuesto).
    /// </summary>
    /// <param name="scalar">Valor escalar.</param>
    /// <returns>Referencia a este vector despues de la multiplicacion.</returns>
    Vec2& operator*=(float scalar);

    /// <summary>
    /// Divide el vector por un escalar y devuelve el resultado.
    /// </summary>
    /// <param name="scalar">Valor escalar.</param>
    /// <returns>Un nuevo vector dividido por <paramref name="scalar"/>.</returns>
    Vec2 operator/(float scalar) const;

    /// <summary>
    /// Divide este vector por un escalar (operador compuesto).
    /// </summary>
    /// <param name="scalar">Valor escalar.</param>
    /// <returns>Referencia a este vector despues de la division.</returns>
    Vec2& operator/=(float scalar);

    /// <summary>
    /// Compara si dos vectores son iguales.
    /// </summary>
    /// <param name="other">Vector a comparar.</param>
    /// <returns>True si las componentes x e y son iguales, false en otro caso.</returns>
    bool operator==(const Vec2& other) const;

    /// <summary>
    /// Devuelve la magnitud (longitud) del vector.
    /// </summary>
    /// <returns>Valor de la magnitud del vector.</returns>
    float magnitude() const;

    /// <summary>
    /// Devuelve una version normalizada del vector (longitud = 1).
    /// </summary>
    /// <returns>Un nuevo vector normalizado.</returns>
    Vec2 normalized() const;

    /// <summary>
    /// Calcula el producto punto con otro vector.
    /// </summary>
    /// <param name="other">Vector con el cual calcular el producto punto.</param>
    /// <returns>El resultado del producto punto.</returns>
    float dot(const Vec2& other) const;

    /// <summary>
    /// Devuelve la magnitud al cuadrado del vector.
    /// </summary>
    /// <returns>Valor de la magnitud al cuadrado.</returns>
    float lengthSquared() const;
};
