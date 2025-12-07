
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>

char input[4096][4096];
char operators[4096];
char operator_line[4096];
int nums[4096][4096];
long long op_nums[4096];
char line[4096];

int main(void) {
    int i, j;

    int row = 0;
    int cols = 0;
    int longest_line = 0;
    while (fgets(line, sizeof(line), stdin)) {
        const char *delims = " \t\r\n";
        char *tok;
        char *c;
        int len, col;

        if (line[0] == '*' || line[0] == '+') {
            strcpy(operator_line, line);
            col = 0;
            tok = strtok(line, delims);
            while (tok) {
                assert(tok[0] == '*' || tok[0] == '+');
                operators[col++] = tok[0];
                tok = strtok(0, delims);
            }
            break;
        }

        len = strlen(line);
        c = line + len-1;
        while (isspace(*c)) {
            *c = 0;
            c--;
            len--;
        }

        if (len > longest_line)
            longest_line = len;

        strcpy(input[row], line);

        c = line;
        while (isspace(*c)) c++;

        col = 0;
        tok = strtok(c, delims);
        while (tok) {
            nums[row][col++] = atoi(tok);
            tok = strtok(0, delims);
        }
        cols = col;

        row++;
    }

    {/* part 1 */
        long long total = 0;
        for (i = 0; i < cols; i++) {
            long long n;
            if (operators[i] == '*') {
                n = 1;
                for (j = 0; j < row; j++) {
                    n *= nums[j][i];
                }
            }
            if (operators[i] == '+') {
                n = 0;
                for (j = 0; j < row; j++) {
                    n += nums[j][i];
                }
            }
            total += n;
        }
        printf("%lld\n", total);
    }

    {/* part 2 */
        long long total = 0;
        int op_num_count = 0;
        for (i = longest_line-1; i >= 0; i--) {
            long long op_num = 0;
            for (j = 0; j < row; j++) {
                int n = (int)input[j][i];
                if (isdigit(n)) {
                    op_num *= 10;
                    op_num += n - '0';
                }
            }
            if (op_num) op_nums[op_num_count++] = op_num;
            if (operator_line[i] == '*') {
                long long prod = 1;
                for (j = 0; j < op_num_count; j++) {
                    prod *= op_nums[j];
                }
                total += prod;
                op_num_count = 0;
            }
            if (operator_line[i] == '+') {
                long long sum = 0;
                for (j = 0; j < op_num_count; j++) {
                    sum += op_nums[j];
                }
                total += sum;
                op_num_count = 0;
            }
        }
        printf("%lld\n", total);
    }

    return 0;
}
