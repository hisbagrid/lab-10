#include <stdio.h>
int main(void) {
    FILE *fp;
    char category[13];
    double amount, total = 0.0;
    int entryNo, i;
    long position;
    /* The task says this file already contains these four records. */
    fp = fopen("expenses.txt", "w");
    if (fp == NULL) {
        printf("Could not create expenses.txt\n");
        return 1;
    }
    fprintf(fp, "%-12s %9.2f\n", "Food", 1200.00);
    fprintf(fp, "%-12s %9.2f\n", "Transport", 500.00);
    fprintf(fp, "%-12s %9.2f\n", "Books", 850.00);
    fprintf(fp, "%-12s %9.2f\n", "Mobile", 300.00);
    fclose(fp);
    /* Append the new expense. */
    printf("Category: ");
    scanf("%12s", category);
    printf("Amount: ");
    scanf("%lf", &amount);
    fp = fopen("expenses.txt", "ab");
    if (fp == NULL) {
        printf("Could not append to expenses.txt\n");
        return 1;
    }
    fprintf(fp, "%-12s %9.2f\n", category, amount);
    fclose(fp);
    fp = fopen("expenses.txt", "rb+");
    if (fp == NULL) {
        printf("Could not reopen expenses.txt\n");
        return 1;
    }
    /* Read the final two records. */
    fseek(fp, -46L, SEEK_END);
    printf("\nLatest two expenses:\n");
    for (i = 0; i < 2; i++) {
        fscanf(fp, "%12s %lf", category, &amount);
        printf("%s %.2f\n", category, amount);
    }
    /* Correct the amount of a selected entry. */
    printf("\nEntry to fix (1-5): ");
    scanf("%d", &entryNo);
    printf("Correct amount: ");
    scanf("%lf", &amount);
    if (entryNo >= 1 && entryNo <= 5) {
        position = (entryNo - 1) * 23L;
        fseek(fp, position, SEEK_SET);
        fscanf(fp, "%12s %lf", category, &total);
        fseek(fp, position, SEEK_SET);
        fprintf(fp, "%-12s %9.2f\n", category, amount);
    } else {
        printf("Invalid entry number.\n");
    }
    /* Print all records and calculate the total. */
    rewind(fp);
    total = 0.0;
    printf("\nAll expenses:\n");
    while (fscanf(fp, "%12s %lf", category, &amount) == 2) {
        printf("%s %.2f\n", category, amount);
        total += amount;
    }
    printf("Total: %.2f\n", total);
    fclose(fp);
    return 0;
}
