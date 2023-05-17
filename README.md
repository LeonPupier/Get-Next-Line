# Get Next Line

This project was completed as part of the curriculum at École 42. The goal of the project is to implement a function that reads a line from a file descriptor, and to learn about memory allocation and file manipulation in the process.

## Installation

To use the `get_next_line` function in your own projects, follow these steps:

1. Clone the repository to your local machine.
2. Open a terminal window and navigate to the root directory of the project.
3. Run the command `make` to compile the library.
4. Include the header file `get_next_line.h` in your source code. 

## Usage

The `get_next_line` function reads a line from a file descriptor, up to a specified delimiter (which defaults to the newline character). The function returns a pointer to a string containing the line read from the file, or `NULL` if there is no more data to read.

To use the function, simply call it with the file descriptor you want to read from, like this:

```c
#include <stdio.h>
#include "get_next_line.h"

int main()
{
    int fd = open("file.txt", O_RDONLY);
    char *line;

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s\n", line);
        free(line);
    }

    close(fd);
    return 0;
}
```

In this example, the `get_next_line` function is used to read lines from a file, which are then printed to the screen using `printf`.

## Credits

This project was completed by Léon Pupier (lpupier) as part of the curriculum at École 42.
