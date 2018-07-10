#include "Functions.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

struct LLTable *head = NULL;

void CreateEmptyTables(int num)//Allocates memory for 15 tables at the beginning of the program
{
    struct LLTable *New = (struct LLTable*)malloc(sizeof(LLTable));
    if(New == 0)
    {
        printf("Error allocating memory\n");
        exit(-1);
    }
    New->TableNumber = num+1;
    New->FirstClient = NULL;
    New->FirstCons = NULL;
    New->Next = head;
    head = New;
}

struct LLTable* FindTable(int TableNum)//Returns pointer to head of found table by number, also checks if table is empty or full
{
    int check = 0;
    struct LLTable *curr = head;
    if(head == NULL)
    {
        return NULL;
    }
    while(curr->TableNumber != TableNum)
    {
        if(curr->Next == NULL)
        {
            return NULL;
        }
        else
        {
            curr = curr->Next;
        }
    }
    check = IsTableEmpty(curr);// Checks if table has already customers or consumption
    if(check == 0)
    {
        return curr;
    }
    else
    {
        printf("Table already taken!\n\n");
        return NULL;
    }
}

int IsTableEmpty(struct LLTable *curr)//When creating new table check if it is empty!
{
    if((curr->FirstClient == NULL) && (curr->FirstCons == NULL))
    {
        return 0;
    }
    else
    {
        return -1;
    }
}

void EnterCust(struct LLTable *head, char name[SizeArr])//Enter customer to already exiting table
{

    struct LLClient *New = (struct LLClient*)malloc(sizeof(struct LLClient));
    if(New == 0)
    {
        printf("Error allocating memory\n");
        exit(-1);
    }
    strcpy(New->Client, name);
    New->Link = head->FirstClient;
    head->FirstClient = New;

}

void EnterDrinks(struct LLTable *head, char name[SizeArr], double price)//Enter drinks to already exiting table
{

    struct LLCons *New = (struct LLCons*)malloc(sizeof(struct LLCons));
    if(New == 0)
    {
        printf("Error allocating memory\n");
        exit(-1);
    }
    strcpy(New->Cons, name);
    New->Price = price;
    New->Next = head->FirstCons;
    head->FirstCons = New;

}

struct LLTable* EnterMoreToTable(int TableNum)//Adjusted function for finding table by number and adding more consumption or clients to it
{
    int check = 0;
    struct LLTable *curr = head;
    if(head == NULL)
    {
        return NULL;
    }
    while(curr->TableNumber != TableNum)
    {
        if(curr->Next == NULL)
        {
            return NULL;
        }
        else
        {
            curr = curr->Next;
        }
    }
    check = IsTableEmpty(curr);
    if(check != 0)
    {
        return curr;
    }
    else
    {
        printf("Table empty!\n\n");
        return NULL;
    }
}

double CalculateBill(struct LLTable *head)//Calculating bill of table
{
    double FinaleBill = 0;
    struct LLCons *temp = head->FirstCons;
    while(temp != NULL)
    {
        FinaleBill = FinaleBill + temp->Price;
        temp = temp->Next;
    }
    return FinaleBill;
}

void SaveTableToFile(struct LLTable *head, double bill)//Outputs the table in folder of program with date and time stamp
{
    time_t curr;
    curr = time(NULL);
    struct tm *t = localtime(&curr);
    char filename[30];
    strftime(filename, sizeof(filename), "%d.%m.%y_%H.%M.%S.txt", t );
    FILE *filepointer;
    filepointer = fopen(filename, "w");
    if(filepointer == NULL)
    {
        printf("Error opening file!\n");
        exit(-1);
    }
    fprintf(filepointer, "Table: %d\n", head->TableNumber);
    fprintf(filepointer, "Clients:");
    struct LLClient *PointClient = head->FirstClient;
    struct LLCons *PointCons = head->FirstCons;
    while(PointClient != 0)
    {
        fprintf(filepointer, "%s ", PointClient->Client);
        PointClient = PointClient->Link;
    }
    fprintf(filepointer, "\nConsumption:");
    while(PointCons != 0)
    {
        fprintf(filepointer, "%s ", PointCons->Cons);
        PointCons = PointCons->Next;
    }
    fprintf(filepointer, "\nBill: %0.2lf\n", bill);
    fclose(filepointer);
}

void ClearTable(struct LLTable *head)//Frees allocated memory for consumption and clients after calculating bill and outputting the information in a file
{
    struct LLCons *FirstPCons = head->FirstCons;
    struct LLCons *SecPCons;
    struct LLClient *FirstPClient = head->FirstClient;
    struct LLClient *SecPClient;
    while(FirstPCons != NULL)
    {
        SecPCons = FirstPCons;
        FirstPCons = SecPCons->Next;
        free(SecPCons);
    }
    head->FirstCons = NULL;
    while(FirstPClient != NULL)
    {
        SecPClient = FirstPClient;
        FirstPClient = SecPClient->Link;
        free(SecPClient);
    }
    head->FirstClient = NULL;
}

void FreeAllTables()//After choosing Exit in program menu frees all the memory allocated for tables
{
    struct LLTable *FirstPoint = head;
    struct LLTable *SecPoint;
    while(FirstPoint != NULL)
    {
        SecPoint = FirstPoint;
        FirstPoint = SecPoint->Next;
        free(SecPoint);
    }
    head = NULL;
}

struct LLTable* CheckAllTables(int TableNum)//Before freeing memory for all tables checks if all of them are empty.Returns error and number of table if it finds a full one
{
    int check = 0;
    struct LLTable *curr = head;
    if(head == NULL)
    {
        return NULL;
    }
    while(curr->TableNumber != TableNum)
    {
        if(curr->Next == NULL)
        {
            curr = NULL;
            return NULL;
        }
        else
        {
            curr = curr->Next;
        }
    }
    check = IsTableEmpty(curr);
    if(check == 0)
    {
        return NULL;
    }
    else
    {
        printf("Table %d is taken!\n\n", TableNum);
        return curr;
    }
}
