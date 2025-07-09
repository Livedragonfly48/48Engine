#include <iostream>  
#include "MathUtils.h"



inline float absf(float x) 
{
	return x < 0 ? -x : x;
}





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





float inv_sqrt_approx(float x)
{
	float xhalf = 0.5f * x;
	int i = *(int*)&x;
	i = 0x5f3759df - (i >> 1);
	x = *(float*)&i;
	x = x * (1.5f - xhalf * x * x);
	return x;
}





float sin_approx(float x)
{
	float x2 = x * x;
	return x - (x2 * x / 6) + (x2 * x2 * x / 120);
}





float cos_approx(float x) 
{
	float x2 = x * x;
	return 1 - (x2 / 2) + (x2 * x2 / 24);
}
