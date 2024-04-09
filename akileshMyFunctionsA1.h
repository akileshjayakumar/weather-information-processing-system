// Name                 : Akilesh Jayakumar
// UOW Student Number   : 7901240
// Tutorial Group Number: T06
// Assignment 1         : Weather Information Processing System

// ------------------------------
// File: akileshMyFunctionsA1.h
// ------------------------------

#ifndef CSCI251_A1_H
#define CSCI251_A1_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <string>

using namespace std;

struct Map
{
	int x;
	int y;
	int value;
	string name;
};

// function prototypes
int selectionList();
void startMenu();
void returnMenu();
void readConfigFile();
void readTextFile(string fileName);
void rowsColumns();
void deallocateMemory(int ** mapArray);
void displaySummaryReport();
void displayAverage(float totalCloudArea, float totalPressureArea, int counter);

// city function prototypes
int cityCounter();
void readCityFile();
void createCityArray();
void displayCityArray();

// cloud function prototypes
void readCloudFile();
void createCloudArray();
void displayCloudArray();
void displayCloudLMH();

// pressure function prototypes
void readPressureFile();
void createPressureArray();
void displayPressureArray();
void displayPressureLMH();

#endif
