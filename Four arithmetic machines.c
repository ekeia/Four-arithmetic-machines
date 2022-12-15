/**********************************************************************
Description: Four operations up to six digits, including priority.
wirte by github：ekeia
hanyang university ercia:2020003927 
***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100
 
typedef struct stack1                      //numbers stack
{
	double num[MAX];
	int top; 
}O_NUM;
 
typedef struct stack2                      //Symbols stack
{
	char symbol[MAX];
	int top;
}O_SY;
 
/**********************************************************************
Description: Initializes the data and symbol stacks
Parameters: O_NUM *stacknum,O_SY *stacksymbol
Return value: void
***********************************************************************/
void init_O_NUM(O_NUM *stacknum)                //init numbers stack
{
	stacknum->top = -1;
}
 
void init_O_SY(O_SY *stacksymbol)               //init Symbols stack
{
	stacksymbol->top = -1;
}
/*************************************************************************
Description: Pushes operands into the operand stack
Parameters: O_NUM *stacknum,double num
Return value :int
**************************************************************************/
int PUSH_Stacknum(O_NUM *stacknum,double num)
{
	if(stacknum->top == MAX-1)
	{
		printf("error,out of max range!\n");
		return -1;
	}
	stacknum->top++;
	stacknum->num[stacknum->top] = num;
	return 0;
}
/***************************************************************************
Description: Pushes a symbol into a symbol stack
Parameters: O_SY *stacksymbol, char ch
Return value: int
***************************************************************************/
int PUSH_Stacksymbol(O_SY *stacksymbol,char ch)
{
	if(stacksymbol->top == MAX-1)
	{
		printf("Error，Out of max range!\n");
		return -1;
	}
	stacksymbol->top++;
	stacksymbol->symbol[stacksymbol->top] = ch;
	return 0;
}
/***************************************************************************
Fetch data from the operand stack
Parameters: O_NUM *stacknum
Return value :double
***************************************************************************/
double POP_Stacknum(O_NUM *stacknum)
{
	double data = 0;
	data = stacknum->num[stacknum->top];
	stacknum->top--;
	return data;
}
/**************************************************************************
Fetch data from symbol stack
Parameters: O_SY *stacksymbol
Return value :char
**************************************************************************/
char POP_Stacksymbol(O_SY *stacksymbol)
{
	char ch;
	ch = stacksymbol->symbol[stacksymbol->top];
	stacksymbol->top--;
	return ch;
}
/*************************************************************************
Define the function judge_symbol to determine whether the number of operators is correct
Parameter: char ch
Return values: 1 (Yes), 0 (No)
*************************************************************************/
int judge_symbol(char ch)
{
	if(ch == '+'||ch == '-'||ch == '*'|| ch == '/'||ch == '('||ch == ')'||ch == '='||ch == '\n')
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
/*************************************************************************
Description: Determines the precedence of the operator versus the top of the stack operator
Parameters :char t1,char t2.
t1 is the pointer at the top of the stack and t2 is the pointer compared to the top of the stack
Return value :char
**************************************************************************/
char op_campare(char t1,char t2)
{
	char ch;
	switch(t2)
	{
		case '+':
		case '-':
		{
			ch = (t1 == '('||t1 == '=')?'<':'>';
			break;
		}
		case '*':
		case '/':
		{
			ch = (t1 == '*'||t1 == '/' ||t1 == ')')?'>':'<';
			break;
		}
		case '(':
		{
		 	if(t1 == ')')
		 	{
				printf("input error\n");
				return -1;
		 	}
			else
			{
				ch = '<';
			}
			break;
		}
		case ')':
		{
			switch(t1)
			{
				case '(':
				{
					ch = '=';
					break;
				}
				case '=':
				{
					printf("error input\n");
					exit(0);
				}
				default:ch = '>';
			}
			break;
		}
		case '=':
		{
			switch(t1)
			{
				case '=':
				{
					ch = '=';
					break;
				}
				case '(':
				{
					printf("error input!\n");
					return -1;
				}
				default:ch = '>';
			}
		}
	}
	return ch;
}
/**********************************************************************
Description: Simple computing features
Parameters :double num1,char op,double num2
Return value :double
***********************************************************************/
double calculate(double num1,char op,double num2)
{
	double result;
	switch(op)
	{
		case '+':
		{
			result = num1 + num2;
			break;
		}
		case '-':
		{
			result = num1 - num2;
			break;
		}
		case '*':
		{
			result = num1 * num2;
			break;
		}
		case '/':
		{
			if(num2 == 0)
			{
				printf("error input!\n");
				return -1;
			}
			else
			{
				result = num1/num2;
			}
		}
	}
	return result;
}
/**************************************************************************
The description is used to get user input and perform calculations
Parameter :void
Return value :double result
***************************************************************************/
double MainCalc()
{
	O_NUM stacknum;                               //number
	O_SY stacksymbol;                             //symbol
	double num1,num2,result,num;
	char ch,sign;
	char *str = NULL; 
	int count = 0;
 
	init_O_NUM(&stacknum);                        //init
	init_O_SY(&stacksymbol);
 
	//Evaluates '=' to the operator stack
	PUSH_Stacksymbol(&stacksymbol,'=');
	ch = getchar();                              //get char from keyboard
	while((ch != '=')||stacksymbol.symbol[stacksymbol.top] != '=')
	{
		if(judge_symbol(ch) == 0)
		{   
			str = (char *)malloc(sizeof(char)*MAX); 
			do
			{
				*str = ch;
				str++;
				count++;
				ch = getchar();
			}while(judge_symbol(ch) == 0);
			*str = '\0';

			str = str - count;
			printf(str);
			//double *numtest = NULL;
			//numtest = (char *)malloc(sizeof(char)*MAX); 
			num = atof(str);                     //warning:Converts string to float number, but "atof" only holds six digits, so it is discarded.
			//numtest = strtod(str,NULL);
			printf("%g\n",num);
			PUSH_Stacknum(&stacknum,num);        //将数推进操作数栈中
			
			str = NULL;
		
			count = 0;
		}
		else
		{
			switch(op_campare(stacksymbol.symbol[stacksymbol.top],ch))
			{
				case '<':
				{
					PUSH_Stacksymbol(&stacksymbol,ch);
					ch = getchar();
					break;
				}
				case '=':
				{
					sign = POP_Stacksymbol(&stacksymbol);
					ch = getchar();
					break;
				}
				case '>':
				{
					sign = POP_Stacksymbol(&stacksymbol);
					num2 = POP_Stacknum(&stacknum);
					num1 = POP_Stacknum(&stacknum);
					printf(" 1 %g\n",num1);
					printf(" 2 %g\n",num2);
					result = calculate(num1,sign,num2);
					printf(" > %g\n",result);
					PUSH_Stacknum(&stacknum,result);
					break;
				}
			}
		}
	}
	
	result = stacknum.num[stacknum.top];
	return result;
}
 
int main()
{
	double result;
 
	result = MainCalc();
	printf("%g\n",result);
	return 0;
}
