#pragma once


inline float absf(float x);  






inline float Clamp(float value, float min, float max)
{
    if (value < min) return min;
    if (value > max) return max;
    return value;
}








// Ra�z cuadrada aproximada

float sqrt_approx(float x);     





// Inversa de ra�z cuadrada (m�s r�pida en algunos casos)

float inv_sqrt_approx(float x);  





// Seno aproximado

float sin_approx(float x);       





// Coseno aproximado

float cos_approx(float x);       
