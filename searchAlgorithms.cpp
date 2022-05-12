#include <vector>
#include <time.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

//random accuracy rating for phase 1
int random_num() {
    return rand() % 100 + 1;
}

//checking if value is already added to current set of features 
bool checker(vector<int> mySet, int val) {
    bool check = true;
    for(int i=0; i<mySet.size(); i++) {
        if(mySet[i] == val) 
            check = false;
    }

    return check;
}

void forward_selection(int numFeatures) {
    vector<int> current_set_of_features;

    //for loop for levels
	for(int i=1; i<numFeatures+1; i++) {
		cout << "On level " << i << " of the search tree\n";
        vector<int> feature_to_add_at_this_level;
        int best_so_far_accuracy = 0;

        //for loop for nodes at that level
		for(int k=1; k<numFeatures+1; k++) {
            //if statement to add only if it hasn't been added already
            if(checker(current_set_of_features, k)) {
                int accuracy = random_num();
                cout << "--Consider adding feature " << k << " with accuracy = " << accuracy << endl;

                //checking for highest accuracy of the level
                if(accuracy > best_so_far_accuracy) {
                    best_so_far_accuracy = accuracy;
                    feature_to_add_at_this_level.push_back(k);
                }
            }
            
		}

        //add value with highest accuracy to current set of features
        current_set_of_features.push_back(feature_to_add_at_this_level.back());
        cout << "On level " << i << " I added feature " << feature_to_add_at_this_level.back() << " to the current set\n";
	}
}

void backward_selection(int numFeatures) {
    vector<int> current_set_of_features;

    //for loop for levels
	for(int i=numFeatures; i>0; i--) {
		cout << "On level " << i << " of the search tree\n";
        vector<int> feature_to_add_at_this_level;
        int best_so_far_accuracy = 0;

        //for loop for nodes at that level
		for(int k=numFeatures; k>0; k--) {
             //if statement to remoce only if it hasn't been removed already
            if(checker(current_set_of_features, k)) {
                int accuracy = random_num();
                cout << "--Consider removing feature " << k << " with accuracy = " << accuracy << endl;

                //checking for highest accuracy of the level
                if(accuracy > best_so_far_accuracy) {
                    best_so_far_accuracy = accuracy;
                    feature_to_add_at_this_level.push_back(k);
                }
            }
		}

        //add value with highest accuracy to current set of features
        current_set_of_features.push_back(feature_to_add_at_this_level.back());
        cout << "On level " << i << " I removed feature " << feature_to_add_at_this_level.back() << " from the current set\n";
	}
}