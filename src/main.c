/**
 * main.c - Demonstrates the usage of safe_scanf functions
 */

#include <stdio.h>
#include "../include/safe_scanf.h"

int main()
{
    // Reading a string
    char name[50];
    size_t chars_read;
    safe_scanf_status status;

    printf("Enter your name: ");
    status = safe_scanf_string(name, sizeof(name), &chars_read);
    if (status == SAFE_SCANF_SUCCESS)
    {
        printf("Hello, %s! (%zu chars read)\n", name, chars_read);
    }
    else if (status == SAFE_SCANF_BUFFER_OVERFLOW)
    {
        printf("Error: Input exceeded buffer size.\n");
    }
    else
    {
        printf("Error reading string: %d\n", status);
    }

    // Reading an integer
    int age;
    printf("Enter your age: ");
    status = safe_scanf_int(&age);
    if (status == SAFE_SCANF_SUCCESS)
    {
        printf("You are %d years old\n", age);
    }
    else if (status == SAFE_SCANF_INTEGER_OVERFLOW)
    {
        printf("Error: Integer value out of range.\n");
    }
    else if (status == SAFE_SCANF_CONVERSION_ERROR)
    {
        printf("Error: Invalid integer format.\n");
    }
    else
    {
        printf("Error reading integer: %d\n", status);
    }

    // Reading a double
    double height;
    printf("Enter your height in meters: ");
    status = safe_scanf_double(&height);
    if (status == SAFE_SCANF_SUCCESS)
    {
        printf("You are %.2f meters tall\n", height);
    }
    else if (status == SAFE_SCANF_DOUBLE_OVERFLOW)
    {
        printf("Error: Double value out of range.\n");
    }
    else if (status == SAFE_SCANF_CONVERSION_ERROR)
    {
        printf("Error: Invalid double format.\n");
    }
    else
    {
        printf("Error reading double: %d\n", status);
    }

    return 0;
}
