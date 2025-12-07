
#include <stdio.h>
#include <ctype.h>

char line[4096];
char grid[4096][4096];

int main(void) {
    int x, y, dx, dy;
    int part1;

    int w = 0;
    int h = 0;

    while (fgets(line, sizeof(line), stdin)) {
        if (isspace(line[0])) break;
        if (w==0) {
            char *c;
            for (c = line; !isspace(*c); c++) {
                w++;
            }
        }
        for (x = 0; x < w; x++) {
            grid[h][x] = line[x];
        }
        h++;
    }

    part1 = 0;
    for (y = 0; y < h; y++) {
        for (x = 0; x < w; x++) {
            int rolls;
            if (grid[y][x] != '@') continue;

            rolls = 0;
            for (dy = -1; dy <= 1; dy++) {
                for (dx = -1; dx <= 1; dx++) {
                    int nx = x + dx;
                    int ny = y + dy;
                    if (nx < 0 || nx >= w) continue;
                    if (ny < 0 || ny >= h) continue;
                    rolls += (grid[ny][nx] == '@');
                }
            }

            part1 += (rolls < 5);
        }
    }

    printf("%d\n", part1);

    return 0;
}
