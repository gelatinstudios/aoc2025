
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int dial = 50;
    int zero_count1 = 0;
    int zero_count2 = 0;

    char dir;
    int n;
    while (scanf("%c%d ", &dir, &n) > 0) {
        int m = n % 100;
        if (dial != 0) {
            if (dir=='R') {
                zero_count2 += (dial + m >= 100);
            } else {
                zero_count2 += (dial - m <= 0);
            }
        }
        zero_count2 += n/100;
        if (dir == 'L') m = -m;
        dial = (dial + m + 100) % 100;
        zero_count1 += (dial==0);
    }
    printf("%d\n", zero_count1);
    printf("%d\n", zero_count2);

    return 0;
}
