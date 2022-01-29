#include "types.h"
#include "user.h"
#include "date.h"

int main(int argc, char *argv[])
{
    struct rtcdate r;
    int result = date(&r);
    if (result == -1)
    {
        printf(2, "date failed\n");
        exit();
    }
    printf(2, "Year: %d\n", r.year);
    printf(2, "Month: %d\n", r.month);
    printf(2, "Date: %d\n", r.day);
    printf(2, "Hour: %d\n", r.hour);
    printf(2, "Minute: %d\n", r.minute);
    printf(2, "Second: %d\n", r.second);
    exit();
}