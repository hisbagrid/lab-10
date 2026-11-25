#include <stdio.h>
int main(void) {
    FILE *fp;
    int roll, attended, leaveLectures, lastRoll, lastAttended;
    char name[16], lastName[16];
    double percentage;
    long position;
    fp = fopen("attendance.txt", "w");
    if (fp == NULL) {
        printf("Could not create attendance.txt\n");
        return 1;
    }
    fprintf(fp, "%-3d %-15s %3d\n", 1, "Ayesha", 18);
    fprintf(fp, "%-3d %-15s %3d\n", 2, "Bilal", 14);
    fprintf(fp, "%-3d %-15s %3d\n", 3, "Hamza", 20);
    fprintf(fp, "%-3d %-15s %3d\n", 4, "Sana", 12);
    fprintf(fp, "%-3d %-15s %3d\n", 5, "Zainab", 16);
    fclose(fp);
    fp = fopen("attendance.txt", "rb+");
    if (fp == NULL) {
        printf("Could not open attendance.txt\n");
        return 1;
    }
    printf("Roll number to check: ");
    scanf("%d", &roll);
    if (roll < 1 || roll > 5) {
        printf("Invalid roll number.\n");
    } else {
        position = (roll - 1) * 24L;
        fseek(fp, position, SEEK_SET);
        fscanf(fp, "%d %15s %d", &roll, name, &attended);
        percentage = attended * 100.0 / 20;
        printf("%s: %d / 20 (%.1f%%)", name, attended, percentage);
        if (percentage < 75.0)
            printf(" Short attendance");
        printf("\n");
    }
    printf("\nRoll number for leave: ");
    scanf("%d", &roll);
    printf("Lectures to add: ");
    scanf("%d", &leaveLectures);
    if (roll >= 1 && roll <= 5 && leaveLectures >= 0) {
        position = (roll - 1) * 24L;
        fseek(fp, position, SEEK_SET);
        fscanf(fp, "%d %15s %d", &roll, name, &attended);
        attended += leaveLectures;
        if (attended > 20)
            attended = 20;
        fseek(fp, position, SEEK_SET);
        fprintf(fp, "%-3d %-15s %3d\n", roll, name, attended);
        printf("%s: now %d / 20 (%.1f%%)\n",
               name, attended, attended * 100.0 / 20);
    } else {
        printf("Invalid roll number or lecture count.\n");
    }
    fseek(fp, -24L, SEEK_END);
    fscanf(fp, "%d %15s %d", &lastRoll, lastName, &lastAttended);
    printf("Last record: %d %s %d\n",
           lastRoll, lastName, lastAttended);
    fclose(fp);
    return 0;
}
