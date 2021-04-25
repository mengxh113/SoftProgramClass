#include "pch.h"
#include "CppUnitTest.h"
#include "../Test/Calculator.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		//返回“#”优先级
		TEST_METHOD(Priority1)
		{
			Assert::AreEqual(-1, OperatorPriority('#'));
		}
		//返回“(”优先级
		TEST_METHOD(Priority2)
		{
			Assert::AreEqual(0, OperatorPriority('('));
		}
		//返回“+”优先级
		TEST_METHOD(Priority3)
		{
			Assert::AreEqual(1, OperatorPriority('+'));
		}
		//返回“-”优先级
		TEST_METHOD(Priority4)
		{
			Assert::AreEqual(1, OperatorPriority('-'));
		}
		//返回“*”优先级
		TEST_METHOD(Priority5)
		{
			Assert::AreEqual(2, OperatorPriority('*'));
		}
		//返回“/”优先级
		TEST_METHOD(Priority6)
		{
			Assert::AreEqual(2, OperatorPriority('/'));
		}
		//返回“/”优先级
		TEST_METHOD(Priority7)
		{
			Assert::AreEqual(3, OperatorPriority(')'));
		}
		//判断出一年级题目
		TEST_METHOD(OneGrade)
		{
			char* str = "0+14+5";
			Assert::AreEqual(1, main(str));
		}
		//判断出二年级题目
		TEST_METHOD(TwoGrade)
		{
			char* str = "20+29-29";
			Assert::AreEqual(2, main(str));
		}
		//判断出三年级题目
		TEST_METHOD(ThreeGrade)
		{
			char* str = "899+25*4-949";
			Assert::AreEqual(3, main(str));
		}
		//判断出四到六年级年级题目（不缺少符号）
		TEST_METHOD(FourToSixGrade)
		{
			char* str = "10+(20-3)*40/5";
			Assert::AreEqual(46, main(str));
		}
		//判断出四到六年级年级题目（只缺少“+”号）
		TEST_METHOD(FourToSixGrade_ButAdd)
		{
			char* str = "(100-20)*20-150/15";
			Assert::AreEqual(46, main(str));
		}
		//判断出四到六年级年级题目（只缺少“-”号）
		TEST_METHOD(FourToSixGrade_ButSub)
		{
			char* str = "1000*(20+1000)/20";
			Assert::AreEqual(46, main(str));
		}
		//判断出四到六年级年级题目（只缺少“*”号）
		TEST_METHOD(FourToSixGrade_ButMul)
		{
			char* str = "100/((5+20/4)-5)";
			Assert::AreEqual(46, main(str));
		}
		//判断出四到六年级年级题目（只缺少“/”号）
		TEST_METHOD(FourToSixGrade_ButDiv)
		{
			char* str = "(5*4+3*(6+9)-20)";
			Assert::AreEqual(46, main(str));
		}
		//错误10：需要判断优先级的字符不在优先级数组中
		TEST_METHOD(ERROR_10)
		{
			Assert::AreEqual(10, OperatorPriority('='));
		}
		//错误11：出现非法字符错误
		TEST_METHOD(ERROR_11)
		{
			char* str = "2+3,";
			Assert::AreEqual(11, main(str));
		}
		//错误12：运算过程中出现负数
		TEST_METHOD(ERROR_12)
		{
			char* str = "10-20+30";
			Assert::AreEqual(12, main(str));
		}
		//错误12：括号内运算过程中出现负数
		TEST_METHOD(ERROR_12in)
		{
			char* str = "10-20+30";
			Assert::AreEqual(12, main(str));
		}
		//错误13：除0错误
		TEST_METHOD(ERROR_13)
		{
			char* str = "5/0+(2-1)";
			Assert::AreEqual(13, main(str));
		}
		//错误13：括号内除0错误
		TEST_METHOD(ERROR_13in)
		{
			char* str = "10+5/(1-1)";
			Assert::AreEqual(13, main(str));
		}
		//错误14：非法表达式错误
		TEST_METHOD(ERROR_14)
		{
			char* str = "2+-3+5-3";
			Assert::AreEqual(14, main(str));
		}
		//错误14：括号内非法表达式错误
		TEST_METHOD(ERROR_14in)
		{
			char* str = "(+6*5)-5+6";
			Assert::AreEqual(14, main(str));
		}
		//错误15：无法鉴别年级错误：
		//一至二年级之间：运算过程中达到20但没有减法
		TEST_METHOD(ERROR_15_1)
		{
			char* str = "10+3+7";
			Assert::AreEqual(15, main(str));
		}
		//错误15：无法鉴别年级错误：
		//一至二年级之间：没有减法但运算过程达到20
		TEST_METHOD(ERROR_15_2)
		{
			char* str = "30-10-20";
			Assert::AreEqual(15, main(str));
		}
		//错误15：无法鉴别年级错误：
		//二至三年级（或至四到六年级）之间：运算过程中达到50但没有乘法（或除法）
		TEST_METHOD(ERROR_15_3)
		{
			char* str = "10+40-20";
			Assert::AreEqual(15, main(str));
		}
		//错误15：无法鉴别年级错误：
		//三至四到六年级之间：运算过程中达到1000但没有括号
		TEST_METHOD(ERROR_15_4)
		{
			char* str = "100+10*90-100";
			Assert::AreEqual(15, main(str));
		}
		//错误15：无法鉴别年级错误：
		//三至二年级之间：没有加法但有乘法
		TEST_METHOD(ERROR_15_5)
		{
			char* str = "10*90-100";
			Assert::AreEqual(15, main(str));
		}
		//错误15：无法鉴别年级错误：
		//三至二年级之间：没有减法法但有乘法
		TEST_METHOD(ERROR_15_6)
		{
			char* str = "10*90+10";
			Assert::AreEqual(15, main(str));
		}
		//错误15：无法鉴别年级错误：
		//四到六年级至三年级之间：有除法但没有括号
		TEST_METHOD(ERROR_15_7)
		{
			char* str = "10+10*90-100/10";
			Assert::AreEqual(15, main(str));
		}
		//错误15：无法鉴别年级错误：
		//四到六年级至三年级之间：有除法但只有两种运算符
		TEST_METHOD(ERROR_15_8)
		{
			char* str = "10*(10/10)/10";
			Assert::AreEqual(15, main(str));
		}
	};
}
