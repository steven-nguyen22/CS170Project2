// Steven Nguyen
#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <cmath>
#include <float.h>
#include <algorithm>

#include "searchAlgorithms.cpp"

using namespace std;

int main() {
    srand (time(NULL)); //seeding random time

    vector<vector<double>> testData;

    // vector<int> v1 = {1, 3, 5, 7};
    // vector<int> v2 = {8, 6, 4, 2};
    // modifyData(v1, v2);

    //menu for the program
    cout << "Welcome to Steven Nguyen's Feature Selection Algorithm.\n\n";
    cout << "Please enter the total number of features: ";
    int featureChoice;
    cin >> featureChoice;
    cin.ignore();

    cout << "Please select a dataset: \n";
    cout << "1. Personal Small Dataset\n";
    cout << "2. Personal Large Dataset\n";
    cout << "3. General Small Dataset\n";
    cout << "4. General Large Dataset\n";
    int dataChoice;
    cin >> dataChoice;
    cin.ignore();

    loadData(testData, dataChoice);

    // int temp = getAccuracy(testData);
    // cout << temp << endl;

    //choosing which type of search algorithm to apply to the puzzle
    cout << "\nEnter your choice of algorithm\n";
    cout << "1. Forward Selection\n";
    cout << "2. Backward Elimination\n";
    // cout << "3. My algorithm\n";
    int algorithm; 
    cin >> algorithm;
    if(algorithm == 1) {
      forward_selection(testData, featureChoice);
    }
    if(algorithm == 2) {
       backward_selection(testData, featureChoice);
    }
    // if(algorithm == 3) {
        
    // }

    return 0;
}