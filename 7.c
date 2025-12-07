
#include <stdio.h>
#include <assert.h>

typedef struct {
    int beams[4096];
    int count;
} Beams;

void add_beam(Beams *b, int n) {
    int i;
    for (i = 0; i < b->count; i++) {
        if (b->beams[i] == n) return;
    }
    b->beams[b->count++] = n;
}

int main(void) {
    static char line[4096];
    Beams beams = {0};
    int split_count;
    int i;
    char *c;

    fgets(line, sizeof(line), stdin);

    for (c = line; *c; c++) {
        if (*c == 'S') {
            beams.beams[beams.count++] = c - line;
        }
    }

    split_count = 0;
    while (fgets(line, sizeof(line), stdin)) {
        Beams b = {0};
        for (i = 0; i < beams.count; i++) {
            int n = beams.beams[i];
            if (line[n] == '^') {
                add_beam(&b, n-1);
                add_beam(&b, n+1);
                split_count++;
            } else {
                add_beam(&b, n);
            }
        }
        beams = b;
    }

    printf("%d\n", split_count);

    return 0;
}
