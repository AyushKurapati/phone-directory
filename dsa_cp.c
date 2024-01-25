#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <conio.h>

#define FILENAME_SIZE 1024
#define MAX_LINE 2048

struct Node
{
    char fname[30];
    struct Node *next;
};

struct Node *head;
FILE *fp, *fp1;

void print(struct Node *p)
{
    printf("\n");
    while (p->next != NULL)
    {
        puts(p->fname);
        p = p->next;
    }
    printf("\n");
}

struct Node *initializeContacts()
{
    struct Node *p, *head;
    char buf[4096];
    head = (struct Node *)malloc(sizeof(struct Node));
    fp = fopen("Contacts.txt", "a+");
    p = head;
    while (fgets(buf, sizeof(buf), fp) == buf)
    {
        p->next = (struct Node *)malloc(sizeof(struct Node));
        strcpy(p->fname, buf);
        fgets(buf, sizeof(buf), fp);
        fgets(buf, sizeof(buf), fp);

        p = p->next;
    }
    p->next = NULL;
    fclose(fp);
    return head;
}

void printdelContacts()
{

    FILE *temp1 = fopen("Bin.txt", "r");
    char buf[4096];
    printf("\n");
    while (fgets(buf, sizeof(buf), temp1))
    {
        int ln = strlen(buf) - 1;
        if (buf[ln] == '\n')
            buf[ln] = '\0';

        printf("Name: %s\n", buf);
        fgets(buf, sizeof(buf), temp1);
        int ln1 = strlen(buf) - 1;
        if (buf[ln1] == '\n')
            buf[ln1] = '\0';
        printf("Number : %s\n", buf);
        fgets(buf, sizeof(buf), temp1);
        printf("Gmail : %s\n", buf);
        printf("\n");
    }
    fclose(temp1);
}

struct Node *newUserContact(struct Node *head)
{
    struct Node *temp = head;
    struct Node *next1 = (struct Node *)malloc(sizeof(struct Node));
    next1->next = NULL;
    if (temp == NULL)
    {
        printf("Unable to allocate memory!!");
    }
    else
    {
        char buf[30];
        char buf1[30];
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = next1;

        fp = fopen("Contacts.txt", "a+");
        printf("Name :- ");
        gets(next1->fname);
        fprintf(fp, "%s\n", next1->fname);
        char man[30] = "+91 ";
        bool read = true;
        while (read)
        {
            printf("\nNumber :- ");
            gets(buf);
            if (strlen(buf) != 10)
            {
                printf("\nEnter a Valid Number\n");
            }
            else
            {
                strcat(man, buf);
                read = false;
            }
        }
        fprintf(fp, "%s\n", man);

        printf("\nGmail :- ");
        gets(buf1);

        fprintf(fp, "%s\n", buf1);
        fclose(fp);
    }
    printf("\nContact Added Successfully\n");

    return head;
}

void updateNumber(struct Node *ptr, char fname1[30], char number1[30])
{
    int counter = 0;
    fp = fopen("Contacts.txt", "r+");
    char buf[4096];
    while (fgets(buf, sizeof(buf), fp))
    {
        int ln = strlen(buf) - 1;
        if (buf[ln] == '\n')
            buf[ln] = '\0';

        if (!strcmp(buf, fname1))
        {
            // printf("Name: %s\n", buf);
            counter++;
            break;
        }
        counter++;
    }
    counter++;
    fclose(fp);

    char filename[FILENAME_SIZE] = "Contacts.txt";
    char temp_filename[FILENAME_SIZE];

    char delete_line[MAX_LINE];
    char buffer[MAX_LINE];

    FILE *file, *temp;
    int z = 0;
    char buf2[4096];
    strcpy(temp_filename, "temp__");
    strcat(temp_filename, filename); // temp__Contacts

    file = fopen(filename, "r");
    temp = fopen(temp_filename, "w");
    while (!feof(file))
    {
        strcpy(buf2, "\0");
        fgets(buf2, sizeof(buf2), file);
        if (!feof(file))
        {
            z++;
            if (z != counter)
            {
                fprintf(temp, "%s", buf2);
            }
            else
            {
                fprintf(temp, "%s\n", number1);
            }
        }
    }
    fclose(file);
    fclose(temp);
    remove(filename);
    rename(temp_filename, filename);
    bool keep_reading = true;
    file = fopen(filename, "w");
    temp = fopen(temp_filename, "r");
    while (keep_reading)
    {
        char buf[MAX_LINE];
        fgets(buf, MAX_LINE, temp);
        if (feof(temp))
            keep_reading = false;
        else
        {

            fprintf(file, "%s", buf);
        }
    }
    fclose(file);
    fclose(temp);
    printf("\nContact Updated Successfully\n");
}

void searchByName(struct Node *ptr, char fname1[30])
{
    printf("\n");
    int counter = 0;
    fp = fopen("Contacts.txt", "r+");
    char buf[4096];
    while (fgets(buf, sizeof(buf), fp))
    {
        int ln = strlen(buf) - 1;
        if (buf[ln] == '\n')
            buf[ln] = '\0';

        if (!strcmp(buf, fname1))
        {
            printf("Name: %s\n", buf);
            fgets(buf, sizeof(buf), fp);
            int ln = strlen(buf) - 1;
            if (buf[ln] == '\n')
                buf[ln] = '\0';
            printf("Number : %s\n", buf);
            fgets(buf, sizeof(buf), fp);
            printf("Gmail : %s\n", buf);
            counter = 1;
            break;
        }
    }
    if (counter == 0)
    {
        printf("\nContact Not found\n");
    }
    printf("\n");
    fclose(fp);
}

void deleteNode()
{

    char filename[FILENAME_SIZE] = "Contacts.txt";
    char temp_filename[FILENAME_SIZE];

    char delete_line[MAX_LINE];
    char buffer[MAX_LINE];

    FILE *file, *temp, *bin;

    strcpy(temp_filename, "temp__");
    strcat(temp_filename, filename); // temp__Contacts

    printf("Delete Name: ");
    fgets(delete_line, MAX_LINE, stdin);

    file = fopen(filename, "r");
    temp = fopen(temp_filename, "w");
    bin = fopen("Bin.txt", "a");

    if (file == NULL || temp == NULL)
    {
        printf("Error opening file(s).\n");
    }

    bool keep_reading = true;
    do
    {
        fgets(buffer, MAX_LINE, file);
        if (feof(file))
            keep_reading = false;
        else if (strcmp(buffer, delete_line) == 0)
        {
            fputs(buffer, bin);
            fgets(buffer, MAX_LINE, file);
            fputs(buffer, bin);
            fgets(buffer, MAX_LINE, file);
            fputs(buffer, bin);
        }
        else if (strcmp(buffer, delete_line) != 0)
            fputs(buffer, temp);

    } while (keep_reading);

    keep_reading = false;
    fclose(file);
    fclose(temp);
    fclose(bin);
    remove(filename);
    rename(temp_filename, filename);

    keep_reading = true;
    file = fopen(filename, "w");
    temp = fopen(temp_filename, "r");
    while (keep_reading)
    {
        char buf[MAX_LINE];
        fgets(buf, MAX_LINE, temp);
        if (feof(temp))
            keep_reading = false;
        else
        {

            fprintf(file, "%s", buf);
        }
    }
    fclose(file);
    fclose(temp);
    fclose(bin);
    printf("\nContact Deleted Successfully\n");
}

int main()
{
    printf("\n\n");
    printf("======================================================");
    printf("\n=======           Phone-Book Directory         =======");
    printf("\n======================================================");
    fp = fopen("Contacts.txt", "a+");
    fp1 = fopen("Bin.txt", "a+");
    head = (struct Node *)malloc(sizeof(struct Node));
    char buf1[30];
    int ch = 0;
    char temp;
    char fname1[30], number1[30];
    head = initializeContacts();

    while (ch != 7)
    {
        printf("\n\n\t1. Add a New Contact\n\t2. Search Contact\n\t3. Delete any Contact by Name\n\t4. Update a Contact By Name\n\t5. Display All Contacts\n\t6. Display Deleted Contacts\n\t7. Exit\n\nWhat would you like to do - ");
        scanf("%d", &ch);
        scanf("%c", &temp);
        switch (ch)
        {
        case 1:
            printf("\n");
            fclose(fp);
            head = newUserContact(head);
            printf("\n");
            break;
        case 2:
            printf("\n");
            printf("Enter Name for search: - ");
            gets(buf1);
            searchByName(head, buf1);
            break;
        case 3:
            printf("\n");
            deleteNode();
            head = initializeContacts();
            printf("\n");
            break;
        case 4:
            printf("\n");
            char buf[30];
            printf("Enter Contact Name where Number to be Updated: - ");
            gets(fname1);
            printf("Old Contact - ");
            searchByName(head, fname1);
            printf("\n");
            char man[30] = "+91 ";
            bool read = true;
            while (read)
            {
                printf("New Number to be Updated: - ");
                gets(number1);
                if (strlen(number1) != 10)
                {
                    printf("\nEnter a Valid Number!\n");
                }
                else
                {
                    strcat(man, number1);
                    read = false;
                }
            }
            updateNumber(head, fname1, man);
            printf("\n");
            break;
        case 5:
            printf("\nContacts Available: - \n");
            head = initializeContacts();
            print(head);
            fclose(fp);
            printf("\n");
            break;
        case 6:
            printdelContacts();
            printf("\n");
            break;
        case 7:
            printf("\t======================================================");
            printf("\n\t  THANK YOU FOR USING THE PhoneBook Directory!!!");
            printf("\n\t\tCreated By: Group CSB - SY-26, VIT");
            printf("\n\t\t      Have a nice day!\n");
            printf("\t======================================================");
            fclose(fp);
            fclose(fp1);
            exit(0);
        }
    }

    return 0;
}