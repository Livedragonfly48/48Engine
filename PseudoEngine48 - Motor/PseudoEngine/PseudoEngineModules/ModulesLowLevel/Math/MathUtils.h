#pragma once

/// <summary>
/// Devuelve el valor absoluto de un valor en coma flotante.
/// </summary>
/// <param name="x">Valor de entrada.</param>
/// <returns>El valor absoluto de <paramref name="x"/>.</returns>
inline float absf(float x);

/// <summary>
/// Restringe un valor a un rango definido entre <paramref name="min"/> y <paramref name="max"/>.
/// </summary>
/// <param name="value">Valor que se quiere limitar.</param>
/// <param name="min">Valor menor permitido.</param>
/// <param name="max">Valor mayor permitido.</param>
/// <returns>
/// Si <paramref name="value"/> es menor que <paramref name="min"/>, devuelve <paramref name="min"/>.<br/>
/// Si <paramref name="value"/> es mayor que <paramref name="max"/>, devuelve <paramref name="max"/>.<br/>
/// En cualquier otro caso devuelve <paramref name="value"/>.
/// </returns>
inline float Clamp(float value, float min, float max)
{
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

/// <summary>
/// Calcula una estimacion de la raiz cuadrada de un valor.
/// </summary>
/// <param name="x">Valor de entrada, debe ser mayor o igual a 0.</param>
/// <returns>Una estimacion de <c>√x</c>.</returns>
float sqrt_approx(float x);

/// <summary>
/// Calcula una estimacion de la inversa de la raiz cuadrada, es decir, <c>1 / √x</c>.
/// </summary>
/// <param name="x">Valor de entrada, debe ser mayor que 0.</param>
/// <returns>Una estimacion de <c>1 / √x</c>.</returns>
float inv_sqrt_approx(float x);

/// <summary>
/// Calcula una estimacion del seno de un valor de angulo.
/// </summary>
/// <param name="x">Valor de angulo en radianes.</param>
/// <returns>Una estimacion de <c>sin(x)</c>.</returns>
float sin_approx(float x);

/// <summary>
/// Calcula una estimacion del coseno de un valor de angulo.
/// </summary>
/// <param name="x">Valor de angulo en radianes.</param>
/// <returns>Una estimacion de <c>cos(x)</c>.</returns>
float cos_approx(float x);
