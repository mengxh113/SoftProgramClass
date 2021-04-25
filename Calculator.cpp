#include<stdio.h>
#include<string.h>
#include "Calculator.h"
#define ni ExpressionIndex
#define ri OperatorIndex
#define di OperandIndex
//��Ų������ַ��Լ����ȼ�������
const char Operator_Sign[7] = { '#','(','+','-','*','/',')' };
const int Operator_Priority[7] = { -1,0,1,1,2,2,3 };
int OperatorPriority(char ch)
{
	//����ָ���ַ���Ӧ���������ȼ�
	for (int i = 0;i < 7;i++)
	{
		if (ch == Operator_Sign[i])
		{
			return Operator_Priority[i];
		}
	}
	//ERROR10:��Ҫ�ж����ȼ����ַ��������ȼ�������
	printf("����");
	return 10;
}
int main()
{
	char Expression[100];//��ű��ʽ�ַ�����
	char Operators[50] = { NULL };//��Ų������ַ�����
	int Operands[50] = { 0 };//��Ų������ַ�����
	int ExpressionIndex = 0;//��ű��ʽ�����±�
	int OperatorIndex = 0;//��Ų����������±�
	int OperandIndex = 0;//��Ų����������±�
	int CountOperator = 0;//�����������������
	int OperatorSign[4] = { 0 };//���������������б�λ
	int GradeSign[4] = { 1,1,1,1 };//�꼶��Ŀ�б�λ
	scanf("%s",Expression);//���ʽ�ַ�����
	ni = strlen(Expression);//�����ַ�������
	Expression[ni++] = '#';
	Expression[ni] = '\0';//���ʽ��ĩβ���#��"\0"
	Operators[ri++] = '#';//������ջ�����#
	for (int i = 0;i < ni;i++)
	{
		//���ʽ����
		if (Expression[i] >= '0' && Expression[i] <= '9')
		{
			//ɨ���ַ�Ϊ����
			Operands[di] = Operands[di] * 10 + Expression[i] - '0';
			if (Expression[i + 1] < '0' || Expression[i + 1] > '9')
			{
				di++;
			}
		}
		else
		{
			//ɨ���ַ�Ϊ�����֣�������������ַ���
			switch (Expression[i])
			{
			case '/':
				//���ֳ��������ų�һ�����꼶��Ŀ����
				GradeSign[2] = 0;
			case '*':
				//���ֳ˷��������ų�һ���꼶��Ŀ����
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
							//ɨ�����
							for (int i = 0;i < 4;i++)
								CountOperator += OperatorSign[i];
							if (CountOperator == 1 && GradeSign[0])
							{
								printf("һ�꼶");
								return 1;
							}
							else if (CountOperator == 2 && GradeSign[1])
							{
								printf("���꼶");
								return 2;
							}
							else if (CountOperator == 3 && GradeSign[2])
							{
								printf("���꼶");
								return 3;
							}
							else if (CountOperator >= 3 && GradeSign[3] >= 2)
							{
								printf("�ĵ����꼶");
								return 46;
							}
							else
							{
								//ERROR15:��Ŀ�������������꼶Ҫ��
								printf("����");
								return 15;
							}
						}
						else
						{
							//ERROR14:�Ƿ����ʽ����
							printf("����");
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
							//ERROR13:��0����
							printf("����");
							return 13;
						}
						Operands[di - 2] /= Operands[di - 1];
						OperatorSign[0] = 1;
						break;
					}
					if (Operands[di - 2] < 0)
					{
						//ERROR12:��������г��ָ���
						printf("����");
						return 12;
					}
					else if (Operands[di - 2] >= 1000)
					{
						//������̳��ִﵽ1000�����ų�һ�����꼶��Ŀ����
						GradeSign[0] = 0;
						GradeSign[1] = 0;
						GradeSign[2] = 0;
					}
					else if (Operands[di - 2] >= 50)
					{
						//������̳��ִﵽ50�����ų�һ���꼶��Ŀ����
						GradeSign[0] = 0;
						GradeSign[1] = 0;
					}
					else if (Operands[di - 2] >= 20)
					{
						//������̳��ִﵽ20�����ų�һ�꼶��Ŀ����
						GradeSign[0] = 0;
					}
					Operands[--di] = 0;
					Operators[--ri] = NULL;
				}
				Operators[ri++] = Expression[i];
				break;
			case '(':
				//���������ų�һ�����꼶��Ŀ�����Բ���֤�ĵ����꼶��Ŀ������
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
						//ERROR14:�����ڷǷ����ʽ����
						printf("����");
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
							//ERROR13:�����ڳ�0����
							printf("����");
							return 13;
						}
						Operands[di - 2] /= Operands[di - 1];
						OperatorSign[0] = 1;
						break;
					}
					if (Operands[di - 2] < 0)
					{
						//ERROR12:��������������г��ָ���
						printf("����");
						return 12;
					}
					else if (Operands[di - 2] >= 1000)
					{
						//������̳��ֳ���1000�����ų�һ�����꼶��Ŀ����
						GradeSign[0] = 0;
						GradeSign[1] = 0;
						GradeSign[2] = 0;
					}
					else if (Operands[di - 2] >= 50)
					{
						//������̳��ֳ���50�����ų�һ���꼶��Ŀ����
						GradeSign[0] = 0;
						GradeSign[1] = 0;
					}
					else if (Operands[di - 2] >= 20)
					{
						//������̳��ֳ���20�����ų�һ�꼶��Ŀ����
						GradeSign[0] = 0;
					}
					Operands[--di] = 0;
					Operators[--ri] = NULL;
				}
				Operators[--ri] = NULL;//�����ŵ���ջ
				break;
			default:
				//ERROR11:���ַǷ��ַ�����
				printf("����");
				return 11;
			}
		}
	}
}
