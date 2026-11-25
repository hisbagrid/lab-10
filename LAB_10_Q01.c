#include <stdio.h>
int main(void) {
    FILE *fp;
    int itemNo, quantity, stock;
    char name[21];
    double price, amount, total = 0.0;
    long position;
    /* Create the file and write the initial stock. */
    fp = fopen("items.txt", "w");
    if (fp == NULL) {
        printf("Could not create items.txt\n");
        return 1;
    }
    fprintf(fp, "%-4d %-20s %9.2f %5d\n", 1, "Rice", 250.00, 40);
    fprintf(fp, "%-4d %-20s %9.2f %5d\n", 2, "Sugar", 160.00, 25);
    fprintf(fp, "%-4d %-20s %9.2f %5d\n", 3, "Milk", 220.00, 30);
    fprintf(fp, "%-4d %-20s %9.2f %5d\n", 4, "CookingOil", 560.00, 12);
    fprintf(fp, "%-4d %-20s %9.2f %5d\n", 5, "Tea", 450.00, 18);
    fclose(fp);
    fp = fopen("items.txt", "rb+");
    if (fp == NULL) {
        printf("Could not open items.txt\n");
        return 1;
    }
    while (1) {
        printf("\nItem no (0 to finish): ");
        scanf("%d", &itemNo);
        if (itemNo == 0)
            break;
        if (itemNo < 1 || itemNo > 5) {
            printf("Invalid item number.\n");
            continue;
        }
        printf("Quantity: ");
        scanf("%d", &quantity);
        if (quantity <= 0) {
            printf("Enter a positive quantity.\n");
            continue;
        }
        position = (itemNo - 1) * 42L;
        fseek(fp, position, SEEK_SET);
        fscanf(fp, "%d %20s %lf %d", &itemNo, name, &price, &stock);
        if (quantity <= stock) {
            amount = quantity * price;
            printf("%s  %d x %.2f = %.2f\n",
                   name, quantity, price, amount);
            total += amount;
            stock -= quantity;
            /* Move back to the start of this record before writing. */
            fseek(fp, position, SEEK_SET);
            fprintf(fp, "%-4d %-20s %9.2f %5d\n",
                    itemNo, name, price, stock);
        } else {
            printf("Only %d %s in stock.\n", stock, name);
        }
    }
    printf("\nTotal bill: %.2f\n", total);
    fclose(fp);
    return 0;
}
