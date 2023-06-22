#include "monty.h"

#define MAX_LINE_LENGTH 1024

int main(int argc, char *argv[])
{
    FILE *file;
    char line[MAX_LINE_LENGTH];
    unsigned int line_number = 0;
    stack_t *stack = NULL;
    instruction_t instructions[] = {
        {"push", push},
        {"pall", pall},
        {NULL, NULL}
    };
    
    char *opcode;
    char *arg;

    if (argc != 2)
    {
        fprintf(stderr, "Usage: monty file\n");
        exit(EXIT_FAILURE);
    }

    file = fopen(argv[1], "r");
    if (!file)
    {
        fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    while (fgets(line, sizeof(line), file))
    {
        line_number++;
        /* Tokenize line into opcode and argument */
        opcode = strtok(line, " \t\n");
        arg = strtok(NULL, " \t\n");

        if (opcode)
        {
            int i = 0;
            while (instructions[i].opcode)
            {
                if (strcmp(opcode, instructions[i].opcode) == 0)
                {
                    if (arg)
                        instructions[i].f(&stack, line_number);
                    else
                    {
                        fprintf(stderr, "L%u: usage: %s integer\n", line_number, opcode);
                        exit(EXIT_FAILURE);
                    }
                    break;
                }
                i++;
            }
            if (!instructions[i].opcode)
            {
                fprintf(stderr, "L%u: unknown instruction %s\n", line_number, opcode);
                exit(EXIT_FAILURE);
            }
        }
    }

    fclose(file);
    /* Free the stack */
    while (stack)
    {
        stack_t *temp = stack;
        stack = stack->next;
        free(temp);
    }

    return 0;
}
