
#include <stdio.h>
#include <ctype.h>

int main(void) {
    int i;
    static char line[1024];
    int total_joltage = 0;
    while (fgets(line, sizeof(line), stdin)) {
        char *c;
        int a, a_index, b, joltage;

        int len = 0;
        for (c = line; isdigit(*c); c++) {
            len++;
        }

        a = 0;
        for (i = 0; i < len-1; i++) {
            if (line[i] > a) {
                a = line[i];
                a_index = i;
            }
        }

        b = 0;
        for (i = a_index+1; i < len; i++) {
            if (line[i] > b) {
                b = line[i];
            }
        }

        joltage = (a-'0')*10 + (b-'0');

        total_joltage += joltage;
    }

    printf("%d\n", total_joltage);

    return 0;
}
