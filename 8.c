
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

#define N 1024

IV3 junctions[N];
int junction_count = 0;

int circuits[N];

#define M 4096
int circuit_sizes[M];
int circuit_sizes_sorted[M];

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

void add_pair(Pair p, int *circuit_max, int *circuit_count) {
    int a, b, c, d;
    int i;

    a = p.a;
    b = p.b;

    if (circuits[a] && circuits[b] && circuits[a] == circuits[b]) return;

    if (circuits[a] && circuits[b]) {
        c = circuits[a];
        d = circuits[b];
        for (i = 0; i < junction_count; i++) {
            if (circuits[i] == d)
                circuits[i] = c;
        }
        circuit_sizes[c] += circuit_sizes[d];
        circuit_sizes[d] = 0;
        (*circuit_count)--;
        return;
    } else if (circuits[a]) {
        c = circuits[a];
        (*circuit_count)--;
    } else if (circuits[b]) {
        c = circuits[b];
        (*circuit_count)--;
    } else {
        (*circuit_count)--;
        c = (*circuit_max)++;
        circuit_sizes[c] = 1;
    }

    circuit_sizes[c]++;

    circuits[a] = c;
    circuits[b] = c;
}

int main(void) {
    long long prod;
    int circuit_count, circuit_max;
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

    circuit_count = junction_count;

    /* part 1 */
#ifdef TEST
    n = 10;
#else
    n = 1000;
#endif
    circuit_max = 1;
    for (i = 0; i < n; i++) {
        add_pair(pairs[i], &circuit_max, &circuit_count);
    }
    memcpy(circuit_sizes_sorted, circuit_sizes, sizeof(circuit_sizes));
    qsort(circuit_sizes_sorted, circuit_max, sizeof(circuit_sizes[0]), int_comp_rev);
    prod = 1;
    for (i = 0; i < 3; i++) {
        prod *= circuit_sizes_sorted[i];
    }
    printf("%lld\n", prod);

    /* part 2 */
    for (i = n; i < pair_count; i++) {
        add_pair(pairs[i], &circuit_max, &circuit_count);
        if (circuit_count == 1) {
            long long a = junctions[pairs[i].a].x;
            long long b = junctions[pairs[i].b].x;
            printf("%lld\n", a*b);
            break;
        }
    }

    return 0;
}
