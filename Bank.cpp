#include<iostream>
#include<fstream>
#include<vector>
#include<limits>
#include<iomanip>
#include<string>
using namespace std;
const string Data = "Data_Bank.txt";

struct Data_client
{
	string Account_number;
	string Pin_Code;
	string Full_name;
	string Phone;
	double Account_Balance;
	bool MArking = false;

};


enum EN_Record { Show = 1, Add = 2, Delete = 3, Update = 4, Find = 5, Tranacthions = 6, Exit = 7, };
enum EN_Record_Tranacthions {Deposit_1 = 1  , Winthdraw_1 = 2 , toala_balances = 3 , Main_menu = 4 };

vector<string>Split_string(string line, string Dlimter)
{
	short Index = 0;

	string word;

	vector<string>Vstring;

	while ((Index = line.find(Dlimter)) != std::string::npos)
	{
		word = line.substr(0, Index);
		if (!word.empty())
		{
			Vstring.push_back(word);
		}
		line.erase(0, Index + Dlimter.length());
	}
	if (!line.empty())
	{
		Vstring.push_back(line);
	}
	return  Vstring;
}

Data_client Adding_data_TO_client(string line_file, string Space = "|?|")
{
	vector<string>From;
	Data_client  To;
	From = Split_string(line_file, Space);
	To.Account_number = From[0];
	To.Pin_Code = From[1];
	To.Full_name = From[2];
	To.Phone = From[3];
	To.Account_Balance = stod(From[4]);
	return To;
}
vector<Data_client>Adding_data_in_file_TO_vactor(const string& locthoin_file)
{
	vector<Data_client> One_Client;
	fstream Adding_data;
	Adding_data.open(locthoin_file, ios::in);//Reading Mod //
	if (Adding_data.is_open())
	{
		string line; // this is Read_one_line_file//
		Data_client Cli; // this is a struct Adding data in the Functhoin adding//
		while (getline(Adding_data, line))///What IS THis ///
		{
			Cli = Adding_data_TO_client(line);///thr adding here is the adding data to strucr  //
			One_Client.push_back(Cli);

		}
		Adding_data.close();
	}
	return One_Client;
}


void Pritn_data_Record(Data_client client)//data client is  a vector data struct //
{
	
	system("Color 0A");
	cout << "| " << setw(15) << client.Account_number;
	cout << "| " << setw(10) << client.Pin_Code;
	cout << "| " << setw(40) << client.Full_name;
	cout << "| " << setw(12) << client.Phone;
	cout << "| " << setw(12) << client.Account_Balance;
}
void Pritn_data_For_vectorst(vector<Data_client>client)
{
	system("Color 0A");

	cout << "\n\t\t\t\t\t client List(" << client.size() << ")Client(s)" << endl;

	cout << "\n=================================================================================================*\n" << endl;
	cout << "| " << left << setw(15) << " Accout Number ";
	cout << "| " << left << setw(10) << " Pin Code ";
	cout << "| " << left << setw(40) << " Client Name ";
	cout << "| " << left << setw(12) << " Phone ";
	cout << "| " << left << setw(12) << " Balance ";
	cout << "\n=================================================================================================*\n" << endl;
	for (Data_client One_client : client)
	{
		Pritn_data_Record(One_client);
		cout << endl;
	}
	cout << "\n=================================================================================================*\n" << endl;

}

void show_data()///the Functhoin is call //
{
	vector<Data_client>data = Adding_data_in_file_TO_vactor (Data);

	system("cls");

	cout << "=============================" << endl;
	cout << "\t Show Data\t" << endl;
	cout << "=============================" << endl;

	Pritn_data_For_vectorst(data);

}

///step Two Add data To File And Check_Account number //

bool Check_Data_account_number(string Account_number , string locthoin ) // check- account number /
{
	fstream check;
	check.open(locthoin, ios::in);///Read mod//
	if (check.is_open())
	{
	    string line;
		while (getline(check , line))
		{
			Data_client data = Adding_data_TO_client(line);

			if (data.Account_number == Account_number )
			{
				check.close();
				return true;
			}

		}
		check.close();
	}
	return false;
}

Data_client Read_data()
{
	Data_client adding;

	getline(cin>>ws, adding.Account_number);

	while (Check_Data_account_number(adding.Account_number , Data))
	{
	cout << "Account Number already exists, please enter a new one.\n";
	getline(cin >> ws, adding.Account_number);
	}

	cout << "Enter  pin code : ";
	getline(cin, adding.Pin_Code);

	cout << "Enter full Name : ";
	getline(cin, adding.Full_name);

	cout << "Enter  phone :";
	getline(cin, adding.Phone);

	cout << "Enter Account Number :";
	cin >> adding.Account_Balance;

	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	return adding;
}


void Adding_Data(string File_Name, string Data)
{
	fstream Data_B;
	Data_B.open(File_Name, ios::out | ios::app); //
	if (Data_B.is_open())
	{
		Data_B << Data << endl;
		Data_B.close();
	}
}


string Adding_data_to_string(Data_client Adding, string space = "|?|")
{
	string Add =
		Adding.Account_number + space +
		Adding.Pin_Code + space +
		Adding.Full_name + space +
		Adding.Phone + space +
		to_string(Adding.Account_Balance);
	return Add;
}

void Adding_More()
{
	Data_client data ;
	char Read = 'Y';
	do
	{
		data = Read_data();

		Adding_Data(Adding_data_to_string(data), Data);

		cout << "Do You Add New Data  [ Y / N  ] : ";

		cin >> Read;

		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		system("cls");

		cout << "\t\tAdd New Data :-) \n";

	} while (toupper(Read)=='Y');

}

void Adding_New_Data()
{
	system("cls");

	cout << "=============================" << endl;
	cout << "\t Add Data \t" << endl;
	cout << "=============================" << endl;

	Adding_More();

}

/// step three Delete Data///

string read_Account_number()
{
	string read;
	cout << "Enter a Account Number : ";
	getline(cin>>ws, read);
	return read;
}

bool check_Account_number_And_Show_data(const string& Account_number, Data_client& Data_org)
{
	vector<Data_client>from = Adding_data_in_file_TO_vactor(Data);
	for (Data_client loop : from)
	{
		if (loop.Account_number == Account_number)
		{
			Data_org = loop;
			return true;
		}
	}
	return false;

}

void show_data(Data_client data)
{
	
	cout << "======================" << endl;
	cout << " Account Number: " << data.Account_number << endl;

	cout << " Pin code      : " << data.Pin_Code << endl;

	cout << " Full Name     : " << data.Full_name << endl;

	cout << " Phone         : " << data.Phone << endl;

	cout << "Account Balance: " << data.Account_Balance << endl;
	cout << "======================" << endl;
}

bool find_data_account_number(const string& account_number, vector<Data_client>&data, Data_client& New_data)
{
	for (Data_client loop : data)
	{
		if (loop.Account_number == account_number)
		{
			New_data = loop;
			return true;
		}
	}
	return false;
}

bool mark_and_check_account_number(const string& Account_number, vector<Data_client>& data)
{
	for (Data_client& loop : data)
	{
		if (loop.Account_number == Account_number)
		{
			loop.MArking = true;
			return true;
		}
	}
	return false;
}

 vector<Data_client> Delete_data_or_save (const string&locthoin, vector<Data_client> datal)
{
	fstream Delete_line;
	
	Delete_line.open(locthoin, ios::out);///delete_data;
	if (Delete_line.is_open())
	{
		for (Data_client& data_client : datal)
		{
			if (!data_client.MArking)
			{
				
			Delete_line <<  Adding_data_to_string(data_client) << endl;

			}
		}
		Delete_line.close();
	}
	return datal;
}

 bool check_add_more_delete_data(const string& Account_number, vector<Data_client>& Delete_data_client)
 {
	 Data_client New_delet;
	 char user = 'n';
	 if (find_data_account_number(Account_number, Delete_data_client, New_delet))
	 {
		 show_data(New_delet);
		 cout << "\n\n  Are You Sure You Want Delete This Client [ Y / N ] ? :";
		 cin >> ws, user;
		 cin.ignore(numeric_limits<streamsize>::max(), '\n');
		 if (toupper(user)=='Y')
		 {
			 mark_and_check_account_number(Account_number, Delete_data_client);
			 Delete_data_or_save(Data, Delete_data_client);
			 Delete_data_client = Adding_data_in_file_TO_vactor(Data);
			 return true;
		 }
		 else
		 {
			 cout << "\nDeletion cancelled by user." << endl;
		 }
		 return false;
	 }
	 else
	 {
		 cout << "\n Client with Account Number " << Account_number << "Is Not Found ! ";
		 return false;
	 }

 }

 void delete_data()
 {
	 system("cls");

	 cout << "=============================" << endl;
	 cout << "\t  Delete Data \t" << endl;
	 cout << "=============================" << endl;

	 vector<Data_client> New_data = Adding_data_in_file_TO_vactor(Data);

	 string user_input = read_Account_number();

	 check_add_more_delete_data(user_input, New_data);
 }


 bool Update_data(const string& Account, vector<Data_client>& data_client)
 {
	 Data_client data_updte;
	 char user = 'n';
	 if (find_data_account_number(Account, data_client, data_updte))
	 {
		 show_data(data_updte);
		 cout << " Are You Sure You Want update This Client [ Y / N ] : ";
		 cin >> ws >> user;
		 cin.ignore(numeric_limits<streamsize>::max(), '\n');
		 if (toupper(user) == 'Y')
		 {
			 for (Data_client& loop : data_client)
			 {
				 if (loop.Account_number == Account)
				 {
					 loop = Read_data();
					 break;
				 }
			 }
			 Delete_data_or_save(Data, data_client);
			 cout << "\n\n clirnt updata Successfully :) " << endl;
			 return true;
		 }
	 }
	 else
	 {
		 cout << "Client with Account Number  " << Account << "is Not Found :( " << endl;
		 return false;

	 }
 
 }

 void UPdate__data()
{
  system("cls");

 cout << "=============================" << endl;
 cout << "\t  Update Data \t" << endl;
cout << "=============================" << endl;

 vector<Data_client> New_data = Adding_data_in_file_TO_vactor(Data);

 string user_input = read_Account_number();

 Update_data(user_input, New_data);
 }


 void Find_data()
 {
	 Data_client data;
	 system("cls");

	 cout << "=============================" << endl;
	 cout << "\t  Find Data \t" << endl;
	 cout << "=============================" << endl;

	 string user_input = read_Account_number();

	 if (check_Account_number_And_Show_data(user_input, data))
	 {
		 cout << "\t\t Data_client\t\t"<<endl;
		 show_data(data);
	 }
	 else
	 {
		 cout << "sorry The Account Number Is Not Found :( ! "<<endl;
	 }
	
 }
  

 bool DePosit_balance (const string& Account, vector<Data_client>& data_client)///doble type ya donky 
 {
	 Data_client data_updte;
	 char user = 'n';
	 double user1 = 0;
	 if (find_data_account_number(Account, data_client, data_updte))
	 {
		 show_data(data_updte);
		 do
		 {
			 cout << "Please Enter Deposit Amount: ";
			 cin >> user1;
			 cin.ignore(numeric_limits<streamsize>::max(), '\n');
			 if (user1 <= 0)
			 {
				 cout << "Invalid amount! Please enter a positive number.\n";
			 }

		 } while (user1 <= 0);
		 cout << "Are you sure You want Perfrom this transacthion [ Y / N ] : ";
		 cin >> user;
		 if (toupper(user) == 'Y')
		 {
			 for (Data_client& loop : data_client)
			 {
				 if (loop.Account_number == Account)
				 {
					
					 loop.Account_Balance += user1;
					 cout << "New Add Deposit " << loop.Account_Balance << endl;
					 break;
				 }
			 }
			 Delete_data_or_save(Data, data_client);
			
			
			 return true;
		 }
	 }
	 else
	 {
		 cout << "Client with  [ " << Account << " ] does  Not exist  :( " << endl;
		 return false;

	 }

 }  

 void Deposit()
 {
	 string user_input = read_Account_number();
	 vector<Data_client>data_TO_vector = Adding_data_in_file_TO_vactor(Data);
	 system("cls");
	 cout << "=============================" << endl;
	 cout << "\t    Deposit   \t" << endl;
	 cout << "=============================" << endl;
	 if (DePosit_balance(user_input, data_TO_vector))
	 {
		 cout << "Transaction completed successfully!\n";
	 }
	 else
	 {
		 cout << "Transaction cancelled or failed.\n";
	 }

 }

 /// strp siven
 bool Withdraw(const string& Account, vector<Data_client>& data_client)///doble type ya donky 
 {
	 Data_client data_updte;
	 char user = 'n';
	 double user1 = 0;
	 if (find_data_account_number(Account, data_client, data_updte))
	 {
		 show_data(data_updte);
		 do
		 {
			 cout << "Please Enter Withdraw Amount : ";
			 cin >> user1;
			 cin.ignore(numeric_limits<streamsize>::max(), '\n');
			 if (user1 >= data_updte.Account_Balance)
			 {
				 cout << "Amount exceeds balance! You can withdraw up to: " << data_updte.Account_Balance << endl;
			 }

		 } while (user1 <= 0 || user1 >= data_updte.Account_Balance);
		 cout << "Are you sure You want Perfrom this transacthion [ Y / N ] : ";
		 cin >> ws >> user;
		 cin.ignore(numeric_limits<streamsize>::max(), '\n');
		 if (toupper(user) == 'Y')
		 {
			 for (Data_client& loop : data_client)
			 {
				 if (loop.Account_number == Account)
				 {

					 loop.Account_Balance -= user1;
					 cout << "Withdrawal successful! New Balance: " << loop.Account_Balance << endl;
					 break;
				 }
			 }
			 Delete_data_or_save(Data, data_client);


			 return true;
		 }
	 }
	 else
	 {
		 cout << "Client with  [ " << Account << " ] does  Not exist  :( " << endl;
		 return false;

	 }
 }

 void Withdraw()
 {
	 string user_input = read_Account_number();
	 vector<Data_client>data_TO_vector = Adding_data_in_file_TO_vactor(Data);
	 system("cls");
	 cout << "=============================" << endl;
	 cout << "\t    Withdraw   \t" << endl;
	 cout << "=============================" << endl;
	 if (Withdraw(user_input, data_TO_vector))
	 {
		 cout << "Transaction completed successfully!\n";
	 }
	 else
	 {
		 cout << "Transaction cancelled or failed.\n";
	 }
 }
 


 void print_data_B(Data_client client)
 {

	 system("Color 0A");
	 cout << "| " << setw(15) << client.Account_number;
	 cout << "| " << setw(40) << client.Full_name;;
	 cout << "| " << setw(12) << client.Account_Balance;
 }
 void print_data_B1(vector<Data_client>client)
 {
	 double total_balance = 0;
	 system("Color 0A");

	 cout << "\n\t\t\t\t\t client List(" << client.size() << ")Client(s)" << endl;

	 cout << "\n=================================================================================================*\n" << endl;
	 cout << "| " << left << setw(15) << " Accout Number ";
	 cout << "| " << left << setw(40) << " Client Name ";
	 cout << "| " << left << setw(12) << " Balance ";
	 cout << "\n=================================================================================================*\n" << endl;
	 for (Data_client One_client : client)
	 {
		 print_data_B(One_client);
		 cout << endl;
		 total_balance += One_client.Account_Balance;
	 }
	 cout << "\n\t\t\t\t\t TOtal Balances : " << total_balance << endl;
	 cout << "\n=================================================================================================*\n" << endl;

 }
 
 void Show_balance()
 {
	 vector<Data_client>New_data = Adding_data_in_file_TO_vactor(Data);
	 system("cls");
	 print_data_B1(New_data);
 }



 void Exit_Program()
 {
	 system("cls");
	 cout << "=============================" << endl;
	 cout << "\t   Thank  :)   \t" << endl;
	 cout << "=============================" << endl;
	
 }
 void Print_menu();
 void GO_back_end()
 {
	 cout << "\n\nPress any key to go back to Main Menue..." << endl;
	 system("pause>0");
	 Print_menu();
 }
 void Print_Menu_Tranacthions();
 void main_menu_back()
 {
	 cout << "\n\nPress any key to go back to Main Menue..." << endl;
	 system("pause>0");
	 Print_Menu_Tranacthions();
 }


 void start_data( EN_Record  data)///edit 
 {
 switch (data)
 {
 case EN_Record::Show:
	 system("cls");
	 show_data();
	 GO_back_end();
	 break;
 case EN_Record::Add:
	 system("cls");
	 Adding_New_Data();
	 GO_back_end();
	 break;
 case EN_Record::Delete:
	 system("cls");
	 delete_data();
	 GO_back_end();
	 break;
 case EN_Record::Update:
	 system("cls");
	 UPdate__data();
     GO_back_end();
	 break;
 case EN_Record::Find:
	 system("cls");
	 Find_data();
	 GO_back_end();
	 break;
 case EN_Record::Tranacthions:
	 system("cls");
	 Print_Menu_Tranacthions();
	 GO_back_end();
	 break;
 case EN_Record::Exit:
	 Exit_Program();
	 break;
 }

 }


 void start_data_Tranacthions(EN_Record_Tranacthions Recordeing)
 {
	 switch(Recordeing)
	 {
	 case EN_Record_Tranacthions::Deposit_1:
		 Deposit();
		 main_menu_back();
		 break;
	 case EN_Record_Tranacthions::Winthdraw_1:
		 Withdraw();
		 main_menu_back();
		 break;
	 case EN_Record_Tranacthions::toala_balances:
		 Show_balance();
		 GO_back_end();
		 break;
	 case EN_Record_Tranacthions::Main_menu:
		 main_menu_back();
		 break;
	 }

 }

 short read____()
 {
	 short data;
	 cout << "Choose what Do you  Want To Do :[ 1 To 4 ] : ";
	 cin >> data;
	 cin.ignore(numeric_limits<streamsize>::max(), '\n');
	 return data;
 }

void Print_Menu_Tranacthions()
 {
	 system("cls");
	 system("Color 0A");
	 cout << "===============================================" << endl;
	 cout << "\t\t Tranacthions Menu Screen " << endl;
	 cout << "===============================================" << endl;
	 cout << "\t Deposit         [1] . " << endl;
	 cout << "\t withdraw        [2] . " << endl;
	 cout << "\t Total Balances  [3] . " << endl;
	 cout << "\t Main Menue      [4] . " << endl;
	 cout << "===============================================" << endl;
	 start_data_Tranacthions((EN_Record_Tranacthions)read____());
 }

short raed()
{
	short r;
	cout << "Enter a Number [  1 To 7 ] :";
	cin >> r;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	return r;
}

void Print_menu()
{
	system("cls");
	system("Color 0A");
	cout << "===============================================" << endl;
	cout << "\t\t Main Menu Screen " << endl;
	cout << "===============================================" << endl;
	cout << "\t Show Client List [1] : " << endl;
	cout << "\t Add  New Client  [2] : " << endl;
	cout << "\t Delete Client    [3] : " << endl;
	cout << "\t Update Client    [4] : " << endl;
	cout << "\t Find Client      [5] : " << endl;
	cout << "\t Tranacthions     [6] : "  << endl;
	cout << "\t Exit             [7] : " << endl;
	cout << "===============================================" << endl;
	start_data((EN_Record)raed());
}

int main()
{
	Print_menu();
	system("pause>0");
	return 0;
}