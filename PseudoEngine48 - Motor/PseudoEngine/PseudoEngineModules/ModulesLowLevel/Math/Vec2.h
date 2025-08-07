#pragma once

struct Vec2 {
    float x, y;

    Vec2();
    Vec2(float x, float y);

    Vec2 operator+(const Vec2& other) const;
    Vec2& operator+=(const Vec2& other);        // <- operador compuesto suma

    Vec2 operator-(const Vec2& other) const;
    Vec2& operator-=(const Vec2& other);        // <- operador compuesto resta

    Vec2 operator*(float scalar) const;
    Vec2& operator*=(float scalar);              // <- operador compuesto multiplicacion

    Vec2 operator/(float scalar) const;
    Vec2& operator/=(float scalar);              // <- operador compuesto division

    bool operator==(const Vec2& other) const;   // opcional, compara igualdad

    float magnitude() const;
    Vec2 normalized() const;
    float dot(const Vec2& other) const;
    float lengthSquared() const;
};
