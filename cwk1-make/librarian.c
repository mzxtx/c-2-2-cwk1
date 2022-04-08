#include <stdio.h>
#include "menu.h"
#include "user.h"
#include "librarian.h"
#include "book_management.h"

void librarian_menu()
{
    char root_name[100] = "librarian";
    int choice;
    do
    {
        printf("\n(logged in as : %s)", root_name);
        printf("\nPlease choose an option:\n");
        printf("1) Add a book\n");
        printf("2) Remove a book\n");
        printf("3) Search for books\n");
        printf("4) Display all books\n");
        printf("5) Log out\n Option: ");
        scanf("%d", &choice);
        getchar();
        switch (choice)
        {
        case 1:
            add_book();
            break;
        case 2:
            Display();
            remove_book();
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
