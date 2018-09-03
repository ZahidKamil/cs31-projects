/*
The program below is an import duty calculator and it will first ask for 3 pieces of information 
for the user to input: an importer, a product value, and the product's name. These inputs will be 
stored in the variables "importer", "value", and "productName", respectively.
The conditional statements in lines 24, 29, and 34 check for any erroneous inputs,
and will output an error message for the earliest erroneous input. 
The code in line 28 and 30 makes sure the user can input a string of more than one word
right after they were asked to input a number for the variable "value".
If all inputs were valid, then the else statement in line 39 is executed and will 
calculate the import duty. 
The conditional statements in lines 51 and 58 check to see whether productName is "pigs"
or "mud" because for those 2 products, if they have product values greater than 500 trillion 
grubnicks, then the next 400 trillion grubnicks will have a duty rate of 29% instead of 25% for 
all other products. 
*/
#include <iostream>
#include <string>
using namespace std;
int main()
{
	string importer;
	double value;
	string productName;
	double duty;
	cout << "Importer: ";
	getline(cin, importer);
	cout << "Product value (in trillions): ";
	cin >> value;
	cin.ignore(10000, '\n'); // for inputs of type string after the input of a number
	cout << "Product: ";
	getline(cin, productName);
	cout << "---" << endl;
	if (importer == "") //checks to see if user inputted an empy string for importer
	{
		cout << "You must enter an importer." << endl;
		return 1; // non-zero return value means program couldn't do its job
	}
	else if (value < 0) //checks to see if user inputted a negative product value
	{
		cout << "The product value must not be negative." << endl;
		return 1;
	}
	else if (productName == "") //checks to see if user inputted empty string for productName
	{
		cout << "You must enter a product." << endl;
		return 1;
	}
	else
	{
		cout.setf(ios::fixed);
		cout.precision(2); //makes sure that duty is outputted with only 2 digits to the right of decimal
		if (value <= 500)
		{
			duty = value * 0.31;
		}
		else if (value <= 900)
		{
			if (productName == "pigs" || productName == "mud") 
				duty = (500 * 0.31) + ((value - 500) * 0.29); 
			else
				duty = (500 * 0.31) + ((value - 500) * 0.25);
		}
		else
		{
			if (productName == "pigs" || productName == "mud")
				duty = (500 * 0.31) + (400 * 0.29) + ((value - 900) * 0.22);
			else
				duty = (500 * 0.31) + (400 * 0.25) + ((value - 900) * 0.22);
		}

		cout << "The import duty for " << importer << " is G" << duty << " trillion." << endl;
	}
}
