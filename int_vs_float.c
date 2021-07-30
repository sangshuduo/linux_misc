#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#define MAX_PREPARED_RAND  1000000

int32_t  randint[MAX_PREPARED_RAND];
int64_t  randbigint[MAX_PREPARED_RAND];
float    randfloat[MAX_PREPARED_RAND];
double   randdouble[MAX_PREPARED_RAND];

static int32_t rand_int(){
    static int cursor;
    cursor++;
    cursor = cursor % MAX_PREPARED_RAND;
    return randint[cursor];
}

static float rand_float(){
    static int cursor;
    cursor++;
    cursor = cursor % MAX_PREPARED_RAND;
    return randfloat[cursor];
}

static void init_rand_data() {
    for (int i = 0; i < MAX_PREPARED_RAND; i++){
        randint[i] = (int)(rand() % 65535);
        randbigint[i] = (int64_t)(rand() % 2147483648);
        randfloat[i] = (float)(rand() / 1000.0);
        randdouble[i] = (double)(rand() / 1000000.0);
    }
}

int main(int argc, char *argv[])
{
    init_rand_data();

    char buffer[20];
    int64_t i, j, loop;

    loop = atoi(argv[1]);

    struct timespec start1, end1, start2, end2;

    clock_gettime(CLOCK_MONOTONIC_RAW, &start1);
    for (i = 0; i < loop; i ++)
        sprintf(buffer, "%d", rand_int());
    clock_gettime(CLOCK_MONOTONIC_RAW, &end1);

    clock_gettime(CLOCK_MONOTONIC_RAW, &start2);
    for (j = 0; j < loop; j ++)
        sprintf(buffer, "%10.4f", rand_float());
    clock_gettime(CLOCK_MONOTONIC_RAW, &end2);

    uint64_t delta_us1 = (end1.tv_sec - start1.tv_sec) * 1000000 + (end1.tv_nsec - start1.tv_nsec) / 1000;
    uint64_t delta_us2 = (end2.tv_sec - start2.tv_sec) * 1000000 + (end2.tv_nsec - start2.tv_nsec) / 1000;

    printf("sprintf rand_int   loop %ld, spent: %ld microseconds\n", loop, delta_us1);
    printf("sprintf rand_float loop %ld, spent: %ld microseconds\n", loop, delta_us2);

    return 0;
}
