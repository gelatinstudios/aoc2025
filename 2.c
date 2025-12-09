
#include <stdio.h>
#include <string.h>
#include <stdint.h>

int main(void) {
    const char *delims = ", \r\n";
    char *range;
    int i;
    int64_t part1 = 0;
    int64_t part2 = 0;
    static char input[256*1024];
    fgets(input, sizeof(input), stdin);

    range = strtok(input, delims);
    while (range) {
        int64_t start, end, id;
        sscanf(range, "%lld-%lld", &start, &end);

        for (id = start; id <= end; id++) {
            int64_t a, m;
            int part, id_valid;
            int64_t n = id;
            int digit_count = 0;
            while (n > 0) {
                digit_count++;
                n /= 10;
            }
            id_valid = 1;
            for (part = 2; part < 8; part++) {
                int part_valid = 0;
                if (digit_count % part != 0) continue;
                m = 1;
                for (i = 0; i < digit_count/part; i++)
                    m *= 10;
                a = id % m;
                n = id;
                for (i = 0; i < part; i++) {
                    if (n % m != a) {
                        part_valid = 1;
                        break;
                    }
                    n /= m;
                }
                if (!part_valid) {
                    if (part == 2) part1 += id;
                    id_valid = 0;
                    break;
                }
            }
            if (!id_valid) part2 += id;
        }

        range = strtok(0, delims);
    }

    printf("%lld\n", part1);
    printf("%lld\n", part2);

    return 0;
}
