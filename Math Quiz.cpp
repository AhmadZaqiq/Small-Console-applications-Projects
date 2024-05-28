//Ahmad JR

/*
Instructions:-

1. Compile and run the code in a C++ environment.
2. Enter the number of questions you want to answer when prompted.
3. Select the difficulty level of the questions.
4. Choose the type of mathematical operations you want to practice.
5. Answer the math questions presented by the program.
6. View your results and decide if you want to play again.
*/

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

enum enQuestionLevel { EasyLevel = 1, MedLevel = 2, HardLevel = 3, Mix = 4 };

enum enOperationType { Add = 1, Sub = 2, Muly = 3, Div = 4, MixOp = 5 };

struct stQuestion
{
	int Number1 = 0, Number2 = 0;

	enOperationType OperationType;
	enQuestionLevel QuestionLevel;

	int CorrectAnswer = 0;
	int PlayAnswer = 0;

	bool AnswerResult = false;
};

struct stQuizz
{
	stQuestion QuestinList[100];

	short NumberOfQuestions = 0;

	enQuestionLevel QuestionLevel;
	enOperationType OpType;

	short NumberOfWrongAnswers = 0, NumberOfRightAnswers = 0;

	bool IsPass = false;
};

short RandomNumber(int From, int To)
{
	short randNum = rand() % (To - From + 1) + From;
	return randNum;
}

short ReadHowManyQuestions()
{
	short NumberOfQuestions = 0;

	do
	{
		cout << "How Many Questions Do You Want To Answer ? ";
		cin >> NumberOfQuestions;

	} while (NumberOfQuestions < 1 || NumberOfQuestions>100);

	return NumberOfQuestions;
}

enQuestionLevel ReadQuestionsLevel()
{
	short QuestionLevel = 0;

	do
	{
		cout << "Enter Question Level [1] Easy, [2] Med, [3] Hard, [4] Mix ? ";
		cin >> QuestionLevel;

	} while (QuestionLevel < 1 || QuestionLevel>4);

	return (enQuestionLevel)QuestionLevel;
}

enOperationType ReadOpType()
{
	short OpType = 0;

	do
	{
		cout << "Enter Operation Type [1] Add, [2] Sub, [3] Mult, [4] Div, [5] Mix ? ";
		cin >> OpType;

	} while (OpType < 1 || OpType>5);

	return (enOperationType)OpType;
}

enOperationType GetRandomOperationType()
{
	int Op = RandomNumber(1, 4);
	return (enOperationType)Op;
}

short SimpleCalculator(short Number1, short Number2, enOperationType OpType)
{
	switch (OpType)
	{
	case enOperationType::Add:
		return Number1 + Number2;
	case enOperationType::Sub:
		return Number1 - Number2;
	case enOperationType::Muly:
		return Number1 * Number2;
	case enOperationType::Div:
		return Number1 / Number2;
	default:
		return Number1 + Number2;
	}
}

stQuestion GenerateQuestion(enQuestionLevel QuestionLevel, enOperationType OpType)
{
	stQuestion Question;

	if (QuestionLevel == enQuestionLevel::Mix)
	{
		QuestionLevel = (enQuestionLevel)RandomNumber(1, 3);
	}

	if (OpType == enOperationType::MixOp)
	{
		OpType = GetRandomOperationType();
	}

	Question.OperationType = OpType;

	switch (QuestionLevel)
	{
	case enQuestionLevel::EasyLevel:
		Question.Number1 = RandomNumber(1, 10);
		Question.Number2 = RandomNumber(1, 10);

		Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
		Question.QuestionLevel = QuestionLevel;
		return Question;

	case enQuestionLevel::MedLevel:
		Question.Number1 = RandomNumber(1, 50);
		Question.Number2 = RandomNumber(1, 50);

		Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
		Question.QuestionLevel = QuestionLevel;
		return Question;

	case enQuestionLevel::HardLevel:
		Question.Number1 = RandomNumber(50, 100);
		Question.Number2 = RandomNumber(50, 100);

		Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
		Question.QuestionLevel = QuestionLevel;
		return Question;
	}
	return Question;
}

void GenerateQuizzQuestions(stQuizz& Quizz)
{
	for (short Question = 0; Question < Quizz.NumberOfQuestions; Question++)
	{
		Quizz.QuestinList[Question] = GenerateQuestion(Quizz.QuestionLevel, Quizz.OpType);
	}
}

string GetOpTypeSymbol(enOperationType OperationType)
{
	string OpTypeArrSymbol[4] = { "+","-","*","/" };
	return OpTypeArrSymbol[OperationType - 1];
}

void PrintTheQuestion(stQuizz Quizz, short QuestinNumber)
{
	cout << "\n";
	cout << "Question[" << QuestinNumber + 1 << "/" << Quizz.NumberOfQuestions << "]\n\n";
	cout << Quizz.QuestinList[QuestinNumber].Number1 << endl;
	cout << Quizz.QuestinList[QuestinNumber].Number2 << " ";
	cout << GetOpTypeSymbol(Quizz.QuestinList[QuestinNumber].OperationType);
	cout << "\n_________" << endl;

}

short ReadQuestionAnswer()
{
	short Answer = 0;
	cin >> Answer;
	return Answer;
}

void SetScreenColor(bool checkanswer)
{
	if (checkanswer)
	{
		system("color 2f ");
	}
	else
	{
		system("color 4f \n");
		cout << "\a";
	}
}

void CorrectTheQuestinAnswer(stQuizz& Quizz, short QuestinNumber)
{
	if (Quizz.QuestinList[QuestinNumber].PlayAnswer != Quizz.QuestinList[QuestinNumber].CorrectAnswer)
	{
		Quizz.QuestinList[QuestinNumber].AnswerResult = false;
		Quizz.NumberOfWrongAnswers++;

		cout << "Wrong Answer :-(\n";
		cout << "The Right Answer is: " << Quizz.QuestinList[QuestinNumber].CorrectAnswer << "\n";
	}
	else
	{
		Quizz.QuestinList[QuestinNumber].AnswerResult = true;
		Quizz.NumberOfRightAnswers++;

		cout << "Right Answer :-)\n";
	}
	cout << "\n";

	SetScreenColor(Quizz.QuestinList[QuestinNumber].AnswerResult);
}

void AskAndCorrectQuestionListAnswers(stQuizz& Quizz)
{
	for (short QuestinNumber = 0; QuestinNumber < Quizz.NumberOfQuestions; QuestinNumber++)
	{
		PrintTheQuestion(Quizz, QuestinNumber);

		Quizz.QuestinList[QuestinNumber].PlayAnswer = ReadQuestionAnswer();

		CorrectTheQuestinAnswer(Quizz, QuestinNumber);
	}

	Quizz.IsPass = (Quizz.NumberOfRightAnswers > Quizz.NumberOfWrongAnswers);
}

string FinalResult(bool Pass)
{
	if (Pass)
		return "Pass :-)";
	else
		return "Fail P-(";
}

string GetQuestionLevelText(enQuestionLevel QuestionLevel)
{
	string ArrQuestionLevel[4] = { "Easy","Med","Hard","Mix" };

	return ArrQuestionLevel[QuestionLevel - 1];
}

void PrintQuizzResults(stQuizz Quizz)
{
	cout << "----------------------\n";
	cout << "Final Result " << FinalResult(Quizz.IsPass) << endl;
	cout << "----------------------\n";

	cout << "Number Of Questions : " << Quizz.NumberOfQuestions << endl;
	cout << "Question Level : " << GetQuestionLevelText(Quizz.QuestionLevel) << endl;
	cout << "OpType : " << GetOpTypeSymbol(Quizz.OpType) << endl;
	cout << "Number Of Rigth Answers : " << Quizz.NumberOfRightAnswers << endl;
	cout << "Number Of Wrong Answers : " << Quizz.NumberOfWrongAnswers << endl;
	cout << "----------------------\n";
}

void PlayMathGame()
{
	stQuizz Quizz;

	Quizz.NumberOfQuestions = ReadHowManyQuestions();
	Quizz.QuestionLevel = ReadQuestionsLevel();
	Quizz.OpType = ReadOpType();

	GenerateQuizzQuestions(Quizz);

	AskAndCorrectQuestionListAnswers(Quizz);
	PrintQuizzResults(Quizz);
}

void ResetScreen()
{
	system("cls");
	system("color 0F");
}

void StartGame()
{
	char PlayAgain = 'Y';

	do
	{
		ResetScreen();
		PlayMathGame();

		cout << "\n" << "Do you Want To play again [Y/N] ? ";
		cin >> PlayAgain;

	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
	srand((unsigned)time(NULL));

	StartGame();
}
