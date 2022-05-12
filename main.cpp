// Steven Nguyen
#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include "searchAlgorithms.cpp"

using namespace std;

int main() {
    srand (time(NULL)); //seeding random time

    //menu for the program
    cout << "Welcome to Steven Nguyen's Feature Selection Algorithm.\n\n";
    cout << "Please enter the total number of features: ";
    int featureChoice;
    cin >> featureChoice;
    cin.ignore();


    //choosing which type of search algorithm to apply to the puzzle
    cout << "\nEnter your choice of algorithm\n";
    cout << "1. Forward Selection\n";
    cout << "2. Backward Elimination\n";
    // cout << "3. My algorithm\n";
    int algorithm; 
    cin >> algorithm;
    if(algorithm == 1) {
      forward_selection(featureChoice);
    }
    if(algorithm == 2) {
       backward_selection(featureChoice);
    }
    // if(algorithm == 3) {
        
    // }

    return 0;
}