#include <stdio.h>
#include "menu.h"
#include "user.h"
#include "librarian.h"
#include "book_management.h"

char option[5][50] = {
    "Register an account", "Login", "Search for books", "Display all books", "Quit"
};

int menu(void)
{
    int choice;
    int i;
    printf("Please choose an option:\n");
    for (i=0; i<5; i++)
    {
        printf("%d) %s\n",i+1,option[i]);
    }
    printf("Option:");
    scanf("%d",&choice);
    if(choice == 1)
    {
        Register();
        menu();
    }
    if(choice == 2)
    {
        Login();
        menu();
    }
    if(choice == 3)
    {
        Search();
        menu();
    }
    if(choice == 4)
    {
        Display();
        menu();
    }
    if(choice == 5)
    {
        printf("Thank you for using the library!\n");
        printf("Goodbye!\n");
    }
    if(choice !=5 && choice != 1 && choice != 2 && choice != 3 && choice != 4)
    {
        getchar();
        printf("Sorry, the option you entered was invalid, please try again.\n\n");
        menu();
    }

    return choice;
}



