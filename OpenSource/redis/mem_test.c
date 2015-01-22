/*
 * export REDIS_SRC=../../../redis-2.8.19/src/
 * gcc mem_test.c -I$REDIS_SRC $REDIS_SRC/zmalloc.c
 */

#include "zmalloc.h"
#include "stdio.h"

int main()
{
	int * pi = zmalloc(sizeof(int) * 4);
	*pi = 10;

	printf("zmsize=%lu\n", zmalloc_size(pi));
	pi = zrealloc(pi, sizeof(int)*8);

	printf("v0=%d, v1=%d\n", pi[0], pi[1]);
	printf("zmsize=%lu\n", zmalloc_size(pi));
	zfree(pi);
	return 0;
}

