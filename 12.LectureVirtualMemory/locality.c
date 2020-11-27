
/*

Simple example to demonstrate impact of locality of refernce
on performance due to caching

$ gcc -O3 locality.c -o locality
$ time locality 0 50000 50000
allocating a 50000x50000 array = 10.0Gb
writing to array i-j order

real    0m1.906s
user    0m0.336s
sys 0m1.563s
$ time locality 1 50000 50000
allocating a 50000x50000 array = 10.0Gb
writing to array j-i order

real    0m13.171s
user    0m10.331s
sys 0m2.826s

$ valgrind '--tool=cachegrind' ./locality 0 10000 10000
allocating a 10000 x 10000 int array = 0.4Gb
writing to array i-j order
==473447==
==473447== I   refs:      175,353,857
==473447== I1  misses:          1,193
==473447== LLi misses:          1,182
==473447== I1  miss rate:        0.00%
==473447== LLi miss rate:        0.00%
==473447==
==473447== D   refs:       25,070,976  (57,624 rd   + 25,013,352 wr)
==473447== D1  misses:      6,263,358  (12,659 rd   +  6,250,699 wr)
==473447== LLd misses:      6,252,757  ( 2,156 rd   +  6,250,601 wr)
==473447== D1  miss rate:        25.0% (  22.0%     +       25.0%  )
==473447== LLd miss rate:        24.9% (   3.7%     +       25.0%  )
==473447==
==473447== LL refs:         6,264,551  (13,852 rd   +  6,250,699 wr)
==473447== LL misses:       6,253,939  ( 3,338 rd   +  6,250,601 wr)
==473447== LL miss rate:          3.1% (   0.0%     +       25.0%  )
$ valgrind '--tool=cachegrind' ./locality 1 10000 10000
allocating a 10000 x 10000 int array = 0.4Gb
writing to array j-i order
==473415==
==473415== I   refs:      500,283,856
==473415== I1  misses:          1,188
==473415== LLi misses:          1,176
==473415== I1  miss rate:        0.00%
==473415== LLi miss rate:        0.00%
==473415==
==473415== D   refs:      100,060,975  (47,623 rd   + 100,013,352 wr)
==473415== D1  misses:    100,003,357  ( 2,659 rd   + 100,000,698 wr)
==473415== LLd misses:      6,262,750  ( 2,150 rd   +   6,260,600 wr)
==473415== D1  miss rate:        99.9% (   5.6%     +       100.0%  )
==473415== LLd miss rate:         6.3% (   4.5%     +         6.3%  )
==473415==
==473415== LL refs:       100,004,545  ( 3,847 rd   + 100,000,698 wr)
==473415== LL misses:       6,263,926  ( 3,326 rd   +   6,260,600 wr)
==473415== LL miss rate:          1.0% (   0.0%     +         6.3%  )

*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void test0(int x, int y, int a[x][y]) {
    printf("writing to array i-j order\n");
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            a[i][j] = i+j;
        }
    }
}

void test1(int x, int y, int a[x][y]) {
    printf("writing to array j-i order\n");
    for (int j = 0; j < y; j++) {
        for (int i = 0; i < x; i++) {
            a[i][j] = i+j;
        }
    }
}


int main(int argc, char*argv[]) {
    size_t x = atoi(argv[2]);
    size_t y = atoi(argv[3]);

    size_t n_bytes = x * y * sizeof (int);

    printf("allocating a %d x %d int array = %.1lfGb\n", (int)x, (int)y, n_bytes/1000000000.0);

    void *m = malloc(n_bytes);

    if (m == NULL) {
        fprintf(stderr, "malloc failed\n");
        return 1;
    }

    if (atoi(argv[1])) {
        test1(x, y, m);
    } else {
        test0(x, y, m);
    }

    return 0;
}