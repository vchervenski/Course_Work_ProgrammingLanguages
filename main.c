#include "Functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


int main()
{
    int choice = 0, i, TableNumber, NumbCustDrinks, flag = 0;
    double priceBill;
    char NameCustCost[SizeArr];
    LLTable *TableFill;
    for(i = 0; i < SizeArr; i++)
    {
        CreateEmptyTables(i);
    }
    while(1)
    {
        printf("1.Start a new table\n2.Enter a new client\n3.Enter more consumption\n4.Calculate bill\n5.Exit\nYour choice:");
        scanf("%d", &choice);
        fflush(stdin);
        switch(choice)
        {
        case 1:
            printf("\nEnter table number:");
            scanf("%d", &TableNumber);
            if(TableNumber > 15 || TableNumber < 1)
            {
                printf("Wrong table numbegr!\n\n");
                system("pause");
                system("cls");
                break;
            }
            TableFill = FindTable(TableNumber);
            if(TableFill == NULL)
            {
                system("pause");
                system("cls");
                break;
            }
            printf("\nEnter number of customers:");
            scanf("%d", &NumbCustDrinks);
            for(i = 0; i < NumbCustDrinks; i++)
            {
                printf("Enter name of client %d:", i+1);
                scanf("%s", NameCustCost);
                EnterCust(TableFill, NameCustCost);
            }
            printf("\nEnter number of drinks:");
            scanf("%d", &NumbCustDrinks);
            for(i = 0; i < NumbCustDrinks; i++)
            {
                printf("Enter drink %d:", i+1);
                scanf("%s", NameCustCost);
                printf("Enter price of drink:");
                scanf("%lf", &priceBill);
                EnterDrinks(TableFill, NameCustCost, priceBill);
            }
            system("pause");
            system("cls");
            break;
        case 2:
            printf("\nEnter table number:");
            scanf("%d", &TableNumber);
            if(TableNumber > 15 || TableNumber < 1)
            {
                printf("Wrong table number!\n\n");
                system("pause");
                system("cls");
                break;
            }
            TableFill = EnterMoreToTable(TableNumber);
            if(TableFill == NULL)
            {
                system("pause");
                system("cls");
                break;
            }
            printf("\nEnter number of new customers:");
            scanf("%d", &NumbCustDrinks);
            for(i = 0; i < NumbCustDrinks; i++)
            {
                printf("Enter name of client %d:", i+1);
                scanf("%s", NameCustCost);
                EnterCust(TableFill, NameCustCost);
            }
            system("pause");
            system("cls");
            break;
        case 3:
            printf("\nEnter table number:");
            scanf("%d", &TableNumber);
            if(TableNumber > 15 || TableNumber < 1)
            {
                printf("Wrong table number!\n\n");
                system("pause");
                system("cls");
                break;
            }
            TableFill = EnterMoreToTable(TableNumber);
            if(TableFill == NULL)
            {
                system("pause");
                system("cls");
                break;
            }
            printf("\nEnter number of extra drinks:");
            scanf("%d", &NumbCustDrinks);
            for(i = 0; i < NumbCustDrinks; i++)
            {
                printf("Enter drink %d:", i+1);
                scanf("%s", NameCustCost);
                printf("Enter price of drink:");
                scanf("%lf", &priceBill);
                EnterDrinks(TableFill, NameCustCost, priceBill);
            }
            system("pause");
            system("cls");
            break;
        case 4:
            printf("\nEnter table number:");
            scanf("%d", &TableNumber);
            if(TableNumber > 15 || TableNumber < 1)
            {
                printf("Wrong table number!\n\n");
                system("pause");
                system("cls");
                break;
            }
            TableFill = EnterMoreToTable(TableNumber);
            if(TableFill == NULL)
            {
                system("pause");
                system("cls");
                break;
            }
            priceBill = CalculateBill(TableFill);
            printf("Bill for table %d is: %0.2lf\n\n", TableNumber, priceBill);
            SaveTableToFile(TableFill, priceBill);
            ClearTable(TableFill);
            system("pause");
            system("cls");
            break;
        case 5:
            for(i = 0; i < 15; i++)
            {
                flag = 0;
                TableFill = CheckAllTables(i);
                if(TableFill != NULL)
                {
                    break;
                }
                flag = 1;
            }
            if(flag == 0)
            {
                system("pause");
                system("cls");
                break;
            }
            else
            {
                FreeAllTables();
                exit(0);
            }
        default:
            if(choice > 5 || choice < 1)
            {
                printf("Invalid option!\n\n");
            }
        }
    }
    return 0;
}
