#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED
#define SizeArr 15

typedef struct LLClient
{
    char Client[SizeArr];
    struct LLClient *Link;
}LLClient;

struct LLCons
{
    char Cons[SizeArr];
    double Price;
    struct LLCons *Next;
}LLCons;

typedef struct LLTable
{
    int TableNumber;
    struct LLClient *FirstClient;
    struct LLCons *FirstCons;
    struct LLTable *Next;

}LLTable;

void CreateEmptyTables(int num);
struct LLTable* FindTable(int TableNum);
int IsTableEmpty(struct LLTable *curr);
void EnterCust(struct LLTable *head, char name[SizeArr]);
void EnterDrinks(struct LLTable *head, char name[SizeArr], double price);
struct LLTable* EnterMoreToTable(int TableNum);
double CalculateBill(struct LLTable *head);
void SaveTableToFile(struct LLTable *head, double bill);
void ClearTable(struct LLTable *head);
void FreeAllTables();
struct LLTable* CheckAllTables(int TableNum);


#endif // FUNCTIONS_H_INCLUDED
