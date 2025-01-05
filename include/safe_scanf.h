/**
 * safe_scanf.h - A safer implementation of scanf-like functionality
 *
 * This implementation focuses on safety against:
 * - Buffer overflows
 * - NULL pointer dereferences
 * - Memory leaks
 * - Integer overflows
 * - Format string vulnerabilities
 */

#ifndef SAFE_SCANF_H
#define SAFE_SCANF_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdint.h>
#include <limits.h>

// Return codes for safe_scanf functions
typedef enum
{
    SAFE_SCANF_SUCCESS = 0,
    SAFE_SCANF_NULL_PTR = -1,
    SAFE_SCANF_INVALID_FORMAT = -2,
    SAFE_SCANF_BUFFER_OVERFLOW = -3,
    SAFE_SCANF_CONVERSION_ERROR = -4,
    SAFE_SCANF_IO_ERROR = -5,
    SAFE_SCANF_INTEGER_OVERFLOW = -6,
    SAFE_SCANF_DOUBLE_OVERFLOW = -7
} safe_scanf_status;

/**
 * Clears the remaining input in stdin to prevent it from affecting subsequent reads.
 */
void clear_stdin_buffer(void);

/**
 * Safely reads a string with a maximum length
 *
 * @param buffer Pointer to the buffer where the string will be stored
 * @param buffer_size Size of the buffer in bytes
 * @param chars_read Pointer to store the number of characters read
 * @return safe_scanf_status indicating success or type of error
 */
safe_scanf_status safe_scanf_string(char *buffer, size_t buffer_size, size_t *chars_read);

/**
 * Safely reads an integer value
 *
 * @param value Pointer to store the integer value
 * @return safe_scanf_status indicating success or type of error
 */
safe_scanf_status safe_scanf_int(int *value);

/**
 * Safely reads a double value
 *
 * @param value Pointer to store the double value
 * @return safe_scanf_status indicating success or type of error
 */
safe_scanf_status safe_scanf_double(double *value);

#endif // SAFE_SCANF_H
