#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <iomanip>
#include "functions.h"
using namespace std;

// function declarations

// read file and save data points to array
void readFile(Point array[]) {
    string city;
    double lat, lng;
    int counter = 0;
    ifstream myfile;
    myfile.open("us-cities-sample.csv");
    if (myfile.is_open()) {
        while ( myfile >> city >> lat >> lng ) {
            array[counter].coord[0] = lat;
            array[counter].coord[1] = lng;
            strcpy(array[counter].name, city.c_str());
            counter++;
        }
        myfile.close();
    } else {
        cout << "Unable to open file." << endl;
    }
}

// count the number of lines in the file
int findFileSize() {
    string city;
    double lat, lng;
    int counter = 0;
    ifstream myfile;
    myfile.open("us-cities-sample.csv");
    if (myfile.is_open()) {
        while ( myfile >> city >> lat >> lng ) {
            counter++;
        }
        myfile.close();
    } else {
        cout << "Unable to open file." << endl;
    }
    return counter;
}

// randomly assigns the first centroids when starting a new cluster for k clusters
void findCentroid(int kClusters, int listSize, Point centroids[], Point citiesList[]) {
    int index;
    srand (time(NULL));
    
    // for each centroid k
    for (int i = 0; i < kClusters; i++) {
        index = rand() % listSize;
        centroids[i].coord[0] = citiesList[index].coord[0];
        centroids[i].coord[1] = citiesList[index].coord[1];
        centroids[i].kValue = i;
    }
}

// assigns all non centroid points to its nearest centroid
void assignToCentroid(int kClusters, int listSize, Point centroids[], Point citiesList[]) {
    // for each point in citiesList[]
    for (int i=0; i < listSize; i++) {
        bool firstCompare = true;
        double previousDist = 0;
        // loop through the centroids
        for (int j=0; j < kClusters; j++) {
            // find distance between two points
            double currentDist = distanceFormula(citiesList[i],centroids[j]);
            // if the citie is not the centroid and its the first time comparing the city to the centroids
            if (currentDist != 0 && firstCompare) {
                firstCompare = false;
                // assign city to the given cluster
                citiesList[i].kValue = j;
                previousDist = currentDist;
            } else if (currentDist != 0 && currentDist < previousDist) {
                // a closer centroid was found for the current city
                citiesList[i].kValue = j;
                previousDist = currentDist;
            } else if (currentDist == 0 ) {
                cout << "Random Centroid " << j;
                cout << ":  Lat = " << centroids[j].coord[0];
                cout << "      Long = " << centroids[j].coord[1] << endl;
            }
        }
    }
}

// Calculates the new centroid of each cluster, "returns" the newCentroids[]
void calcNewCentroid(int kClusters, int listSize, Point newCentroids[], Point citiesList[]) {
    // for each cluster
    for (int i=0; i < kClusters; i++) {
        // declare tallying variables
        double xDist = 0;
        double yDist = 0;
        int numPoints = 0;
        
        // Loop through array of cities
        for (int j=0; j < listSize; j++) {
            // if the current city belongs to the current cluster,
            // add to it's total x and y distances
            // increment the total number of points in current cluster
            if (citiesList[j].kValue == i) {
                xDist += citiesList[j].coord[0];
                yDist += citiesList[j].coord[1];
                numPoints++;
            }
        }
        
        // calculate the average x and y distance to find the new centroid
        newCentroids[i].coord[0] = xDist / (double)numPoints;
        newCentroids[i].coord[1] = yDist / (double)numPoints;
        newCentroids[i].kValue = i;
    }
}

// returns true if the centroids list are the same, false if ANY changed
bool compareCentroid(int kClusters, Point currentCentroids[], Point newCentroids[]) {
    for (int i = 0; i < kClusters; i++) {
        // if current and new latitudes are NOT Equal OR the current and new longitudes are NOT Equal
        if (currentCentroids[i].coord[0] != newCentroids[i].coord[0] || currentCentroids[i].coord[1] != newCentroids[i].coord[1]) {
            return false;
        }
    }
    return true;
}

// updates the current centroid to equal the new centroid
void updateCentroid(int kClusters, Point currentCentroids[], Point newCentroids[]) {
    for (int i=0; i < kClusters; i++) {
        currentCentroids[i].coord[0] = newCentroids[i].coord[0];
        currentCentroids[i].coord[1] = newCentroids[i].coord[1];
    }
}

// calculate distance between 2 points
double distanceFormula(Point coord1, Point coord2) {
    double x1 = coord1.coord[0];
    double y1 = coord1.coord[1];
    double x2 = coord2.coord[0];
    double y2 = coord2.coord[1];
    
    return sqrt( pow( (x2 - x1), 2.0 ) + pow( (y2 - y1), 2.0 ) );
}
