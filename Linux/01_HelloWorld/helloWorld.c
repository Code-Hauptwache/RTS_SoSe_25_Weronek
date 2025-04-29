#include <stdio.h>
#include <stdlib.h>

int main (int argc, char* argv[])
{
    if (argc != 4)
    {
        printf("Usage: %s <string> <integer 1> <integer 2>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    char *endptr_a;
    char *endptr_b;
    int a = (int)strtol(argv[2], &endptr_a, 10);
    int b = (int)strtol(argv[3], &endptr_b, 10);

    if (*endptr_a != '\0' || *endptr_b != '\0')
    {
        printf("Usage:  %s <Integer 1> <Integer 2>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    printf("%s %d * %d = %d\n", argv[1], a, b, a*b);

    return EXIT_SUCCESS;
}