#include <stdio.h>
#include <string.h>
int main(void) {
    FILE *fp;
    int i, roomNo, nights, storedRoom, storedNights;
    int rooms[10];
    char status, guest[21], guests[10][21], searchName[21];
    double rate, bill;
    long position;
    fp = fopen("hotel.txt", "w");
    if (fp == NULL) {
        printf("Could not create hotel.txt\n");
        return 1;
    }
    for (i = 0; i < 10; i++)
        fprintf(fp, "%3d %c %-20s %2d %8.2f\n",
                101 + i, 'F', "-", 0, 8000.00);
    fclose(fp);
    fp = fopen("hotel.txt", "rb+");
    if (fp == NULL) {
        printf("Could not open hotel.txt\n");
        return 1;
    }
    /* Check-in */
    printf("Check-in room (101-110): ");
    scanf("%d", &roomNo);
    printf("Guest name: ");
    scanf("%20s", guest);
    printf("Nights: ");
    scanf("%d", &nights);
    if (roomNo >= 101 && roomNo <= 110 && nights > 0) {
        position = (roomNo - 101) * 39L;
        fseek(fp, position, SEEK_SET);
        fscanf(fp, "%d %c %20s %d %lf",
               &storedRoom, &status, guests[0], &storedNights, &rate);
        if (status == 'F') {
            fseek(fp, position, SEEK_SET);
            fprintf(fp, "%3d %c %-20s %2d %8.2f\n",
                    roomNo, 'B', guest, nights, 8000.00);
            printf("Room %d booked\n", roomNo);
        } else {
            printf("Room already booked.\n");
        }
    } else {
        printf("Invalid room number or nights.\n");
    }
    /* Load guest names and room numbers for searching. */
    rewind(fp);
    for (i = 0; i < 10; i++) {
        fscanf(fp, "%d %c %20s %d %lf",
               &rooms[i], &status, guests[i], &storedNights, &rate);
    }
    printf("\nSearch name: ");
    scanf("%20s", searchName);
    for (i = 0; i < 10; i++) {
        if (strcmp(guests[i], searchName) == 0) {
            printf("%s is in room %d\n", searchName, rooms[i]);
            break;
        }
    }
    if (i == 10)
        printf("Guest not found.\n");
    /* Check-out */
    printf("\nCheck-out room (101-110): ");
    scanf("%d", &roomNo);
    if (roomNo >= 101 && roomNo <= 110) {
        position = (roomNo - 101) * 39L;
        fseek(fp, position, SEEK_SET);
        fscanf(fp, "%d %c %20s %d %lf",
               &storedRoom, &status, guest, &nights, &rate);
        if (status == 'B') {
            bill = nights * rate;
            printf("Bill: %d x %.2f = %.2f\n", nights, rate, bill);
            fseek(fp, position, SEEK_SET);
            fprintf(fp, "%3d %c %-20s %2d %8.2f\n",
                    roomNo, 'F', "-", 0, 8000.00);
        } else {
            printf("This room is already free.\n");
        }
    } else {
        printf("Invalid room number.\n");
    }
    fclose(fp);
    return 0;
}
