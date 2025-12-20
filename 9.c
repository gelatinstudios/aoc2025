
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>

#define Min(a,b) ((a)<(b)?(a):(b))
#define Max(a,b) ((a)>(b)?(a):(b))

int int_comp(const void *A, const void *B) {
    int a = *(int *)A;
    int b = *(int *)B;
    return a < b ? -1 : a > b;
}

typedef struct {
    int x, y;
} IV2;

IV2 iv2(int x, int y) {
    IV2 v;
    v.x=x;
    v.y=y;
    return v;
}

IV2 compressed_tiles[512];
IV2 tiles[512];
int tile_count = 0;

int xs[512];
int xs_count =0 ;

int ys[512];
int ys_count = 0;

char rg_tiles[512][512];

int is_rg(int a_index, int b_index) {
    int x,y;
    IV2 a = compressed_tiles[a_index];
    IV2 b = compressed_tiles[b_index];
    for (y = Min(a.y,b.y); y <= Max(a.y,b.y); y++) {
        for (x = Min(a.x,b.x); x <= Max(a.x,b.x); x++) {
            if (rg_tiles[y][x] == 0) return 0;
        }
    }
    return 1;
}

void print_largest_area(int part2) {
    int64_t largest_area, area;
    IV2 a, b;
    int i, j;
    largest_area = 0;
    for (i = 0; i < tile_count; i++) {
        a = tiles[i];
        for (j = i+1; j < tile_count; j++) {
            b = tiles[j];
            if (!part2 || is_rg(i, j)) {
                area = (int64_t)(abs(a.x - b.x) + 1) * (int64_t)(abs(a.y - b.y) + 1);
                if (area > largest_area) {
                    largest_area = area;
                }
            }
        }
    }
    printf("%ld\n", largest_area);
}

int main(void) {
    int i, j;
    IV2 a, b, v;
    int found;

    int x, y;
    while (scanf("%d,%d ", &x, &y) > 0) {
        tiles[tile_count++] = iv2(x,y);
    }

    print_largest_area(0);

    for (i = 0; i < tile_count; i++) {
        v = tiles[i];
        found = 0;
        for (j = 0; j < xs_count; j++) {
            if (xs[j]==v.x) {
                found=1;
                break;
            }
        }
        if (!found) xs[xs_count++] = v.x;
        found = 0;
        for (j = 0; j < ys_count; j++) {
            if (ys[j]==v.y) {
                found=1;
                break;
            }
        }
        if (!found) ys[ys_count++] = v.y;
    }

    qsort(xs, xs_count, sizeof(int), int_comp);
    qsort(ys, ys_count, sizeof(int), int_comp);

    for (i = 0; i < tile_count; i++) {
        v = tiles[i];
        for (j = 0; j < xs_count; j++) {
            if (xs[j] == v.x) {
                v.x = j;
                break;
            }
        }
        for (j = 0; j < ys_count; j++) {
            if (ys[j] == v.y) {
                v.y = j;
                break;
            }
        }
        compressed_tiles[i] = v;
    }

    a = compressed_tiles[tile_count-1];
    for (i = 0; i < tile_count; i++) {
        b = compressed_tiles[i];
        for (y = Min(a.y,b.y); y <= Max(a.y,b.y); y++) {
            for (x = Min(a.x,b.x); x <= Max(a.x,b.x); x++) {
                rg_tiles[y][x] = 1;
            }
        }
        a = b;
    }

    /* find inner cell */
    x = 0;
    y = ys_count/2;
    while (rg_tiles[y][x] == 0) x++;
    x++;
    assert(rg_tiles[y][x]==0);

    { /* flood-fill */
        static IV2 stack[512*512];
        int count = 0;
        stack[count++] = iv2(x,y);
        while (count > 0) {
            v = stack[--count];
            x = v.x;
            y = v.y;
            if (rg_tiles[y][x]) continue;
            rg_tiles[y][x] = 1;
            stack[count++] = iv2(x+1,y+0);
            stack[count++] = iv2(x+0,y+1);
            stack[count++] = iv2(x-1,y+0);
            stack[count++] = iv2(x+0,y-1);
        }
    }

    print_largest_area(1);

    return 0;
}
