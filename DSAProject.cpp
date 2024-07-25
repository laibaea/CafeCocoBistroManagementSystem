#include<iostream>	//PREPROCESSOR DIRECTIVE
#include<stdio.h>	//PREPROCESSOR DIRECTIVE
#include<stdlib.h>	//PREPROCESSOR DIRECTIVE
#include<conio.h>	//PREPROCESSOR DIRECTIVE
#include<string.h>	//PREPROCESSOR DIRECTIVE
#include<ctime>		//PREPROCESSOR DIRECTIVE
#include<fstream>	//PREPROCESSOR DIRECTIVE
#include<string>	//PREPROCESSOR DIRECTIVE

using namespace std;	//STANDARD LIBRARY

void insert(string n, float p, int fin);		//FUNCTION DECLARATION
int sizefll();
void delete_dish(int pos); 					//void delete_at_start(); void delete_at_end();
void display();
int login();
void order();
void display_rd_hist();
void edit();
struct Item* binarySearch(int key);			//struct Item* middle(Item* start, Item* end)
struct order_hist* getnewNode_hist();


struct Item					//STRUCTURE TO STORE MENU ITEMS
{
	string name;
	float rating;
	float price;
	int food_Id_No;
	struct Item* next;
	struct Item* prev;
};

int cust_id = 1;			//GLOBAL VARIABLES
struct Item* head;
struct Item* last;
int today_customer = 0;
float total_earning = 0;

struct order_hist		//STRUCTURE TO STORE ORDER HISTORY
{
	int customer_ID;
	int items[10][2];
	float amount;
	string date;
	struct order_hist* next;
	struct order_hist* prev;
};

struct order_hist* head1;
struct order_hist* last1;

void insert(string n, float p, int fin)
{
	struct Item* temp = new Item();
	temp->food_Id_No = fin;
	temp->name = n;
	temp->rating = 5.0;
	temp->price = p;
	temp->next = NULL;
	temp->prev = NULL;

	if (head == NULL)
	{
		head = temp;
		last = temp;
	}

	else
	{
		temp->prev = last;
		last->next = temp;
		last = temp;
	}
}

int sizefll()			//calulating size of the linkedlist
{
	int count = 1;
	Item* temp = head;

	if (temp == NULL)
	{
	}
	else {
		while (temp->next != NULL)
		{
			temp = temp->next;
			count++;
		}
	}
	return count;
}

void delete_at_start()
{
	struct Item* temp = head;
	if (sizefll() == 1)
	{
		cout << "Delete at start is empty!" << endl;
	}
	else
	{
		head = head->next;
		temp = NULL;
		delete temp;
	}
	struct Item* temp2 = head;
	for (int i = 1; i <= last->food_Id_No; i++)
	{
		temp2->food_Id_No = i;
		if (temp2->next == NULL)
		{

		}
		else {
			temp2 = temp2->next;
		}
	}
}

void delete_at_end()
{
	struct Item* temp = head;
	struct Item* temp2 = new Item();
	temp2 = temp;
	while (temp->next != NULL)
	{
		temp2 = temp;
		temp = temp->next;
	}
	temp2->next = NULL;
	delete temp;
}

void delete_dish(int pos)
{
	int count = 1;
	struct Item* temp = new Item();
	temp = head;

	struct Item* temp2 = new Item();
	temp2 = head;
	int check = sizefll();


	if (pos == 1)
	{
		delete_at_start();
	}
	else if (pos == check)
	{
		delete_at_end();
	}
	else
	{

		while (count != pos)		//delete_at_mid
		{
			temp2 = temp;
			temp = temp->next;
			++count;
		}
		temp2->next = temp->next;
		delete temp;

		Item* temp4 = head;				//fixing indexes 
		for (int i = 1; i <=last->food_Id_No; i++)
		{
			temp4->food_Id_No = i;
			if (temp4->next == NULL)
			{

			}
			else 
			{
				temp4 = temp4->next;
			}
		}
	}
}

struct order_hist* getnewNode_hist()
{
	struct order_hist* temp = new order_hist();
	temp->next = temp->prev = NULL;
	return (temp);
}

void display()
{
	cout << "                                             -------------                                            \n";
	cout << "---------------------------------------------    MENU    ----------------------------------------------\n";
	cout << "                                             -------------                                            \n";
	cout << "INDEX\t\tITEM NAME\t\tPRICE\t\tRATING\n\n";

	struct Item* temp = head;
	if (temp == NULL)
	{
		cout << "Empty" << endl;
	}

	while (temp != NULL)
	{
		cout << temp->food_Id_No << "\t\t" << temp->name << "\t\t" << temp->price << "\t\t" << temp->rating << "\n";
		temp = temp->next;
	}
	cout << "-------------------------------------------------------------------------------------------------------\n";
}


int login()
{
	char username[6];
	char userpwd[8]; // for storing password
	int i;

	cout << "Enter your User name : ";
	cin >> username;

	cout << "Enter your Password : ";
	for (i = 0; i < 8; i++)
	{
		userpwd[i] = _getch();
		cout << "*";
	}
	userpwd[i] = '\0';


	if (!strcmp(username, "danial") && !strcmp(userpwd, "danial12") || !strcmp(username, "laiba") && !strcmp(userpwd, "laiba123") || !strcmp(username, "zawar") && !strcmp(userpwd, "zawar123"))
	{
		cout << "\n\nLogged In Successfully!\n";
		return 1;
	}

	else
	{
		cout << "\n\nIncorrect Username or Password!!\n";
		return 0;
	}
	return 1;
}

void order()
{

	ofstream f;
	int a[10][10];	//MENU
	int orderop, j = 0, i = 0; // id & quantity
	time_t now = time(0);

	// convert now to string form
	char* dt = ctime(&now);

	do {
		display();
		cout << "Please Enter the Food ID and Quantity: ";
		for (i = 0; i < 2; i++)
		{
			cin >> a[j][i];
		}
		j++;
		cout << "Do you want to order more items?";
		cout << "\n\t1. Yes! :D \n\t2. No :( ";
		cout << "\nEnter: ";
		cin >> orderop;
	} while (orderop == 1);

	Item* temp = new Item();
	float total_amount = 0.0;
	string name;
	cout << "Enter your Name : ";
	cin >> name;
	temp->name = name;

	int quan = 0;
	cout << "\n";
	cout << "                  -------------                                            \n";
	cout << "------------------    BILL     ------------------\n";
	cout << "                  -------------                                            \n"<<endl;
	cout << "Name:\t\t" << name << endl;
	cout << "Date & Time:\t" << dt << endl;

	for (quan = 0; quan < j; quan++)
	{
		struct Item* temp = head;
		while (temp->food_Id_No != a[quan][0])
		{
			temp = temp->next;
		}//printf("%f\n",temp->price);

		cout << "\n-------------------------------------------------\n";
		cout << temp->food_Id_No << "\t" << temp->name << "\t" << a[quan][1] << "\t\t" << (a[quan][1] * (temp->price)) << "\n";
		total_amount += (a[quan][1] * (temp->price));
	}

	cout << "\n-------------------------------------------------"<<endl;
	cout << "\tTotal Payment Amount: \t\t" << total_amount << endl;
	cout << "-------------------------------------------------\n";


	f.open("BillRecord.txt", ios::app);				//FILE NAME
	if (f.is_open())								//CHECK IF FILE IS OPEN
	{
		f << "\n\n\n-------------------------------------------------\n";
		f << "                      BILL                       \n"<<endl;
		f << "Name:\t\t" << name << endl;
		f << "Date & Time:\t" << dt << endl;

		for (quan = 0; quan < j; quan++)
		{
			struct Item* temp = head;
			while (temp->food_Id_No != a[quan][0])
			{
				temp = temp->next;
			}

			f << "\n-------------------------------------------------\n";
			f << temp->food_Id_No << "\t" << temp->name << "\t" << a[quan][1] << "\t\t" << (a[quan][1] * (temp->price)) << "\n";
		}										

		f << "\n-------------------------------------------------"<<endl;
		f << "\tTotal Payment Amount: \t\t" << total_amount << endl;
		f << "-------------------------------------------------\n";
	}
	else										//ERROR IF FILE IS NOT OPEN
	{
		cout << "Error: file could not be opened!" << endl;
	}
	f.close();


	struct order_hist* temp2 = getnewNode_hist();
	temp2->amount = total_amount;
	temp2->customer_ID = cust_id++;

	int p, s;		//ID & quantity in array[10][10]

	for (p = 0; p < j; p++)
	{
		for (s = 0; s < 10; s++)
		{
			temp2->items[p][s] = a[p][s];
		}
	}


	if (head1 == NULL)
	{
		head1 = last1 = temp2;
	}

	else
	{
		last1->next = temp2;
		temp2->prev = last1;
		last1 = temp2;
	}

	today_customer++;
	total_earning += total_amount;
}

void display_rd_hist()
{
	string data;
	ifstream f;
	cout << "\n";
	cout << "                                            -------------                                            \n";
	cout << "------------------------------------------- ORDER HISTORY ---------------------------------------------\n";
	cout << "                                            -------------                                            \n";
	cout << "SR_NO          TOTAL AMOUNT\n";

	struct order_hist* temp = head1;
	if (head1 == NULL)
	{
		cout << "Empty";
	}

	while (temp != NULL)
	{
		cout << temp->customer_ID << "\t" << temp->date << "\t" << temp->amount << "\t\n";
		temp = temp->next;
	}

	f.open("BillRecord.txt");
	if (f.is_open()) {
		string data;
		while (getline(f, data))
		{
			cout << data << "\n";
		}
		f.close();
	}
}

Item* middle(Item* start, Item* end)
{
	if (start == NULL)
	{
		return NULL;
	}
	Item* current = start;
	Item* currnext = start -> next;
 	while (currnext != end)
 	{
		currnext = currnext -> next;
		if (currnext != end)
		{
			current = current -> next;
			currnext = currnext -> next;
 		}
 	}
 	return current;
}

Item* binarySearch(int key)
{
	Item* head = NULL;
	Item* start = head;
	Item* end = NULL;
	do
	{
		Item* mid = middle(start, end);
		if (mid == NULL)
		{
			return NULL;
		}
		if (mid->food_Id_No == key)
		{
			return mid;
		}
		else if (mid->food_Id_No < key)
		{
			start = mid->next;
		}
		else
		{
			end = mid;
		}
	} while (end == NULL || end != start);
	return NULL;
}

void edit()
{
	Item* temp = head;
	string x;
	int y;
	cout << "\n-------------------------------------------------------------------------------------------------------\n" << endl;
	cout << "1. Search By ID." << endl;
	cout << "2. Search By Name." << endl;
	cout << "3. EXIT." << endl;
	int Ecommand;
	cout << "Enter the Command: ";
	cin >> Ecommand;
	switch (Ecommand)
	{

	case 1:
	{
		bool Echeck;
		cout << "Enter the ID to Edit: ";
		cin >> y;
		while (temp != NULL)
		{
			binarySearch(y);
			if (temp->food_Id_No == y)
			{
				cout << "\n-------------------------------------------------------------------------------------------------------\n" << endl;
				cout << "Name: " << temp->name << endl;
				cout << "Price: " << temp->price << endl;
				cout << "\n-------------------------------------------------------------------------------------------------------\n" << endl;
				Echeck = true;
				break;
			}
			temp = temp->next;
		}
		if (Echeck == true)
		{
			int command;
			cout << "1. Edit this Item." << endl;
			cout << "2. Exit editing this Item." << endl;
			cout << "Enter: ";
			cin >> command;
			switch (command)
			{
			case 1:
			{
				cout << "\nEnter New Name: ";
				getline(cin, x);
				getline(cin, x);
				temp->name = x;
				cout << "Enter New Price: ";
				cin >> y;
				temp->price = y;

				cout << "-------------------------------------------------------------------------------------------------------\n";
				cout << "                 DISH IS EDITED SUCESSFULLY!!\n";
				cout << "-------------------------------------------------------------------------------------------------------\n";
				break;
			}
			case 2:
			{
				edit();
				break;
			}
			}
		}
		else if (Echeck == false)
		{
			cout << "Searched Item Not Found!" << endl;
		}
		break;
	}

	case 2:
	{
		bool Echeck;
		cout << "\nEnter the Name to Edit: ";
		getline(cin, x);
		getline(cin, x);
		while (temp != NULL)
		{
			if (temp->name == x)
			{
				cout << "\n-------------------------------------------------------------------------------------------------------\n" << endl;
				cout << "Name: " << temp->name << endl;
				cout << "Price: " << temp->price << endl;
				cout << "\n-------------------------------------------------------------------------------------------------------\n" << endl;
				Echeck = true;
				break;
			}
			temp = temp->next;
		}
		if (Echeck == true)
		{
			int command;
			cout << "1. Edit this Item." << endl;
			cout << "2. Exit editing this Item." << endl;
			cout << "Enter: ";
			cin >> command;
			switch (command)
			{
			case 1:
			{
				cout << "\nEnter New Name: ";
				getline(cin, x);
				getline(cin, x);
				temp->name = x;
				cout << "Enter New Price: ";
				cin >> y;
				temp->price = y;

				cout << "-------------------------------------------------------------------------------------------------------\n";
				cout << "                 DISH IS EDITED SUCESSFULLY!!\n";
				cout << "-------------------------------------------------------------------------------------------------------\n";
				break;
			}
			case 2:
			{
				edit();
				break;
			}
			}
		}
		else if (Echeck == false)
		{
			cout << "Searched Item Not Found!" << endl;
		}
		break;
	}
	}
}

int main()
{
	system("Color E0");			//CONSOLE COLOR
	head = NULL;
	last = NULL;

	insert("MOCHA SHAKE   ", 830, 1);
	insert("CARAMELATTE   ", 680, 2);
	insert("HOT CHOCOLATE ", 750, 3);
	insert("CHAI TEA LATTE ", 600, 4);
	insert("RED VELVET CAKE", 2500, 5);
	insert("CAFFE MOCHA ", 650, 6);
	insert("CAFFE AMERICANO", 500, 7);
	insert("SANDWICH ", 100, 8);
	insert("WAFFLES ", 200, 9);
	insert("PANCAKES    ", 300, 10);

	int choice;

	do 
	{
		cout<<"\n            **************************************************************************\n";
    	cout<<"                            WELCOME TO CAFE COCOBISTRO MANAGEMENT SYSTEM                 ";
    	cout<<"\n            **************************************************************************\n";
		cout << "\n\t\t1.  Order";
		cout << "\n\t\t2.  Admin Panel";
		cout << "\n\t\t3.  EXIT";
		cout << "\n\t\tEnter your choice: ";
		cin >> choice;
		switch (choice)
		{
			case 1:
			{
				cout << "\n";
				int ex;

				do 
				{
					cout << "What do you want to order?\n";
					order();
					cout << "\n\t1.Order";
					cout << "\n\t2.Main Menu";
					cout << "\n\tEnter: ";
					cin >> ex;
				} while (ex == 1);
				break;
			}

			case 2:
			{
				cout << "\n";
				int k = login();
				int e;
				if (k == 1) 
				{
					do 
					{
						cout << "\n-------------------------------------------------------------------------------------------------------\n";
						cout << "1.     ADD A DISH"<<endl;
						cout << "2.     UPDATE A DISH"<<endl;
						cout << "3.     DELETE A DISH"<<endl;
						cout << "4.     TODAY'S  TOTAL EARNING"<<endl;
						cout << "5.     TODAY'S TOTAL NO. OF CUSTOMER(s)"<<endl;
						cout << "6.     ORDER HISTORY"<<endl;
						cout << "7.     LIST OF ITEMS";
						cout << "\n-------------------------------------------------------------------------------------------------------\n";
						cout << "Pick: ";
						int ch;
						cin >> ch;
						switch (ch)
						{
							case 1:
								{
									cout << "\n";
									float p;
									int fin, flag = 0;
									string n;
									Item* temp = head;
								
									cout << "Enter the Food ID of Item: ";
									cin >> fin;
									
									
                					while(temp!=NULL)
                					{
                    					if(temp->food_Id_No==fin)
                    					{
                        					cout<<"\nItem with this Serial No. Already Exists!!"<<endl;
                        					flag=1;
                        					break;
                    					}
                    					temp=temp->next;
                					}
                					if(flag)
                					{
                    					break;
                					}
			
									cout << "Enter the Name of Item: ";
									getline(cin,n);
									getline(cin,n);
	
									cout << "Enter the Price of Item: ";
									cin >> p;
	
									insert(n, p, fin);
									cout << "-------------------------------------------------------------------------------------------------------\n";
									cout << "                 NEW DISH IS ADDED SUCESSFULLY!!\n";
									cout << "-------------------------------------------------------------------------------------------------------\n";
									cout << "\n";
									break;
								}
						
							case 2:
								{
									edit();
									cout << "\n";
									break;
								}
						
							case 3:
								{
									int del_id;
									cout << "\nEnter ID of the Dish to be Deleted: ";
									cin >> del_id;
									delete_dish(del_id);
									cout << "-------------------------------------------------------------------------------------------------------\n";
									cout << "                 DISH IS DELETED SUCESSFULLY!!\n";
									cout << "-------------------------------------------------------------------------------------------------------\n";
									cout << "\n";
									break;
								}
						
							case 4:
								{
									cout << "-------------------------------------------------------------------------------------------------------\n";
									cout << "                TODAY'S  TOTAL EARNING IS:  \t" << total_earning << endl;
									cout << "-------------------------------------------------------------------------------------------------------\n";
									break;
								}
						
							case 5:
								{
									cout << "-------------------------------------------------------------------------------------------------------\n";
									cout << "                TOTAL NO. OF CUSTOMER(s) VISITED TODAY: \t" << today_customer << endl;
									cout << "-------------------------------------------------------------------------------------------------------\n";
									break;
								}

							case 6:
								{
									display_rd_hist();
									cout << "\n";
									break;
								}

							case 7:
								{
									cout << "\n";
									display();
									break;
								}
						}

						cout << "\n\t1.  Admin Panel";
						cout << "\n\t2.  Main Menu";
						cout << "\n\tEnter: ";
						cin >> e;
					} while (e == 1);
				}
			break;
			}
		}
	} while (choice != 3);	
}
