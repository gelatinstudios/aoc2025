
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <ctype.h>

#define Min(a,b) ((a)<(b)?(a):(b))
#define Max(a,b) ((a)>(b)?(a):(b))

int64_t ranges[4096][2];
int range_count = 0;

int main(void) {
    static char line[4096];
    int64_t fresh_count;
    int collapsing;
    int i, j;

    while (fgets(line, sizeof(line), stdin)) {
        int64_t start, end;

        if (isspace(line[0])) break;

        sscanf(line, "%lld-%lld", &start, &end);

        ranges[range_count][0] = start;
        ranges[range_count][1] = end;
        range_count++;
    }

    fresh_count = 0;
    while (fgets(line, sizeof(line), stdin)) {
        int fresh;
        int64_t n;

        if (isspace(line[0])) break;

        n = atol(line);

        fresh = 0;
        for (i = 0; i < range_count; i++) {
            if (n >= ranges[i][0] && n <= ranges[i][1]) {
                fresh = 1;
                break;
            }
        }
        fresh_count += fresh;
    }

    printf("%lld\n", fresh_count);

    do {
        collapsing = 0;
        for (i = 0; i < range_count; i++) {
            for (j = 0; j < range_count; j++) {
                if (i==j) continue;
                if ((ranges[j][0] <= ranges[i][0] && ranges[i][0] <= ranges[j][1]) ||
                    (ranges[j][0] <= ranges[i][1] && ranges[i][1] <= ranges[j][1]))
                {
                    ranges[i][0] = Min(ranges[i][0], ranges[j][0]);
                    ranges[i][1] = Max(ranges[i][1], ranges[j][1]);

                    ranges[j][0] = ranges[range_count-1][0];
                    ranges[j][1] = ranges[range_count-1][1];

                    range_count--;

                    collapsing = 1;
                    break;
                }
            }
            if (collapsing) break;
        }
    } while (collapsing);

    fresh_count = 0;
    for (i = 0; i < range_count; i++) {
        fresh_count += ranges[i][1] - ranges[i][0] + 1;
    }

    printf("%lld\n", fresh_count);

    return 0;
}
