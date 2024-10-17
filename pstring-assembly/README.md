# String Manipulation Program

## Overview
This program is designed to perform various string manipulation tasks. The user can choose from a menu of options, which include calculating the length of a string, swapping the case of characters, and copying a substring. Each operation will prompt the user for input and display the result.

## User Instructions
1. **Run the program**: Execute the program in your environment.
2. **Choose an option**: A menu will be displayed with the following choices:
   - Option 1: Calculate Length
   - Option 2: Swap Case
   - Option 3: Copy Substring
   - Option 4: Exit
3. **Provide input**: Based on the selected option, enter the required string or indices when prompted.
4. **View the output**: The program will display the result of the selected operation.
5. **Repeat or exit**: You can choose another option or exit the program.

### Expected Output
- If you choose **Option 1** and input the string `"Hello, World!"`, the output will be:

- If you choose **Option 2** and input the string `"Hello, World!"`, the output will be:

- If you choose **Option 3** and input the string `"Hello, World!"`, along with indices `0` and `4`, the output will be:

- If you choose **Option 4**, the program will exit.

## File Descriptions

## 1. `main.c`

- **Description**: This is the main entry point of the program.
- **Functionality**:
- Displays the menu options to the user.
- Reads the user's selection and calls the appropriate string manipulation function based on that selection.
- Handles user input and provides feedback if the input is invalid.

## 2. `func_select.s`

This assembly program provides several string manipulation operations based on user input. The user can choose to:
1. Calculate the lengths of two strings.
2. Swap the cases of characters in two strings.
3. Copy a substring from one string to another based on user-defined indices.

## Expected User Actions
- The user is prompted to enter an option (31, 33, or 34).
- Depending on the chosen option:
  - For option **31**, the user must provide two strings, and the program will print their lengths.
  - For option **33**, the program will swap the cases of characters in the two strings and print the results.
  - For option **34**, the user is prompted to enter two indices to specify a substring to copy from one string to another.

## Section Descriptions

### 1. **.rodata Section**
This section contains read-only data, which includes string literals used for output formatting:
- **`invalid_input_fmt`**: 
  - Format: `"invalid option!\n"`
  - Purpose: Displays an error message when an invalid option is selected.

- **`len_fmt`**: 
  - Format: `"first pstring length: %d, second pstring length: %d\n"`
  - Purpose: Displays the lengths of two strings.

- **`func2_fmt`**: 
  - Format: `"length: %d, string: %s\n"`
  - Purpose: Displays the length and content of a string.

- **`scanf_fmt`**: 
  - Format: `" %d %d"`
  - Purpose: Used to read two integer inputs from the user.

### 2. **.text Section**
This section contains the executable code. The program begins execution from the `run_func` label.

### 3. **Function: run_func**
- **Stack Frame Setup**: 
  - The function sets up the stack frame by pushing the base pointer (`%rbp`) onto the stack and updating the base pointer with the current stack pointer (`%rsp`).

- **Choice Handling**: 
  - The function checks the value in the `edi` register (the user's menu choice) against specific values:
    - **31**: Calls the `pstrlen` function to calculate the lengths of the two strings and prints them.
    - **33**: Calls `swapCase` to swap the cases of the characters in the two strings and prints the results.
    - **34**: Copies a substring from the second string to the first string based on user-defined indices.

- **Error Handling**: 
  - If the option is not recognized, the program prints an invalid option message and exits.

### 4. **Sub-functions**
- **Length Calculation (`.pstr_len`)**:
  - Uses the `pstrlen` function to determine the lengths of the provided strings and prints them using the `printf` function.

- **Case Swapping (`.swap_case`)**:
  - Calculates the lengths of the two strings, calls `swapCase` for both strings to change their character cases, and prints the modified strings.

- **Substring Copying (`.cpy_str`)**:
  - Prompts the user for indices, validates the input, and calls `pstrijcpy` to copy a substring from the second string to the first string. It also handles invalid input by printing error messages and the original strings.

### 5. **Exit Sequence**
The program concludes by cleaning up the stack and returning control to the caller.

## Summary
This assembly program provides a user-interactive way to perform string manipulations such as length calculation, case swapping, and substring copying. Proper error handling ensures that invalid user inputs are managed gracefully.

## 3. `pstring.s`

This code defines three functions for string manipulation: `pstrlen`, `swapCase`, and `pstrijcpy`.

## 1. `pstrlen`

**Purpose**: Calculate the length of a null-terminated string.

### Key Points:
- Initializes a length counter to 0.
- Loops through each character until the null terminator is reached, incrementing the counter.
- Returns the length in the `%eax` register.

## 2. `swapCase`

**Purpose**: Swap the case of alphabetic characters in a string.

### Key Points:
- Checks each character's ASCII value.
- Converts lowercase letters to uppercase by subtracting `32` and vice versa by adding `32`.
- Continues until a null terminator is encountered.

## 3. `pstrijcpy`

**Purpose**: Copy a portion of one string to another based on provided indices.

### Key Points:
- Skips the first `k` characters from the source string.
- Copies characters from the source to the destination until a specified end index is reached.
- Returns the pointer to the destination string.

These functions demonstrate basic string manipulation techniques in x86-64 assembly.
