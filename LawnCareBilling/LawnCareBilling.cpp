// LawnCareBilling.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;
void openFiles(ifstream&, ofstream&);
void getHourlyRate(double&);
void processClients(ifstream&, ofstream&, double);
void processAClient(ifstream&, ofstream&, int&, double);
void printResults(int, int, double);
void getLineSkips(ifstream&);
void processAddressLines(ifstream&, ofstream&);
int main()
{
    //main Variables
    ifstream inFile;
    ofstream outFile;
    int hours, minutes;
    double hourlyRate;
    // main Operations
    openFiles(inFile, outFile);
    getHourlyRate(hourlyRate);
    processClients(inFile, outFile, hourlyRate);
}

void openFiles(ifstream& inFile, ofstream& outFile) {
    string fileName;
    cout << "Enter name of file you wish to open: ";
    cin >> fileName;
    inFile.open(fileName);
    if (inFile.is_open())
        cout << "File opened successfully" << endl;
    else {
        cout << "Could not find file or was unable to be opened." << endl;
        terminate();
    }

    outFile.open("Billing_" + fileName);
    outFile << "Billing for clients on file: " << fileName << endl;
}

void getHourlyRate(double& rate) {
    cout << "Enter hourly rate: ";
    cin >> rate;
}

void processClients(ifstream& inFile, ofstream& outFile, double hourlyRate) {
    int totalTime = 0, numOfBills = 0;
    while (inFile) {
        processAClient(inFile, outFile, totalTime, hourlyRate);
        numOfBills++;
    }
    printResults(numOfBills, totalTime, hourlyRate);
}

void processAClient(ifstream& inFile, ofstream& outFile, int& totalTime, double hourlyRate){
    int time = 0, hours, minutes, numOfJobs;
    float cost;
    string clientName;
    getline(inFile, clientName);
    outFile << clientName << endl;
    processAddressLines(inFile, outFile);
    inFile >> numOfJobs;
    for (int i = 1; i <= numOfJobs; i++) {
        inFile >> hours >> minutes;
        int hours2Mins = hours * 60;
        time += hours2Mins + minutes;
        outFile << "Job " << i << ": " << hours << " hours " << minutes << " minutes" << endl;
    }
    cost = static_cast<float>(time) / 60 * hourlyRate;
    totalTime += time;
    outFile << "Bill Amount: $" << fixed << setprecision(2) << cost << "\n\n";
    getLineSkips(inFile);
}

void getLineSkips(ifstream& inFile) {
    string skip;
    getline(inFile, skip);
    getline(inFile, skip);
}

void processAddressLines(ifstream& inFile, ofstream& outFile) {
    string address;
    for (int i = 1; i <= 2; i++) {
        getline(inFile, address);
        outFile << address << endl;
    }
}

void printResults(int numOfBills, int totalTime, double hourlyRate) {
    cout << "Total Jobs: " << fixed << setprecision(2) << numOfBills << endl;
    float hoursWorked = static_cast<float>(totalTime) / 60;
    cout << "Total Hours: " << hoursWorked << endl;
    float avgHoursPerJob = hoursWorked / static_cast<float> (numOfBills);
    cout << "Averge Hours Per Job: " << avgHoursPerJob << endl;
    float totalBilled = hoursWorked * static_cast<float>(hourlyRate);
    cout << "Total Billed: " << totalBilled << endl;
    float avgBillPerJob = totalBilled / static_cast<float>(numOfBills);
    cout << "Averge Bill Per Job: " << avgBillPerJob << endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
