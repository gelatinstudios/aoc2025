
#include <stdio.h>
#include <ctype.h>

int main(void) {
    long long joltages[2] = {0};
    static char line[1024];
    int part, i;

    while (fgets(line, sizeof(line), stdin)) {
        for (part = 0; part < 2; part++) {
            char *c;
            int last_index;
            int digit, digits;
            long long joltage, mul;

            int len = 0;
            for (c = line; isdigit(*c); c++) {
                len++;
            }

            if (part == 0) digits = 2;
            else           digits = 12;

            mul = 1;
            for (i = 0; i < digits-1; i++) {
                mul *= 10;
            }

            joltage = 0;
            last_index = -1;
            for (digit = 0; digit < digits; digit++) {
                int end = len - (digits - (digit+1));
                int n = 0;
                for (i = last_index+1; i < end; i++) {
                    if (line[i] > n) {
                        n = line[i];
                        last_index = i;
                    }
                }
                joltage += (long long)(n-'0') * mul;
                mul /= 10;
            }

            joltages[part] += joltage;
        }
    }

    printf("%lld\n", joltages[0]);
    printf("%lld\n", joltages[1]);

    return 0;
}
