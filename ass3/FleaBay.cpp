/****************************************************************************************************
Filename:				FleaBay.cpp
Version: 				1.0                                         
Author:					Amaury Diaz Diaz                                              
Student No:  			040 738 985                                             
Course Name/Number:		CST8219 C++                                 
Lab Sect: 				302                                                      
Assignment #:			3
Assignment name:		FleaBay	with Polymorphic Inheritance.
Due Date:				December 5 2015                                           
Submission Date:		December 5 2015
Professor:				Andrew Tyler                                           
Purpose: 				Until the user quits, it allows the user to login into FleaBay(create a new 
						account or log in into an existing one), overload the output stream 
						operator in order to print the FleaBay database and make the accounts
						accesible by using their IDs as an index.
****************************************************************************************************/
#include <iostream>
#include "Item.h"
#include "Account.h"
#include "FleaBay.h"
using namespace std;

/****************************************************************************************************
Function name:			FleaBay() Constructor
Purpose:				Initializes the members of the FleaBay class. 
In parameters:			none
Out parameters:			none
Version:				1.0
Author:					Amaury Diaz Diaz
****************************************************************************************************/
FleaBay::FleaBay(){
	accounts=nullptr;
	numAccounts=0;
}
/****************************************************************************************************
Function name:			Login
Purpose:				Allows the user to add a new account into the FleaBay database 
						and/or opening an existing account(make sure that the account is valid).
						Once the account is opened you can select if you want to change its password
						or if you want to add items to it.
In parameters:			none
Out parameters:			boolean(true for succesful execution)
Version:				1.0
Author:					Amaury Diaz Diaz
****************************************************************************************************/
bool FleaBay::Login(){
	char option;
	char option2='Y';
	char lookUpID[45]={'\0'};
	char lookUpPassword[45]={'\0'};
	char tempPassWord [100];

	if(numAccounts==0){
		cout<<"**NO ACCOUNTS**"<<endl;
	}

	cout<<"1. Add a new Account"<<endl;
	cout<<"2. Open an existing Account"<<endl;
	cout<<"3. Return to Main Menu"<<endl;
	cin>>option;
	cin.ignore(128,'\n');

	switch (option)
	{
	case '1':
		AddNewAccount();
		break;

	case '2':
		if(numAccounts==0){
			cout<<"**NO ACCOUNTS**"<<endl;
		}
		else{
			do{
				cout<<"please enter your account ID: ";
				cin.getline(lookUpID,sizeof(lookUpID));
			}while(strlen(lookUpID)<1);

			/*Make sure that the account exists*/
			for(unsigned int i=0;i<numAccounts;i++){
				if(strcmp(accounts[i]->getID(),lookUpID)==0){
					/*If account exists enter its password*/
					cout<<"please enter your password: ";
					cin.getline(lookUpPassword,sizeof(lookUpPassword));
					/*If password is correct show what is on sale*/
					if(strcmp(accounts[i]->getPassWord(),lookUpPassword)==0){
						if(accounts[i]->getnumItems()==0){
							cout<<"No items in your account"<<endl;
						}
						else{
							cout<<"These are your current items for sale: "<<endl;
							cout<< *(accounts[i]);
						}
						/*Give the user the option to change the account password or add new items*/
						while(option2!='Q'){

							cout<<"Do you wish to change a password? (yes = 'P')"<<endl;
							cout<<"Do you wish to add another Item? (yes ='Y')"<<endl;
							cout<<"Want to quit this menu? (yes = 'Q')"<<endl;
							cin>>option2;
							cin.ignore(128,'\n');
							switch(option2){

							case 'P':
								cout<<"Please enter your new password: "<<endl;
								cin.getline(tempPassWord,sizeof(tempPassWord));
								delete[] accounts[i]->getPassWord();
								accounts[i]->getPassWord() = new char[strlen(tempPassWord) + 1];
								strcpy(accounts[i]->getPassWord(), tempPassWord);
								break;
							case 'Y':
								accounts[i]->AddItem();
								break;
							case 'Q':
								break;
							default:
								cout<<"Invalid option!!!!!!"<<endl;
								break;
							}
						}

					}
					/*If account password is incorrect*/
					else{
						cout<<lookUpPassword<<endl<<"password doesn't match this ID "<<endl;
					}
					break;
				}
				/*If account ID does not exists*/
				else{
					if(i==(numAccounts-1)){
						cout<<lookUpID<<" is invalid ID"<<endl;
					}
				}
			}

		}
		break;
	case '3':
		break;
	default:
		cout<<"Invalid Option!!!!"<<endl;
		break;
	}
	return true;
}
/****************************************************************************************************
Function name:			AddNewAccount
Purpose:				Add a new FleaBay account. If the account already exists prompt the user 
						to enter a new account name until there is no account with the same name. 
In parameters:			none
Out parameters:			boolean(true for succesful execution)
Version:				1.0
Author:					Amaury Diaz Diaz
****************************************************************************************************/
bool FleaBay::AddNewAccount(){
	ppAccount tempArray;
	char tempID[45]={'\0'};
	char tempPassword[45]={'\0'};
	int check=1;

	if(numAccounts<=0){
		accounts = new pAccount[numAccounts+1];
	}
	else{
		tempArray=accounts;
		accounts = new pAccount[numAccounts+1];
		for(unsigned int i=0;i<numAccounts;i++){
			accounts[i] = tempArray[i];
		}
		delete[] tempArray;
	}


	if(numAccounts<=0){
		do{
			cout<<"please enter your account ID: ";
			cin.getline(tempID,sizeof(tempID));
		}while(strlen(tempID)<1);

		do{
			cout<<"please enter your account password: ";
			cin.getline(tempPassword,sizeof(tempPassword));
		}while(strlen(tempPassword)<1);

		accounts[numAccounts]= new Account(tempID,tempPassword); 
	}
	/*Check that a repeated account is not added*/
	else{
		while(check==1){
			do{
				cout<<"please enter your account ID: ";
				cin.getline(tempID,sizeof(tempID));
			}while(strlen(tempID)<1);
			for(unsigned int i=0;i<numAccounts;i++){
				/*If an account with that name exists ask for re-entry*/
				if(strcmp(accounts[i]->getID(), tempID)==0){
					cout<<"There already exists an account with this name: "<<accounts[i]->getID()<<endl;
					cout<<"Please Re-enter a new account name"<<endl;
					break;
				}
				/*Otherwise continue with the account addition process*/
				else{
					if(i==(numAccounts-1)){
						check =0;
						do{
							cout<<"please enter your account password: ";
							cin.getline(tempPassword,sizeof(tempPassword));
						}while(strlen(tempPassword)<1);
						accounts[numAccounts]= new Account(tempID,tempPassword);
					}
				}
			}
		}
	}
	numAccounts++;
	return true;
}

/****************************************************************************************************
Function name:			~FleaBay() Destructor
Purpose:				Deletes the space allocated for an Account and the array of pointers to them.
In parameters:			none
Out parameters:			none
Version:				1.0
Author:					Amaury Diaz Diaz
****************************************************************************************************/
FleaBay::~FleaBay(){
	if(numAccounts != 0) { 
		for(unsigned int i=0;i<numAccounts;i++){
			delete accounts[i];
		}
		delete [] accounts;
	} 
}
/****************************************************************************************************
Function name:			operator[]
Purpose:				Overloads the indexing operator to makeit able to acces an account by
						using its ID as an index.
In parameters:			pointer to a char containing the ID of the Account.
Out parameters:			An Account object matching the ID. If no account object matches the ID
						An Account object with the string "Invalid Account" as an ID is returned.
Version:				1.0
Author:					Amaury Diaz Diaz
****************************************************************************************************/
Account FleaBay :: operator[](char* lookUpID){
	for(unsigned int i=0;i<numAccounts;i++){
		if(strcmp(accounts[i]->getID(),lookUpID)==0){
			return *(accounts[i]);
		}
	}
	/*In case no ID with the name passed in the parameter is found*/
	cout<<lookUpID<<" is invalid ID"<<endl;
	return Account("FailedID","Hahahaha");
}
/****************************************************************************************************
Function name:			operator<<
Purpose:				Overloads the output stream operator to make it able to output the accounts
						in the FleaBay database.
In parameters:			Reference to an output stream object--- os
						Reference to a FleaBay object------- fBay
Out parameters:			A reference to an output stream object.
Version:				1.0
Author:					Amaury Diaz Diaz
****************************************************************************************************/
ostream& operator<<(ostream& os ,FleaBay& fBay){
	if(fBay.numAccounts<=0){
		os<<"**NO ACCOUNTS ON FILE YET**"<<endl;
	}
	else{
		for(unsigned int i=0;i<fBay.numAccounts;i++){
			os<<*(fBay.accounts[i]);
			os<<endl;
		}
	}
	return os;
}


