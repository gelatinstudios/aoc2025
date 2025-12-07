
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int nums[4096][4096];
char line[4096];

int main(void) {
    long long total = 0;
    int row = 0;
    int cols = 0;
    int i;
    while (fgets(line, sizeof(line), stdin)) {
        int col = 0;
        char *tok = strtok(line, " \r\n");
        if (!isdigit(tok[0])) {
            while (tok) {
                if (tok[0] == '*') {
                    long long prod = 1;
                    for (i = 0; i < row; i++) {
                        prod *= nums[col][i];
                    }
                    total += prod;
                }
                if (tok[0] == '+') {
                    long long sum = 0;
                    for (i = 0; i < row; i++) {
                        sum += nums[col][i];
                    }
                    total += sum;
                }
                col++;
                tok = strtok(0, " \r\n");
            }
            break;
        }
        while (tok) {
            int n = atoi(tok);
            nums[col][row] = n;
            col++;
            tok = strtok(0, " \r\n");
        }
        row++;
        if (col > cols) cols = col;
    }

    printf("%lld\n", total);

    return 0;
}
