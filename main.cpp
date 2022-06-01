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

#include "searchAlgorithms.cpp"

using namespace std;

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

int main() {
    srand (time(NULL)); //seeding random time

    vector<vector<double>> testData;

    fstream myFile;
    myFile.open("CS170_Spring_2022_Small_data__146.txt", ios::in);
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

    vector<double> object_to_classify;
    vector<double> label_object_to_classify;

    //loops to get our vectors
    for(int row=0; row<testData.size(); row++) {
      label_object_to_classify.push_back(testData[row][0]);
      for(int col=1; col<testData[row].size(); col++) {
        object_to_classify.push_back(testData[row][col]);
      }
    }

    int number_correctly_classified = 0;

    for(int i=1; i<testData.size(); i++) {
      double nearest_neighbor_distance = DBL_MAX;
      int nearest_neighbor_location = INT_MAX;
      double nearest_neighbor_label = 0;

      for(int k=1; k<testData.size(); k++) {
        if(k != i) {
          // cout << "Ask if " << i << " is nearest neighbors with " << k << endl;
          double euclidian_distance = calculate_distance(object_to_classify, object_to_classify, i-1, k-1);

          //don't compare with itself
          if(euclidian_distance < nearest_neighbor_distance) {
            nearest_neighbor_distance = euclidian_distance;
            nearest_neighbor_location = k;
            nearest_neighbor_label = label_object_to_classify[k];
            // cout << nearest_neighbor_distance << endl;
          }
        }
      }

      //prolly sumn wrong with this if statement
      if(label_object_to_classify[i] == nearest_neighbor_label) {
        number_correctly_classified++;
      }

      // cout << "Object " << i << " is class " << label_object_to_classify[i-1];
      // cout << endl << "Its nearest neighbor is " << nearest_neighbor_location << " which is in class " << nearest_neighbor_label << endl;

    }

    double accuracy = (number_correctly_classified * 1.0) / testData.size();


    //only 70 of them are right but i got 77% accuracy 
    cout << "test data size: " << testData.size();

    cout << "number correct classify: " << number_correctly_classified;

    cout << "accuracy is: " << accuracy;

    // return accuracy
    // should all be in a function


    // for(auto x : label_object_to_classify) {
    //   cout << x << endl;
    // }

    // for(auto x : object_to_classify) {
    //   cout << x << endl;
    // }


    // //menu for the program
    // cout << "Welcome to Steven Nguyen's Feature Selection Algorithm.\n\n";
    // cout << "Please enter the total number of features: ";
    // int featureChoice;
    // cin >> featureChoice;
    // cin.ignore();


    // //choosing which type of search algorithm to apply to the puzzle
    // cout << "\nEnter your choice of algorithm\n";
    // cout << "1. Forward Selection\n";
    // cout << "2. Backward Elimination\n";
    // // cout << "3. My algorithm\n";
    // int algorithm; 
    // cin >> algorithm;
    // if(algorithm == 1) {
    //   forward_selection(featureChoice);
    // }
    // if(algorithm == 2) {
    //    backward_selection(featureChoice);
    // }
    // // if(algorithm == 3) {
        
    // // }

    return 0;
}