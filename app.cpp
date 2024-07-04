#include	<iostream>
#include	<fstream>
#include	<cstdlib>
#include	<cstdio>
#include	<ctime>
#include	"BST.h"
#include    "Student.h"

using namespace std;

bool readFile(const char *, BST *);
int menu();

//Sub-function
void displayHeader(const char*);

int main() {

	//Declaration
	system("color 02");
	Student stu;
	BST t1, t2;
	int choice, order, source;
	char filename[100];

	//Do while loop
	do {
		choice = menu();

		switch (choice) {

		//(1)	Read data to BST
		case 1:

			displayHeader("Read Data to BST");
			cout << "\t\t\t\t\tFilename: ";
			cin >> filename;
			if (!readFile(filename, &t1))
				cout << "\n\n\t\t < < < < < < < < < < < < < Fail to open the text file > > > > > > > > > > > > > \n\n";
			else
				cout << "\n\n\t\t\t\t<<< T1 has been created with " << t1.size() << " records! >>>\n\n";
			break;

		//(2)	Print deepest nodes
		case 2:

			displayHeader("Print Deepest Nodes");
			if (!t1.deepestNodes())
				cout << "\n\n\t\t < < < < < < < < < < < < < < < < Tree is empty. > > > > > > > > > > > > > > > >\n" << endl;
			break;

		//(3)	Display student
		case 3:

			displayHeader("Display Student");
			cout << "\n\n\t\t\tHow do you want to display the information?\n";
			cout << "\t\t\t1. Display to screen" << endl;
			cout << "\t\t\t2. File" << endl;
			cout << "\t\t\tSource: ";
			cin >> source;

			cout << "\n\n\t\t\tDisplay in which order?\n";
			cout << "\t\t\t1. Ascending" << endl;
			cout << "\t\t\t2. Descending" << endl;
			cout << "\t\t\tOrder: ";
			cin >> order;
			if (!t1.display(order, source))
				cout << "\n\n\t\t < < < < < < < < < < < < < < < < Tree is empty. > > > > > > > > > > > > > > > >\n" << endl;
			break;

		//(4)	Clone Subtree
		case 4:

			displayHeader("Clone Subtree");
			cout << "\t\t\t\t\tID: ";
			cin >> stu.id;
			if (t2.CloneSubtree(t1, stu)) {
				system("cls");
				cout << "********************************************************************************\n";
				cout << "                                       T1\n";
				cout << "********************************************************************************\n";
				t1.preOrderPrint();
				cout << "********************************************************************************\n";
				cout << "                                       T2\n";
				cout << "********************************************************************************\n";
				t2.preOrderPrint();
			}
			else
				cout << "\n\n\t\t< < < < < < < < < < < < < < Cannot clone subtree. > > > > > > > > > > > > > > >\n";
			break;

		//(5)	Print Level Nodes
		case 5:

			displayHeader("Print Level Nodes");
			if (!t1.printLevelNodes())
				cout << "\n\n\t\t < < < < < < < < < < < < < < < < Tree is empty. > > > > > > > > > > > > > > > >\n" << endl;
			break;

		//(6)	Print Path
		case 6:

			displayHeader("Print Path");
			if (!t1.printPath())
				cout << "\n\n\t\t < < < < < < < < < < < < < < < < Tree is empty. > > > > > > > > > > > > > > > >\n" << endl;
			break;

		//(7)	Exit
		case 7:

			break;

		default:
			cout << "\n\n\t\t < < < < < < < < < < < < INVALID INPUT. PLEASE TRY AGAIN. > > > > > > > > > > >\n\n";
		}
		cout << endl << "\t\t\t\t\t";
		system("pause");
		system("cls");

	} while (choice != 7);
	
	return 0;
}

//(1)	Read data to BST
bool readFile(const char* filename, BST* t1) {
	
	//Declaration
	int dup = 0;
	Student stulist;
	char n[256];
	bool exist = false;
	ifstream infile(filename);

	//Check if tree is empty
	if (!t1->empty()) t1->EmptyList();

	//Check if the file can be opened
	if (infile.fail()) return false;

	//Read file
	while (!infile.eof()) {
		for (int i = 0; i < 3; i++) infile >> n;
		infile >> stulist.id;
		for (int i = 0; i < 2; i++) infile >> n;
		infile.getline(stulist.name, 30);
		for (int i = 0; i < 2; i++) infile >> n;
		infile.getline(stulist.address, 100);
		for (int i = 0; i < 2; i++) infile >> n;
		infile >> stulist.DOB;
		for (int i = 0; i < 3; i++) infile >> n;
		infile >> stulist.phone_no;
		for (int i = 0; i < 2; i++) infile >> n;
		infile >> stulist.course;
		for (int i = 0; i < 2; i++) infile >> n;
		infile >> stulist.cgpa;

		//Check duplicates
		t1->FindItem(stulist, t1->root, exist);
		if (!exist && infile)
			t1->insert(stulist);
		else
			dup++;
	}
	//Output duplicates (if any)
	if (exist)
		cout << endl << "\t\t\t\t\t" << dup << " duplicate record(s) found!\n";
	
	//Check if text file is empty
	if (t1->empty())
		cout << endl << "\t\t\t\t\t" << filename << " is empty" << endl;

	infile.close();
	return true;
}

//Display Menu
int menu() {

	//Declaration
	int choice;

	//Menu
	cout << "\t\t\t     ___           ___           ___           ___     " << endl;
	cout << "\t\t\t    /\\  \\         /\\__\\         /\\  \\         /\\  \\    " << endl;
	cout << "\t\t\t   |::\\  \\       /:/ _/_        \\:\\  \\        \\:\\  \\   " << endl;
	cout << "\t\t\t   |:|:\\  \\     /:/ /\\__\\        \\:\\  \\        \\:\\  \\  " << endl;
	cout << "\t\t\t __|:|\\:\\  \\   /:/ /:/ _/_   _____\\:\\  \\   ___  \\:\\  \\ " << endl;
	cout << "\t\t\t/::::|_\\:\\__\\ /:/_/:/ /\\__\\ /::::::::\\__\\ /\\  \\  \\:\\__\\" << endl;
	cout << "\t\t\t\\:\\~~\\  \\/__/ \\:\\/:/ /:/  / \\:\\~~\\~~\\/__/ \\:\\  \\ /:/  /" << endl;
	cout << "\t\t\t \\:\\  \\        \\::/_/:/  /   \\:\\  \\        \\:\\  /:/  / " << endl;
	cout << "\t\t\t  \\:\\  \\        \\:\\/:/  /     \\:\\  \\        \\:\\/:/  /  " << endl;
	cout << "\t\t\t   \\:\\__\\        \\::/  /       \\:\\__\\        \\::/  /   " << endl;
	cout << "\t\t\t    \\/__/         \\/__/         \\/__/         \\/__/    " << endl;

	cout << "\n\n\t\t\t\t\t(1)	Read data to BST\n";
	cout << "\t\t\t\t\t(2)	Print deepest nodes\n";
	cout << "\t\t\t\t\t(3)	Display student\n";
	cout << "\t\t\t\t\t(4)	Clone Subtree\n";
	cout << "\t\t\t\t\t(5)	Print Level Nodes\n";
	cout << "\t\t\t\t\t(6)	Print Path\n";
	cout << "\t\t\t\t\t(7)	Exit\n";
	cout << "\t\t\t\t\tSelection (1-7): ";

	cin >> choice;
	cin.ignore();
	system("cls");
	return choice;
}

//Sub-function

//Display Header
void displayHeader(const char* header) {
	int length = 0;
	length = (76 - strlen(header)) / 2;
	cout << "\t\t********************************************************************************\n\t\t";
	for (int i = 0; i <= length; i++) cout << " ";
	cout << header;
	for (int i = 0; i <= length; i++) cout << " ";
	cout << endl;
	cout << "\t\t********************************************************************************\n\n";
}