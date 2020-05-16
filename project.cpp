#include<iostream>
#include<string>
#include<fstream>
#include<vector>
using namespace std;

class displays
{
public:
	void DisplayHeader()
	{
		system("cls");
		cout << endl;

		// Upper Border
		cout << " \xC9";
		for (int i = 0; i < 76; i++)
			cout << "\xCD";
		cout << "\xBB";
		cout << endl;

		// Middle Border
		cout << " \xBA";
		//      [FROM_HERE                                                            TO_HERE]
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
		cout << "Welcome to the Movie Reservation System. " << endl;
		cout << "Select option: " << endl;
		cout << "[1]	User" << endl;
		cout << "[2]	Admin" << endl;
	}
	void displayusermenu()
	{
		cout << "Select Option: " << endl;
		cout << "[1]	Book Ticket" << endl;
		cout << "[2]	View Ticket" << endl;
		cout << "[3]	Cancel Booking" << endl;
		cout << "[4]	Exit" << endl;
	}
	void displayadminmenu()
	{
		cout << "Select Option: " << endl;
		cout << "[1]	Add Movie" << endl;
		cout << "[2]	Delete Movie" << endl;
		cout << "[3]	Another option" << endl;
	}
};
displays display;
class Movie
{
	static int position; //this is to determine position of read pointer
	//so the next time we open file we can start reading from the same position
	string  title,  runtime, synopsis, line, id;
	public:
	
	Movie() //read data from file and paste to movie attributes
	{
		ifstream is("movies.txt");
		if(is)
		{
		is.seekg(position, ios::beg);
		getline(is, id);
		getline(is, line);
		title = line;
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
}; int Movie::position = 0;
vector <Movie> object;//vector of movie objects so I can add another movie later on
class Admin
{
	public:
	void addmovie()
	{
		string s; //temporary string to hold movie info
		ofstream os("movies.txt", ios::app); //open file in append mode to add movies
		
		while(1)
		{
			int z=0;
			cout << "Enter Movie ID: ";
		    cin >> s;
		for(Movie v: object)
		{
		if(s==v.getID())
		{
			z=1;
			cout << "ID must be unique.\n";
			break;	
		}
		}
		if(z==0)
		{
		os << s << endl;
		break;
		}
		}
		fflush(stdin);
		cout << "Enter Movie Title: ";
    while( getline( cin, s ) && s != "" )
    {
        os << s << endl;
    }
	cout << "Enter Running Time: ";
	getline(cin , s);
	os << s << endl;
	cout << "Enter Synopsis: ";
	while( getline( cin, s ) && s != "" )
    {
        os << s << endl;
    }
	os.put('/'); //to identify where one movie ends 
	os.close();
	Movie newmovie; //creating an instance of movie, the constructor will read the movie 
	//data just entered from file and paste it to the new movie object
	object.push_back(newmovie); //adding new movie to vector
	}
};

int main()
{
	display.DisplayHeader();
	system("PAUSE");
	display.displayadminmenu();
	system("PAUSE");
	display.displayadminmenu();
	system("PAUSE");
	 
	for(int i=0; i<5; i++)
	{
		Movie mov;
	object.push_back(mov);
	//object[i].display();
	}
	Admin obj;
	//obj.addmovie();
	for(Movie v: object)
	v.display();
}



