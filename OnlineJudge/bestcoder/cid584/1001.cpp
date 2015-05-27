#include <stdio.h>
#include <stdint.h>

unsigned table[1000000];

int main()
{
	table[0] = 1;
	table[1] = 2;
	for (int i = 2; i < 1000000; i++) {
		uint64_t a1 = table[i-1];
		uint64_t a2 = table[i-2];
		uint64_t a3 = a1 + a2 * i;
		table[i] = a3 % 1000000007;
	}

	unsigned t = 0;
	scanf("%u", &t);
	for (unsigned i = 0; i < t; i++) {
		unsigned n = 0;
		scanf("%u", &n);
		printf("Case #%u:\n", i+1);
		printf("%u\n", table[n-1]);
	}
	return 0;
}

