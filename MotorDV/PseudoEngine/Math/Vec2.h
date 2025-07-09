#pragma once


struct Vec2 {

	float x, y;





	// Constructor por defecto

	Vec2();





	// Constructor con parámetros

	Vec2(float x, float y);






	// Suma de vectores

	Vec2 operator+(const Vec2& other) const;






	// Resta de vectores

	Vec2 operator-(const Vec2& other) const;






	// Multiplicación por escalar

	Vec2 operator*(float scalar) const;






	// División por escalar

	Vec2 operator/(float scalar) const;






	// Magnitud (longitud del vector)

	float magnitude() const;






	// Normalización (vector unitario)

	Vec2 normalized() const;






	// Producto punto

	float dot(const Vec2& other) const;

};
