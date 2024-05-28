//Ahmad JR

/*
Important Note: Upon running the program for the first time,
there will be no text file containing Client names in the program files.
When the first client is added,a text file named "clients" will be automatically created.

Instructions:-

1.Compile and run the program using a C++ compiler.
2.The main menu screen will be displayed with options to manage client data.
3.Choose an option by entering the corresponding number (1 to 6).
4.To show the client list, select option 1.
5.To add a new client, select option 2 and follow the prompts to enter client details.
6.To delete a client, select option 3, and enter the account number when prompted.
7.To update a client's information, select option 4, and enter the account number when prompted.
8.To find a specific client, select option 5 and enter the account number.
9.To exit the program, select option 6.
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

void PrintClientByAccountNumber(stClient Client)
{
	cout << "\nThe Follwing Are The Client Details:-\n\n";

	cout << "Account Number :" << Client.AccountNumber << "\n";
	cout << "PIN Code       :" << Client.PINCode << "\n";
	cout << "Client Name    :" << Client.Name << "\n";
	cout << "Phone          :" << Client.Phone << "\n";
	cout << "Balance        :" << Client.AccountBalance << "\n";
}


//[1] ShowClientList
void PrintHeader(vector <stClient>);

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

//[3] DeleteCliemt
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
void ShowClientList()
{
	stClient Client;
	vector <stClient> vClients = LoadClientsDataFromFile(ClientsFileName);

	PrintHeader(vClients);

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
void PrintHeader(vector <stClient> vClients)
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


//Operations
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
	cout << "        [6] Exit.\n";
	cout << "=========================================\n";
}

enum enMainMenuOption { ShowClientData = 1, enAddNewClients = 2, enDeleteClient = 3, UpdateClientInfo = 4, enFindClient = 5, Exit = 6 };

short ReadNumber(string Message)
{
	short Number = 5;

	do
	{
		if (Number < 1 || Number >6)
		{
			cout << "Invalid Try Again...\n";
		}

		cout << Message;
		cin >> Number;


	} while (Number < 1 || Number >6);
	return Number;
}

void ChooseOption()
{
	short Number = 0;

	do
	{
		Number = ReadNumber("Choose What Do You Want To do[1 to 6] ? ");

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
		case enMainMenuOption::Exit:

			system("cls");
			ExitHeader();

			system("pause>0");

			break;
		}
		system("cls");
		ShowMainMenuScreen();

	} while (Number != 6);
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
