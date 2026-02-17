#include <stdio.h>
#include <math.h>

int s=0,cnt[10000]={0};
int number[10000]={0};
int a[100][100];
void ac()
{
	printf("1\n");
	///fprintf(stderr,"Correct");
	fprintf(stderr,"Зөв хариулт");
}
void wa()
{
	printf("0\n");
	///fprintf(stderr,"Incorrect");
	fprintf(stderr,"Буруу хариулт");
}

int main(int argc, char* argv[])
{
//freopen("input00.txt", "r", stdin);
    long long m,n;
    FILE* stream = freopen(argv[2], "r", stdin);
    fscanf(stream, "%lld\n", &n);

    stream = freopen(argv[3], "r", stdin);
    fscanf(stream, "%lld", &m);

    if (n==m) ac(); else wa();
    return 0;
}

