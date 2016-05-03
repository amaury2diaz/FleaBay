/****************************************************************************************************
Filename:				Item.cpp
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
Purpose: 				Mantains the item objects.It also overloads the output
						stream operator in order to output an item.
****************************************************************************************************/
#include "Item.h"
#include "Account.h"
#include "FleaBay.h"
#include <iostream>
#include <iomanip>
using namespace std;
/****************************************************************************************************
Function name:			Item() Constructor
Purpose:				Initializes the members of the Item structure. 
In parameters:			none
Out parameters:			none
Version:				1.0
Author:					Amaury Diaz Diaz
****************************************************************************************************/
Item::Item(){
	description=nullptr;
	price=0;
}
/****************************************************************************************************
Function name:			Item(Item&) Copy Constructor
Purpose:				Creates an object based on the one pased in the parameter 
In parameters:			Reference to an item object
Out parameters:			none
Version:				1.0
Author:					Amaury Diaz Diaz
****************************************************************************************************/
Item::Item(Item& R){
	description = new char[(strlen(R.description)+1)];
	strcpy(description,R.description);

	price = R.price;
}
/****************************************************************************************************
Function name:			Item(char*,double) Constructor
Purpose:				Initializes the members of the Item class based on the Description and 
						price passed in the parameter.
In parameters:			char*--------->initDescription
						double--------->initPrice
Out parameters:			none
Version:				1.0
Author:					Amaury Diaz Diaz
****************************************************************************************************/
Item::Item(char * initDescription, double initPrice){
	description = new char[(strlen(initDescription)+1)];
	strcpy(description,initDescription);

	price = initPrice;
}
/****************************************************************************************************
Function name:			~Item() Destructor
Purpose:				Deletes the space allocated for the description of the Item. 
In parameters:			none
Out parameters:			none
Version:				1.0
Author:					Amaury Diaz Diaz
****************************************************************************************************/
Item::~Item(){
	delete [] description;
}
/****************************************************************************************************
Function name:			operator<<
Purpose:				Overloads the output stream operator to make it able to output the description
						and the price of the item.
In parameters:			Reference to an output stream object--- os
						Reference to a Item object------- item
Out parameters:			A reference to an output stream object.
Version:				1.0
Author:					Amaury Diaz Diaz
****************************************************************************************************/
ostream& operator<<(ostream& os, Item& item){
	item.Report();
	os<<setiosflags(ios::fixed);
	os<<"  "<<item.description<<", cost = $"<<setprecision(2)<<item.price<<endl<<endl;
	return os;
}
/****************************************************************************************************
Function name:			FoodAndBeverages(Date,char*,double) Constructor
Purpose:				Initializes the members of the FoodAndBeverages class based on the expiry date,
						Description and price passed in the parameter.
In parameters:			Date----------> date
						char*--------->initDescription
						double--------->initPrice
Out parameters:			none
Version:				1.0
Author:					Amaury Diaz Diaz
****************************************************************************************************/
FoodAndBeverages::FoodAndBeverages(Date date,char* initDescription,double initPrice):Item(initDescription,initPrice){
	expiryDate.day=date.day;
	expiryDate.month=date.month;
	expiryDate.year=date.year;
}
/****************************************************************************************************
Function name:			FoodAndBeverages(FoodAndBeverages&) Copy Constructor
Purpose:				Creates an object based on the one pased in the parameter 
In parameters:			Reference to a FoodAndBeverages object
Out parameters:			none
Version:				1.0
Author:					Amaury Diaz Diaz
****************************************************************************************************/
FoodAndBeverages::FoodAndBeverages(FoodAndBeverages& foodie):Item(foodie){
	expiryDate.day = foodie.expiryDate.day;
	expiryDate.month = foodie.expiryDate.month;
	expiryDate.year = foodie.expiryDate.year;
}
/****************************************************************************************************
Function name:			Report
Purpose:				Polymorphic function that prints a report for a FoodAndBeverages object 
In parameters:			none
Out parameters:			none
Version:				1.0
Author:					Amaury Diaz Diaz
****************************************************************************************************/
void FoodAndBeverages::Report(void){
	cout<<"Food and Beverage Report"<<endl;
	cout<<"Expiry date: "<<expiryDate.day<<" "<<expiryDate.month<<" "<<expiryDate.year<<endl;
}
/****************************************************************************************************
Function name:			ToysAndHobbies(int,char*,double) Constructor
Purpose:				Initializes the members of the ToysAndHobbies class based on the suitable age,
						Description and price passed in the parameter.
In parameters:			int----------->suitable age
						char*--------->initDescription
						double--------->initPrice
Out parameters:			none
Version:				1.0
Author:					Amaury Diaz Diaz
****************************************************************************************************/
ToysAndHobbies::ToysAndHobbies(int groupAge,char* initDescription,double initPrice):Item(initDescription,initPrice){
	suitableAge=groupAge;
}
/****************************************************************************************************
Function name:			ToysAndHobbies(ToysAndHobbies&) Copy Constructor
Purpose:				Creates an object based on the one pased in the parameter 
In parameters:			Reference to a ToysAndHobbies object
Out parameters:			none
Version:				1.0
Author:					Amaury Diaz Diaz
****************************************************************************************************/
ToysAndHobbies::ToysAndHobbies(ToysAndHobbies& th):Item(th){
	suitableAge=th.suitableAge;
}
/****************************************************************************************************
Function name:			Report
Purpose:				Polymorphic function that prints a report for a ToysAndHobbies object 
In parameters:			none
Out parameters:			none
Version:				1.0
Author:					Amaury Diaz Diaz
****************************************************************************************************/
void ToysAndHobbies::Report(void){
	cout<<"Toys and Hobbies Report"<<endl;
	cout<<"Suitable Age: "<<suitableAge<<" years"<<endl;
}
/****************************************************************************************************
Function name:			Deals(Date,char*,double) Constructor
Purpose:				Initializes the members of the Deals class based on the expiration
						date, Description and price passed in the parameter.
In parameters:			Date---------->expiration date
						char*--------->initDescription
						double--------->initPrice
Out parameters:			none
Version:				1.0
Author:					Amaury Diaz Diaz
****************************************************************************************************/
Deals::Deals(Date date,char* initDescription,double initPrice):Item(initDescription,initPrice){
	closingDate.day=date.day;
	closingDate.month=date.month;
	closingDate.year=date.year;
}
/****************************************************************************************************
Function name:			Deals(Deals&) Copy Constructor
Purpose:				Creates an object based on the one pased in the parameter 
In parameters:			Reference to a Deals object
Out parameters:			none
Version:				1.0
Author:					Amaury Diaz Diaz
****************************************************************************************************/
Deals::Deals(Deals& deals):Item(deals){
	closingDate.day = deals.closingDate.day;
	closingDate.month = deals.closingDate.month;
	closingDate.year = deals.closingDate.year;
}
/****************************************************************************************************
Function name:			Report
Purpose:				Polymorphic function that prints a report for a Deals object 
In parameters:			none
Out parameters:			none
Version:				1.0
Author:					Amaury Diaz Diaz
****************************************************************************************************/
void Deals::Report(void){
	cout<<"Deals Report"<<endl;
	cout<<"Closing date: "<<closingDate.day<<" "<<closingDate.month<<" "<<closingDate.year<<endl;
}