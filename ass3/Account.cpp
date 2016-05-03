/****************************************************************************************************
Filename:				Account.cpp
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
Purpose: 				Allows to user to add an item into the Account.It also overloads the output
stream operator in order to output an account.
****************************************************************************************************/
#include "Item.h"
#include "Account.h"
#include "FleaBay.h"
#include <iostream>
using namespace std;

/****************************************************************************************************
Function name:			Account() Constructor
Purpose:				Initializes the members of the Account class. 
In parameters:			none
Out parameters:			none
Version:				1.0
Author:					Amaury Diaz Diaz
****************************************************************************************************/
Account::Account(){
	ID=nullptr;
	PassWord=nullptr;
	numItems=0;
	items=nullptr;
}

/****************************************************************************************************
Function name:			Account(Account&) Copy Constructor
Purpose:				Creates an object based on the one pased in the parameter 
In parameters:			Reference to an account object
Out parameters:			none
Version:				1.0
Author:					Amaury Diaz Diaz
****************************************************************************************************/
Account::Account(Account& R){
	ID = new char[strlen(R.ID) + 1];
	strcpy(ID, R.ID);

	PassWord = new char[strlen(R.PassWord) + 1];
	strcpy(PassWord, R.PassWord);

	numItems=R.numItems;

	items = new pItem[R.numItems];              
	for(unsigned int i = 0; i<R.numItems ; i++ ){
		if(dynamic_cast<FoodAndBeverages*>(R.items[i])!=nullptr){
			items[i] = new FoodAndBeverages( *(static_cast<FoodAndBeverages*>(R.items[i])));
		}
		else if(dynamic_cast<ToysAndHobbies*>(R.items[i])!=nullptr){
			items[i] = new ToysAndHobbies( *(static_cast<ToysAndHobbies*>(R.items[i])));
		}
		else{
			items[i] = new Deals( *(static_cast<Deals*>(R.items[i])));
		}

	}
}
/****************************************************************************************************
Function name:			Account(char*,char*) Constructor
Purpose:				Initializes the members of the Account class based on the ID and Password
passed in the parameter.
In parameters:			char*--------->initID 
char*--------->initPassword
Out parameters:			none
Version:				1.0
Author:					Amaury Diaz Diaz
****************************************************************************************************/
Account::Account(char* initID,char* initPassword){
	ID = new char[strlen(initID) + 1];
	strcpy(ID, initID);

	PassWord = new char[strlen(initPassword) + 1];
	strcpy(PassWord, initPassword);

	numItems=0;

	items=nullptr;
}

/****************************************************************************************************
Function name:			AddItem
Purpose:				Adds Items to the account. It adss the Item to the dependig genre
						(Toys and hobbies, food and beverages or deals).
In parameters:			none
Out parameters:			none
Version:				1.0
Author:					Amaury Diaz Diaz
****************************************************************************************************/
void Account :: AddItem(){
	char tempDescription[100],option;
	ppItem tempArray;
	bool valid;
	double price;
	Date date;
	int ageGroup;
	/*Initialize the array of pointer to items the first time an item is going to be added*/
	if(numItems<=0){
		items= new pItem[numItems+1];
	}
	/*Otherwise create a temporary array, create space for the new arry of items and copy
	the previous items into it*/
	else{
		tempArray=items;
		items = new pItem[numItems+1];
		for(unsigned int i=0;i<numItems;i++){
			items[i] = tempArray[i];
		}
		delete[] tempArray;
	}

	/*Enter the item description*/
	do{
		cout<<"Enter the new Item description: "<<endl;
		cin.getline(tempDescription,sizeof(tempDescription));
	}while(strlen(tempDescription)<1);
	/*Enter the item price*/
	do{
		cout<<"Please enter the new item price: ";
		cin>>price;

		if(!cin.good() || price < 0.0){
			valid=false;
			cin.clear();
			cin.ignore(128,'\n');
			cout<<"Invalid price!!!!!. Please re-enter"<<endl;
			continue;
		}
		cin.ignore(128,'\n');
		valid=true;

	}while(!valid);
	/*Allow the user to select what kind of item is being added*/
	do{
		cout<<"What category of item is it? ('F' = FoodAndBeverages, 'T' =ToysAndHobbies, 'D'"<<endl<<"= Deals)"<<endl;
		cin>>option;
		cin.ignore(128,'\n');
		switch(option){
		/*For food ask the user for an expiry date*/
		case 'F':
			cout<<"Please enter a expiry date as: day month year ";
			cin>>date.day>>date.month>>date.year;
			items[numItems]= new FoodAndBeverages (date,tempDescription,price); 
			valid=true;
			break;
		/*For toys ask the user for an appropriate age group*/
		case 'T':
			cout<<"Please enter the appropriate age group ( e.g. 6): ";
			cin>>ageGroup;
			cin.ignore(128,'\n');
			items[numItems]= new ToysAndHobbies (ageGroup,tempDescription,price);
			valid=true;
			break;
		/*For deals ask the user for a deal expiration date*/
		case 'D':
			cout<<"Please enter the date the deal expires as: day month year ";
			cin>>date.day>>date.month>>date.year;
			items[numItems]= new Deals(date,tempDescription,price);
			valid=true;
			break;
		/*On other selection ask for re-entry*/
		default:
			cout<<"Wrong selection please re-enter!!!!"<<endl;
			valid=false;
			break;
		}
	}while(!valid);
	/*Increase by 1 the number of items added*/
	numItems++;

}
/****************************************************************************************************
Function name:			getPassword
Purpose:				Accesor to the password field in the Account.
In parameters:			none.
Out parameters:			A reference to a pointer to a character that contains the current password
in the account. Because a reference to an array of chars is returned it can
be used as an lvalue.
Version:				1.0
Author:					Amaury Diaz Diaz
****************************************************************************************************/
char*& Account::getPassWord(){
	return PassWord;
}

/****************************************************************************************************
Function name:			~Account() Destructor
Purpose:				Deletes the space allocated for the ID and Password of the Account. The space
allocated for an Item and the array of pointers to Items.
In parameters:			none
Out parameters:			none
Version:				1.0
Author:					Amaury Diaz Diaz
****************************************************************************************************/
Account::~Account(){
	delete  ID;
	delete  PassWord;

	for(unsigned int i=0;i<numItems;i++){
		delete items[i];
	}
	delete [] items;
}
/****************************************************************************************************
Function name:			operator<<
Purpose:				Overloads the output stream operator to make it able to output the items
in the current account; or invalid account in case the account does not
exist in the FleaBay Database.
In parameters:			Reference to an output stream object--- os
Reference to an Account object------- account
Out parameters:			A reference to an output stream object.
Version:				1.0
Author:					Amaury Diaz Diaz
****************************************************************************************************/
ostream& operator<<(ostream& os ,Account& account){
	os<<"Account ID: "<<account.ID<<endl;
	if(strcmp(account.ID,"FailedID")!=0){
		if(account.numItems<=0){	
			os<<"**NO ITEMS ON SALE YET**"<<endl;
		}
		else{
			for(unsigned int i=0;i<account.numItems;i++){
				os<< "Item "<<i<<": ";
				os<<*(account.items[i]);
			}
		}

	}
	return os;
}