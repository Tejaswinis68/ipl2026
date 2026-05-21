#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char name[30];
    int age;
} Record;

void writeRecords(const char *filename, int n) {
    FILE *fp = fopen(filename, "wb");
    if (!fp) {
        perror("Unable to open file for writing");
        return;
    }

    for (int i = 0; i < n; i++) {
        Record rec;
        printf("Enter record %d ID: ", i + 1);
        scanf("%d", &rec.id);
        getchar();
        printf("Enter record %d name: ", i + 1);
        fgets(rec.name, sizeof(rec.name), stdin);
        rec.name[strcspn(rec.name, "\n")] = '\0';
        printf("Enter record %d age: ", i + 1);
        scanf("%d", &rec.age);
        getchar();

        fwrite(&rec, sizeof(Record), 1, fp);
    }

    fclose(fp);
    printf("%d records written to %s\n", n, filename);
}

void displayRecord(const char *filename, int m) {
    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        perror("Unable to open file for reading");
        return;
    }

    if (m < 1) {
        printf("Record number must be 1 or greater.\n");
        fclose(fp);
        return;
    }

    long offset = (long)(m - 1) * sizeof(Record);
    if (fseek(fp, offset, SEEK_SET) != 0) {
        perror("fseek failed");
        fclose(fp);
        return;
    }

    Record rec;
    if (fread(&rec, sizeof(Record), 1, fp) != 1) {
        printf("Record %d does not exist.\n", m);
    } else {
        printf("Record %d:\n", m);
        printf("  ID: %d\n", rec.id);
        printf("  Name: %s\n", rec.name);
        printf("  Age: %d\n", rec.age);
    }

    fclose(fp);
}

void displayAllRecords(const char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        perror("Unable to open file for reading");
        return;
    }

    Record rec;
    int index = 1;
    while (fread(&rec, sizeof(Record), 1, fp) == 1) {
        printf("Record %d:\n", index);
        printf("  ID: %d\n", rec.id);
        printf("  Name: %s\n", rec.name);
        printf("  Age: %d\n", rec.age);
        index++;
    }

    if (index == 1) {
        printf("No records found in %s.\n", filename);
    }

    fclose(fp);
}

void deleteRecord(const char *filename, int m) {
    if (m < 1) {
        printf("Record number must be 1 or greater.\n");
        return;
    }

    FILE *src = fopen(filename, "rb");
    if (!src) {
        perror("Unable to open file for reading");
        return;
    }

    FILE *tmp = fopen("temp.dat", "wb");
    if (!tmp) {
        perror("Unable to open temporary file");
        fclose(src);
        return;
    }

    Record rec;
    int index = 1;
    int deleted = 0;
    while (fread(&rec, sizeof(Record), 1, src) == 1) {
        if (index == m) {
            deleted = 1;
        } else {
            fwrite(&rec, sizeof(Record), 1, tmp);
        }
        index++;
    }

    fclose(src);
    fclose(tmp);

    if (!deleted) {
        printf("Record %d does not exist. No deletion performed.\n", m);
        remove("temp.dat");
        return;
    }

    if (remove(filename) != 0) {
        perror("Unable to remove original file");
        remove("temp.dat");
        return;
    }

    if (rename("temp.dat", filename) != 0) {
        perror("Unable to rename temporary file");
        return;
    }

    printf("Record %d deleted successfully.\n", m);
}

int main(void) {
    const char *filename = "records.dat";
    int choice;

    do {
        printf("\nBinary Record Manager\n");
        printf("1. Create records\n");
        printf("2. Display all records\n");
        printf("3. Get m-th record\n");
        printf("4. Delete record\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1: {
                int n;
                printf("Enter number of records to store: ");
                scanf("%d", &n);
                getchar();
                if (n > 0) {
                    writeRecords(filename, n);
                } else {
                    printf("Invalid number of records.\n");
                }
                break;
            }
            case 2:
                displayAllRecords(filename);
                break;
            case 3: {
                int m;
                printf("Enter record number to read: ");
                scanf("%d", &m);
                getchar();
                displayRecord(filename, m);
                break;
            }
            case 4: {
                int m;
                printf("Enter record number to delete: ");
                scanf("%d", &m);
                getchar();
                deleteRecord(filename, m);
                break;
            }
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}
