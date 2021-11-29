#include <stdio.h>
#include "sym_table.h"

int main (int argc, char** argv)
{
    void *a;
    int b = 5;
    a = (void *)&b;

    return 0;
}