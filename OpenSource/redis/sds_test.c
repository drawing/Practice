/*
 * export REDIS_SRC=../../../redis-2.8.19/src/
 * gcc sds_test.c -I$REDIS_SRC $REDIS_SRC/sds.c $REDIS_SRC/zmalloc.c
 */

#include "sds.h"
#include "stdio.h"

int main()
{
	sds s1 = sdsnew("Test");
	printf("s1.len=%lu, s1.free=%lu\n", sdslen(s1), sdsavail(s1));
	s1 = sdscat(s1, " ok");
	printf("s1.len=%lu, s1.free=%lu\n", sdslen(s1), sdsavail(s1));
	return 0;
}

