
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int x, y;
} IV2;

IV2 tiles[512];
int tile_count = 0;

int main(void) {
    int64_t largest_area;
    int i, j;

    int x, y;
    while (scanf("%d,%d ", &x, &y) > 0) {
        IV2 v;
        v.x = x;
        v.y = y;
        tiles[tile_count++] = v;
    }

    largest_area = 0;
    for (i = 0; i < tile_count; i++) {
        IV2 a = tiles[i];
        for (j = i+1; j < tile_count; j++) {
            IV2 b = tiles[j];
            int64_t area = (int64_t)abs(a.x - b.x + 1) * (int64_t)abs(a.y - b.y + 1);
            if (area > largest_area) {
                largest_area = area;
            }
        }
    }

    printf("%ld\n", largest_area);

    return 0;
}
