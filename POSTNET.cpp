// I declare that this assignment is my own work and that I have correctly acknowledged the
// work of others. I acknowledged that I have read and followed the Academic Honesty and
// Integrity related policies as outlined in the syllabus.
//
// _____Joseph Dillman____ _____September 30, 2017______________
//
// ____ 301317623______
//
// (if this is group project, please list all the team members at the following space:
//
// _____Cyrus WaChong____ _____September 30, 2017______________
//
// ____301306459______
/**
* @file hw1.cpp
* @author Cyrus WaChong, Joseph Dillman
* @date October 2,2017
* @version 1
*
* @brief <ENSC 251, Lab 1>
*
* @section DESCRIPTION
*
* <DESCRIPTION FOR THIS CODE>
* Our code will take either a zip code input or barcode as the input. 
* It is then able to convert either of the values to the other, and error check
* them to make sure they meet the standards of certain value (barcodes need
* to be 27 number in length starting and ending in 1's, and zipcodes need to be
* integer inputs that are 5 numbers long)
*/

#include <iostream>
#include <string>
#include <bits/stdc++.h>

using namespace std;

// relevant variables intiialized 
const int NO_NUM = 0;
const string ZERO  = "11000";
const string ONE   = "00011";
const string TWO   = "00101";
const string THREE = "00110";
const string FOUR  = "01001";
const string FIVE  = "01010";
const string SIX   = "01100";
const string SEVEN = "10001";
const string EIGHT = "10010";
const string NINE  = "10100";
const int POSTNET_MAX_VAL = 5; 
const int BARCODE_MAX_LENGTH=27;

// Class to contain, encode, and decode a POSTNET barcode or zipcode.
class ZipCode
{
    public:
        
        void Set(string barcode);
        // For an input as a binary string barcode, convert to an int number
        // and store in the private variable zip.

        void Set(int zipcode);
        // For a 5 digit integer zipcode, convert to barcode and store in bar

        int GetZip();
        // Return the private variable zip.
        
        string GetBar();
        // Return private variable string 
        
        ZipCode();
        // first constructor sets zip to NO_NUM (zero) if nothing is passed in
        
        ZipCode(string barcode);
        // Second constructor assignes zip if barcode is passed 
        
        ZipCode(int zipcode);
        // third constructor assigns zip if zipcode is passed
    
    private:
    
        int BarToZip(string barcode);
        // Pre-condition: Input is a valid POSTNET string of 27 digits.
        // Post-condition: Output is a 5 digit integer representing the barcode.
        
        string ZipToBar(int zip);
        //Pre-condition: Input is 5 digit zip code 
        //Post-condition: Output is 25 digit barcode

        int GroupToNum(string group);
        // Pre-condition: Input is a group of 5 binary numbers.
        // Post-condition: Output is a single digit according to POSTNET rules.
        
        bool CheckValidity(string barcode);
        // Returns true if barcode is a valid POSTNET barcode 
        
        bool CheckValidity(int zipcode);
        // Returns true if zipcode is a valid POSTNET zipcode
        
        int zip;
        // Main holder of POSTNET values, wether they be set from a string 
        // (barcode) or an integer (zipcode)
};

// Member function definitions 
ZipCode::ZipCode()
{
/**
* @brief This function enters the value of 0 for the case of no number inputted
*
*/
    zip = NO_NUM;
}
        
ZipCode::ZipCode(string barcode)
{
/**
* @brief This function applies the value of the barcode into the string variable
*
* @param barcode is an initialized string variable
*/
    Set(barcode);
}
    
ZipCode::ZipCode(int zipcode)
{
/**
* @brief This function applies the value of the zipcode into the integer variable
*
* @param zipcode is an initialized integer variable
* @return void
*/
    Set(zipcode);
}

void ZipCode::Set(string barcode) 
{
/**
* @brief This function tests for errors in the inputted barcode, and if it works, 
* sets the new value of the barcode, then converts it to a zipcode
*
* @param barcode is an initialized string variable
* @return void
*/
    if(CheckValidity(barcode) == false)
    {
        cerr << "ERROR: Entered barcode is not valid" << endl;
        return;
    }

    zip = BarToZip(barcode);  
}

void ZipCode::Set(int zipcode)
{
/**
* @brief This function tests for errors in the inputted zipcode, and if it works, 
* sets the new value of the zipcode, then stores the value of the zipcode.
*
* @param zipcode is an initialized integer variable
* @return void
*/
    if(CheckValidity(zipcode) == false)
    {
        cerr << "ERROR: Entered zipcode is not valid" << endl;
        return;
    }
    
    zip = zipcode;
}

int ZipCode::GetZip()
{
/**
* @brief This function returns the zip value if it is error free
*
* @return int
*/
    if(zip == NO_NUM)
    {
        cerr << "ERROR: Zip/barcode has not been defined, zip will be returned as zero" << endl;
    }
    
    return zip;
}

string ZipCode::GetBar()
{
/**
* @brief This function returns the barcode as a zip code if it is error free.
*
* @return string
*/
    if(zip == NO_NUM)
    {
        cerr << "ERROR: Zip/barcode has not been defined, return value will be empty"<< endl;
        return " ";
    }
    
    return ZipToBar(zip);
}

int ZipCode::BarToZip(string barcode) 
{
/**
* @brief This function converts the barcode into a zipcode
*
* @param barcode is an initialized string variable
* @return int
*/
    int outputNum = 0;

    // The barcode will need to be broken into 5 groups of 5 digits each.
    // Each group of 5 digits will represent one number in the POSTNET code.
    // Here we initialize the 5 groups and the 5 corresponding numbers.
    string group1;
    string group2;
    string group3;
    string group4;
    string group5;

    int num1 = 0;
    int num2 = 0;
    int num3 = 0;
    int num4 = 0;
    int num5 = 0;
    
    // First and last digits of the POSTNET barcode are removed.
    barcode.erase(0,1);
    barcode.erase(barcode.length()-1,1);

    // Break up main barcode into 5 smaller groups of 5 numbers.
    group1.append(barcode,0,5);
    group2.append(barcode,5,5);
    group3.append(barcode,10,5);
    group4.append(barcode,15,5);
    group5.append(barcode,20,5);

    // Turn each of the groups of 5 numbers into a single number using the 
    // GroupToNum function.
    num1 = GroupToNum(group1);
    num2 = GroupToNum(group2);
    num3 = GroupToNum(group3);
    num4 = GroupToNum(group4);
    num5 = GroupToNum(group5);

    // Convert the 5 final integers into one number of 5 digits 
    // i.e. second number is in the thousands placevalue, so multiply by 1000
    outputNum = num1*10000 + num2*1000 + num3*100 + num4*10 + num5;

    return outputNum;
}

string ZipCode::ZipToBar(int zip)
{
/**
* @brief This function converts a zip code into a barcode groups are of type 
* string, and each group will be transferred to a single integer value
* e.g: 10001 is 7 in this case, following the setup of {7,4,2,1,0} 
*
* @param zip is an initialized integer variable
* @return string
*/
    //This function converts a zip code into a barcode
    // groups are of type string, and each group will be transferred to a single integer value
    // e.g: 10001 is 7 in this case, following the setup of {7,4,2,1,0} 
    int zipCode[POSTNET_MAX_VAL]={'\0'};
    string newvalue;
    int number =zip;
    string newBarCode;
    
    for (int i =POSTNET_MAX_VAL-1 ; i >= -1; i--) // a function found online to convert an integer into an array
    {
        zipCode[i] = number % 10; //inputs last number of int into the rightmost available spot of the array 
        number /= 10; //gets rid of the last number
    }
    
    for (int i=0; i<POSTNET_MAX_VAL; i++)
    {
        if (zipCode[i]==0)
        {
            newvalue=ZERO;
        }
        else if ( zipCode[i]==1)
        {
            newvalue=ONE;
        }
        else if ( zipCode[i]==2)
        {
            newvalue=TWO;
        }
        else if ( zipCode[i]==3)
        {
            newvalue=THREE;
        }
        else if ( zipCode[i]==4)
        {
            newvalue=FOUR;
        }
        else if ( zipCode[i]==5)
        {
            newvalue=FIVE;
        }
        else if ( zipCode[i]==6)
        {
            newvalue=SIX;
        }
        else if ( zipCode[i]==7)
        {
            newvalue=SEVEN;
        }
        else if ( zipCode[i]==8)
        {
            newvalue=EIGHT;
        }
        else if ( zipCode[i]==9)
        {
            newvalue=NINE;
        }
        else 
        {
         cerr << "ERROR: You have entered and invalid zipcode\n";
         cerr << "Return value will be empty";
         return "";
        }
    newBarCode = newBarCode.append(newvalue);
    }
            
newBarCode= '1'+newBarCode+'1';
return newBarCode;
}

int ZipCode::GroupToNum(string group)
{
/**
* @brief This function converts the calculated string of each group of a barcode
* to its corresponding number/
*
* @param group is an initialized string variable
* @return int
*/
    // Each of the 5 digits in the group will decide the final output number
    // according to the rules of POSTNET. The groups are of type string.
    // Ascii will be used to compare numbers of type string, 49 in ascii is 1.
    const int ASCII_ONE = 49; 
    const int ELEVEN = 11;
    const int TEN =10;
    const int TWELVE =12;
    int num = 0;
    int limit=0;
   

    if(group[0] == ASCII_ONE)
    {
        num = num + 7;
        limit++;
    }
    
    if(group[1] == ASCII_ONE)
    {
        num = num + 4;
        limit++;
    }

    if(group[2] == ASCII_ONE)
    {
        num = num + 2;
        limit++;
    }

    if(group[3] == ASCII_ONE)
    {
        num += 1;
        limit++;
    }
    if(group[4] == ASCII_ONE)
    {
        limit++;
        
    }
    
    // a special case in POSTNET exists where "11" outputs '0'
    if(num == ELEVEN)
    {
        num = 0;
    }

    return num;
}

bool ZipCode::CheckValidity(string barcode) 
{
    //This function checks the validity of the inputted barcode
    //There can only be 2 ones in every group of 5 numbers
    //There can only be ones and zeroes
    //There must also be a 1 at the start and at the end
    // If any of these conditions are not met, the barcode is invalid
    
    int Ones=0;
    int blocks=0;
    
    
    if (barcode.size()!=BARCODE_MAX_LENGTH)
    {
        cerr << "ERROR: Your inputted barcode is not 27 characters exactly\n";
        return false;
    }
    
    if (barcode[0] != '1' || barcode[26] != '1')
    {
        cerr << "ERROR: Your inputted barcode is currupted (first and last digit must be 1)\n";
        return false;
    }

    barcode=barcode.erase(26,1);
    barcode=barcode.erase(0,1);
    
    
    for (blocks=0; blocks<POSTNET_MAX_VAL; blocks++)
    {
        Ones=0;
        
        for(int k=0; k<POSTNET_MAX_VAL; k++)
        {
            if (barcode[k+blocks*5] !='1' && barcode[k+blocks*5] !='0')
            {
             cerr << "ERROR: There is a non binary input into the barcode\n";
             return false;
            }
            if (barcode[k+blocks*5]=='1')
            {
                Ones++;
            }
        }
    
        if(Ones!=2)
        {
            cerr << "ERROR: Invalid barcode entered\n" << "Barcode does not contain valid amount of 1's\n";
            return false;
        }
    }

return true;
}

bool ZipCode::CheckValidity(int zipcode)
{
    int count =0;
    while(zipcode)
    {
        zipcode = zipcode/10;
        count++;
    }
    
    if (count != 5)
    {
        return false;
    }
    else
    {
        return true;
    }
}

// Main function will be a testbench for all test cases involving 
// improper inputs and error messages. 
int main()
{
    cout << endl << endl << endl;
    cout << "This output will display all test cases for the ZipCode class\n";
    cout << "See int main() comments for notes on what each test case means\n\n";
    
    // Input a valid barcode, output the zipcode translation
    cout << "Using the set function with a string barcode\n";
    ZipCode x;
    x.Set("110100101000101011000010011");
    cout << "The barcode input and zipcode output are:\n";
    cout << x.GetBar() << endl << x.GetZip() << endl << endl;
    
    // input valid zipcode, output barcode translation 
    cout << "Using the set function with an integer zipcode\n";
    ZipCode y;
    y.Set(12345);
    cout << "The zipcode input and barcode output are:\n";
    cout << x.GetZip() << endl << x.GetBar() << endl << endl;
    
    // barcode or zipcode can be entered via constructor
    cout << "Using the constructor with a string barcode\n";
    ZipCode zip(12345);
    cout << "The zipcode input and barcode output are:\n";
    cout << zip.GetZip() << endl << zip.GetBar() << endl << endl;
    
    // Constructor will also work for the barcode string 
    cout << "Using the constructor with an integer zipcode\n";
    ZipCode z("110100101000101011000010011");
    cout << "The barcode input and zipcode output are:\n";
    cout << z.GetBar() << endl << z.GetZip() << endl << endl;
    
    // Error test cases 
    cout << "Now for error test cases\n\n";
    
    // ZipCode() constructor will automatically make the private member zip
    // equal to 0. If any get() function tries to retrieve zip before having zip
    // properly defined by the user, an error will show
    ZipCode b;
    cout << "The failed outputs for GetZip() and GetBar() when zip hasn't been defined yet:\n";
    cout << b.GetZip() << endl << b.GetBar() << endl;
    
    cout << "Errors for invalid inputs" << endl << endl;
    
    // input zipcode isn't 5 digits long 
    
    cout << "The error message for setting a zipcode that isn't 5 digits long is:\n";
    ZipCode c(123456);
    cout << endl << "The same also applies to a zipcode that is too short\n";
    ZipCode d(1234);
    
    cout << endl << "The error message for setting a barcode that doesn't have a 1 at the beggining is:\n";
    ZipCode e("010100101000101011000010011");
    cout << endl << "Same for a code that doesn't have a 1 at the end\n";
    ZipCode f("110100101000101011000010010");
    
    
    return 0;
}