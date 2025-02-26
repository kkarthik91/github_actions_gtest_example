// #include "StringCalculator.h"

#include <string>
#include <vector>
#include <numeric>
#include <regex>
#include <gtest/gtest.h>

using namespace testing;
using namespace std;

class StringCalculator {
public:
	int Add(const string &input);
};


class GetNegatives {
private:
	string negatives;

public:
	void operator()(int i) {
		if (i < 0)
			negatives.append(to_string(i) + ",");
	}

	operator string() {
		if (negatives.length() > 0)
			negatives.pop_back();

		return negatives;
	}
};

void check_for_negatives(const vector<int> &numbers) {
	string negatives = for_each(numbers.begin(), numbers.end(), GetNegatives());

	if (negatives.size() > 0) {
		throw invalid_argument("Negatives not allowed: " + negatives);
	}
}

void add_if_valid(vector<int> &numbers, string number_string) {
	int number = stoi(number_string);
	if (number <= 1000)
		numbers.push_back(number);
}

vector<int> get_numbers(const string &input) {
	regex numbers_only("(-?\\d+)+");

	vector<int> numbers;
	for_each(sregex_token_iterator(input.begin(), input.end(), numbers_only),
				sregex_token_iterator(),
				[&numbers](string s) { add_if_valid(numbers, s); });

	return numbers;
}

int StringCalculator::Add(const string &input) {
	if (input.empty())
		return 0;

	vector<int> numbers = get_numbers(input);

	check_for_negatives(numbers);

	return accumulate(numbers.begin(), numbers.end(), 0);
}

//Test fixture
class string_calculator_add:public TestWithParam<std::tuple<string,int>>{
protected:
	//Arrange //creating object for 4 test cases
	StringCalculator ObjUnderTest;
};

TEST_P(string_calculator_add, AssertAddOperation){
	const std:tuple<string,int> & parameter = GetParam();
	string input = std::get<0>(parameter);
	int expectedValue = std::get<1>(parameter);
	int actualValue = ObjUnderTest.Add(input);
}
INSTANTIATE_TEST_SUITE_P(
	StringCalcualtorParameterTest,
	string_calculator_add,
	Values(
		std::make_tuple("", 0),
		std::make_tuple("1", 1),
		std::make_tuple("1,2", 3),
		std::make_tuple("1,2,3", 6),
	));

// TEST_F(string_calculator_add,When_passed_A_Single_Number_returns_0_for_empty_string){
// 	//Arrange
// 	// StringCalculator ObjUnderTest;
// 	string input = " ";
// 	int expectedValue=0;
	
// 	//Act
// 	int actualValue=ObjUnderTest.Add(input);

// 	//Assert
// 	ASSERT_EQ(actualValue,expectedValue);
// }

// TEST_F(string_calculator_add,When_passed_A_Single_Number_returns_1_for_string_1){
// 	//Arrange
// 	// StringCalculator ObjUnderTest;
// 	string input = "1";
// 	int expectedValue=1;

// 	//Act
// 	int actualValue=ObjUnderTest.Add(input);

// 	//Assert
// 	ASSERT_EQ(actualValue,expectedValue);
// }

// TEST_F(string_calculator_add,When_passed_A_Single_Number_returns_3_for_string_1_2){
// 	//Arrange
// 	// StringCalculator ObjUnderTest;
// 	string input = "1,2";
// 	int expectedValue=3;
	
// 	//Act
// 	int actualValue=ObjUnderTest.Add(input);

// 	//Assert
// 	ASSERT_EQ(actualValue,expectedValue);
// }
// TEST_F(string_calculator_add,When_passed_A_Single_Number_returns_6_for_string_1_2_3){
// 	//Arrange
// 	// StringCalculator ObjUnderTest;
// 	string input = "1,2,3";
// 	int expectedValue=6;
	
// 	//Act
// 	int actualValue=ObjUnderTest.Add(input);

// 	//Assert
// 	ASSERT_EQ(actualValue,expectedValue);
// }
class Even_Test_Suite : public TestWithParam<int>{

};

bool isEven(int number){ return number % 2 == 0;}
TEST_P(Even_Test_Suite, AssertForEvenNumber){
	int input=GetParam();
	bool expectedValue=true;
	bool actualValue = isEven(input);
	ASSERT_EQ(expectedValue,actualValue);
}

INSTANTIATE_TEST_SUITE_P(
IsEvenParamTestExample,
Even_Test_Suite,
Values(12,4,6,18,8,24)
);
