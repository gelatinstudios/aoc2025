
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct {
    int x, y, z;
} IV3;

long long distance2(IV3 a, IV3 b) {
    long long x = a.x - b.x;
    long long y = a.y - b.y;
    long long z = a.z - b.z;
    long long result = x*x + y*y + z*z;
    return result;
}

IV3 junctions[1024];
int junction_count = 0;

int circuits[1024];
int circuit_sizes[1024];

int int_comp_rev(const void *A, const void *B) {
    int a = *(int *)A;
    int b = *(int *)B;
    return a > b ? -1 : a < b;
}

typedef struct {
    int a, b; /* indices */
} Pair;

int pair_dist_comp(const void *A, const void *B) {
    Pair *a = (Pair *)A;
    Pair *b = (Pair *)B;
    long long a_dist = distance2(junctions[a->a], junctions[a->b]);
    long long b_dist = distance2(junctions[b->a], junctions[b->b]);
    return a_dist < b_dist ? -1 : a_dist > b_dist;
}

Pair pairs[1024*1024];
int pair_count = 0;

int main(void) {
    long long prod;
    int circuit_count;
    int i, j, n;

    int x, y, z;
    while (scanf("%d,%d,%d ", &x, &y, &z) > 0) {
        IV3 v = {x, y, z};
        junctions[junction_count++] = v;
    }

    for (i = 0; i < junction_count; i++) {
        for (j = i+1; j < junction_count; j++) {
            Pair p = {i, j};
            pairs[pair_count++] = p;
        }
    }

    qsort(pairs, pair_count, sizeof(Pair), pair_dist_comp);

#ifdef TEST
    n = 10;
#else
    n = 1000;
#endif

    circuit_count = 1;
    for (i = 0; i < n; i++) {
        int a, b, c, d;

        a = pairs[i].a;
        b = pairs[i].b;

        if (circuits[a] && circuits[b] && circuits[a] == circuits[b]) continue;

        if (circuits[a] && circuits[b]) {
            c = circuits[a];
            d = circuits[b];
            for (j = 0; j < junction_count; j++) {
                if (circuits[j] == d)
                    circuits[j] = c;
            }
            circuit_sizes[c] += circuit_sizes[d];
            circuit_sizes[d] = 0;
            continue;
        } else if (circuits[a]) {
            c = circuits[a];
        } else if (circuits[b]) {
            c = circuits[b];
        } else {
            c = circuit_count++;
            circuit_sizes[c] = 1;
        }

        circuit_sizes[c]++;

        circuits[a] = c;
        circuits[b] = c;
    }

    qsort(circuit_sizes, circuit_count, sizeof(circuit_sizes[0]), int_comp_rev);

    prod = 1;
    for (i = 0; i < 3; i++) {
        prod *= circuit_sizes[i];
    }

    printf("%lld\n", prod);

    return 0;
}
