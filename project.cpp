#include<iostream>
#include<string.h>
#include<string>
#include<fstream>
#include<vector>
#include<conio.h>
#define KEY_LEFT 75
#define KEY_RIGHT 77 //to move back and forth between movies
using namespace std;
void adminfunctions();
class Customer;
class Theatre;
class Movie
{
	static int position; //this is to determine position of read pointer
	//so the next time we open file we can start reading from the same position
	string  title, runtime, synopsis, line, id;
public:
	Movie() //read data from file and paste to movie attributes
	{
		ifstream is("movies.txt");
		if (is)
		{
			is.seekg(position, ios::beg);
			getline(is, line);
			title = line;
			getline(is, line);
			id = line;
			getline(is, line);
			runtime = line;
			getline(is, synopsis, '/');
			position = is.tellg();
		}
		else
		{
			cout << "File not found.";
		}

		is.close();
	}
	void display()
	{
		cout << "Movie ID: " << id << endl;
		cout << "Movie Title: " << title << endl;
		cout << "Running Time: " << runtime << endl;
		cout << "Synopsis: \n\n" << synopsis << endl;
	}
	string getID()
	{
		return id;
	}
	string getname()
	{
		return title;
	}
}; int Movie::position = 0;
static vector <Movie> object;//vector of movie objects so I can add another movie later on
class Registration
{
public:
	Registration(){}
	int menu()
	{
		int choice;
		cout << "\t\t------------Menu----------" << endl;
		cout << "[1]		View Ticket" << endl;
		cout << "[2]		Main Menu" << endl;
		cin >> choice;
		return choice;
	}
};
class Booking:public Registration
{
	char* moviename = new char[500];
	char* time = new char[10];
	char* date = new char[500];
	char* movieid = new char[50];
	char* category = new char[500];
	int numberoftickets;
	double price;
	static int goldseats;
	static int silverseats;
	static int diamondseats;
public:
	Booking()
	{

	}
	void movieselection()
	{
		string temp;
		cout << "Use arrow keys to move to the next or previous movie. Press y for movie selection." << endl << endl;
		vector <Movie> ::iterator itr = object.begin();
		itr->display();
		itr = object.begin();
		while (1)
		{

			int c = _getch();
			if (c == 0 || c == 224|| c == 'y')
			{
				if (c == 'y')
				{
					temp = itr->getID();
					strcpy_s(movieid, 6, temp.c_str());
					temp = itr->getname();
					strcpy_s(moviename, 499, temp.c_str());
					break;

				}
				switch ((c = _getch())) 
				{
				case KEY_LEFT:

					if (itr == object.begin())
					{
						break;
					}
					else
					{
						system("CLS");
						itr--;
						itr->display();
						break;
					}

				case KEY_RIGHT:
					if (itr == object.end() - 1)
					{
						break;
					}
					else
					{
						system("CLS");
						itr++;
						itr->display();
						break;
					}
				default:
					cout << "Non standard input" << endl;

				}
			}

		}
		system("CLS");
		while (1)
		{
			
			int timechoice;
			cout << "Available Timings" << endl;
			cout << "[1]	4:00 pm" << endl;
			cout << "[2]	7:00 pm" << endl;
			cout << "[3]	11:00 pm" << endl;
			cin >> timechoice;
			if (timechoice == 1)
			{
				temp = "4:00 pm";
				strcpy_s(time, 9, temp.c_str());
				break;
			}
			else if (timechoice == 2)
			{
				temp = "7:00 pm";
				strcpy_s(time, 9, temp.c_str());
				break;
			}
			else if (timechoice == 3)
			{
				temp = "11:00 pm";
				strcpy_s(time, 9, temp.c_str());
				break;
			}
			else if (timechoice != 1 && timechoice != 2 && timechoice != 3)
			{
				cout << "\nInvalid Input" << endl;;
				cin.clear();
				cin.ignore();
			}
				
		}
		cin.ignore();
		system("CLS");
		cout << "Select number of tickets: (You can purchase a maximum of 20 tickets at a time) " << endl;
		while (1)
		{
			cin >> numberoftickets;
			if (numberoftickets > 20 || cin.fail())
			{
				cout << "Error, please enter a value less than 21" << endl;
				cin.clear();
				cin.ignore();
			}
			else
				break;
		}
		cin.ignore();
		system("CLS");
		cout << "Ticket Prices: " << endl;
		ifstream ifs("price.txt");
		if (ifs)
		{
			string z;
			getline(ifs, z);
			cout << "Gold Ticket: " << z << " Rs" << endl;
			getline(ifs, z);
			cout << "Silver Ticket: " << z << " Rs" << endl;
			getline(ifs, z);
			cout << "Diamond Ticket: " << z << " Rs" << endl;
			ifs.close();
		}
		cout << "\nSelect Ticket Type: " << endl;
		cout << "[1]	Gold" << endl;
		cout << "[2]	Silver" << endl;
		cout << "[3]	Diamond " << endl;
		int x;
		string tempo;
		while (1)
		{
			cin >> x;
			if (x == 1)
			{
				if (goldseats >= numberoftickets)
				{
					tempo = "gold";
					strcpy_s(category, 9, tempo.c_str());
					goldseats = goldseats - numberoftickets;
					break;
				}
				else
				{
					cout << "\nSeats Unavailable" << endl;
				}
					
			}
			if (x == 2)
			{
				if (silverseats >= numberoftickets)
				{
					tempo = "silver";
					strcpy_s(category, 9, tempo.c_str());
					silverseats = silverseats - numberoftickets;
					break;
				}
				else
					cout << "\nSeats Unavailable" << endl;
			}
			if (x == 3)
			{
				if (silverseats >= numberoftickets)
				{
					tempo = "diamond";
					strcpy_s(category, 9, tempo.c_str());
					diamondseats = diamondseats - numberoftickets;
					break;
				}
				else
					cout << "\nSeats Unavailable" << endl;
			}
			if (x != 1 && x != 2 && x != 3)
			{
				cout << "\nInvalid Input" << endl;
				cin.clear();
				cin.ignore();
			}
		}
		
	}
	void getprice()
	{
		ifstream inp("price.txt");
		if (inp)
		{
			string temp;
			if (strcmp(category, "gold") == 0)
			{
				getline(inp,temp);
				price = stoi(temp);
				price = price*numberoftickets;

			}
			if (strcmp(category, "silver") == 0)
			{
				getline(inp, temp);
				getline(inp, temp);
				price = stoi(temp);
				price = price*numberoftickets;

			}
			if (strcmp(category, "diamond") == 0)
			{
				getline(inp, temp);
				getline(inp, temp);
				getline(inp, temp);
				price = stoi(temp);
				price = price * numberoftickets;
			}
			inp.close();
		}
		cout << "Your movie selection is complete, press any key to proceed to pruchase details.";
		_getch();
		system("CLS");
	}
	
	void viewbooking()
	{
		cout << "\n\n----Movie Booking Details----\n\n";
		cout << "Movie ID: " << movieid << endl;
		cout << "Movie Name: " << moviename << endl;  
		cout << "Movie Time: " << time << endl;
		cout << "Ticket category: " << category << endl;
		cout << "Number of Tickets Booked: " << numberoftickets << endl;
		cout << "Total price of Tickets: " << price << endl << endl;
	}
	void fileit()
	{

		ofstream os1("customerdetails.txt", ios::app | ios::binary);
		os1.write((char*)this, sizeof(*this));
		os1.close();
	}
	void showit()
	{
		ifstream is1("customerdetails.txt");
		if (is1)
		{

			is1.read((char*)this, sizeof(*this));
		}
		viewbooking();
		is1.close();
	}
}; 
int Booking::goldseats = 100;
int Booking::silverseats = 100;
int Booking::diamondseats = 100;
class Customer:public Registration
{
	char* firstname = new char[500];
	char* lastname = new char[500];
	char* email = new char[500];
	char* number = new char[500];
	char* address = new char[500];
public:
	Customer()
	{
	}
	void customerdataregistration()
	{
		cin.ignore();
		cout << "Enter your First Name : ";
		cin.getline(firstname, 499);
		cout << "Enter your Last Name: ";
		cin.getline(lastname, 499);
		cout << "Enter your Email Address : ";
		cin.getline(email, 499);
		cout << "Enter your Contact Number : ";
		cin.getline(number, 499);
		cout << "Enter your Address : ";
		cin.getline(address, 499);
		cout << "Your information has been registered, press any key to proceed to the movie booking!";
		_getch();
		system("CLS");
	}
	void displaycustomerdetails()
	{
		
		cout << "\n----Customer Details----" << endl;
		cout << "\nFirst Name : " << firstname << endl;
		cout << "Last Name : " << lastname << endl;
		cout << "Contact Number : " << number << endl;
		cout << "Email : " << email << endl;
		cout << "Address: " << address << endl;
	}

	void fileit()
	{
		ofstream os2("customerdetails.txt", ios::app| ios::binary);
		os2.write((char*)this, sizeof(*this));
		os2.close();
	}
	void showit()
	{
		ifstream is2("customerdetails.txt");
		if (is2)
		{
			is2.read((char*)this, sizeof(*this));
		}
		displaycustomerdetails();
		is2.close();
	}

};
class Purchase : public Registration
{
	char* cc_number = new char[200];
	char* cc_code = new char[200];
	char* cc_expiration_month = new char[200];
	char* cc_expiration_year = new char[200];
public:
	Purchase()
	{

	}
	void purchaseinput()
	{
		
		cin.ignore();
		while (1)
		{
			int x = 0;
			cout << "Enter Credit Card Number: ";
			cin.getline(cc_number, 199);
			if (is_digits(cc_number) == false)
			{
				x = 1;
			}
			cout << "Enter Credit Card Code: ";
			cin.getline(cc_code, 199);
			if (is_digits(cc_code) == false)
			{
				x = 1;
			}
			cout << "Enter Credit Expiry Month: ";
			cin.getline(cc_expiration_month, 199);
			if (is_digits(cc_expiration_month) == false)
			{
				x = 1;
			}
			cout << "Enter Credit Card Expiry Year: ";
			cin.getline(cc_expiration_year, 199);
			if (is_digits(cc_expiration_year) == false)
			{
				x = 1;
			}
			if (x == 0)
				break;
			else
				cout << "\nThe above fields only accept numbers as valid input, try again" << endl;
		}
		
		cout << "Movie Ticket Booked!" << endl;
		system("PAUSE");
		system("CLS");
	}
	bool is_digits(const std::string& str) //checking if input is numbers only
	{
		return str.find_first_not_of("0123456789") == std::string::npos;
	}
	void purchasedetails()
	{
		cout << "----Purchase Details----" << endl;
		cout << "\nCredit Card Number: " << cc_number << endl;
		cout << "Credit Card Code: " << cc_code << endl;
		cout << "Credit Card Expiry Month: " << cc_expiration_month << endl;
		cout << "Credit Card Expiry Year: " << cc_expiration_year << endl;
	}
	void fileitt()
	{
		ofstream os("customerdetails.txt", ios::app | ios::binary);
		os.write((char*)this, sizeof(*this));
		os.close();

	}
	void showitt()
	{
		ifstream is("customerdetails.txt");
		if (is)
		{

			is.read((char*)this, sizeof(*this));
		}
		purchasedetails();
		is.close();
	}


};
class Admin
{
	string usernameentered, usernamefromfile, passwordentered, passwordfromfile;
	bool valid;
	//password entered is the user password input attemtping to login
	//password from file is the correct password to be comapred to
	//same with username
	char pass[5];
	//character array pass holds password then it is copied to string to make comparison easier
public:
	bool getValidity()
	{
		return valid;
	}
	void menu()
	{
		cout << "Select Option: " << endl;
		cout << "[1]	Add Movie" << endl;
		cout << "[2]	Delete Movie" << endl;
		cout << "[3]	View Movies" << endl;
		cout << "[4]	Change Password" << endl;
		cout << "[5]	View All Bookings" << endl;
		cout << "[6]	Main Menu" << endl;
	}
	void adminmenu()
	{
		int choice=0;
		while (choice!=6)
		{
			this->menu();
			fflush(stdin);
			cin >> choice;
			if (choice == 1)
			{
				system("CLS");
				this->addmovie();
				cout << "Movie added successfully!" << endl;
				system("PAUSE");
				system("CLS");
			}
			if (choice == 2)
			{
				system("CLS");
				this->deletemovie();
				cout << "Movie deleted successfully!" << endl;
				cout << "Movie will not be available for future customers to view." << endl;
				system("PAUSE");
				system("CLS");
			}

			if (choice == 4)
			{
				system("CLS");
				this->changepassword();
				system("PAUSE");
				system("CLS");
			}
			if (choice == 3)
			{
				system("CLS");
				cout << "\n\t\t----------MOVIE LIST----------" << endl;
				for (Movie v : object)
					v.display();
				cout << "\n\t\t\t-x-x-x-x-x-x-x-x--x-x-x-x-x-x-x-x-\n\n\n";
				system("PAUSE");
				system("CLS");
			}
			if (choice == 5)
			{
				system("CLS");
				viewbookings();
				system("PAUSE");
				system("CLS");
			}
			if (choice == 6)
			{
				system("CLS");
				break;
			}
				
		}
	}
	void maskpassword() //takes password input from user and from file
	{
		passwordentered = "";
		fflush(stdin);
		char ch;
		for (int i = 0;i<5;) //masking password with aesterik until user presses enter
		{
			ch = _getch();
			if (ch == '\r') //terminate whe user presses enter
				break;
			if (ch == '\b')// handle backspace
			{
				
				if (i <=0)
				{

				}
				else
				{
					cout << "\b \b";
					i--; //so we can overwrite this array element again
				}
				    
			}
			else
			{
				pass[i] = ch;
				cout << "*";
				i++;
			}
		}
		for (int i = 0; i < 5; i++) //array stored in string
		{
			passwordentered.push_back(pass[i]);
		}
		//not efficient but works ¯\_(ツ)_/¯
		ifstream is("admin.txt");
		if(is)
		{
			getline(is, usernamefromfile);
			getline(is, passwordfromfile);
		}
		else
		{
			cout << "Error Opening File";
		}
		is.close();
	}
	Admin()
	{
		int i = 0;
		int x = 0;
		while (1)
		{
			cout << "Username: ";
			cin >> usernameentered;
			cout << "Enter 5-character Password:  ";
			maskpassword();
			if (passwordentered == passwordfromfile && usernameentered == usernamefromfile)
			{
				cout << "\n\nLogin Successful!\n";
				x = 1;
				passwordentered = "";
				valid = true;
				system("PAUSE");
				system("CLS");
				break;
				
			}
			else
			{
				cout << "\n\nUsername or password Incorrect.\n";
				i++;
				passwordentered = "";
			}

			//3 tries for password
			if (i == 3)
			{
				cout << "\n\nYou have entered password incorectly 3 times :(";
				valid = false;
				break;
			}
		}

	}
	void changepassword()
	{
		char ch;
		cout << "Enter Previous Password: ";
		maskpassword();
		if (passwordentered == passwordfromfile)
		{
			while (1)
			{
				cout << "\nEnter new password, password length MUST be 5 characters: ";
				passwordentered = "";
				cin >> passwordentered;
				if (passwordentered.length() != 5)
					cout << "Password must be 5 characters long" << endl;
				else
					break;
			}
			
			
			ifstream is("admin.txt");
			string line;
			if (is)
			{
				getline(is, line, '/');
				int pos = line.find(passwordfromfile);
				if (pos != string::npos)
				{
					line.replace(pos, 5, passwordentered);
					ofstream os("admin.txt");
					os << line << endl;
					os.put('/');
					os.close();
				}

				is.close();
			}

			else
				cout << "Error Opening File";

			cout << "\nPassword changed successfully" << endl;

		}
		else
		{
			cout << "Incorrect Password." << endl;
		}
		
	}
	void addmovie()
	{
		string s; //temporary string to hold movie info
		ofstream os("movies.txt", ios::app); //open file in append mode to add movies
		cin.ignore();
		cout << "Enter Movie Title: ";
		getline(cin, s);
			os << s << endl;
		while (1)
		{
			int z = 0;
			cout << "Enter Movie ID: ";
			cin >> s;
			for (Movie v: object)
			{
				if (s == v.getID())
				{
					z = 1;
					cout << "ID must be unique.\n";
					break;
				}
			}
			if (z == 0)
			{
				os << s << endl;
				break;
			}
		}
		fflush(stdin);
		cin.ignore();
		cout << "Enter Running Time: ";
		getline(cin, s);
		os << s << endl;
		cin.ignore();
		cout << "Enter Synopsis: ";
		fflush(stdin);
		while (getline(cin, s) && s !="")
		{
			os << s << endl;
		}
		os.put('/'); //to identify where one movie ends 
		os.close();
		Movie newmovie; //creating an instance of movie, the constructor will read the movie 
		//data just entered from file and paste it to the new movie object
		object.push_back(newmovie); //adding new movie to vector
	}
	void deletemovie()
	{
		string s; //temporary string to hold movie info
		ifstream is("movies.txt"); //open file in append mode to add movies
		while (1)
		{
			int z = 0;
			cout << "Enter id of movie you want to delete: ";
			cin >> s;
			for (int i = 0; i < object.size(); i++)
			{
				if (s == object[i].getID())
				{
					object.erase(object.begin() + i);
					z = 1;
					break;
				}
			}
			if (z == 0)
				cout << "Invalid ID entered." << endl;
			else
			{
				break;
			}
		}
	}
	void viewbookings()
	{
		ifstream handles("customerdetails.txt");
		Customer obj;
		Booking obj1;
		Purchase obj2;
		if (handles)
		{
			handles.read((char*)&obj, sizeof(obj));
			handles.read((char*)&obj1, sizeof(obj1));
			handles.read((char*)&obj2, sizeof(obj2));
			while (!handles.eof())
			{
				obj.displaycustomerdetails();
				obj1.viewbooking();
				obj2.purchasedetails();
				handles.read((char*)&obj, sizeof(obj));
				handles.read((char*)&obj1, sizeof(obj1));
				handles.read((char*)&obj2, sizeof(obj2));
			}
		}
		else
		{
			cout << "\nUnable to open file." << endl;
		}
		handles.close();
	}
};
class Theatre
{
public:
	void displaybox() //I kinda stole this :/
	{
		system("CLS");
		cout << endl;

		// Upper Border
		cout << " \xC9";
		for (int i = 0; i < 76; i++)
			cout << "\xCD";
		cout << "\xBB";
		cout << endl;

		// Middle Border
		cout << " \xBA";
		//      starts here                                                        ends here
		cout << "                          Movie Reservation System                          ";
		cout << "\xBA";
		cout << endl;

		// Upper Border
		cout << " \xC8";
		for (int i = 0; i < 76; i++)
			cout << "\xCD";
		cout << "\xBC";
		cout << endl;
		cout << endl;
	}

	void mainmenu()
	{
		cout << "Welcome to the Movie Reservation System! " << endl;
		cout << "Select option: " << endl;
		cout << "[1]	User" << endl;
		cout << "[2]	Admin" << endl;
		cout << "[3]	Exit" << endl;

	}
	void mainmenuoptions() //choose from main menu using switch
	{
		while (1)
		{
			int choice;
			cin >> choice;
			if (choice == 1)

			{
				system("CLS");
				Customer* cust = new Customer;
				cust->customerdataregistration();
				cust->fileit();
				Booking* book = new Booking;
				book->movieselection();
				book->getprice();
				book->fileit();
				Purchase* pur = new Purchase;
				pur->purchaseinput();
				pur->fileitt();
				Registration* obj = new Registration;
				int c;
				while (1)
				{
					c = obj->menu();
					if (c == 1)
					{
						system("CLS");
						cout << "\n\t\t\t\t------------Ticket-----------\n" << endl;
						cust->displaycustomerdetails();
						book->viewbooking();
						pur->purchasedetails();
						system("PAUSE");
						system("CLS");
					}
					if (c == 2)
					{
						system("CLS");
						mainmenu();
						mainmenuoptions();
					}
				}
				break;
			}
			if (choice == 2)
			{
				system("CLS");
				adminfunctions();
				break;
			}
			if (choice == 3)
			{
				//to clear all object data files
				ofstream filehandler("customerdetails.txt");
				filehandler.close();
				exit(1);
			}
			if (choice != 1 && choice != 2 && choice != 3)
			{
				cout << "\nInvalid Input" << endl;
				cin.clear();
				cin.ignore();
			}
		}
		
	}
}; // this is the main class, Like the head class
Theatre* display = new Theatre;
int main()
{
	for (int i = 0; i < 5; i++) //read all movies from file and create objects, adding them to vector
	{
		Movie mov;
		object.push_back(mov);
	}
	display->displaybox();
	display->mainmenu();
	display->mainmenuoptions();

}
void adminfunctions() //checks if password is correct then gives access to admin functions
{
	cout << "To enter the admin panel, login first" << endl;
	Admin* obj = new Admin;
	if (obj->getValidity() == true)
	{
		obj->adminmenu();
	}
	else if (obj->getValidity() == false) //if the user doesn't enter correct password, the admin object is deleted to prevent access of any admin functions
	{
		delete obj;
		display->mainmenu();
		display->mainmenuoptions();
	} 
	display->mainmenu(); //if the user chooses to go to main menu from the admin options, he exits a loop and flow diverts here
	display->mainmenuoptions();
}
