/**
 * safe_scanf.c - Implementation of safe_scanf functions
 *
 * This file contains the definitions of the functions declared in safe_scanf.h.
 */

#include "../include/safe_scanf.h"

/**
 * Clears the remaining input in stdin to prevent it from affecting subsequent reads.
 */
void clear_stdin_buffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

/**
 * Safely reads a string with a maximum length
 *
 * @param buffer Pointer to the buffer where the string will be stored
 * @param buffer_size Size of the buffer in bytes
 * @param chars_read Pointer to store the number of characters read
 * @return safe_scanf_status indicating success or type of error
 */
safe_scanf_status safe_scanf_string(char *buffer, size_t buffer_size, size_t *chars_read)
{
    if (buffer == NULL || chars_read == NULL)
    {
        return SAFE_SCANF_NULL_PTR;
    }

    if (buffer_size == 0)
    {
        return SAFE_SCANF_BUFFER_OVERFLOW;
    }

    // Clear errno before operation
    errno = 0;

    // Read input ensuring space for null terminator
    if (fgets(buffer, (int)buffer_size, stdin) == NULL)
    {
        if (ferror(stdin))
        {
            clearerr(stdin);
            return SAFE_SCANF_IO_ERROR;
        }
        // EOF reached
        buffer[0] = '\0';
        *chars_read = 0;
        return SAFE_SCANF_SUCCESS;
    }

    // Check if the input was truncated (no newline found)
    size_t len = strnlen(buffer, buffer_size);
    if (len == buffer_size - 1 && buffer[len - 1] != '\n')
    {
        // Input was truncated; clear the remaining input
        clear_stdin_buffer();
        return SAFE_SCANF_BUFFER_OVERFLOW;
    }

    // Remove trailing newline if present
    if (len > 0 && buffer[len - 1] == '\n')
    {
        buffer[len - 1] = '\0';
        len--;
    }

    *chars_read = len;
    return SAFE_SCANF_SUCCESS;
}

/**
 * Safely reads an integer value
 *
 * @param value Pointer to store the integer value
 * @return safe_scanf_status indicating success or type of error
 */
safe_scanf_status safe_scanf_int(int *value)
{
    if (value == NULL)
    {
        return SAFE_SCANF_NULL_PTR;
    }

    char buffer[32]; // Large enough for any integer
    size_t chars_read;

    safe_scanf_status status = safe_scanf_string(buffer, sizeof(buffer), &chars_read);
    if (status != SAFE_SCANF_SUCCESS)
    {
        return status;
    }

    // Clear errno before conversion
    errno = 0;
    char *endptr;
    long result = strtol(buffer, &endptr, 10);

    // Check for conversion errors
    if (endptr == buffer || *endptr != '\0')
    {
        return SAFE_SCANF_CONVERSION_ERROR;
    }

    // Check for overflow/underflow
    if (errno == ERANGE || result > INT_MAX || result < INT_MIN)
    {
        return SAFE_SCANF_INTEGER_OVERFLOW;
    }

    *value = (int)result;
    return SAFE_SCANF_SUCCESS;
}

/**
 * Safely reads a double value
 *
 * @param value Pointer to store the double value
 * @return safe_scanf_status indicating success or type of error
 */
safe_scanf_status safe_scanf_double(double *value)
{
    if (value == NULL)
    {
        return SAFE_SCANF_NULL_PTR;
    }

    char buffer[64]; // Large enough for any double
    size_t chars_read;

    safe_scanf_status status = safe_scanf_string(buffer, sizeof(buffer), &chars_read);
    if (status != SAFE_SCANF_SUCCESS)
    {
        return status;
    }

    // Clear errno before conversion
    errno = 0;
    char *endptr;
    double result = strtod(buffer, &endptr);

    // Check for conversion errors
    if (endptr == buffer || *endptr != '\0')
    {
        return SAFE_SCANF_CONVERSION_ERROR;
    }

    // Check for overflow/underflow
    if (errno == ERANGE)
    {
        return SAFE_SCANF_DOUBLE_OVERFLOW;
    }

    *value = result;
    return SAFE_SCANF_SUCCESS;
}
