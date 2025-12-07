
#include <stdio.h>
#include <assert.h>

typedef struct {
    int pos;
    long long timelines;
} Beam;

typedef struct {
    Beam beams[4096];
    int count;
} Beams;

void add_beam(Beams *b, int pos, long long timelines) {
    int i;
    for (i = 0; i < b->count; i++) {
        if (b->beams[i].pos == pos) {
            b->beams[i].timelines += timelines;
            return;
        }
    }
    b->beams[b->count].pos = pos;
    b->beams[b->count].timelines = timelines;
    b->count++;
}

int main(void) {
    static char line[4096];
    Beams beams = {0};
    int split_count;
    long long timelines;
    int i;
    char *c;

    fgets(line, sizeof(line), stdin);

    for (c = line; *c; c++) {
        if (*c == 'S') {
            add_beam(&beams, c - line, 1);
        }
    }

    split_count = 0;
    while (fgets(line, sizeof(line), stdin)) {
        Beams b = {0};
        for (i = 0; i < beams.count; i++) {
            Beam beam = beams.beams[i];
            int n = beam.pos;
            long long t = beam.timelines;
            if (line[n] == '^') {
                add_beam(&b, n-1, t);
                add_beam(&b, n+1, t);
                split_count++;
            } else {
                add_beam(&b, n, t);
            }
        }
        beams = b;
    }

    printf("%d\n", split_count);

    timelines = 0;
    for (i = 0; i < beams.count; i++) {
        timelines += beams.beams[i].timelines;
    }

    printf("%lld\n", timelines);

    return 0;
}
