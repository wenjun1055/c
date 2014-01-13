#include <stdio.h>
#include <stdlib.h>

typedef struct _stack {
    int top;
    int max;
    void **elements;
} stack_base;


#define SUCCESS                     0
#define FAILURE                     -1
#define STACK_BLOCK_SIZE            64
#define ZEND_STACK_APPLY_TOPDOWN    1
#define ZEND_STACK_APPLY_BOTTOMUP   2

int stack_init(stack_base *stack);
int stack_push(stack_base *stack, const void *element, int size);
int stack_top(const stack_base *stack, void **element);
int stack_del_top(stack_base *stack);
int stack_int_top(const stack_base *stack);
int stack_is_empty(const stack_base *stack);
int stack_destroy(stack_base *stack);
void **stack_base(const stack_base *stack);
int stack_count(const stack_base *stack);
void stack_apply(stack_base *stack, int type, int (*apply_function)(void *element));
void stack_apply_with_argument(stack_base *stack, int type, int (*apply_function)(void *element, void *arg), void *arg);
