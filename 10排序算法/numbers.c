#include <time.h>
#include <math.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <stdint.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <strings.h>
#include <pthread.h>
#include <semaphore.h>

#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char **argv)
{
	FILE *fp = fopen("numbers.txt", "w");

	srand(time(NULL));

	char n[20];
	int i;
	for(i=0; i<1000*1000; i++)
	{
		bzero(n, 20);
		int exp = (int)pow(10, rand()%8+5);

		snprintf(n, 20, "%u\n", rand()%exp);
		fwrite(n, strlen(n), 1, fp);
	}

	fclose(fp);

	return 0;
}
