#include <vector>
#include <time.h>
#include <stdlib.h>
#include <iostream>

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


using namespace std;

//random accuracy rating for phase 1
int random_num() {
    return rand() % 100 + 1;
}

double calculate_distance(vector<double> p, vector<double> q, int i, int k) {
  double distance = 0;

  //distance = sqrt((q1-p1)^2 + (q2-p2)^2 + ...)
  //we want to compare the 10 features of 1 to the 10 features of 2,3, etc...
  //we want 10-19 minus 0-9
  //need to change k=1 to 10-19
  //need to change i=0 to 0-9
  k += 9;
  for(int x=0; x<10; x++) {
    distance += pow( q[k] - p[i], 2);
    k++;
    i++;
  }
  return sqrt(distance);
}

void loadData (vector<vector<double>> &testData, int choice) {
  string fileName = "";
  if(choice == 1) {
    // fileName = "CS170_Spring_2022_Small_data__146.txt";
    fileName = "small-test-dataset.txt";
  }
  else {
    fileName = "CS170_Spring_2022_Large_data__146.txt";
  }

  fstream myFile;
    myFile.open(fileName, ios::in);
    if(myFile.is_open()) {
      string line;
      while(getline(myFile, line)) {
        string s;
        vector<double> temp;
        stringstream iss(line);
        while(iss >> s) {
          temp.push_back(stod(s));
        }
        testData.push_back(temp);
        temp.clear();
        // cout << line << endl;
      }
      myFile.close();
    }
}


void modifyData(vector<double> &temp, vector<int> current_set, vector<int> feature_to_add) {
  //1. combine vectors and sort them in order
  //2. invert the vectors
  //3. change columns to 0 according  to inverted vector

  //combining current set and feature to add
  vector<int> combine_vector(current_set.size() + feature_to_add.size());
  merge(current_set.begin(), current_set.end(), feature_to_add.begin(), feature_to_add.end(), combine_vector.begin());

  //sorting them
  sort(combine_vector.begin(), combine_vector.end());

  //making the inverted vector
  vector<int> inverted_vec;
  bool located_in = false;

  //inverted vector using 10 features
  for(int x=1; x<11; x++) {
    for(int i=0; i<combine_vector.size(); i++) {
      if(x == combine_vector[i]) {
        located_in = true;
      }
    }

    if(located_in == false) {
      inverted_vec.push_back(x);
    }
    located_in = false;
  }

  // for(auto x : inverted_vec) {
  //   cout << x << " ";
  // }


  //looping through each value in inverted_vec
  for(int i=0; i<inverted_vec.size(); i++) {
    // cout << inverted_vec[i] << " ";
    
    // cout << i << " ";
    int change=0;
    
    temp[inverted_vec[i]-1] =0;
    // cout << inverted_vec[i]-1 << " ";
    //looping through vector of features (temp)
    for(int x=inverted_vec[i]-1; x<temp.size(); x++) {
      //every 10th item make 0 
      if(change == 10) {
        temp[x]=0;
        change=0;
        // cout << x << " ";
      }
      change++;
    }
  }

//   int change = 0;
//   for(int i=0; i<temp.size(); i++) {
//       cout << temp[i] << " ";
//       change++;
//       if(change == 10) {
//         cout << endl;
//         change=0;
//       }
//     }

}

double getAccuracy(vector<vector<double>> testData, vector<int> current_set, vector<int> feature_to_add) {
    vector<double> object_to_classify; //vector of features
    vector<double> label_object_to_classify; //vector of class labels 
    vector<double> temp; //copy features here, make modifications, change back to og, repeat 

    //loops to get our vectors
    for(int row=0; row<testData.size(); row++) {
      label_object_to_classify.push_back(testData[row][0]);
      for(int col=1; col<testData[row].size(); col++) {
        object_to_classify.push_back(testData[row][col]);
        temp.push_back(testData[row][col]); //test
      }
    }
    // cout<<"im here\n";
    // vector<int> z = {1,4,7}; //make these 2 vectors into parameters
    // vector<int> y = {10};
    modifyData(temp, current_set, feature_to_add);

    // cout<<"imhere 2\n";

    int number_correctly_classified = 0;

    //going over the rows of the dataset
    for(int i=1; i<testData.size(); i++) {
      double nearest_neighbor_distance = DBL_MAX;
      int nearest_neighbor_location = INT_MAX;
      double nearest_neighbor_label = 0;

      //nearest neighbor with 
      for(int k=1; k<testData.size(); k++) {
        //don't compare with itself
        if(k != i) {
          // cout << "Ask if " << i << " is nearest neighbors with " << k << endl;
          double euclidian_distance = calculate_distance(temp, temp, i-1, k-1);

          if(euclidian_distance < nearest_neighbor_distance) {
            nearest_neighbor_distance = euclidian_distance;
            nearest_neighbor_location = k;
            nearest_neighbor_label = label_object_to_classify[k];
            // cout << nearest_neighbor_distance << endl;
          }
        }
      }

      //checks to see if the class of the object to classify is the same class as its nearest neighbor
      if(label_object_to_classify[i-1] == nearest_neighbor_label) {
        // cout << label_object_to_classify[i] << " AND " << nearest_neighbor_label << endl;
        // cout << number_correctly_classified << endl;
        number_correctly_classified++;

      }

      // cout << "Object " << i << " is class " << label_object_to_classify[i-1];
      // cout << endl << "Its nearest neighbor is " << nearest_neighbor_location << " which is in class " << nearest_neighbor_label << endl;
      temp = object_to_classify;
    }

    double accuracy = (number_correctly_classified * 1.0) / testData.size();


    // only 70 of them are right but i got 77% accuracy 
    // cout << "test data size: " << testData.size();
 
    // cout << "number correct classify: " << number_correctly_classified;

    // cout << "accuracy is: " << accuracy;

    // for(auto x : label_object_to_classify) {
    //   cout << x << endl;
    // }

    // for(auto x : object_to_classify) {
    //   cout << x << endl;
    // }

    return accuracy;
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

void forward_selection(vector<vector<double>> testData, int numFeatures) {
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
                double accuracy = getAccuracy(testData, current_set_of_features, feature_to_add_at_this_level);
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

void backward_selection(vector<vector<double>> testData, int numFeatures) {
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
                int accuracy = getAccuracy(testData, current_set_of_features, feature_to_add_at_this_level);
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

