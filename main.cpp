#include <iostream>
#include <string>
#include <vector>

using namespace std;

void forward_selection(int numFeatures) {
    vector<int> current_set_of_features;

	for(int i=1; i<numFeatures+1; i++) {
		cout << "On level " << i << " of the search tree\n";
        vector<int> feature_to_add_at_this_level;
		for(int k=1; k<numFeatures+1; k++) {
            //if statement to add only if it hasn't been added already
            cout << "--Consider adding the " << k << " feature\n";
		}
	}
}

void backward_selection(int numFeatures) {
	for(int i=numFeatures; i>0; i--) {
		cout << "On level " << i << " of the search tree\n";
		for(int k=numFeatures; k>0; k--) {
            cout << "--Consider removing the " << k << " feature\n";
		}
	}
}



int main() {
    //menu for the program
    cout << "Welcome to Steven Nguyen's Feature Selection Algorithm.\n\n";
    cout << "Please enter the total number of features: ";
    int featureChoice = 4;
    // cin >> featureChoice;
    // cin.ignore();


    //choosing which type of search algorithm to apply to the puzzle
    cout << "\nEnter your choice of algorithm\n";
    cout << "1. Forward Selection\n";
    cout << "2. Backward Elimination\n";
    cout << "3. My algorithm\n";
    int algorithm = 1; 
    // cin >> algorithm;
    if(algorithm == 1) {
      forward_selection(featureChoice);
    }
    if(algorithm == 2) {
       backward_selection(featureChoice);
    }
    if(algorithm == 3) {
        
    }


    return 0;
}