#include <iostream>
#include "MathUtils.h"

/// <summary>
/// Devuelve el valor absoluto de un valor en coma flotante.
/// </summary>
/// <param name="x">Valor de entrada.</param>
/// <returns>El valor absoluto de <paramref name="x"/>.</returns>
inline float absf(float x)
{
    return x < 0 ? -x : x;
}

/// <summary>
/// Calcula una estimacion de la raiz cuadrada de un valor.
/// </summary>
/// <param name="x">Valor de entrada, debe ser mayor o igual a 0.</param>
/// <returns>Una estimacion de <c>√x</c>. Devuelve -1 si el valor es invalido o no converge.</returns>
float sqrt_approx(float x)
{
    if (x < 0)
    {
        return -1.0f;
    }

    if (x == 0)
    {
        return 0.0f;
    }

    float guess = (x > 1.0f) ? x * 0.5f : x;
    const float epsilon = 0.0001f;
    int max_iter = 1000;

    for (int i = 0; i < max_iter; ++i)
    {
        float guess_squared = guess * guess;
        float diff = guess_squared - x;

        if (absf(diff) < epsilon)
        {
            return guess;
        }

        guess = 0.5f * (guess + x / guess);

        if (guess < 0)
        {
            return -1.0f;
        }
    }

    return -1.0f;
}

/// <summary>
/// Calcula una estimacion de la inversa de la raiz cuadrada, es decir, <c>1 / √x</c>.
/// </summary>
/// <param name="x">Valor de entrada, debe ser mayor que 0.</param>
/// <returns>Una estimacion rapida de <c>1 / √x</c>.</returns>
float inv_sqrt_approx(float x)
{
    float xhalf = 0.5f * x;
    int i = *(int*)&x;
    i = 0x5f3759df - (i >> 1);
    x = *(float*)&i;
    x = x * (1.5f - xhalf * x * x);
    return x;
}

/// <summary>
/// Calcula una estimacion del seno de un valor de angulo.
/// </summary>
/// <param name="x">Valor de angulo en radianes.</param>
/// <returns>Una estimacion de <c>sin(x)</c> usando expansion en serie.</returns>
float sin_approx(float x)
{
    float x2 = x * x;
    return x - (x2 * x / 6) + (x2 * x2 * x / 120);
}

/// <summary>
/// Calcula una estimacion del coseno de un valor de angulo.
/// </summary>
/// <param name="x">Valor de angulo en radianes.</param>
/// <returns>Una estimacion de <c>cos(x)</c> usando expansion en serie.</returns>
float cos_approx(float x)
{
    float x2 = x * x;
    return 1 - (x2 / 2) + (x2 * x2 / 24);
}
