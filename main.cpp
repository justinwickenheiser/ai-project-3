// CIS 365 Project 3
// use 'clang++ main.cpp -o output' to compile

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <iomanip>
using namespace std;

struct Point {
	double coord[2];
	int kValue;
};

// prototypes
void readFile(Point array[]);
int findFileSize();
void findCentroid(int kClusters, int listSize, Point centroids[], Point citiesList[]);
void assignToCentroid(int kClusters, int listSize, Point centroids[], Point citiesList[]);
double distanceFormula(Point coord1, Point coord2);
void calcNewCentroid(int kClusters, int listSize, Point newCentroids[], Point citiesList[]);
bool compareCentroid(int kClusters, Point currentCentroids[], Point newCentroids[]);
void updateCentroid(int kClusters, Point currentCentroids[], Point newCentroids[]);

int main() {
	int listSize = findFileSize();
	Point cities[listSize];
	// fills cities[] with the values from the file
	readFile(cities);

	// for each set of centroids (or k clusters)
	for (int i = 3; i <= 3; i++) {
		// tracks the number of points assigned to each cluster
		Point centroids[i];
		Point newCentroids[i];
		bool isCentroidSame = false;
		
		findCentroid(i, listSize, centroids, cities);
		// start while loop
		while ( !isCentroidSame ) {
			assignToCentroid(i, listSize, centroids, cities);
			calcNewCentroid(i, listSize, newCentroids, cities);
			isCentroidSame = compareCentroid(i, centroids, newCentroids);
			// if compare returns false then centroids = newCentroids
			if ( !isCentroidSame ) {
				updateCentroid(i, centroids, newCentroids);
			}
		}
		
		cout << "City" << setw(13) << "Lat" << setw(13) << "Long" << setw(10) << "kValue" << endl;
		cout << "----" << setw(13) << "-------" << setw(13) << "-------" << setw(10) << "------" << endl;
		// loop through list of cities and display the final state for each city
		for (int j=0; j < listSize; j++) {
         	        cout << j << setw(15) <<  cities[j].coord[0] << setw(10) << cities[j].coord[1] << setw(10) << cities[j].kValue << endl;
        	}
	}

	return 0;
}

// function declarations

// read file and save data points to array
void readFile(Point array[]) {
	string city;
	double lat, lng;
	int counter = 0;
	ifstream myfile;
	myfile.open("latLongData.txt");
	if (myfile.is_open()) {
		while ( myfile >> city >> lat >> lng ) {
			array[counter].coord[0] = lat;
			array[counter].coord[1] = lng;
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
	myfile.open("latLongData.txt");
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
				cout << "Centroid " << j <<": City -> " << i << endl;
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
