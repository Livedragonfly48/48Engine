#include "Vec2.h"
#include "MathUtils.h"  
#include <iostream>  

Vec2::Vec2() : x(0), y(0) {}





Vec2::Vec2(float x, float y) : x(x), y(y) {}





Vec2 Vec2::operator+(const Vec2& other) const 
{
	return Vec2(x + other.x, y + other.y);
}





Vec2 Vec2::operator-(const Vec2& other) const 
{
	return Vec2(x - other.x, y - other.y);
}





Vec2 Vec2::operator*(float scalar) const
{
	return Vec2(x * scalar, y * scalar);
}





Vec2 Vec2::operator/(float scalar) const 
{
	return Vec2(x / scalar, y / scalar);
}





float Vec2::magnitude() const 
{
	float mag_sq = x * x + y * y;
	if (mag_sq < 0) 
	{
		std::cerr << "Error: Magnitud negativa detectada!" << std::endl;
		return std::nan("");  
	}
	return sqrt_approx(mag_sq);
}





Vec2 Vec2::normalized() const
{
	float mag = magnitude();
	if (mag == 0.0f) return Vec2(0, 0);
	return (*this) / mag;
}





float Vec2::dot(const Vec2& other) const 
{
	return x * other.x + y * other.y;
}
