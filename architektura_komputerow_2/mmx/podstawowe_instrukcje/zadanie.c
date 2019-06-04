#include <stdio.h>

void copy_memory8(void * a, void * b);
void simple_addition(void * a, void * b);
void example_of_conversion_and_shift(void * a, void * b);

int main () {
	long long b = 0x0fffffff00000000;
	long long c = 0x00000000ffffffff;
	printf("%lld == %lld\n", b, c);
	copy_memory8(&b, &c);
	printf("%lld == %lld\n", b, c);

	b = 0x1111111122222222;
	c = 0x3333333344444444;
	printf("%lld == %lld\n", b, c);
	simple_addition(&b, &c);
	printf("%lld == %lld\n", b, c);

	b = 0x1;
	c = 0x2233;
	printf("%lld == %lld\n", b, c);
	example_of_conversion_and_shift(&b, &c);
	printf("%lld == %lld\n", b, c);
		

	return 0;
}
