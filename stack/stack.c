#include "stack.h"

int stack_init(stack_info *stack)// this is return type
{
    stack->top = 0;
    stack->max = 0
    stack->element = NULL;
    return SUCCESS;
}

int stack_push(stack_base *stack, const void *element, int size)
{
    if (stack->top >= stack->max) {
        stack->elements = (void **)realloc(stack->elements, (sizeof(void **) * (stack->max += STACK_BLOCK_SIZE) ));
    }
}
