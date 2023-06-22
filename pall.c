#include "monty.h"

/**
 * pall - Prints all the values on the stack, starting from the top.
 * @stack: Double pointer to the head of the stack.
 * @line_number: Line number being executed from the Monty file.
 */
void pall(stack_t **stack, unsigned int line_number)
{
    stack_t *temp;

    (void)line_number;

    temp = *stack;
    while (temp)
    {
        printf("%d\n", temp->n);
        temp = temp->next;
    }
}