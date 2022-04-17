#include "types.h"
#include "user.h"
#include "date.h"

// int arrGlobal[10000];

int main(int argc, char *argv[])
{
    int result = pgtPrint();
    if (result == 0)
    {
        printf(2, "Failed to execute pgtPrint\n");
        exit();
    }
    int arrLocal[10000];
    arrLocal[100] = 69;
    printf(2, "Result: %d\n", result);
    printf(2, "Result: %d\n", arrLocal[100]);
    exit();
}