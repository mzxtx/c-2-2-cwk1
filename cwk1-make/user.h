#ifndef USER_H_INCLUDED
#define USER_H_INCLUDED
#define MAX_PEOPLE 1000

void Register();
void read_users();
struct user
{
    char account[20];
    char passwd[20];
    int borrow_book[10];
    int borrow_number;
};
struct users
{
    struct user us[MAX_PEOPLE];
    int top;
};
void Login();

#endif // USER_H_INCLUDED
