#include<stdio.h>
#include<stdlib.h>
 struct Student
 {
    int id;
    char name[20];
    float marks;
 };

 void writeRecords(struct Student s[],int n);
 void createSeekArray(long pos[],int n);
 void displayRecord(int recNo, long pos[]);

 int main()
 {
   int i, n, choice;

   printf("Enter number of students:");
   scanf("%d",&n);

   struct Student s[n];

   for(i=0; i<n;i++){
      printf("Enter details of student %d", i+1);

      printf("ID:");
      scanf("%d",&s[i].id);

      printf("Name:");
      scanf("%s",s[i].name);

      printf("Marks:");
      scanf("%f",&s[i].marks);
   }

   writeRecords(s,n);

   long pos[n];

   createSeekArray(pos,n);

   

   printf("Seek Positions:");

   for(int i=0;i<n;i++){
      printf("Record %d - %ld\n",i+1,pos[i]);
   }

   printf("Enter record number to display:");
   scanf("%d",&choice);

   displayRecord(choice, pos); 

return 0;
}

void writeRecords(struct Student s[],int n){

   FILE*fp;
   int i;

   fp=fopen("student.txt", "w");

   if(fp==NULL){
      printf("File cannot be opened\n");
      exit(1);
   }

   for(i=0;i<n;i++)
   {
      fprintf(fp,"%d %s %.2f\n", s[i].id, s[i].name, s[i].marks);
      }
         fclose(fp);
   
}

void createSeekArray(long pos[],int n){
FILE*fp;
int i;

struct Student temp;

fp=fopen("student.txt","r");

if(fp==NULL){
printf("File cannot be opened\n");
exit(1);
}

for(i=0;i<n;i++){
   pos[i]=ftell(fp);

   fscanf(fp, "%d %s %f",&temp.id, temp.name, &temp.marks);

   printf("\nRecord Found:\n");

   printf("ID: %d\n",temp.id);
   printf("Name:%s\n", temp.name);
   printf("Marks:%.2f\n",temp.marks);

}
   fclose(fp);
}
void displayRecord(int recNo, long pos[])
{
    FILE *fp;

    struct Student temp;

    fp = fopen("student.txt", "r");

    if(fp == NULL)
    {
        printf("File cannot be opened\n");
        exit(1);
    }

    fseek(fp, pos[recNo-1], SEEK_SET);

    fscanf(fp, "%d %s %f",
           &temp.id,
           temp.name,
           &temp.marks);

    printf("\nRequired Record:\n");

    printf("ID: %d\n", temp.id);
    printf("Name: %s\n", temp.name);
    printf("Marks: %.2f\n", temp.marks);

    fclose(fp);
}