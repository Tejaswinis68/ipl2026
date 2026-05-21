#include <stdio.h>
#include <stdlib.h>

struct Student
{
    int roll;
    char name[30];
    float marks;
};

/* Function to display a record */
void display(struct Student s)
{
    printf("\nRoll No : %d", s.roll);
    printf("\nName    : %s", s.name);
    printf("\nMarks   : %.2f\n", s.marks);
}

/* Function to get mth record using fseek */
void getRecord(int m)
{
    FILE *fp;
    struct Student s;

    fp = fopen("student.dat", "rb");

    if (fp == NULL)
    {
        printf("File cannot be opened\n");
        return;
    }

    /* Move file pointer to mth record */
    fseek(fp, (m - 1) * sizeof(struct Student), SEEK_SET);

    if (fread(&s, sizeof(struct Student), 1, fp) == 1)
    {
        printf("\n%dth Record:\n", m);
        display(s);
    }
    else
    {
        printf("\nRecord not found\n");
    }

    fclose(fp);
}

/* Function to delete a record */
void deleteRecord(int delRoll)
{
    FILE *fp, *temp;
    struct Student s;
    int found = 0;

    fp = fopen("student.dat", "rb");
    temp = fopen("temp.dat", "wb");

    if (fp == NULL || temp == NULL)
    {
        printf("Error opening file\n");
        return;
    }

    /* Copy all records except the one to delete */
    while (fread(&s, sizeof(struct Student), 1, fp))
    {
        if (s.roll != delRoll)
        {
            fwrite(&s, sizeof(struct Student), 1, temp);
        }
        else
        {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    /* Replace original file with temp file */
    remove("student.dat");
    rename("temp.dat", "student.dat");

    if (found)
        printf("\nRecord deleted successfully\n");
    else
        printf("\nRecord not found\n");
}

/* Function to display all records */
void displayAll()
{
    FILE *fp;
    struct Student s;

    fp = fopen("student.dat", "rb");

    if (fp == NULL)
    {
        printf("File cannot be opened\n");
        return;
    }

    printf("\nAll Records:\n");

    while (fread(&s, sizeof(struct Student), 1, fp))
    {
        display(s);
    }

    fclose(fp);
}

int main()
{
    FILE *fp;
    struct Student s;
    int n, i, m, delRoll;

    fp = fopen("student.dat", "wb");

    if (fp == NULL)
    {
        printf("File cannot be created\n");
        return 1;
    }

    printf("Enter number of records: ");
    scanf("%d", &n);

    /* Store records */
    for (i = 0; i < n; i++)
    {
        printf("\nEnter details of student %d\n", i + 1);

        printf("Roll No: ");
        scanf("%d", &s.roll);

        printf("Name: ");
        scanf("%s", s.name);

        printf("Marks: ");
        scanf("%f", &s.marks);

        fwrite(&s, sizeof(struct Student), 1, fp);
    }

    fclose(fp);

    /* Display all records */
    displayAll();

    /* Get mth record */
    printf("\nEnter record number to fetch: ");
    scanf("%d", &m);

    getRecord(m);

    /* Delete a record */
    printf("\nEnter roll number to delete: ");
    scanf("%d", &delRoll);

    deleteRecord(delRoll);

    /* Display remaining records */
    printf("\nRecords after deletion:\n");
    displayAll();

    return 0;
}