#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
typedef struct sll
{
    char money[50];
    struct sll *next_node;
} sll;
void Account_numgen(void);
int check_Account_num(void);
void depositMoney(sll **, int *);
void withdrawMoney(sll **, int *);
void transaction(sll **, char *);
void showBalance(int *);
void display_transaction(sll **);
void help();
int main()
{
    int choice1, choice2;
    int Account_NumberValid, balance;
    sll *head = NULL;
    lable : Account_NumberValid = 0;
    balance = 0;
    while (1)
    {
        printf("\n\n----------ABHINAV BANK OF INDIA----------\n\n");
        printf("1. Create Account \n2. Account info / Withdraw-add money\n3. Exit\n4. Help desk\n");
        printf("\nYour choice: ");
        scanf("%d", &choice1);
        switch (choice1)
        {
        case 1:
            Account_numgen();
            goto lable;
        case 2:
            Account_NumberValid = check_Account_num();
            if (Account_NumberValid)
            {
                printf("\nValid Account_Number\n");
            }
            else
            {
                printf("\nInvalid Account_Number. Please create a Account by selecting option 1\n");
                exit(0);
            }
            while (Account_NumberValid)

            {
                printf("\n----------ABHINAV BANK OF INDIA MENU----------\n\n\n");
printf("1. Check Balance\n2. Deposit Money\n3. Withdraw Money\n4. View transaction details\n5.Quit(Your Account will be deleted)\n6. Help desk\n7. Back\n");
printf("Enter choice: ");
scanf("%d", &choice2);
switch (choice2)
{
                case 1:
                    showBalance(&balance);
                    break;
                case 2:
                    depositMoney(&head, &balance);
                    break;
                case 3:
                    withdrawMoney(&head, &balance);
                    break;
                case 4:
                    display_transaction(&head);
                    break;
                case 5:
                    printf("\nTHANL YOU FOR BANKING WITH US\n");
                    printf("HOPE TO SEE YOU AGAIN");
                    exit(0);
                case 6:
                    help();
                    break;
                case 7:
                    goto lable;
                    break;
                default:
                    printf("\nInvalid option entered!\n");
                    break;
}
            }
        case 3:
            printf("HOPE TO SEE YOU AGAIN........THANK YOU FOR BANKING WITH US");
            exit(0);
        case 4:
            help();
            break;
        default:
            printf("\nInvalid choice...Try again...\n");
            break;
        }
    }
    return 0;
}
void Account_numgen(void)
{
    FILE *fp;

    srand(time(NULL));
    int generatedAccount_Number = 1000 + rand() % 9000;
    printf("\nAccount Created successfully\n");
    printf("\nYour generated Account_Number: %d\n", generatedAccount_Number);
    printf("\nRe-run the program and use our bank with this Account_Number\n\n");
    fp = fopen("temp.txt", "a");
    if (NULL == fp)
    {
        printf("\nCannot open file!");
        exit(0);
    }
    fprintf(fp, "%d\n", generatedAccount_Number);
    fclose(fp);
}
int check_Account_num(void)
{
    FILE *fp;
    char Account_Number[8];
    char keyAccount_Number[8];
    int Account_NumberValid = 0;
    printf("\n\nEnter the Account_Number: \n");
    scanf("%s", keyAccount_Number);
    fp = fopen("temp.txt", "r");

    if (NULL == fp)
    {
        printf("\nFile cannot be opened\n");
        exit(0);
    }
    while (fgets(Account_Number, sizeof(Account_Number), fp) != NULL)
    {
        if (strstr(Account_Number, keyAccount_Number))
        {
            Account_NumberValid = 1;
        }
    }
    fclose(fp);
    return Account_NumberValid;
}
void showBalance(int *balance)
{
    printf("\nYour current balance is Rs.%d\n", *balance);
}
void depositMoney(sll **head, int *balance)
{
    int depositAmount;
    char depositStmt[50];

    printf("\nEnter amount to deposit: ");
    scanf("%d", &depositAmount);
    if (depositAmount > 0)
    {
        *balance += depositAmount;
        printf("\nRs.%d deposited\n", depositAmount);
        snprintf(depositStmt, sizeof(depositStmt), "Rs.%d deposited\n", depositAmount);
        transaction(head, depositStmt);
    }
    else
    {
        printf("\nInvalid amount entered\n.");
    }
}
void withdrawMoney(sll **head, int *balance)
{
    int withdraw_amount;
    char withdrawStmt[50];
    printf("\nEnter amount to withdraw: ");
    scanf("%d", &withdraw_amount);
    if (withdraw_amount > 0)
    {
        if (withdraw_amount > *balance)
        {

            printf("\nCannot withdraw. Balance Rs.%d\n", *balance);
        }
        else
        {
            *balance = *balance - withdraw_amount;
            printf("\nRs.%d withdrawn\n", withdraw_amount);
            snprintf(withdrawStmt, sizeof(withdrawStmt), "Rs.%d withdrawn\n", withdraw_amount);
            transaction(head, withdrawStmt);
        }
    }
    else
    {
        printf("\nInvalid amount entered\n.");
    }
}
void transaction(sll **head, char *str)
{
    static int c = 0;
    sll *temp;
    temp = (sll *)malloc(sizeof(sll));
    strcpy(temp->money, str);
    temp->next_node = NULL;
    if (NULL == *head)
    {
        *head = temp;

        c++;
    }
    else
    {
        sll *p;
        p = *head;
        while (NULL != p->next_node)
        {
            p = p->next_node;
        }
        p->next_node = temp;
        c++;
    }
}
void display_transaction(sll **head)
{
    sll *temp;
    temp = *head;
    if (NULL == temp)
    {
        printf("\nNo transaction history...\n");
    }
    else
    {
        printf("\nTransaction History\n-------------------\n\n");
        while (NULL != temp)
        {

            printf("%s\n", temp->money);
            temp = temp->next_node;
        }
    }
}
void help()
{
    printf("\n\n\n\nYou can reach us by calling our toll free Number ******** \n");
    printf(" or ");
    printf("\nYou can write us at abcd@xyz.domain\n");
    printf(" or ");
    printf("\nYou can visit our nearest Bank\n\n\n\n\n\n\n\n");
    exit(0);
}
