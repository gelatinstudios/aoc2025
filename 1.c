
#include <stdio.h>

int main(void) {
    int dial = 50;
    int zero_count = 0;

    static char line[4096];
    while (fgets(line, sizeof(line), stdin)) {
        char dir;
        int n;
        sscanf(line, "%c%d", &dir, &n);
        if (dir == 'L') n = -n;
        dial = (dial + n + 100) % 100;
        zero_count += (dial == 0);
    }
    printf("%d\n", zero_count);

    return 0;
}
