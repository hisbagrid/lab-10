#include <stdio.h>
int markZone(char map[][5], int r, int c, char label) {
    if (r < 0 || r >= 5 || c < 0 || c >= 5)
        return 0;
    if (map[r][c] != '*')
        return 0;
    map[r][c] = label;
    return 1
        + markZone(map, r - 1, c, label)
        + markZone(map, r + 1, c, label)
        + markZone(map, r, c - 1, label)
        + markZone(map, r, c + 1, label);
}
int main(void) {
    float temp[5][5] = {
        { 2.1, -1.5, -2.0,  3.0,  4.2},
        { 1.8, -0.5,  2.5,  3.1, -1.0},
        { 3.3,  2.0,  1.5, -0.8, -2.0},
        {-1.2,  3.4,  4.0,  3.8, -0.6},
        {-2.5, -3.1,  5.1,  6.0,  4.7}
    };
    char map[5][5];
    int r, c, size, zones = 0;
    /* Convert the temperature grid into the frost map. */
    for (r = 0; r < 5; r++) {
        for (c = 0; c < 5; c++) {
            if (temp[r][c] < 0)
                map[r][c] = '*';
            else
                map[r][c] = '.';
        }
    }
    /* Each unmarked frost station starts a new zone. */
    for (r = 0; r < 5; r++) {
        for (c = 0; c < 5; c++) {
            if (map[r][c] == '*') {
                zones++;
                size = markZone(map, r, c, 'A' + zones - 1);
                printf("Zone %c: %d stations\n", 'A' + zones - 1, size);
            }
        }
    }
    printf("Total zones: %d\n", zones);
    for (r = 0; r < 5; r++) {
        for (c = 0; c < 5; c++)
            printf("%c ", map[r][c]);
        printf("\n");
    }
    return 0;
}
