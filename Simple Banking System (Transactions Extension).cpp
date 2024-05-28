//Ahmad JR

/*

Important Note: Upon running the program for the first time,
there will be no text file containing Client names in the program files.
When the first client is added,a text file named "clients" will be automatically created.

Instructions:-

1.Compile and run the code.
2.The main menu displays options for managing clients and transactions.
3.Choose an option by entering the corresponding number.
4.Add a client by providing details such as account number, PIN, name, phone, and balance.
5.Delete or update client information by entering the account number and following the prompts.
6.Use the transactions menu to deposit or withdraw funds and view total balances.
7.The program will return to the main menu after each operation.
8.Use the "Exit" option to end the program.

*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include<iomanip>
using namespace std;

const string ClientsFileName = "Clients.txt";

//Common functions
string ReadString(string Message)
{
	string String = "";

	cout << Message;
	cin >> String;

	return String;
}

struct stClient
{
	string AccountNumber = "", Name = "", Phone = "", PINCode = "";
	double AccountBalance = 0;
	bool MarkForDelete = false;
};

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



//[1] ShowClientList
void PrintHedar(vector <stClient>);

void PrintClient(stClient Clients)
{
	cout << "| " << left << setw(15) << Clients.AccountNumber;
	cout << "| " << left << setw(10) << Clients.PINCode;
	cout << "| " << left << setw(40) << Clients.Name;
	cout << "| " << left << setw(12) << Clients.Phone;
	cout << "| " << left << setw(12) << Clients.AccountBalance;
}

void PrintClients(vector <stClient> vClients)
{
	for (stClient C : vClients)
	{
		PrintClient(C);
		cout << "\n";
	}
}


//[2] AddClient
stClient ReadNewClient(string UserAccountNumber)
{
	stClient Client;

	do
	{
		if (CheckIfClientAccountExist(UserAccountNumber))
		{
			cout << "Client With Accoutnt [" << UserAccountNumber << "] Already Exists, Enter Another Account Number?";
			getline(cin >> ws, UserAccountNumber);
		}

	} while (CheckIfClientAccountExist(UserAccountNumber));

	Client.AccountNumber = UserAccountNumber;

	cout << "please Enter Client Data     :-\n\n";

	cout << "Enter PIN Code               : ";
	getline(cin >> ws, Client.PINCode);
	cout << "Enter Name                   : ";
	getline(cin, Client.Name);
	cout << "Enter Phone                  : ";
	getline(cin, Client.Phone);
	cout << "Enter AccountBalance         : ";
	cin >> Client.AccountBalance;

	return Client;
}

void AddNewClient()
{
	stClient Client;
	string UserAccountNumber;

	cout << "Enter Account Number : ";

	getline(cin >> ws, UserAccountNumber);

	Client = ReadNewClient(UserAccountNumber);

	SaveClientToFile(ClientsFileName, ConvertRecordToLine(Client, "#//#"));
}


//[3] DeleteClient
bool MarkClientForDeleteByAccountNumber(string UserAccountNumber, vector <stClient>& vClients)
{
	for (stClient& C : vClients)
	{
		if (UserAccountNumber == C.AccountNumber)
		{
			C.MarkForDelete = true;
			return true;
		}
	}
	return false;
}

bool DeleteClientByAccountNumber(string UserAccountNumber, vector <stClient>& vClients)
{
	stClient Client;
	char Answer = 'N';

	if (CheckIfClientAccountExist(Client, UserAccountNumber, vClients))
	{
		PrintClientByAccountNumber(Client);

		cout << "Are You Sure you want to delete this Client [Y/y] ? ";
		cin >> Answer;

		if (toupper(Answer) == 'Y')
		{
			MarkClientForDeleteByAccountNumber(UserAccountNumber, vClients);

			SaveClientsDataToFile(ClientsFileName, vClients);

			vClients = LoadClientsDataFromFile(ClientsFileName);

			cout << "Client Deleted Successfully";
			return true;
		}

	}
	else
	{
		cout << "Client With Account Number (" << UserAccountNumber << ") Not Found!";
		return false;
	}
}


//[4] UpdateClientInfo
stClient ChangeClientRecord(string UserAccountNumber)
{
	stClient Client;

	cout << "please Enter New Client Data     :-\n\n";


	Client.AccountNumber = UserAccountNumber;

	cout << "Enter PIN Code               : ";
	getline(cin >> ws, Client.PINCode);
	cout << "Enter Name                   : ";
	getline(cin, Client.Name);
	cout << "Enter Phone                  : ";
	getline(cin, Client.Phone);
	cout << "Enter AccountBalance         : ";
	cin >> Client.AccountBalance;

	return Client;
}

bool UpdateClientByAccountNumber(string UserAccountNumber, vector <stClient>& vClients)
{
	stClient Client;
	char Answer = 'N';

	if (CheckIfClientAccountExist(Client, UserAccountNumber, vClients))
	{
		PrintClientByAccountNumber(Client);

		cout << "Are You Sure you want to Update this Client [Y/y] ? ";
		cin >> Answer;

		if (toupper(Answer) == 'Y')
		{
			for (stClient& C : vClients)
			{
				if (C.AccountNumber == UserAccountNumber)
				{
					C = ChangeClientRecord(UserAccountNumber);
					break;
				}
			}

			SaveClientsDataToFile(ClientsFileName, vClients);

			cout << "Client Updated Successfully";
			return true;
		}
	}
	else
	{
		cout << "Client With Account Number (" << UserAccountNumber << ") Not Found!";
		return false;
	}
}


//OptionsMenu
void PrintHeadar(vector <stClient>);

void ShowClientList()
{
	stClient Client;
	vector <stClient> vClients = LoadClientsDataFromFile(ClientsFileName);

	PrintHeadar(vClients);

	PrintClients(vClients);
}

void AddClient()
{
	char AddNew = 'Y';

	do
	{
		AddNewClient();

		cout << "Client Added Successfully, Do You Want To Add More Client [Y/y] ? ";
		cin >> AddNew;

	} while (toupper(AddNew) == 'Y');
}

void DeleteClient()
{
	stClient Client;
	string UserAccountNumber = ReadString("please Enter Account Number ? ");
	vector <stClient> vClients = LoadClientsDataFromFile(ClientsFileName);

	DeleteClientByAccountNumber(UserAccountNumber, vClients);
}

void UpdateClienInfo()
{
	stClient Client;
	string UserAccountNumber = ReadString("please Enter Account Number ? ");
	vector <stClient> vClients = LoadClientsDataFromFile(ClientsFileName);

	UpdateClientByAccountNumber(UserAccountNumber, vClients);
}

void FindClient()
{
	stClient Client;
	string UserAccountNumber = ReadString("please Enter Account Number ? ");


	if (CheckIfClientAccountExist(Client, UserAccountNumber))
		PrintClientByAccountNumber(Client);
	else
		cout << "Client With Account Number (" << UserAccountNumber << ") Not Found!";
}


//OptionsHeders
void PrintHeadar(vector <stClient> vClients)
{
	cout << "                                    Client list (" << vClients.size() << ") Client(s)\n\n";

	cout << "_______________________________________________________________________________________________\n\n";
	cout << "| " << left << setw(15) << "Account Number";
	cout << "| " << left << setw(10) << "PIN Code";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Phone";
	cout << "| " << left << setw(12) << "Balance";
	cout << "\n_______________________________________________________________________________________________\n\n";
}

void AddNewClientsHeader()
{
	cout << "\n\n-----------------------------------------\n";
	cout << "          Add New Clients Screen\n";
	cout << "-----------------------------------------\n";
	cout << "Adding New Client:-\n";
}

void DeleteClientHeader()
{
	cout << "\n\n-----------------------------------------\n";
	cout << "          Delete Client Screen\n";
	cout << "-----------------------------------------\n";
}

void UpdateClientInfoHeader()
{
	cout << "\n\n-----------------------------------------\n";
	cout << "          Update Client Info Screen\n";
	cout << "-----------------------------------------\n";
}

void FindClientHeader()
{
	cout << "\n\n-----------------------------------------\n";
	cout << "           Find Client Screen\n";
	cout << "-----------------------------------------\n";
}

void ExitHeader()
{
	cout << "\n\n-----------------------------------------\n";
	cout << "            Program Ends :-)\n";
	cout << "-----------------------------------------\n";
}



//[1]Deposit
stClient UpdateClientDepositAmount(stClient& Client, string UserAccountNumber)
{
	double DepositAmount = 0;

	cout << "\nplease Enter Deposit Amount ?";
	cin >> DepositAmount;

	Client.AccountBalance += DepositAmount;

	return Client;
}

bool UpdateClientAmountDepositByAccountNumber(string UserAccountNumber, vector <stClient>& vClients)
{
	stClient Client;
	char Answer = 'N';

	if (CheckIfClientAccountExist(Client, UserAccountNumber, vClients))
	{
		PrintClientByAccountNumber(Client);

		cout << "Are You Sure you want to Perform This Transaction [Y/y] ? ";
		cin >> Answer;

		if (toupper(Answer) == 'Y')
		{
			for (stClient& C : vClients)
			{
				if (C.AccountNumber == UserAccountNumber)
				{
					C = UpdateClientDepositAmount(Client, UserAccountNumber);
					break;
				}
			}
			SaveClientsDataToFile(ClientsFileName, vClients);

			cout << "Done Successfully\n\n";
			cout << "New Balance : " << Client.AccountBalance;
			return true;
		}
	}
	else
	{
		cout << "Client With Account Number (" << UserAccountNumber << ") Not Found!";
		return false;
	}
}


//[2]Withdraw
stClient UpdateClientWithdrawAmount(stClient& Client, string UserAccountNumber)
{
	double WithdrawAmount = 0;

	do
	{
		cout << "\nplease Enter Withdraw Amount ?";
		cin >> WithdrawAmount;

		if (Client.AccountBalance < WithdrawAmount)
			cout << "Amount Exceeds The Balance, You Can Withdraw up to : " << WithdrawAmount << "\n";

	} while (Client.AccountBalance < WithdrawAmount);

	Client.AccountBalance -= WithdrawAmount;

	return Client;
}

bool UpdateClientAmountWithdrawByAccountNumber(string UserAccountNumber, vector <stClient>& vClients)
{
	stClient Client;
	char Answer = 'N';

	if (CheckIfClientAccountExist(Client, UserAccountNumber, vClients))
	{
		PrintClientByAccountNumber(Client);

		cout << "Are You Sure you want to Perform This Transaction [Y/y] ? ";
		cin >> Answer;

		if (toupper(Answer) == 'Y')
		{
			for (stClient& C : vClients)
			{
				if (C.AccountNumber == UserAccountNumber)
				{
					C = UpdateClientWithdrawAmount(Client, UserAccountNumber);
					break;
				}
			}
			SaveClientsDataToFile(ClientsFileName, vClients);

			cout << "\nDone Successfully\n\n";
			cout << "New Balance : " << Client.AccountBalance;
			return true;
		}
	}
	else
	{
		cout << "Client With Account Number (" << UserAccountNumber << ") Not Found!";
		return false;
	}
}


//[3]BalanceList
void PrintBalance(stClient Clients)
{
	cout << "| " << left << setw(15) << Clients.AccountNumber;
	cout << "| " << left << setw(40) << Clients.Name;
	cout << "| " << left << setw(12) << Clients.AccountBalance;
}

void PrintBalances(vector <stClient> vClients)
{
	for (stClient C : vClients)
	{
		PrintBalance(C);
		cout << "\n";
	}
}

void PrintBalancesListHedar(vector <stClient> vClients)
{
	cout << "                                    Balances list (" << vClients.size() << ") Client(s)\n\n";

	cout << "_______________________________________________________________________________________________\n\n";
	cout << "| " << left << setw(15) << "Account Number";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Balance";
	cout << "\n_______________________________________________________________________________________________\n\n";
}

double CalculateTotalBalances(vector <stClient> vClients)
{
	double TotalBalances = 0;

	for (stClient C : vClients)
	{
		TotalBalances += C.AccountBalance;
	}
	return TotalBalances;
}

void ShowfooterAndTotalBalances(double TotalBalances)
{
	cout << "\n_______________________________________________________________________________________________\n\n";

	cout << "\t\t\t\tTotal Balances =" << TotalBalances << "\n\n";
}


//TransactionsMenu
void UpdateClienBalanceDepositInfo()
{
	stClient Client;
	string UserAccountNumber = AskUserToEnterClientNumberWithLoop();
	vector <stClient> vClients = LoadClientsDataFromFile(ClientsFileName);

	UpdateClientAmountDepositByAccountNumber(UserAccountNumber, vClients);
}

void UpdateClienBalanceWithdrawInfo()
{
	stClient Client;
	string UserAccountNumber = AskUserToEnterClientNumberWithLoop();
	vector <stClient> vClients = LoadClientsDataFromFile(ClientsFileName);

	UpdateClientAmountWithdrawByAccountNumber(UserAccountNumber, vClients);
}

void ShowBalancesList()
{
	stClient Client;
	vector <stClient> vClients = LoadClientsDataFromFile(ClientsFileName);

	double TotalBalances = CalculateTotalBalances(vClients);

	PrintBalancesListHedar(vClients);

	PrintBalances(vClients);

	ShowfooterAndTotalBalances(TotalBalances);
}


//TransactionsHeaders
void DepositHeader()
{
	cout << "\n\n-----------------------------------------\n";
	cout << "          Deposit Screen\n";
	cout << "-----------------------------------------\n";
}

void WithdrawHeader()
{
	cout << "\n\n-----------------------------------------\n";
	cout << "          Withdraw Screen\n";
	cout << "-----------------------------------------\n";
}


//Operations on Transactions Menu
void ShowMainMenuScreen();

void ChooseOption();

void ShowTransactionsMenuScreen()
{
	cout << "=========================================\n";
	cout << "         Transactions Menu Screen\n";
	cout << "=========================================\n";
	cout << "        [1] Deposit.\n";
	cout << "        [2] Withdraw.\n";
	cout << "        [3] Total Balances\n";
	cout << "        [4] Main Menu.\n";
	cout << "=========================================\n";
}

enum enTransactionsOptions { enDeposit = 1, enWithdraw = 2, enTotalBalances = 3, enMainMenu = 4 };

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

	} while (Number < 1 || Number >4);
	return Number;
}

void ChooseTransaction()
{
	short Number = 0;

	do
	{
		Number = ReadTransactionsNumber("Choose What Do You Want To do[1 to 4] ? ");

		enTransactionsOptions TransOption = enTransactionsOptions(Number);

		switch (TransOption)
		{
		case enTransactionsOptions::enDeposit:

			system("cls");

			DepositHeader();
			UpdateClienBalanceDepositInfo();

			cout << "\nPress Any Key To Go back To Transactions Menu...";
			system("pause>0");

			break;
		case enTransactionsOptions::enWithdraw:

			system("cls");

			WithdrawHeader();
			UpdateClienBalanceWithdrawInfo();

			cout << "\nPress Any Key To Go back To Transactions Menu...";
			system("pause>0");

			break;
		case enTransactionsOptions::enTotalBalances:

			system("cls");

			ShowBalancesList();

			cout << "\nPress Any Key To Go back To Transactions Menu...";
			system("pause>0");

			break;
		case enTransactionsOptions::enMainMenu:

			system("cls");

			ShowMainMenuScreen();
			ChooseOption();

			system("pause>0");

			break;
		}

		system("cls");

		ShowTransactionsMenuScreen();

	} while (Number != 4);
}



//Operations on MainMenu
void ShowMainMenuScreen()
{
	cout << "=========================================\n";
	cout << "            Main Menu Screen\n";
	cout << "=========================================\n";
	cout << "        [1] Show Client List.\n";
	cout << "        [2] Add New Client.\n";
	cout << "        [3] Delete Client.\n";
	cout << "        [4] Update Client Info.\n";
	cout << "        [5] Find Client.\n";
	cout << "        [6] Transactions.\n";
	cout << "        [7] Exit.\n";
	cout << "=========================================\n";
}

enum enMainMenuOption { ShowClientData = 1, enAddNewClients = 2, enDeleteClient = 3, UpdateClientInfo = 4, enFindClient = 5, Transactions = 6, Exit = 7 };

short ReadOptionsNumber(string Message)
{
	short Number = 5;

	do
	{
		if (Number < 1 || Number >7)
		{
			cout << "Invalid Try Again...\n";
		}

		cout << Message;
		cin >> Number;


	} while (Number < 1 || Number >7);
	return Number;
}

void ChooseOption()
{
	short Number = 0;

	do
	{
		Number = ReadOptionsNumber("Choose What Do You Want To do[1 to 7] ? ");

		enMainMenuOption Option = enMainMenuOption(Number);

		switch (Option)
		{
		case enMainMenuOption::ShowClientData:

			system("cls");

			ShowClientList();

			cout << "\nPress Any Key To Go back To Main Menu...";
			system("pause>0");

			break;
		case enMainMenuOption::enAddNewClients:

			system("cls");
			AddNewClientsHeader();

			AddClient();

			cout << "\nPress Any Key To Go back To Main Menu...";
			system("pause>0");

			break;
		case enMainMenuOption::enDeleteClient:

			system("cls");
			DeleteClientHeader();

			DeleteClient();

			cout << "\nPress Any Key To Go back To Main Menu...";
			system("pause>0");

			break;
		case enMainMenuOption::UpdateClientInfo:

			system("cls");
			UpdateClientInfoHeader();

			UpdateClienInfo();

			cout << "\nPress Any Key To Go back To Main Menu...";
			system("pause>0");

			break;
		case enMainMenuOption::enFindClient:

			system("cls");
			FindClientHeader();

			FindClient();

			cout << "\nPress Any Key To Go back To Main Menu...";
			system("pause>0");

			break;
		case enMainMenuOption::Transactions:

			system("cls");
			ShowTransactionsMenuScreen();

			ChooseTransaction();

			system("pause>0");

			break;
		case enMainMenuOption::Exit:

			system("cls");
			ExitHeader();

			system("pause>0");

			break;
		}
		system("cls");
		ShowMainMenuScreen();

	} while (Number != 7);
}



void PrintResults()
{
	ShowMainMenuScreen();

	ChooseOption();
}

int main()
{
	PrintResults();

	return 0;
}
