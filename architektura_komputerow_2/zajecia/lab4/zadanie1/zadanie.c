#include <stdio.h>

extern float try_dividing_by_zero(float a, float b);
extern float make_precision_exception(float a);

int main()
{
	try_dividing_by_zero(5.0f, 0.0f);
	float sinusArg = 5.0f;
	float result = make_precision_exception(sinusArg);
	//printf("Wynik sinusa: %f", result);
}