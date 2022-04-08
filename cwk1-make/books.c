#define _CRT_SECURE_NO_WARNINGS
#define MAXLEN 10240

#include <stdio.h>
#include <ctype.h>
#include "menu.h"
#include "user.h"
#include "librarian.h"
#include "book_management.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

BookList *books;
Book *p;
Book book;
char* path = "books.txt";
BookList *init_book_list() {
    struct _BookList *head;
    head = (struct BookList *) malloc(sizeof(struct _BookList));
    head->list = NULL;
    head->length = 0;
    return head;
}


//saves the database of books in the specified file
//returns 0 if books were stored correctly, or an error code otherwise
int store_books(FILE *file){
    file = fopen("path", "w+");
    Book *p = books->list;
    for (int i = 0; i < books->length; i++)
    {
        fprintf(file, "%d|%s|%s|%d|%d\n", p->id, p->title, p->authors, p->year, p->copies);
        p = p->next;
    }
    fprintf(file, "%d|%s|%s|%d|%d", p->id, p->title, p->authors, p->year, p->copies);
    fclose(file);
}

//loads the database of books from the specified file
//the file must have been generated by a previous call to store_books()
//returns 0 if books were loaded correctly, or an error code otherwise
int load_books(FILE *file){
    struct _BookList *head;
    head = init_book_list();
    file = fopen(path, "r");
    if (file == NULL) {
        printf("File (%s) open failed, end program", path);
        exit(0);
    }
    Book *book_p, *pre = head->list;
    char c;
    char tmp[100];
    memset(tmp, '\0', 100);
    int j = 0, k = 1;
    int count = 0;
    char buffer[100]; // buffer to save one-line data
    while ((fgets(buffer,255,file))!=NULL) {
        int id,year,copies;
        char* title = (char*) malloc(sizeof(char)*100);
        char* authors = (char*) malloc(sizeof(char)*100);

        sscanf(buffer,"%u %s %s %u %u",&id,title,authors,&year,&copies); // split string
        book_p = (Book *) malloc(sizeof(Book));
        book_p->next = NULL;
        book_p->id = id;
        book_p->title = title;
        book_p->authors = authors;
        book_p->year = year;
        book_p->copies = copies;

        if(pre == NULL){
            head->list = book_p;
            pre = book_p;
        }else{
            pre->next = book_p;
            pre = book_p;
        }
        count++;
    }
    books = head;
    books->length = count;

//    display_all_books();

    fclose(file);
}

//adds a book to the ones available to the library
//returns 0 if the book could be added, or an error code otherwise
int add_book(Book book) {
    Book *p, *pre = books->list;
    p = (Book *) malloc(sizeof(Book));
    char tmp[100];
    printf("Enter the title of the book you wish to add: ");
    memset(tmp, '\0', 100);
    gets(tmp);
    p->title = (char *) malloc(sizeof(strlen(tmp)));
    strcpy(p->title, tmp);
    printf("Enter the author of the book you wish to add: ");
    memset(tmp, '\0', 100);
    gets(tmp);
    p->authors = (char *) malloc(sizeof(strlen(tmp)));
    strcpy(p->authors, tmp);
    printf("Enter the year that the book you wish to add was release: ");
    scanf("%d", &p->year);
    getchar();
    printf("Enter the number of copies of the book that you wish to add: ");
    scanf("%d", &p->copies);
    getchar();
    books->length++;

    p->id = books->length + 1;

    while (pre->next != NULL) {
        pre = pre->next;
    }
    pre->next = p;
    p->next = NULL;
    printf("add successfully\n");
    return 0;
}

//removes a book from the library
//returns 0 if the book could be successfully removed, or an error code otherwise.
int remove_book(Book book){
    int id;
    printf("Please enter the number of the book  to be removed: ");
    scanf("%d", &id);
    getchar();
    book.id = id;
    struct _BookList *head;
    head = init_book_list();
    Book *p = head->list, *pre;
    while (p != NULL) {
        if (p->id == book.id) {
            pre->next = p->next;
            free(p);
            // p = pre->next;
            books->length--;
            break;
        } else {
            pre = p;
            p = p->next;
        }
    }
    return 0;
}

void Search()
{
    int num;
    while (1) {
        printf("Please choose an option:\n");
        printf("1) Find books by title\n");
        printf("2) Find books by author\n");
        printf("3) Find books by year\n");
        printf("4) Return to previous menu\n Option: ");
        scanf("%d", &num);
        getchar();
        Book *p = books->list;
        if (num == 1)
        {
            find_book_by_title();
        }
        else if (num == 2) {
            find_book_by_author();
        }
        else if (num == 3) {
            find_book_by_year();
        }
        else if (num == 4) {
            break;
        }
    }
}
BookList find_book_by_title () {
    Book *p = books->list;
    char title[100];
    printf("Please enter title: ");
    gets(title);
    printf("ID\tTitle\tAuthor\tyear\tcopies\n");
    while (p->next != NULL) {
//        p = p->next;
        if (strcmp(p->title, title) == 0) {
            printf("%d \t%s \t%s \t%d \t%d\n\n", p->id, p->title, p->authors, p->year, p->copies);
        }
        p = p->next;
    }
    return *books;
}

BookList find_book_by_author () {
    Book *book_p = books->list;
    char author[100];
    printf("Please enter author: ");
    gets(author);
    printf("ID\tTitle\tAuthor\tyear\tcopies\n");
    while (book_p->next != NULL) {
        if (strcmp(book_p->authors, author) == 0) {
            printf("%d \t%s \t%s \t%d \t%d\n\n", book_p->id, book_p->title, book_p->authors, book_p->year, book_p->copies);
        }
        book_p = book_p->next;
    }
}

BookList find_book_by_year () {
    Book *book_p = books->list;
    printf("Please enter year: ");
    unsigned int year;
    scanf("%u", &year);
    getchar();
    printf("ID\tTitle\tAuthor\tyear\tcopies\n");
    while (book_p->next != NULL) {
        book_p = book_p->next;
        if (book_p != NULL && book_p->year == year) {
            printf("%d \t%s \t%s \t%d \t%d\n\n", book_p->id, book_p->title, book_p->authors, book_p->year, book_p->copies);
        }
    }
}

void Display()
{
    Book *p = books->list;
    printf("ID\tTitle\tAuthor\tyear\tcopies\n");
    while (p != NULL) {
        printf("%d \t%s \t%s \t%d \t%d\n", p->id, p->title, p->authors, p->year, p->copies);
        p = p->next;
    }
    return;
}


#define _CRT_SECURE_NO_WARNINGS
#define MAXLEN 10240

#include <stdio.h>
#include <ctype.h>
#include "menu.h"
#include "user.h"
#include "librarian.h"
#include "book_management.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

BookList *books;
Book *p;
Book book;
char* path = "books.txt";
BookList *init_book_list() {
    struct _BookList *head;
    head = (struct BookList *) malloc(sizeof(struct _BookList));
    head->list = NULL;
    head->length = 0;
    return head;
}


//saves the database of books in the specified file
//returns 0 if books were stored correctly, or an error code otherwise
int store_books(FILE *file){
    file = fopen("path", "w+");
    Book *p = books->list;
    for (int i = 0; i < books->length; i++)
    {
        fprintf(file, "%d|%s|%s|%d|%d\n", p->id, p->title, p->authors, p->year, p->copies);
        p = p->next;
    }
    fprintf(file, "%d|%s|%s|%d|%d", p->id, p->title, p->authors, p->year, p->copies);
    fclose(file);
}

//loads the database of books from the specified file
//the file must have been generated by a previous call to store_books()
//returns 0 if books were loaded correctly, or an error code otherwise
int load_books(FILE *file){
    struct _BookList *head;
    head = init_book_list();
    file = fopen(path, "r");
    if (file == NULL) {
        printf("File (%s) open failed, end program", path);
        exit(0);
    }
    Book *book_p, *pre = head->list;
    char c;
    char tmp[100];
    memset(tmp, '\0', 100);
    int j = 0, k = 1;
    int count = 0;
    char buffer[100]; // buffer to save one-line data
    while ((fgets(buffer,255,file))!=NULL) {
        int id,year,copies;
        char* title = (char*) malloc(sizeof(char)*100);
        char* authors = (char*) malloc(sizeof(char)*100);

        sscanf(buffer,"%u %s %s %u %u",&id,title,authors,&year,&copies); // split string
        book_p = (Book *) malloc(sizeof(Book));
        book_p->next = NULL;
        book_p->id = id;
        book_p->title = title;
        book_p->authors = authors;
        book_p->year = year;
        book_p->copies = copies;

        if(pre == NULL){
            head->list = book_p;
            pre = book_p;
        }else{
            pre->next = book_p;
            pre = book_p;
        }
        count++;
    }
    books = head;
    books->length = count;

//    display_all_books();

    fclose(file);
}

//adds a book to the ones available to the library
//returns 0 if the book could be added, or an error code otherwise
int add_book(Book book) {
    Book *p, *pre = books->list;
    p = (Book *) malloc(sizeof(Book));
    char tmp[100];
    printf("Enter the title of the book you wish to add: ");
    memset(tmp, '\0', 100);
    gets(tmp);
    p->title = (char *) malloc(sizeof(strlen(tmp)));
    strcpy(p->title, tmp);
    printf("Enter the author of the book you wish to add: ");
    memset(tmp, '\0', 100);
    gets(tmp);
    p->authors = (char *) malloc(sizeof(strlen(tmp)));
    strcpy(p->authors, tmp);
    printf("Enter the year that the book you wish to add was release: ");
    scanf("%d", &p->year);
    getchar();
    printf("Enter the number of copies of the book that you wish to add: ");
    scanf("%d", &p->copies);
    getchar();
    books->length++;

    p->id = books->length + 1;

    while (pre->next != NULL) {
        pre = pre->next;
    }
    pre->next = p;
    p->next = NULL;
    printf("add successfully\n");
    return 0;
}

//removes a book from the library
//returns 0 if the book could be successfully removed, or an error code otherwise.
int remove_book(Book book){
    int id;
    printf("Please enter the number of the book  to be removed: ");
    scanf("%d", &id);
    getchar();
    book.id = id;
    struct _BookList *head;
    head = init_book_list();
    Book *p = head->list, *pre;
    while (p != NULL) {
        if (p->id == book.id) {
            pre->next = p->next;
            free(p);
            // p = pre->next;
            books->length--;
            break;
        } else {
            pre = p;
            p = p->next;
        }
    }
    return 0;
}

void Search()
{
    int num;
    while (1) {
        printf("Please choose an option:\n");
        printf("1) Find books by title\n");
        printf("2) Find books by author\n");
        printf("3) Find books by year\n");
        printf("4) Return to previous menu\n Option: ");
        scanf("%d", &num);
        getchar();
        Book *p = books->list;
        if (num == 1)
        {
            find_book_by_title();
        }
        else if (num == 2) {
            find_book_by_author();
        }
        else if (num == 3) {
            find_book_by_year();
        }
        else if (num == 4) {
            break;
        }
    }
}
BookList find_book_by_title () {
    Book *p = books->list;
    char title[100];
    printf("Please enter title: ");
    gets(title);
    printf("ID\tTitle\tAuthor\tyear\tcopies\n");
    while (p->next != NULL) {
//        p = p->next;
        if (strcmp(p->title, title) == 0) {
            printf("%d \t%s \t%s \t%d \t%d\n\n", p->id, p->title, p->authors, p->year, p->copies);
        }
        p = p->next;
    }
    return *books;
}

BookList find_book_by_author () {
    Book *book_p = books->list;
    char author[100];
    printf("Please enter author: ");
    gets(author);
    printf("ID\tTitle\tAuthor\tyear\tcopies\n");
    while (book_p->next != NULL) {
        if (strcmp(book_p->authors, author) == 0) {
            printf("%d \t%s \t%s \t%d \t%d\n\n", book_p->id, book_p->title, book_p->authors, book_p->year, book_p->copies);
        }
        book_p = book_p->next;
    }
}

BookList find_book_by_year () {
    Book *book_p = books->list;
    printf("Please enter year: ");
    unsigned int year;
    scanf("%u", &year);
    getchar();
    printf("ID\tTitle\tAuthor\tyear\tcopies\n");
    while (book_p->next != NULL) {
        book_p = book_p->next;
        if (book_p != NULL && book_p->year == year) {
            printf("%d \t%s \t%s \t%d \t%d\n\n", book_p->id, book_p->title, book_p->authors, book_p->year, book_p->copies);
        }
    }
}

void Display()
{
    Book *p = books->list;
    printf("ID\tTitle\tAuthor\tyear\tcopies\n");
    while (p != NULL) {
        printf("%d \t%s \t%s \t%d \t%d\n", p->id, p->title, p->authors, p->year, p->copies);
        p = p->next;
    }
    return;
}
