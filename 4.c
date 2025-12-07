
#include <stdio.h>
#include <string.h>
#include <ctype.h>

char line[4096];
char grid[4096][4096];
char grid_copy[4096][4096];

int main(void) {
    int x, y, dx, dy;
    int removed, total_removed;

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

    total_removed = 0;
    do {
        removed = 0;
        for (y = 0; y < h; y++) {
            for (x = 0; x < w; x++) {
                int rolls;

                grid_copy[y][x] = grid[y][x];

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

                if (rolls < 5) {
                    removed++;
                    grid_copy[y][x] = '.';
                }
            }
        }
        if (!total_removed) printf("%d\n", removed); /* part 1 */
        total_removed += removed;
        memcpy(grid, grid_copy, sizeof(grid));
    } while (removed > 0);

    /* part 2 */
    printf("%d\n", total_removed);

    return 0;
}
