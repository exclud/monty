#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "monty.h"

#define BUFFER_SIZE 1024

int main(int argc, char *argv[])
{
    FILE *file;
    char line[BUFFER_SIZE];
    char *opcode;
    unsigned int line_number = 0;
    stack_t *stack = NULL;

    if (argc != 2)
    {
        fprintf(stderr, "Usage: monty file\n");
        exit(EXIT_FAILURE);
    }

    file = fopen(argv[1], "r");
    if (file == NULL)
    {
        fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    while (fgets(line, BUFFER_SIZE, file) != NULL)
    {
        line_number++;
        /* Remove trailing newline character if present */
        if (line[strlen(line) - 1] == '\n')
            line[strlen(line) - 1] = '\0';

        /* Tokenize the line */
        opcode = strtok_r(line, " ", &line);
        if (opcode != NULL && opcode[0] != '#')
        {
            if (strcmp(opcode, "push") == 0)
                push(&stack, line_number);
            else if (strcmp(opcode, "pall") == 0)
                pall(&stack, line_number);
            else
            {
                fprintf(stderr, "L%d: unknown instruction %s\n", line_number, opcode);
                exit(EXIT_FAILURE);
            }
        }
    }

    fclose(file);

    /* Free the stack */
    while (stack != NULL)
    {
        stack_t *temp = stack;
        stack = stack->next;
        free(temp);
    }

    return 0;
}
