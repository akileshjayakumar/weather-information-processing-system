// Name                 : Akilesh Jayakumar
// UOW Student Number   : 7901240
// Tutorial Group Number: T06
// Assignment 1         : Weather Information Processing System

// ------------------------------
// File: akileshMyFunctionsA1.cpp
// ------------------------------

#include "akileshMyFunctionsA1.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <string>

using namespace std;

int userChoice = 0;
int option = 0;
int number;
int row, column, total;
int min_x, max_x;
int min_y, max_y;
string isEmpty;
string cityFile;
string cloudFile;
string pressureFile;

int ** cityArray = nullptr;
int ** cloudArray = nullptr;
int ** pressureArray = nullptr;

Map * city;
Map * cloud;
Map * pressure;

// function for executing user's preffered choice
void startMenu()
{
	bool leave = false;
	while(!leave)
	{
		switch(selectionList())
		{
			case 1:
				cout << endl;
				readConfigFile();
				rowsColumns();
				createCityArray();
				createCloudArray();
				createPressureArray();
				readCityFile();
				readCloudFile();
				readPressureFile();
				cin.clear();
				break;
			case 2:
				cout << endl;
				displayCityArray();
				returnMenu();
				cin.clear();
				break;
			case 3:
				cout << endl;
				displayCloudArray();
				returnMenu();
				cin.clear();
				break;
			case 4:
				cout << endl;
				displayCloudLMH();
				returnMenu();
				cin.clear();
				break;
			case 5:
				cout << endl;
				displayPressureArray();
				returnMenu();
				cin.clear();
				break;
			case 6:
				cout << endl;
				displayPressureLMH();
				returnMenu();
				cin.clear();
				break;
			case 7:
				cout << endl;
				displaySummaryReport();
				returnMenu();
				cin.clear();
				break;
			case 8:
				cout << "\nThank you for using Weather Information Processing System!" << endl << endl;
				leave = true;
				break;
			default:
				cout << endl;
				cout << "\nPlease enter a valid option: " << endl << endl;
		}
	}
	deallocateMemory(cityArray);
	deallocateMemory(cloudArray);
	deallocateMemory(pressureArray);
}

// function for displaying the start menu options
int selectionList()
{
	cout << "\nStudent ID  :  7901240";
	cout << "\nStudent Name:  Akilesh Jayakumar" << endl;
	cout << "------------------------------------------" << endl;
	cout << "Welcome to Weather Information Processing System!" << endl << endl;
	cout << "1)\tRead in and process a configuration file" << endl;
	cout << "2)\tDisplay city map" << endl;
	cout << "3)\tDisplay cloud coverage map (cloudiness index)" << endl;
	cout << "4)\tDisplay cloud coverage map (LMH symbols)" << endl;
	cout << "5)\tDisplay atmospheric pressure map (pressure index)" << endl;
	cout << "6)\tDisplay atmospheric pressure map (LMH symbols)" << endl;
	cout << "7)\tShow forecast summary report" << endl;
	cout << "8)\tQuit" << endl << endl;
	cout << "Please enter your choice: ";
	cin >> userChoice;
	return userChoice;
}

// function for letting user go back to start menu
void returnMenu()
{
	cout << "\nPress <enter> to go back to main menu  ...";
	cin.ignore();
	cin.get();
	cout << endl;
}
	
// function for reading the config file (option 1)
void readConfigFile()
{
	string inputFileName;
	cout << "[ Read in and process a configuration file ]" << endl;
	cout << "Please enter config filename: ";
	cin >> inputFileName;
	cout << endl;
	fstream inputFile(inputFileName.c_str(), fstream::in);
	string oneLine;
	string delimiter = "=";
	string token;
	char dash;

	if (inputFile.is_open())
	{
		while(getline(inputFile, oneLine))
		{
			if (!(oneLine[0] == '/' && oneLine[1] == '/'))
			{
				if ((oneLine.find("GridX_IdxRange")) != string::npos)
				{
					size_t posit = oneLine.find(delimiter);
					if (posit != string::npos)
					{
						token = oneLine.substr(posit + delimiter.length());
					}
					stringstream ss(token);
					ss >> min_x >> dash >> max_x;
					cout << "Reading in GridX_IdxRange : " << min_x << dash << max_x << "...done!"<< endl;
				}
				if ((oneLine.find("GridY_IdxRange")) != string::npos)
				{
					size_t posit = oneLine.find(delimiter);
					if (posit != string::npos)
					{
						token = oneLine.substr(posit + delimiter.length());
					}
					stringstream ss(token);
					ss >> min_y >> dash >> max_y;
					cout << "Reading in GridY_IdxRange : " << min_y << dash << max_y << "...done!"<< endl;
					cout << endl;
				}
				size_t posit = oneLine.find(".txt");
				if (posit != string::npos)
				{
					readTextFile(oneLine);
					cout << oneLine << " ...done!" << endl;
				}
			}
		}
		cout << endl;
		cout << "\nAll records successfully stored. Going back to main menu ... " << endl;
		cout << endl;
	}
	else
	{
		cout << inputFileName << " cannot be read and processed." << endl;
		cout << "\nYou have entered an invalid filename. Please enter an option again. Going back to main menu ... " << endl;
	}
}

// function for displaying names of city, cloud and pressure text files (option 1)
void readTextFile(string fileName)
{
	if (cityFile == "")
	{
		cout << "Storing data from input file : " << endl;
		cityFile = fileName;
	}
	else if (cloudFile == "")
	{
		cloudFile = fileName;
	}
	else if (pressureFile == "")
	{
		pressureFile = fileName;
	}
	option = userChoice;
}

// function for reading city location text file (option 1)
void readCityFile()
{
	fstream inputFile(cityFile.c_str(), fstream::in);
	string delimiter_1 = "[";
	string delimiter_2 = "-";
	string token;
	char comma;
	char dash;
	number = cityCounter();
	size_t posit = 0;
	int i = 0;
	city = new Map[number];
	
	while (getline(inputFile, cityFile))
	{
		if ((posit = cityFile.find(delimiter_1)) != string::npos)
		{
			token = cityFile.substr(posit + delimiter_1.length());
			stringstream ss1(token);
			ss1 >> city[i].x >> comma >> city[i].y;
		}
		if ((posit = cityFile.find(delimiter_2)) != string::npos)
		{
			token = cityFile.substr(posit + delimiter_2.length());
			stringstream ss2(token);

			ss2 >> city[i].value >> dash >> city[i].name;
			int f = row - city[i].y - 1;
			cityArray[f + min_y][city[i].x - min_x] = city[i].value;
		}
		i++;
	}
}

// function for reading cloud cover text file (option 1)
void readCloudFile()
{
	fstream inputFile(cloudFile.c_str(), fstream::in);
	string delimiter_1 = "[";
	string delimiter_2 = "-";
	string token;
	char comma;
	char dash;
	
	size_t posit = 0;
	int i = 0;
	cloud = new Map[total];
	
	while (getline(inputFile, cloudFile)){
		if ((posit = cloudFile.find(delimiter_1)) != string::npos){
			token = cloudFile.substr(posit + delimiter_1.length());
			stringstream ss1(token);
			ss1 >> cloud[i].x >> comma >> cloud[i].y;
		}

		if ((posit = cloudFile.find(delimiter_2)) != string::npos){
			token = cloudFile.substr(posit + delimiter_2.length());
			stringstream ss2(token);
			ss2 >> cloud[i].value;
			int f = row - cloud[i].y - 1;
			cloudArray[f + min_y][cloud[i].x - min_x] = cloud[i].value;
		}
		i++;
	}
}

// function for reading pressure text file (option 1)
void readPressureFile()
{
	fstream inputFile(pressureFile.c_str(), fstream::in);
	string delimiter_1 = "[";
	string delimiter_2 = "-";
	string token;
	char comma;
	char dash;
	size_t posit = 0;
	int i = 0;
	pressure = new Map[total];
	
	while (getline(inputFile, pressureFile))
	{
		if ((posit = pressureFile.find(delimiter_1)) != string::npos)
		{
			token = pressureFile.substr(posit + delimiter_1.length());
			stringstream ss1(token);
			ss1 >> pressure[i].x >> comma >> pressure[i].y;
		}
		if ((posit = pressureFile.find(delimiter_2)) != string::npos)
		{
			token = pressureFile.substr(posit + delimiter_2.length());
			stringstream ss2(token);
			ss2 >> pressure[i].value;
			int f = row - pressure[i].y - 1;
			pressureArray[f + min_y][pressure[i].x - min_x] = pressure[i].value;
		}
		i++;
	}
}

// function for displaying city map (option 2)
void displayCityArray()
{
	string hash;
	int amtOfHash = column + 2;
	hash.assign(amtOfHash, '#');
	cout << "   ";
	
	for (int i= 0; i < amtOfHash; i++)
	{
		cout << " " << hash[i] << " ";
	}
	cout << endl;
	int a = max_y;
	for (int i = 0; i < row; i++)
	{
		if (a >= 10){
			cout << " " << a << " ";
		}
		else
		{
			cout << " " << a << "  ";
		}
		cout << "# ";
		a--;
		for (int f = 0; f < column; f++)
		{
			if (cityArray[i][f] == 0){
				cout << "   ";
			}
			else
			{
				cout << " " << cityArray[i][f]  << " ";
			}
		}
		cout << " #";
		cout << endl;
	}
	cout << "   ";
	for (int i= 0; i < amtOfHash; i++)
	{
		cout << " " << hash[i] << " ";
	}
	cout << endl;
	cout << "      ";
	for (int i = min_x; i < column + min_x; i++)
	{
		if (i >= 10)
		{
			cout << " " << i;
		}
		else
		{
			cout << " " << i << " ";
		}
	}
	cout << endl;
}

// function for displaying cloud cover array (option 3)
void displayCloudArray()
{
	string hash;
	int amtOfHash = column + 2;
	hash.assign(amtOfHash, '#');
	cout << "   ";
	for (int i=0; i<amtOfHash; i++)
	{
		cout << " " << hash[i] << " ";
	}
	cout << endl;
	int a = max_y;
	for (int i=0; i<row; i++)
	{
		if (a>=10)
		{
			cout << " " << a << " ";
		}
		else
		{
			cout << " " << a << "  ";
		}
		cout << "# ";
		a--;
		for (int f=0; f<column; f++)
		{
			if (cloudArray[i][f] >= 0 && cloudArray[i][f] < 10)
			{
				cout << " " << "0" << " ";
			}
			else if (cloudArray[i][f] >= 10 && cloudArray[i][f] < 20)
			{
				cout << " " << "1" << " ";
			}
			else if (cloudArray[i][f] >= 20 && cloudArray[i][f] < 30)
			{
				cout << " " << "2" << " ";
			}
			else if (cloudArray[i][f] >= 30 && cloudArray[i][f] < 40)
			{
				cout << " " << "3" << " ";
			}
			else if (cloudArray[i][f] >= 40 && cloudArray[i][f] < 50)
			{
				cout << " " << "4" << " ";
			}
			else if (cloudArray[i][f] >= 50 && cloudArray[i][f] < 60)
			{
				cout << " " << "5" << " ";
			}
			else if (cloudArray[i][f] >= 60 && cloudArray[i][f] < 70)
			{
				cout << " " << "6" << " ";
			}
			else if (cloudArray[i][f] >= 70 && cloudArray[i][f] < 80)
			{
				cout << " " << "7" << " ";
			}
			else if (cloudArray[i][f] >= 80 && cloudArray[i][f] < 90)
			{
				cout << " " << "8" << " ";
			}
			else if (cloudArray[i][f] >= 90 && cloudArray[i][f] < 100)
			{
				cout << " " << "9" << " ";
			}
		}
		cout << " #";
		cout << endl;
	}
	cout << "   ";
	for (int i= 0; i < amtOfHash; i++)
	{
		cout << " " << hash[i] << " ";
	}
	cout << endl;
	cout << "      ";
	for (int i = min_x; i < column + min_x; i++)
	{
		if (i >= 10)
		{
			cout << " " << i;
		}
		else
		{
			cout << " " << i << " ";
		}
	}
	cout << endl;
}

// function for displaying cloud cover symbols (option 4)
void displayCloudLMH()
{
	string hash;
	int amtOfHash = column + 2;
	hash.assign(amtOfHash, '#');
	cout << "   ";
	for (int i= 0; i < amtOfHash; i++)
	{
		cout << " " << hash[i] << " ";
	}
	cout << endl;
	int a = max_y;
	for (int i = 0; i < row; i++)
	{
		if (a >= 10)
		{
			cout << " " << a << " ";
		}
		else
		{
			cout << " " << a << "  ";
		}
		cout << "# ";
		a--;
		for (int f = 0; f < column; f++)
		{
			if (cloudArray[i][f] >= 0 &&  cloudArray[i][f] < 35)
			{
				cout << " " << "L" << " ";
			}
			else if (cloudArray[i][f] >= 35 &&  cloudArray[i][f] < 65)
			{
				cout << " " << "M"  << " ";
			}
			else if (cloudArray[i][f] >= 65 &&  cloudArray[i][f] < 100)
			{
				cout << " " << "H"  << " ";
			}
			
		}
		cout << " #";
		cout << endl;
	}
	cout << "   ";
	for (int i= 0; i < amtOfHash; i++)
	{
		cout << " " << hash[i] << " ";
	}
	cout << endl;
	cout << "      ";
	for (int i = min_x; i < column + min_x; i++)
	{
		if (i >= 10)
		{
			cout << " " << i;
		}
		else
		{
			cout << " " << i << " ";
		}
	}
	cout << endl;
}

// function for displaying pressure array (option 5)
void displayPressureArray()
{
	string hash;
	int amtOfHash = column + 2;
	hash.assign(amtOfHash, '#');
	cout << "   ";
	for (int i= 0; i < amtOfHash; i++)
	{
		cout << " " << hash[i] << " ";
	}
	cout << endl;
	int a = max_y;
	for (int i = 0; i < row; i++)
	{
		if (a >= 10)
		{
			cout << " " << a << " ";
		}
		else
		{
			cout << " " << a << "  ";
		}
		cout << "# ";
		a--;
		for (int f = 0; f < column; f++)
		{
			if (pressureArray[i][f] >= 0 &&  pressureArray[i][f] < 10)
			{
				cout << " " << "0" << " ";
			}
			else if (pressureArray[i][f] >= 10 &&  pressureArray[i][f] < 20)
			{
				cout << " " << "1"  << " ";
			}
			else if (pressureArray[i][f] >= 20 &&  pressureArray[i][f] < 30)
			{
				cout << " " << "2"  << " ";
			}
			else if (pressureArray[i][f] >= 30 &&  pressureArray[i][f] < 40)
			{
				cout << " " << "3"  << " ";
			}
			else if (pressureArray[i][f] >= 40 &&  pressureArray[i][f] < 50)
			{
				cout << " " << "4"  << " ";
			}
			else if (pressureArray[i][f] >= 50 &&  pressureArray[i][f] < 60)
			{
				cout << " " << "5"  << " ";
			}
			else if (pressureArray[i][f] >= 60 &&  pressureArray[i][f] < 70)
			{
				cout << " " << "6"  << " ";
			}
			else if (pressureArray[i][f] >= 70 &&  pressureArray[i][f] < 80)
			{
				cout << " " << "7"  << " ";
			}
			else if (pressureArray[i][f] >= 80 &&  pressureArray[i][f] < 90)
			{
				cout << " " << "8"  << " ";
			}
			else if (pressureArray[i][f] >= 90 &&  pressureArray[i][f] < 100)
			{
				cout << " " << "9"  << " ";
			}
		}
		cout << " #";
		cout << endl;
	}
	cout << "   ";
	for (int i= 0; i < amtOfHash; i++){
		cout << " " << hash[i] << " ";
	}
	cout << endl;
	cout << "      ";

	for (int i = min_x; i < column + min_x; i++)
	{
		if (i >= 10)
		{
			cout << " " << i;
		}
		else
		{
			cout << " " << i << " ";
		}
	}
	cout << endl;
}

// function for displaying pressure symbols (option 6)
void displayPressureLMH()
{
	string hash;
	int aHash = column + 2;
	hash.assign(aHash, '#');
	cout << "   ";
	for (int i= 0; i < aHash; i++)
	{
		cout << " " << hash[i] << " ";
	}
	cout << endl;
	int a = max_y;
	for (int i = 0; i < row; i++)
	{
		if (a >= 10)
		{
			cout << " " << a << " ";
		}
		else
		{
			cout << " " << a << "  ";
		}
		cout << "# ";
		a--;
		for (int f = 0; f < column; f++)
		{
			if (pressureArray[i][f] >= 0 &&  pressureArray[i][f] < 35)
			{
				cout << " " << "L" << " ";
			}
			else if (pressureArray[i][f] >= 35 &&  pressureArray[i][f] < 65)
			{
				cout << " " << "M"  << " ";
			}
			else if (pressureArray[i][f] >= 65 &&  pressureArray[i][f] < 100)
			{
				cout << " " << "H"  << " ";
			}
			
		}
		cout << " #";
		cout << endl;
	}
	cout << "   ";
	for (int i= 0; i < aHash; i++)
	{
		cout << " " << hash[i] << " ";
	}
	cout << endl;
	cout << "      ";
	for (int i = min_x; i < column + min_x; i++)
	{
		if (i >= 10)
		{
			cout << " " << i;
		}
		else
		{
			cout << " " << i << " ";
		}
	}
	cout << endl;
}

// function for displaying summary report (option 7)
void displaySummaryReport()
{
	cout << "Weather Forecast Summary Report" << endl;
	cout << "-------------------------------" << endl;

	int * checkPosArray = new int[number];
	for (int i = 0; i < number; i++)
	{
		checkPosArray[i] = city[i].value;
	}
	for (int i = 0; i < number; i++)
	{
		if (checkPosArray[i] != 0)
		{
			float totalCloudArea = 0.00;
			float totalPressureArea = 0.00;
			int counter = 0;
			cout << "City Name : " << city[i].name << endl;
			cout << "City ID   : " << city[i].value << endl;
			for (int a = 0; a < row; a++)
			{
				for (int b = 0; b < column; b++)
				{
					if (cityArray[a][b] == 0)
					{
						bool outerArea = false;
						for (int c = 0; c < 3; c++)
						{
							if (!((a+1-c) < 0) && !((a+1-c) > (row - 1)))
							{
								for (int d = 0; d < 3; d++)
								{
									if (!((b+1-d) < 0) && !((b+1-d) > (column - 1)))
									{
										if (cityArray[(a+1-c)][(b+1-d)] == city[i].value)
										{
											outerArea = true;
										}
									}
								}
							}
						}
						if (outerArea == true)
						{
							totalCloudArea = totalCloudArea + cloudArray[a][b];
							totalPressureArea = totalPressureArea + pressureArray[a][b];
							counter++;
						}
					}
				}
			}

			for (int f = 0; f < number; f++)
			{
				if (checkPosArray[f] == city[i].value)
				{
					for (int k = 0; k < total; k++)
					{
						if ((cloud[k].x == city[f].x) && (cloud[k].y == city[f].y))
						{
							totalCloudArea = totalCloudArea + cloud[k].value;
						}
						if ((pressure[k].x == city[f].x) && (pressure[k].y == city[f].y))
						{
							totalPressureArea = totalPressureArea + pressure[k].value;
						}
					}
					counter++;
					checkPosArray[f] = 0;
				}
			}
			displayAverage(totalCloudArea, totalPressureArea, counter);
			cout << endl;
		}
	}
	delete [] checkPosArray;
}

// function for displaying average cloud cover and pressure (option 7)
void displayAverage(float totalCloudArea, float totalPressureArea, int counter)
{
	cout << setprecision(2) << fixed;
	string cloudLMH;
	string pressureLMH;
	if (((totalCloudArea/counter) >= 0) && ((totalCloudArea/counter) < 35))
	{
		cloudLMH = "(L)";
	}
	else if (((totalCloudArea/counter) >= 35) && ((totalCloudArea/counter) < 65))
	{
		cloudLMH = "(M)";
	}
	else if (((totalCloudArea/counter) >= 65) && ((totalCloudArea/counter) < 100))
	{
		cloudLMH = "(H)";
	}
	cout << left << setfill(' ') << setw(26) << "Ave. Cloud Cover  (ACC)" << " : " << totalCloudArea/counter;
	cout << " " << cloudLMH << endl;
	if (((totalPressureArea/counter) >= 0) && ((totalPressureArea/counter) < 35))
	{
		pressureLMH = "(L)";
	}
	else if (((totalPressureArea/counter) >= 35) && ((totalPressureArea/counter) < 65))
	{
		pressureLMH = "(M)";
	}
	else if (((totalPressureArea/counter) >= 65) && ((totalPressureArea/counter) < 100))
	{
		pressureLMH = "(H)";
	}
	cout << left << setfill(' ') << setw(26) << "Ave. Pressure  (AP)" << " : " << totalPressureArea/counter;
	cout << " " << pressureLMH << endl;
	if (pressureLMH == "(L)")
	{
		if (cloudLMH == "(H)")
		{
			cout <<"Probability of Rain (%)" << " : ";
			cout << " 90.00" << endl;
			cout << "~~~~" << endl;
			cout << "~~~~~" << endl;
			cout << "\\\\\\\\\\" << endl;
		}
		else if (cloudLMH == "(M)")
		{
			cout <<"Probability of Rain (%)" << " : ";
			cout << " 80.00" << endl;
			cout << "~~~~" << endl;
			cout << "~~~~~" << endl;
			cout << " " << "\\\\\\" << endl;
		}
		else if (cloudLMH == "(L)")
		{
			cout <<"Probability of Rain (%)" << " : ";
			cout << " 70.00" << endl;
			cout << "~~~~" << endl;
			cout << "~~~~~" << endl;
			cout << "  " << "\\\\\\" << endl;
		}
	}
	else if (pressureLMH == "(M)")
	{
		if (cloudLMH == "(H)")
		{
			cout <<"Probability of Rain (%)" << " : ";
			cout << " 60.00" << endl;
			cout << "~~~~" << endl;
			cout << "~~~~~" << endl;
			cout << "   " << "\\\\" << endl;
		}
		else if (cloudLMH == "(M)")
		{
			cout <<"Probability of Rain (%)" << " : ";
			cout << " 50.00" << endl;
			cout << "~~~~" << endl;
			cout << "~~~~~" << endl;
			cout << "    " << "\\" << endl;
		}
		else if (cloudLMH == "(L)")
		{
			cout << "Probability of Rain (%)" << " : ";
			cout << " 40.00" << endl;
			cout << "~~~~" << endl;
			cout << "~~~~~" << endl;
			cout << "     " << endl;
		}
	}
	else if (pressureLMH == "(H)")
	{
		if (cloudLMH == "(H)")
		{
			cout <<"Probability of Rain (%)" << " : ";
			cout << " 30.00" << endl;
			cout << "~~~" << endl;
			cout << "~~~~" << endl;
		}
		else if (cloudLMH == "(M)")
		{
			cout <<"Probability of Rain (%)" << " : ";
			cout << " 20.00" << endl;
			cout << "~~" << endl;
			cout << "~~~" << endl;
		}
		else if (cloudLMH == "(L)")
		{
			cout << "Probability of Rain (%)" << " : ";
			cout << " 10.00" << endl;
			cout << "~" << endl;
			cout << "~~" << endl;
		}
	}
}

// function for deallocating memory
void deallocateMemory(int ** mapArray)
{
	if (column <= 0 )
	{
		return;
	}
	for (int i = 0; i < row; i++)
	{
		delete [] mapArray[i];
	}
	delete [] mapArray;
}

// function for finding number of cities
int cityCounter()
{
	fstream inputFile(cityFile.c_str(), fstream::in);
	string delimiter = "[";
	size_t posit = 0;
	number = 0;
	while (getline(inputFile, cityFile))
	{
		if ((posit = cityFile.find(delimiter)) != string::npos)
		{
			number++;
		}
	}
	return number;
}

// function for finding total rows and columns
void rowsColumns()
{
	column = max_x - min_x + 1;	
	row = max_y - min_y + 1;
	total = row * column;
}

// function for creating an array for city location data
void createCityArray()
{
	cityArray = new int * [row];
	for (int i = 0; i < row; i++)
	{
		cityArray[i] = new int[column];
		for (int f = 0; f < column; f++)
		{
			cityArray[i][f] = 0;
		}
	}
}

// function for creating an array for cloud cover data
void createCloudArray()
{
	cloudArray = new int *[row];
	for (int i = 0; i < row; i++)
	{
		cloudArray[i] = new int[column];
		for (int f = 0; f < column; f++)
		{
			cloudArray[i][f] = 0;
		}
	}
}

// function for creating an array for pressure data
void createPressureArray()
{
	pressureArray = new int * [row];
	for (int i = 0; i < row; i++)
	{
		pressureArray[i] = new int[column];
		for (int f = 0; f < column; f++)
		{
			pressureArray[i][f] = 0;
		}
	}
}
