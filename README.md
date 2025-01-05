# Safe Scanf

A safer implementation of `scanf`-like functionality in C.

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
  - [Including the Library](#including-the-library)
  - [Functions](#functions)
    - [`safe_scanf_string`](#safe_scanf_string)
    - [`safe_scanf_int`](#safe_scanf_int)
    - [`safe_scanf_double`](#safe_scanf_double)
  - [Example](#example)
- [API Reference](#api-reference)
  - [Enumerations](#enumerations)
- [Contributing](#contributing)
- [License](#license)
- [Contact](#contact)

## Overview

`Safe Scanf` is a C library designed to provide safer alternatives to the standard `scanf` functions. It addresses common vulnerabilities and issues such as:

- **Buffer Overflows**: Prevents writing beyond the allocated memory buffer.
- **NULL Pointer Dereferences**: Checks for NULL pointers before accessing memory.
- **Memory Leaks**: Ensures proper handling of memory to avoid leaks.
- **Integer Overflows**: Validates integer inputs to prevent overflow errors.
- **Format String Vulnerabilities**: Mitigates risks associated with improper format strings.

By using `Safe Scanf`, developers can perform user input operations more securely and reliably, reducing the risk of common input-related vulnerabilities.

## Features

- **Safe String Input**: Read strings with buffer overflow protection.
- **Safe Integer Input**: Read integers with overflow and conversion error checks.
- **Safe Double Input**: Read floating-point numbers with overflow and conversion error checks.
- **Clear Input Buffer**: Automatically clears the input buffer to prevent residual input from affecting subsequent reads.
- **Comprehensive Error Handling**: Provides distinct error codes for different types of input errors.

## Installation

To use `Safe Scanf` in your project, follow these steps:

1. **Clone the Repository**

   ```bash
   git clone https://github.com/araujo88/safe-scanf.git
   ```

2. **Navigate to the Directory**

   ```bash
   cd safe-scanf
   ```

3. **Include the Header and Source Files**

   - Add `safe_scanf.h` to your project's include directory.
   - Add `safe_scanf.c` to your project's source files.

4. **Compile Your Project**

   When compiling, ensure that `safe_scanf.c` is included. For example:

   ```bash
   gcc -o your_program your_program.c safe_scanf.c
   ```

## Usage

### Including the Library

In your C source file, include the `safe_scanf.h` header:

```c
#include "safe_scanf.h"
```

### Functions

#### `safe_scanf_string`

Safely reads a string with a maximum length.

**Prototype:**

```c
safe_scanf_status safe_scanf_string(char* buffer, size_t buffer_size, size_t* chars_read);
```

**Parameters:**

- `buffer`: Pointer to the buffer where the string will be stored.
- `buffer_size`: Size of the buffer in bytes.
- `chars_read`: Pointer to store the number of characters read.

**Returns:**

- `SAFE_SCANF_SUCCESS` on success.
- Various error codes on failure (e.g., `SAFE_SCANF_BUFFER_OVERFLOW`, `SAFE_SCANF_NULL_PTR`).

#### `safe_scanf_int`

Safely reads an integer value.

**Prototype:**

```c
safe_scanf_status safe_scanf_int(int* value);
```

**Parameters:**

- `value`: Pointer to store the integer value.

**Returns:**

- `SAFE_SCANF_SUCCESS` on success.
- Various error codes on failure (e.g., `SAFE_SCANF_INTEGER_OVERFLOW`, `SAFE_SCANF_CONVERSION_ERROR`).

#### `safe_scanf_double`

Safely reads a double value.

**Prototype:**

```c
safe_scanf_status safe_scanf_double(double* value);
```

**Parameters:**

- `value`: Pointer to store the double value.

**Returns:**

- `SAFE_SCANF_SUCCESS` on success.
- Various error codes on failure (e.g., `SAFE_SCANF_DOUBLE_OVERFLOW`, `SAFE_SCANF_CONVERSION_ERROR`).

### Example

An example program demonstrating the usage of `Safe Scanf` functions.

#### `example.c`

```c
/**
 * example.c - Demonstrates the usage of safe_scanf functions
 */

#include <stdio.h>
#include "safe_scanf.h"

int main() {
    // Reading a string
    char name[50];
    size_t chars_read;
    safe_scanf_status status;

    printf("Enter your name: ");
    status = safe_scanf_string(name, sizeof(name), &chars_read);
    if (status == SAFE_SCANF_SUCCESS) {
        printf("Hello, %s! (%zu chars read)\n", name, chars_read);
    } else if (status == SAFE_SCANF_BUFFER_OVERFLOW) {
        printf("Error: Input exceeded buffer size.\n");
    } else {
        printf("Error reading string: %d\n", status);
    }

    // Reading an integer
    int age;
    printf("Enter your age: ");
    status = safe_scanf_int(&age);
    if (status == SAFE_SCANF_SUCCESS) {
        printf("You are %d years old\n", age);
    } else if (status == SAFE_SCANF_INTEGER_OVERFLOW) {
        printf("Error: Integer value out of range.\n");
    } else if (status == SAFE_SCANF_CONVERSION_ERROR) {
        printf("Error: Invalid integer format.\n");
    } else {
        printf("Error reading integer: %d\n", status);
    }

    // Reading a double
    double height;
    printf("Enter your height in meters: ");
    status = safe_scanf_double(&height);
    if (status == SAFE_SCANF_SUCCESS) {
        printf("You are %.2f meters tall\n", height);
    } else if (status == SAFE_SCANF_DOUBLE_OVERFLOW) {
        printf("Error: Double value out of range.\n");
    } else if (status == SAFE_SCANF_CONVERSION_ERROR) {
        printf("Error: Invalid double format.\n");
    } else {
        printf("Error reading double: %d\n", status);
    }

    return 0;
}
```

**Compilation:**

```bash
gcc -o example example.c safe_scanf.c
```

**Running the Example:**

```bash
./example
```

**Sample Output:**

```
Enter your name: Alice
Hello, Alice! (5 chars read)
Enter your age: 30
You are 30 years old
Enter your height in meters: 1.75
You are 1.75 meters tall
```

## API Reference

### Enumerations

#### `safe_scanf_status`

Return codes for `Safe Scanf` functions.

| Value                         | Description                           |
| ----------------------------- | ------------------------------------- |
| `SAFE_SCANF_SUCCESS`          | Operation successful.                 |
| `SAFE_SCANF_NULL_PTR`         | NULL pointer provided as an argument. |
| `SAFE_SCANF_INVALID_FORMAT`   | Invalid format detected.              |
| `SAFE_SCANF_BUFFER_OVERFLOW`  | Input exceeded buffer size.           |
| `SAFE_SCANF_CONVERSION_ERROR` | Error during conversion.              |
| `SAFE_SCANF_IO_ERROR`         | Input/output error occurred.          |
| `SAFE_SCANF_INTEGER_OVERFLOW` | Integer value out of range.           |
| `SAFE_SCANF_DOUBLE_OVERFLOW`  | Double value out of range.            |

## Contributing

Contributions are welcome! Whether it's reporting bugs, suggesting features, or submitting pull requests, your involvement helps improve `Safe Scanf`. Please follow these steps to contribute:

1. **Fork the Repository**

   Click the "Fork" button at the top-right corner of the repository page to create your own copy.

2. **Clone Your Fork**

   ```bash
   git clone https://github.com/yourusername/safe-scanf.git
   ```

3. **Create a New Branch**

   ```bash
   git checkout -b feature/your-feature-name
   ```

4. **Make Your Changes**

   Implement your changes, ensuring that the code adheres to the project's coding standards and passes all existing tests.

5. **Commit Your Changes**

   ```bash
   git commit -m "Add feature: Your feature description"
   ```

6. **Push to Your Fork**

   ```bash
   git push origin feature/your-feature-name
   ```

7. **Create a Pull Request**

   Navigate to the original repository and create a pull request from your fork's branch. Provide a clear description of your changes and the reasons behind them.

## License

This project is licensed under the [MIT License](LICENSE).
