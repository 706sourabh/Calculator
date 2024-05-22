#include "project.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define USBUART_BUFFER_SIZE (64u)


typedef struct {
    int top;
    int capacity;
    int* array;
} Stack;


Stack* createStack(int capacity) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    if (!stack)
        return NULL;
    stack->top = -1;
    stack->capacity = capacity;
    stack->array = (int*)malloc(stack->capacity * sizeof(int));
    if (!stack->array)
        return NULL;
    return stack;
}


int isEmpty(Stack* stack) {
    return stack->top == -1;
}


void push(Stack* stack, int op) {
    stack->array[++stack->top] = op;
}


int pop(Stack* stack) {
    if (!isEmpty(stack))
        return stack->array[stack->top--];
    return '$';
}


int evaluateExpression(const char* expression) {
    Stack* stack = createStack(strlen(expression));
    if (!stack)
        return -1; 

    int result = 0;
    char lastop = '+';
    int num = 0;

    for (int i = 0; expression[i]; i++) {
        
        if (expression[i] == ' ')
            continue;

        
        if (isdigit(expression[i])) {
            num = num * 10 + (expression[i] - '0');
        }
        
        if (!isdigit(expression[i]) || expression[i + 1] == '\0') {
            
            switch (lastop) {
                case '+':
                    push(stack, num);
                    break;
                case '-':
                    push(stack, -num);
                    break;
                case '*':
                    push(stack, pop(stack) * num);
                    break;
                case '/':
                    push(stack, pop(stack) / num);
                    break;
            }
            num = 0;
            lastop = expression[i];
        }
    }

    while (!isEmpty(stack)) {
        result += pop(stack);
    }

    free(stack->array);
    free(stack);

    return result;
}

int main(void)
{
    CyGlobalIntEnable; 
    USBUART_Start(0, USBUART_3V_OPERATION); 
    
    LCD_Start(); 
    LCD_Position(0, 0);
    LCD_PrintString("ENTER EXPRESSION");
    
    uint16 count = 0;
    
    //uint8 buffer[USBUART_BUFFER_SIZE];
    char expression[USBUART_BUFFER_SIZE]; 
    memset(expression, 0, sizeof(expression)); 
    
    for (;;)
    {
        if(0u != USBUART_IsConfigurationChanged())
        {
            if(0u != USBUART_GetConfiguration())
            {
                USBUART_CDC_Init();
            }
        }
        
        if(0u != USBUART_GetConfiguration())
        {
            if(0u != USBUART_DataIsReady())
            {
                char rcv = USBUART_GetChar();
                LCD_Position(1, 0);
                LCD_PutChar(rcv);
                
                if(0u != rcv)
                {
                    
                    
                    if (rcv == '=')
                    {
                        expression[count++] = '=';
                        expression[count++] = '\0';
                        
                        LCD_Position(1, 0);
                        LCD_PrintString(expression);
			            //for(int j=0;j<1000;j++);
                        int result = evaluateExpression(expression);
                        LCD_PrintNumber(result);
    			        printf("Result of %s = %d\n", expression, result);
                        
                        memset(expression, 0, sizeof(expression));
                        count = 0;
                    }
                    else
                    {
                        
                        LCD_ClearDisplay();
                        LCD_PrintString("ENTER EXPRESSION");
                        expression[count++] = rcv;
                    }
                }  
            }
        }
    }
}
