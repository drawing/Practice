/*
 *  http://bestcoder.hdu.edu.cn/contests/contest_showproblem.php?cid=584&pid=1003
 *
 *  IP聚合  Accepts: 2007   Submissions: 5307
 *  Time Limit: 2000/1000 MS (Java/Others)   Memory Limit: 65536/65536 K (Java/Others)
 *  Problem Description
 *  当今世界，网络已经无处不在了，小度熊由于犯了错误，当上了度度公司的网络管理员，他手上有大量的 IP列表，小度熊想知道在某个固定的子网掩码下，有多少个网络地址。网络地址等于子网掩码与 IP 地址按位进行与运算后的结果，例如：
 *
 *  子网掩码：A.B.C.D
 *
 *  IP 地址：a.b.c.d
 *
 *  网络地址：(A&a).(B&b).(C&c).(D&d)
 *  Input
 *  第一行包含一个整数T，（1≤T≤50）代表测试数据的组数，
 *
 *  接下来T组测试数据。每组测试数据包含若干行，
 *
 *  第一行两个正整数N（1≤N≤1000,1≤M≤50）,M。接下来N行，每行一个字符串，代表一个 IP 地址，
 *
 *  再接下来M行，每行一个字符串代表子网掩码。IP 地址和子网掩码均采用 A.B.C.D的形式，其中A、B、C、D均为非负整数，且小于等于255。
 *  Output
 *  对于每组测试数据，输出两行：
 *
 *  第一行输出: "Case #i:" 。i代表第i组测试数据。
 *
 *  第二行输出测试数据的结果，对于每组数据中的每一个子网掩码，输出在此子网掩码下的网络地址的数量。
 *  Sample Input
 *  2
 *  5 2
 *  192.168.1.0
 *  192.168.1.101
 *  192.168.2.5
 *  192.168.2.7
 *  202.14.27.235
 *  255.255.255.0
 *  255.255.0.0
 *  4 2
 *  127.127.0.1
 *  10.134.52.0
 *  127.0.10.1
 *  10.134.0.2
 *  235.235.0.0
 *  1.57.16.0
 *  Sample Output
 *  Case #1:
 *  3
 *  2
 *  Case #2:
 *  3
 *  4
 */

#include <set>
#include <cstdio>

int main()
{
	int T = 0;
	scanf("%d", &T);
	for (int i = 0; i < T; i++) {
		int N, M;
		scanf("%d %d\n", &N, &M);

		std::set<uint32_t> ips;
		for (int j = 0; j < N; j++) {
			uint32_t a1, a2, a3, a4;
			scanf("%u.%u.%u.%u\n", &a1, &a2, &a3, &a4);
			uint32_t ip = (a1 << 24) | (a2 << 16) | (a3 << 8) | a4;
			ips.insert(ip);
		}

		printf("Case #%d:\n", i+1);
		for (int k = 0; k < M; k++) {
			uint32_t a1, a2, a3, a4;
			scanf("%u.%u.%u.%u", &a1, &a2, &a3, &a4);
			uint32_t mask = (a1 << 24) | (a2 << 16) | (a3 << 8) | a4;

			std::set<uint32_t> result;
			for (std::set<uint32_t>::iterator it = ips.begin(); it != ips.end(); it++) {
				result.insert(mask & *it);
			}
			printf("%u\n", (uint32_t)result.size());
		}
	}
	return 0;
}

