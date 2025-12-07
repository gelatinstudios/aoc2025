
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

long long ranges[4096][2];
int range_count = 0;

int main(void) {
    long long fresh_count;
    static char line[4096];

    while (fgets(line, sizeof(line), stdin)) {
        long long start, end;

        if (isspace(line[0])) break;

        sscanf(line, "%lld-%lld", &start, &end);

        ranges[range_count][0] = start;
        ranges[range_count][1] = end;
        range_count++;
    }

    fresh_count = 0;
    while (fgets(line, sizeof(line), stdin)) {
        int fresh, i;
        long long n;

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

    return 0;
}
