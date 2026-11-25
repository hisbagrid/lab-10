#include <stdio.h>
int main(void) {
    FILE *fp;
    char city[5][11], name[11], hottest[11];
    double temp[5], value, highest;
    int i, cityNo;
    long position;
    fp = fopen("temperature.txt", "w");
    if (fp == NULL) {
        printf("Could not create temperature.txt\n");
        return 1;
    }
    for (i = 0; i < 5; i++) {
        printf("Enter city name and temperature: ");
        scanf("%10s %lf", city[i], &temp[i]);
        fprintf(fp, "%-10s %5.1f\n", city[i], temp[i]);
    }
    fclose(fp);
    fp = fopen("temperature.txt", "rb+");
    if (fp == NULL) {
        printf("Could not open temperature.txt\n");
        return 1;
    }
    printf("\nCity number to view (1-5): ");
    scanf("%d", &cityNo);
    if (cityNo >= 1 && cityNo <= 5) {
        position = (cityNo - 1) * 17L;
        fseek(fp, position, SEEK_SET);
        fscanf(fp, "%10s %lf", name, &value);
        printf("%s %.1f\n", name, value);
    } else {
        printf("Invalid city number.\n");
    }
    printf("\nCity number to correct (1-5): ");
    scanf("%d", &cityNo);
    printf("New temperature: ");
    scanf("%lf", &value);
    if (cityNo >= 1 && cityNo <= 5) {
        position = (cityNo - 1) * 17L;
        fseek(fp, position, SEEK_SET);
        fscanf(fp, "%10s %lf", name, &temp[0]);
        fseek(fp, position, SEEK_SET);
        fprintf(fp, "%-10s %5.1f\n", name, value);
        printf("%s updated to %.1f\n", name, value);
    } else {
        printf("Invalid city number.\n");
    }
    rewind(fp);
    for (i = 0; i < 5; i++) {
        fscanf(fp, "%10s %lf", name, &value);
        if (i == 0 || value > highest) {
            highest = value;
            /* Copy the current city name into hottest. */
            snprintf(hottest, sizeof(hottest), "%s", name);
        }
    }
    printf("Hottest city: %s (%.1f)\n", hottest, highest);
    fclose(fp);
    return 0;
}
