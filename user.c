#include <stdio.h>
#include "menu.h"
#include "user.h"
#include "librarian.h"
#include "book_management.h"

struct users us;
struct users *users = &us;
char current_user[100];
char root_name[100] = "librarian";
char root_passwd[100] = "librarian";
Book *book;
BookList *books;

void read_users()
{
    FILE *fp;
    fp = fopen("users.txt", "r");
    if (fp == NULL)
    {
        exit(0);
    }
    /*
    char ch;
    ch = fgetc(fp);
    while(!feof(fp)){
        putchar(ch);
        ch = fgetc(fp);
    }
    */

    users->top = -1;
    int i;
    for (i = 0; !feof(fp); i++)
    {
        fscanf(fp, "%s %s %d", users->us[i].account, users->us[i].passwd, &users->us[i].borrow_number);
        for (int j = 0; j < users->us[i].borrow_number; j++)
        {
            fscanf(fp, "%d", &users->us[i].borrow_book[j]);
        }
    }
    users->top = i - 1;

    fclose(fp);
    //getchar();
}

void Register(){
    char username[100];
    char passwd[100];

    printf("Please enter a username: ");
    scanf("%s", username);
    printf("Please enter a password: ");
    scanf("%s", passwd);
    int i;
    for (i = 0; i <= users->top; i++)
    {
        if (strcmp(username, users->us[i].account) == 0 || strcmp(username, root_name) == 0)
        {
            printf("Sorry,registration unsuccessful,the username you entered already exists.\n\n");
            break;
        }
    }
    if (i > users->top)
    {
        users->top++;
        strcpy(users->us[users->top].account, username);
        strcpy(users->us[users->top].passwd, passwd);
        users->us[users->top].borrow_number = 0;
        printf("successful\n\n");
    }
}

void Login(){
    char username[100];
    char passwd[100];
    printf("Please enter a username: ");
    scanf("%s", username);
    printf("Please enter a password: ");
    scanf("%s", passwd);
    strcpy(current_user, username);
    if (strcmp(username, root_name) == 0)
    {
        if (strcmp(passwd, root_passwd) == 0)
        {
            librarian_menu();
            return;
        }
    }
    else
    {
        for (int i = 0; i <= users->top; i++)
        {
            if (strcmp(username, users->us[i].account) == 0 && strcmp(passwd, users->us[i].passwd) == 0)
            {
                user_manage();
                return;
            }
        }
    }
    printf("login error\n\n");
}

void user_manage()
{
    int choice;
    do
    {
        printf("\n(logged in as : %s)", current_user);
        printf("\nPlease choose an option:\n");
        printf("1) Borrow a book\n");
        printf("2) Return a book\n");
        printf("3) Search for books\n");
        printf("4) Display all books\n");
        printf("5) Log out\n Option: ");
        scanf("%d", &choice);
        getchar();
        switch (choice)
        {
        case 1:
            borrow_book();
            break;
        case 2:
            return_book();
            break;
        case 3:
            Search();
            break;
        case 4:
            Display();
            break;
        case 5:
            printf("goodbye");
            break;
        default:
            getchar();
            printf("Sorry, the option you entered was invalid, please try again.\n");
        }
    } while (choice != 5);
}

void write_user(){
    FILE *f;
    // write users to users.txt
    f = fopen("users.txt", "w+");
    int i;
    for (i = 0; i < users->top; i++)
    {
        fprintf(f, "%s %s %d\n", users->us[i].account, users->us[i].passwd, users->us[i].borrow_number);
        for (int j = 0; j < users->us[i].borrow_number; j++)
        {
            fprintf(f, "%d\n", users->us[i].borrow_book[j]);
        }
    }
    fprintf(f, "%s %s %d\n", users->us[i].account, users->us[i].passwd, users->us[i].borrow_number);
    int j;
    for (j = 0; j < users->us[i].borrow_number - 1; j++)
    {
        fprintf(f, "%d\n", users->us[i].borrow_book[j]);
    }
    fprintf(f, "%d", users->us[i].borrow_book[j]);
    fclose(f);
}

void borrow_book()
{
    int id;
    printf("Blew is the list of Books you can borrow:\n");
    Display();
    printf("Enter the ID number of the book you wish to borrow: ");
    scanf("%d", &id);
    getchar();
    int i;
    for (i = 0; i <= users->top; i++)
    {
        if (strcmp(current_user, users->us[i].account) == 0 && id > 0)
        {
            users->us[i].borrow_book[users->us[i].borrow_number] = id;
            users->us[i].borrow_number++;
            break;
        }
    }
    if (i > users->top)
    {
        printf("Borrowed book not successfully\n");
    }
    else
    {
        printf("Borrowed book successfully\n");
    }
}

void return_book()
{
    int id;
    printf("Blew is the list of Books you are currently borrowing:\n");
    printf("ID\tTitle\tAuthor\tyear\tcopies\n");

    for (int i = 0; i <= users->top; i++)
    {
        if (strcmp(users->us[i].account, current_user) == 0)
        {
            for (int j = 0; j < users->us[i].borrow_number; j++)
            {
                BookList *p = books->next;
                while (p != NULL)
                {
                    if (p->Book.id == users->us[i].borrow_book[j])
                    {
                        printf("%d \t%s \t%s \t%d \t%d\n", p->Book.id, p->Book.title, p->Book.authors, p->Book.year, p->Book.copies);
                    }
                    p = p->next;
                }
            }
        }
    }

    printf("Enter the ID number of the book you wish to return: ");
    scanf("%d", &id);
    getchar();
    int i, count = 0;
    for (i = 0; i <= users->top; i++)
    {
        if (strcmp(current_user, users->us[i].account) == 0 && id < books->length + 1)
        {
            for (int j = 0; j < users->us[i].borrow_number; j++)
            {
                if (users->us[i].borrow_book[j] == id)
                {
                    for (int k = j; k < users->us[i].borrow_number - 1; k++)
                    {
                        users->us[i].borrow_book[k] = users->us[i].borrow_book[k + 1];
                    }
                    break;
                }
                count++;
            }
            users->us[i].borrow_number--;
            break;
        }
    }
    if (count > users->us[i].borrow_number)
    {
        printf("Returned book not successfully\n");
    }
    else
    {
        printf("Returned book successfully\n");
    }
}
