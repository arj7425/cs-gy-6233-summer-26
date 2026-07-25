#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        return 1;
    }

    int year = atoi(argv[1]);
    int is_leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);

    if (is_leap) {
        printf("%d was a leap year\n", year);
    } else {
        printf("%d was not a leap year\n", year);
    }

    return 0;
}
