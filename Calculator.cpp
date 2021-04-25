#include<stdio.h>
#include<string.h>
#include "Calculator.h"
#define ni ExpressionIndex
#define ri OperatorIndex
#define di OperandIndex
//存放操作符字符以及优先级的数组
const char Operator_Sign[7] = { '#','(','+','-','*','/',')' };
const int Operator_Priority[7] = { -1,0,1,1,2,2,3 };
int OperatorPriority(char ch)
{
	//返回指定字符对应操作数优先级
	for (int i = 0;i < 7;i++)
	{
		if (ch == Operator_Sign[i])
		{
			return Operator_Priority[i];
		}
	}
	//ERROR10:需要判断优先级的字符不在优先级数组中
	printf("错误");
	return 10;
}
int main()
{
	char Expression[100];//存放表达式字符数组
	char Operators[50] = { NULL };//存放操作符字符数组
	int Operands[50] = { 0 };//存放操作数字符数组
	int ExpressionIndex = 0;//存放表达式数组下标
	int OperatorIndex = 0;//存放操作符数组下标
	int OperandIndex = 0;//存放操作数数组下标
	int CountOperator = 0;//计算操作符种类数量
	int OperatorSign[4] = { 0 };//操作符种类数量判别位
	int GradeSign[4] = { 1,1,1,1 };//年级题目判别位
	scanf("%s",Expression);//表达式字符输入
	ni = strlen(Expression);//计算字符串长度
	Expression[ni++] = '#';
	Expression[ni] = '\0';//表达式串末尾添加#和"\0"
	Operators[ri++] = '#';//操作符栈底添加#
	for (int i = 0;i < ni;i++)
	{
		//表达式分析
		if (Expression[i] >= '0' && Expression[i] <= '9')
		{
			//扫描字符为数字
			Operands[di] = Operands[di] * 10 + Expression[i] - '0';
			if (Expression[i + 1] < '0' || Expression[i + 1] > '9')
			{
				di++;
			}
		}
		else
		{
			//扫描字符为非数字（操作符或错误字符）
			switch (Expression[i])
			{
			case '/':
				//出现除法运算排除一二三年级题目可能
				GradeSign[2] = 0;
			case '*':
				//出现乘法法运算排除一二年级题目可能
				GradeSign[1] = 0;
				GradeSign[0] = 0;
			case '-':
			case '+':
			case '#':
				while (OperatorPriority(Expression[i]) <= OperatorPriority(Operators[ri - 1]))
				{
					if (di < 2)
					{
						if (Expression[i] == Operators[0] && Operators[1] == NULL)
						{
							//扫描结束
							for (int i = 0;i < 4;i++)
								CountOperator += OperatorSign[i];
							if (CountOperator == 1 && GradeSign[0])
							{
								printf("一年级");
								return 1;
							}
							else if (CountOperator == 2 && GradeSign[1])
							{
								printf("二年级");
								return 2;
							}
							else if (CountOperator == 3 && GradeSign[2])
							{
								printf("三年级");
								return 3;
							}
							else if (CountOperator >= 3 && GradeSign[3] >= 2)
							{
								printf("四到六年级");
								return 46;
							}
							else
							{
								//ERROR15:题目不属于上述各年级要求
								printf("错误");
								return 15;
							}
						}
						else
						{
							//ERROR14:非法表达式错误
							printf("错误");
							return 14;
						}
					}
					switch (Operators[ri - 1])
					{
					case '+':
						Operands[di - 2] += Operands[di - 1];
						OperatorSign[3] = 1;
						break;
					case '-':
						Operands[di - 2] -= Operands[di - 1];
						OperatorSign[2] = 1;
						break;
					case '*':
						Operands[di - 2] *= Operands[di - 1];
						OperatorSign[1] = 1;
						break;
					case '/':
						if ((Operands[di - 1]) == 0)
						{
							//ERROR13:除0错误
							printf("错误");
							return 13;
						}
						Operands[di - 2] /= Operands[di - 1];
						OperatorSign[0] = 1;
						break;
					}
					if (Operands[di - 2] < 0)
					{
						//ERROR12:运算过程中出现负数
						printf("错误");
						return 12;
					}
					else if (Operands[di - 2] >= 1000)
					{
						//运算过程出现达到1000的数排除一二三年级题目可能
						GradeSign[0] = 0;
						GradeSign[1] = 0;
						GradeSign[2] = 0;
					}
					else if (Operands[di - 2] >= 50)
					{
						//运算过程出现达到50的数排除一二年级题目可能
						GradeSign[0] = 0;
						GradeSign[1] = 0;
					}
					else if (Operands[di - 2] >= 20)
					{
						//运算过程出现达到20的数排除一年级题目可能
						GradeSign[0] = 0;
					}
					Operands[--di] = 0;
					Operators[--ri] = NULL;
				}
				Operators[ri++] = Expression[i];
				break;
			case '(':
				//出现括号排除一二三年级题目可能性并保证四到六年级题目可能性
				GradeSign[3] *= 2;
				GradeSign[2] = 0;
				GradeSign[1] = 0;
				GradeSign[0] = 0;
				Operators[ri++] = Expression[i];
				break;
			case ')':
				while (Operators[ri - 1] != '(')
				{
					if (di < 2)
					{
						//ERROR14:括号内非法表达式错误
						printf("错误");
						return 14;
					}
					switch (Operators[ri - 1])
					{
					case '+':
						Operands[di - 2] += Operands[di - 1];
						OperatorSign[3] = 1;
						break;
					case '-':
						Operands[di - 2] -= Operands[di - 1];
						OperatorSign[2] = 1;
						break;
					case '*':
						Operands[di - 2] *= Operands[di - 1];
						OperatorSign[1] = 1;
						break;
					case '/':
						if ((Operands[di - 1]) == 0)
						{
							//ERROR13:括号内除0错误
							printf("错误");
							return 13;
						}
						Operands[di - 2] /= Operands[di - 1];
						OperatorSign[0] = 1;
						break;
					}
					if (Operands[di - 2] < 0)
					{
						//ERROR12:括号内运算过程中出现负数
						printf("错误");
						return 12;
					}
					else if (Operands[di - 2] >= 1000)
					{
						//运算过程出现超过1000的数排除一二三年级题目可能
						GradeSign[0] = 0;
						GradeSign[1] = 0;
						GradeSign[2] = 0;
					}
					else if (Operands[di - 2] >= 50)
					{
						//运算过程出现超过50的数排除一二年级题目可能
						GradeSign[0] = 0;
						GradeSign[1] = 0;
					}
					else if (Operands[di - 2] >= 20)
					{
						//运算过程出现超过20的数排除一年级题目可能
						GradeSign[0] = 0;
					}
					Operands[--di] = 0;
					Operators[--ri] = NULL;
				}
				Operators[--ri] = NULL;//左括号弹出栈
				break;
			default:
				//ERROR11:出现非法字符错误
				printf("错误");
				return 11;
			}
		}
	}
}
