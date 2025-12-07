
#include <stdio.h>
#include <string.h>

int main(void) {
    const char *delims = ", \r\n";
    char *range;
    int i;
    long long part1 = 0;
    static char input[256*1024];
    fgets(input, sizeof(input), stdin);

    range = strtok(input, delims);
    while (range) {
        long long start, end, id;
        sscanf(range, "%lld-%lld", &start, &end);

        for (id = start; id <= end; id++) {
            long long n = id;
            long long a, b, m;
            int digit_count = 0;
            while (n > 0) {
                digit_count++;
                n /= 10;
            }
            if (digit_count % 2 != 0) continue;
            m = 1;
            for (i = 0; i < digit_count/2; i++)
                m *= 10;
            a = id / m;
            b = id % m;
            if (a == b) {
                part1 += id;
            }
        }

        range = strtok(0, delims);
    }

    printf("%lld\n", part1);


    return 0;
}
