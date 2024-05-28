//Ahmad JR

/*

*important Note:-
You must place the Clients.txt file in the project file...

To enter the system for the first time...Use:

Account Number: A150
PinCode       : 1234

Instructions:-

1.Run the Program.
2.Log In: Enter the account number and PIN code to access the system.
3.Transactions Menu: Select from Quick Withdraw, Normal Withdraw, Deposit, or Check Balance.
4.Perform Transactions: Follow prompts for each transaction type.
5.Logout: Choose the logout option to exit the transactions menu.

*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include<iomanip>

using namespace std;

const string ClientsFileName = "Clients.txt";


//CommonClientfunctions

string ReadString(string Message)
{
	string String = "";

	cout << Message;
	cin >> String;

	return String;
}

double ReadNumber(string Message)
{
	double Number = 0;

	do
	{
		cout << Message;
		cin >> Number;

	} while (Number < 0);

	return Number;
}

vector <string> SplitString(string S1, string delim)
{
	vector <string> vString;

	short pos = 0;
	string Sword;

	while ((pos = S1.find(delim)) != std::string::npos)
	{
		Sword = S1.substr(0, pos);

		if (Sword != "")
		{
			vString.push_back(Sword);
		}
		S1.erase(0, pos + delim.length());
	}

	if (S1 != "")
	{
		vString.push_back(S1);
	}
	return vString;
}

struct stClient
{
	string AccountNumber = "", Name = "", Phone = "", PINCode = "";
	double AccountBalance = 0;
	bool MarkForDelete = false;
};

string ConvertRecordToLine(stClient Client, string delim)
{
	string StringClientData = "";

	StringClientData = StringClientData + Client.AccountNumber + delim;
	StringClientData = StringClientData + Client.PINCode + delim;
	StringClientData = StringClientData + Client.Name + delim;
	StringClientData = StringClientData + Client.Phone + delim;
	StringClientData = StringClientData + to_string(Client.AccountBalance);

	return StringClientData;
}

stClient ConvertLineToRecord(string Line)
{
	stClient Client;
	vector <string> vClientData = SplitString(Line, "#//#");

	Client.AccountNumber = vClientData[0];
	Client.PINCode = vClientData[1];
	Client.Name = vClientData[2];
	Client.Phone = vClientData[3];
	Client.AccountBalance = stod(vClientData[4]);

	return Client;
}

void SaveClientToFile(string FileName, string ClientLine)
{
	fstream MyClientsFile;

	MyClientsFile.open(FileName, ios::out | ios::app);

	if (MyClientsFile.is_open())
	{
		MyClientsFile << ClientLine << endl;

		MyClientsFile.close();
	}
}

vector <stClient> SaveClientsDataToFile(string FileName, vector <stClient> vClients)
{
	fstream MyClientsFile;

	MyClientsFile.open(FileName, ios::out);

	string DataLine;

	if (MyClientsFile.is_open())
	{
		for (stClient& C : vClients)
		{
			if (C.MarkForDelete == false)
			{
				DataLine = ConvertRecordToLine(C, "#//#");
				MyClientsFile << DataLine << endl;
			}
		}

		MyClientsFile.close();
	}
	return vClients;
}

vector <stClient> LoadClientsDataFromFile(string FileName)
{
	fstream MyFile;

	vector <stClient> vClients;

	MyFile.open(FileName, ios::in);

	if (MyFile.is_open())
	{
		string Line;
		stClient Client;

		while (getline(MyFile, Line))
		{
			vClients.push_back(ConvertLineToRecord(Line));
		}
	}
	return vClients;
}

stClient ReadNewClient()
{
	stClient Client;

	cout << "please Enter Client Data     :-\n\n";

	cout << "Enter Account Number         : ";
	getline(cin >> ws, Client.AccountNumber);
	cout << "Enter PIN Code               : ";
	getline(cin, Client.PINCode);
	cout << "Enter Name                   : ";
	getline(cin, Client.Name);
	cout << "Enter Phone                  : ";
	getline(cin, Client.Phone);
	cout << "Enter AccountBalance         : ";
	cin >> Client.AccountBalance;

	return Client;
}

bool CheckIfClientAccountExist(stClient& Client, string UserAccountNumber)
{
	vector <stClient> vClients = LoadClientsDataFromFile(ClientsFileName);

	for (stClient C : vClients)
	{
		if (UserAccountNumber == C.AccountNumber)
		{
			Client = C;
			return true;
		}
	}
	return false;
}

bool CheckIfClientAccountExist(stClient& Client, string UserAccountNumber, vector <stClient> vClients)
{
	for (stClient C : vClients)
	{
		if (UserAccountNumber == C.AccountNumber)
		{
			Client = C;
			return true;
		}
	}
	return false;
}

bool CheckIfClientAccountExist(string UserAccountNumber)
{
	vector <stClient> vClients = LoadClientsDataFromFile(ClientsFileName);

	for (stClient C : vClients)
	{
		if (UserAccountNumber == C.AccountNumber)
		{
			return true;
		}
	}
	return false;
}

void PrintClientByAccountNumber(stClient Client)
{
	cout << "\nThe Follwing Are The Client Details:-\n\n";

	cout << "Account Number :" << Client.AccountNumber << "\n";
	cout << "PIN Code       :" << Client.PINCode << "\n";
	cout << "Client Name    :" << Client.Name << "\n";
	cout << "Phone          :" << Client.Phone << "\n";
	cout << "Balance        :" << Client.AccountBalance << "\n";
}

string AskUserToEnterClientNumberWithLoop()
{
	stClient Client;
	string UserAccountNumber = "";

	do
	{
		UserAccountNumber = ReadString("please Enter Account Number ? ");

		if (!CheckIfClientAccountExist(Client, UserAccountNumber))
			cout << "Client With Account Number (" << UserAccountNumber << ") Does Not Exist.\n\n";

	} while (!CheckIfClientAccountExist(Client, UserAccountNumber));

	return UserAccountNumber;
}


stClient CurrentClient;

vector <stClient> vClients = LoadClientsDataFromFile(ClientsFileName);


//[1]Quick Withdraw

void ShowTransactionsMenuScreen();//Declartion

void ChooseTransaction();//Declartion

enum enQuickWithdrawOptions
{
	enOption1 = 1,
	enOption2 = 2,
	enOption3 = 3,
	enOption4 = 4,
	enOption5 = 5,
	enOption6 = 6,
	enOption7 = 7,
	enOption8 = 8,
	enOption9 = 9
};

short ReadQuickWithdrawOption(string Message)
{
	short Number = 3;

	do
	{
		if (Number < 1 || Number >9)
		{
			cout << "Invalid Try Again...\n";
		}

		cout << Message;
		cin >> Number;

	} while (Number < 1 || Number >9);
	return Number;
}

short QuickWithdrawAmount()
{
	short Number = 0;

	Number = ReadQuickWithdrawOption("Choose What To Withdraw[1 to 9] ? ");

	enQuickWithdrawOptions WithdrawOptions = enQuickWithdrawOptions(Number);

	switch (WithdrawOptions)
	{

	case enQuickWithdrawOptions::enOption1:
		return 20;
		break;

	case enQuickWithdrawOptions::enOption2:
		return 50;
		break;

	case enQuickWithdrawOptions::enOption3:
		return 100;
		break;

	case enQuickWithdrawOptions::enOption4:
		return 200;
		break;

	case enQuickWithdrawOptions::enOption5:
		return 400;
		break;

	case enQuickWithdrawOptions::enOption6:
		return 600;
		break;

	case enQuickWithdrawOptions::enOption7:
		return 800;
		break;

	case enQuickWithdrawOptions::enOption8:
		return 1000;
		break;

	case enQuickWithdrawOptions::enOption9:

		system("cls");

		ShowTransactionsMenuScreen();

		ChooseTransaction();

		break;
	}
}

stClient UpdateClientQuickWithdrawAmount(stClient& Client)
{
	double WithdrawAmount = 0;

	do
	{
		WithdrawAmount = QuickWithdrawAmount();

		if (Client.AccountBalance < WithdrawAmount)
			cout << "Amount Exceeds The Balance, You Can Withdraw up to : " << Client.AccountBalance << "\n";

	} while (Client.AccountBalance < WithdrawAmount);

	Client.AccountBalance -= WithdrawAmount;

	return Client;
}

bool UpdateClientAmountQuickWithdrawByAccountNumber(vector <stClient>& vClients)
{
	char Answer = 'N';

	cout << "Are You Sure you want to Perform This Transaction [Y/y] ? ";
	cin >> Answer;

	if (toupper(Answer) == 'Y')
	{
		for (stClient& C : vClients)
		{
			if (C.AccountNumber == CurrentClient.AccountNumber)
			{
				C = UpdateClientQuickWithdrawAmount(CurrentClient);
				break;
			}
		}
		SaveClientsDataToFile(ClientsFileName, vClients);

		cout << "Done Successfully\n\n";
		cout << "New Balance : " << CurrentClient.AccountBalance;
		return true;
	}

	else
	{
		return false;
	}
}


//[2]Normal Withdraw

double ReadMulNumber(string Message, short MultNumber)
{
	double Number = 0;

	do
	{
		cout << Message;
		cin >> Number;

	} while ((Number < 0) || (short(Number) % 5 != 0));

	return Number;
}

stClient UpdateClientNormalWithdrawAmount(stClient& Client)
{
	double WithdrawAmount = 0;

	do
	{
		WithdrawAmount = ReadMulNumber("\nEnter A Deposit Amount Mul By 5' : ", 5);

		if (Client.AccountBalance < WithdrawAmount)
			cout << "Amount Exceeds The Balance, You Can Withdraw up to : " << Client.AccountBalance << "\n";

	} while (Client.AccountBalance < WithdrawAmount);

	Client.AccountBalance -= WithdrawAmount;

	return Client;
}

bool UpdateClientAmountNormalWithdrawByAccountNumber(vector <stClient>& vClients)
{
	char Answer = 'N';

	cout << "Are You Sure you want to Perform This Transaction [Y/y] ? ";
	cin >> Answer;

	if (toupper(Answer) == 'Y')
	{
		for (stClient& C : vClients)
		{
			if (C.AccountNumber == CurrentClient.AccountNumber)
			{
				C = UpdateClientNormalWithdrawAmount(CurrentClient);
				break;
			}
		}
		SaveClientsDataToFile(ClientsFileName, vClients);

		cout << "Done Successfully\n\n";
		cout << "New Balance : " << CurrentClient.AccountBalance;
		return true;
	}

	else
	{
		return false;
	}
}


//[3]Deposit

stClient UpdateClientDepositAmount(stClient& Client)
{
	double DepositAmount = ReadNumber("\nEnter A Positve Deposit Amount : ");

	Client.AccountBalance += DepositAmount;

	return Client;
}

bool UpdateClientAmountDepositByAccountNumber(vector <stClient>& vClients)
{
	char Answer = 'N';

	cout << "Are You Sure you want to Perform This Transaction [Y/y] ? ";
	cin >> Answer;

	if (toupper(Answer) == 'Y')
	{
		for (stClient& C : vClients)
		{
			if (C.AccountNumber == CurrentClient.AccountNumber)
			{
				C = UpdateClientDepositAmount(CurrentClient);
				break;
			}
		}
		SaveClientsDataToFile(ClientsFileName, vClients);

		cout << "Done Successfully\n\n";
		cout << "New Balance : " << CurrentClient.AccountBalance;
		return true;
	}

	else
	{
		return false;
	}
}


//[4]Check Balance

void ShowClientBalance()
{
	cout << "your Balance Is: {" << CurrentClient.AccountBalance << "}\n\n\n";
}


//TransactionsMenu

void QuickWithdraw()
{
	UpdateClientAmountQuickWithdrawByAccountNumber(vClients);
}

void NormalWithdraw()
{
	UpdateClientAmountNormalWithdrawByAccountNumber(vClients);
}

void Deposit()
{
	UpdateClientAmountDepositByAccountNumber(vClients);
}

void CheckBalance()
{
	ShowClientBalance();
}



//TransactionsHeaders
void QuickWithdrawHeader()
{
	cout << "\n\n=========================================\n";
	cout << "       Quick Withdraw Screen\n";
	cout << "=========================================\n";
	cout << "\t [1] 20  \t[2] 50\n";
	cout << "\t [3] 100  \t[4] 200\n";
	cout << "\t [5] 400  \t[6] 600\n";
	cout << "\t [7] 800  \t[8] 1000\n";
	cout << "\t [9] Exit\n";
	cout << "=========================================\n";
	cout << "Your Balance is {" << CurrentClient.AccountBalance << "}\n\n";
}

void NormalWithdrawHeader()
{
	cout << "\n\n=========================================\n";
	cout << "       Normal Withdraw Screen\n";
	cout << "=========================================\n";
}

void DepositHeader()
{
	cout << "\n\n=========================================\n";
	cout << "          Deposit Screen\n";
	cout << "=========================================\n";
}

void CheckBalanceHeader()
{
	cout << "\n\n=========================================\n";
	cout << "          Check Balance\n";
	cout << "=========================================\n";
}


//OperationsonTransactionsMenu


void LoginScreenHeader();

void LoginScreen();

void ShowTransactionsMenuScreen()
{
	cout << "=========================================\n";
	cout << "         Transactions Menu Screen\n";
	cout << "=========================================\n";
	cout << "        [1] Quick Withdraw .\n";
	cout << "        [2] Normal Withdraw.\n";
	cout << "        [3] Deposit.\n";
	cout << "        [4] Check Balance\n";
	cout << "        [5] Logout .\n";
	cout << "=========================================\n";
}

enum enTransactionsOptions
{
	enQuickWithdraw = 1, enNormalWithdraw = 2, enDeposit = 3, enCheckBalance = 4, enLogout = 5
};

short ReadTransactionsNumber(string Message)
{
	short Number = 3;

	do
	{
		if (Number < 1 || Number >4)
		{
			cout << "Invalid Try Again...\n";
		}

		cout << Message;
		cin >> Number;

	} while (Number < 1 || Number >5);
	return Number;
}

void ChooseTransaction()
{
	short Number = 0;

	do
	{
		Number = ReadTransactionsNumber("Choose What Do You Want To do[1 to 5] ? ");

		enTransactionsOptions TransOption = enTransactionsOptions(Number);

		switch (TransOption)
		{
		case enTransactionsOptions::enQuickWithdraw:

			system("cls");

			QuickWithdrawHeader();

			QuickWithdraw();

			cout << "\nPress Any Key To Go back To Transactions Menu...";
			system("pause>0");

			break;
		case enTransactionsOptions::enNormalWithdraw:

			system("cls");

			NormalWithdrawHeader();

			NormalWithdraw();

			cout << "\nPress Any Key To Go back To Transactions Menu...";
			system("pause>0");

			break;
		case enTransactionsOptions::enDeposit:

			system("cls");

			DepositHeader();

			Deposit();

			cout << "\nPress Any Key To Go back To Transactions Menu...";
			system("pause>0");

			break;
		case enTransactionsOptions::enCheckBalance:

			system("cls");

			CheckBalanceHeader();

			CheckBalance();

			cout << "\nPress Any Key To Go back To Transactions Menu...";
			system("pause>0");

			break;
		case enTransactionsOptions::enLogout:

			system("cls");

			LoginScreenHeader();

			LoginScreen();

			system("pause>0");

			break;
		}

		system("cls");

		ShowTransactionsMenuScreen();

	} while (Number != 5);
}



//OperationsonLoginScreen

void LoginScreenHeader()
{
	cout << "\n\n=========================================\n";
	cout << "          Loging Screen\n";
	cout << "=========================================\n";
}

bool findClientByNameAndPINcode(string AccountNumber, string PINCode, stClient& Client)
{

	for (stClient& C : vClients)
	{
		if (C.AccountNumber == AccountNumber && C.PINCode == PINCode)
		{
			Client = C;
			return true;
		}
	}
	return false;
}

bool LoadClientsFromFile(string AccountNumber, string PINCode)
{
	return  findClientByNameAndPINcode(AccountNumber, PINCode, CurrentClient);
}

void LoginScreen()
{
	LoginScreenHeader();

	string AccountNumber = "", PINCode = "";

	bool LoginFaild = false;

	do
	{
		system("cls");

		LoginScreenHeader();

		if (LoginFaild)
			cout << "Invalid Account Number/PINCode!\n";

		AccountNumber = ReadString("Enter Account Number? ");
		PINCode = ReadString("Enter PINCode? ");

		LoginFaild = !LoadClientsFromFile(AccountNumber, PINCode);

	} while (LoginFaild);

	system("cls");

	ShowTransactionsMenuScreen();

	ChooseTransaction();
}



void PrintResults()
{
	LoginScreen();
}

int main()
{
	PrintResults();

	return 0;
}
