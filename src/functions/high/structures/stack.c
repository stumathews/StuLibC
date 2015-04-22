#include "stack.h"

Stack* newStack(int size)
{
    if (size < 5){
        size = 5;
    }
    Stack* stack = malloc(sizeof(Stack));
    stack->container = malloc(sizeof(void**) * size);
    stack->counter = 0;
    stack->max = size;
    return stack;
}

void freeStack(Stack* stack)
{
    free(stack->container);
    free(stack);
}

int getSize(Stack* stack)
{
    return stack->counter;
}

int getMax(Stack* stack)
{
    return stack->max;
}

int isEmpty(Stack* stack)
{
    if(stack->counter == 0)
        return 1;
    return 0;
}

void** resizeContainer(Stack* stack)
{
    void** tmpContainer = malloc(sizeof(void**) * stack->max * 2);
    memcpy( tmpContainer, stack->container, sizeof(void**)*stack->max);
    stack->max *= 2;
    return tmpContainer;
}

void trace(Stack* stack)
{
    int i;
    for(i = stack->counter - 1; i >= 0; i--)
    printf("%d: %p \n", i, stack->container[i]);
}

int search(void* value, Stack* stack)
{
    int i;
    for(i = stack->counter - 1; i >= 0; i--)
    {
    
    if(stack->container[i] == value)
        return i;
    }
    return -1;
}

void* peek(Stack* stack)
{
    if (stack->counter > 0)
    {
        return stack->container[stack->counter - 1];
    }
    fprintf(stderr, "stack counter is 0... can't peek an empty stack.");
    return NULL;
}

void push(void* item, Stack* stack)
{
    if (stack->counter == stack->max)
        stack->container = resizeContainer(stack);
    
    stack->container[stack->counter] = item;
    stack->counter++;
}

void* pop(Stack* stack)
{
    if (stack->counter > 0){
        stack->counter--;
        return stack->container[stack->counter];
    }
    fprintf(stderr, "stack counter is 0... can't pop an empty stack.");
    return NULL;
}

