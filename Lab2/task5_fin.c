#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#define SWAP(x, y)   \
    int32_t tmp = x; \
    x = y;           \
    y = tmp;

int32_t calculations(int32_t a, int32_t b, int32_t c, int32_t arr1, int32_t arr2);
void KStat(int32_t *array, int32_t start, int32_t end, int32_t k);

int main()
{
    FILE *fin = fopen("kth.in", "r");
    FILE *fout = fopen("kth.out", "w");
    int32_t n, k, a, b, c;
    fscanf(fin, "%" SCNd32 "%" SCNd32 "%" SCNd32 "%" SCNd32 "%" SCNd32, &n, &k, &a, &b, &c);

    if (n == 1)
    {
        int32_t number;
        fscanf(fin, "%" SCNd32, &number);
        fprintf(fout, "%" PRId32, number);
        return 0;
    }

    int32_t *array = (int32_t *)malloc(n * sizeof(int32_t));
    fscanf(fin, "%" SCNd32 "%" SCNd32, &array[0], &array[1]);

    for (int32_t i = 2; i < n; ++i)
    {
        array[i] = calculations(a, b, c, array[i - 2], array[i - 1]);
    }

    KStat(array, 0, n - 1, k - 1);
    fprintf(fout, "%" PRId32, array[k - 1]);

    free(array);
    fclose(fin);
    fclose(fout);
    return 0;
}

int32_t calculations(int32_t a, int32_t b, int32_t c, int32_t x, int32_t y)
{
    return a * x + b * y + c;
}


void KStat(int32_t *array, int32_t start, int32_t end, int32_t k){
    int32_t pivot = array[(start + end) / 2];
    int32_t i = start;
    int32_t j = end;

    while (i <= j){
        while (array[i] < pivot){
            ++i;
        }
        while (array[j] > pivot){
            --j;
        }
        if (i <= j){
            SWAP(array[i], array[j]);
            ++i;
            --j;
        }
    }

    if (start < j && k <= j){
        KStat(array, start, j, k);
    }
    else if (end > i && k >= i){
        KStat(array, i, end, k);
    }
}
