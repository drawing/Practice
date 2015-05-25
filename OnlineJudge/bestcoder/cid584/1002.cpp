#include <cstdio>
#include <cstring>

char pass[100002];
char res[100002];

int main()
{
	int T;
	char end;
	scanf("%d%c", &T, &end);

	for (int i = 0; i < T; i++) {
		gets(pass);

		int len = strlen(pass);
		int key;
		scanf("%d%c", &key, &end);

		int line = len / key;
		int pad = len % key;

		// printf("pad=%d, len=%d, line=%d\n", pad, len, line);
		int col = 0;
		int row = 0;
		for (int j = 0; j < len; j++) {
			res[row * key + col] = pass[j];
			row ++;
			if (pad == 0) {
				if (row >= line) {
					row = 0;
					col ++;
				}
			}
			else {
				if (row >= line + 1) {
					row = 0;
					col ++;
					pad --;
				}
			}
		}

		res[len] = 0;

		printf("Case #%d:\n", i+1);
		printf("%s\n", res);
	}
}


