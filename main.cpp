// CIS 365 Project 3
// use 'clang++ main.cpp -o output' to compile

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <math.h>
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
void calcNewCentroid(int kClusters, 

int main() {
	int listSize = findFileSize();
	Point cities[listSize];
	// fills cities[] with the values from the file
	readFile(cities);

/*	
	for (int i=0; i < listSize; i++) {
		cout << "----City:  " << i << "---- " << endl;
		cout << "Lat: " << cities[i].coord[0] << endl;
		cout << "Long: " << cities[i].coord[1] << endl;
		cout << endl;
	}
*/	

	// for each set of centroids (or k clusters)
	for (int i = 3; i <= 3; i++) {
		// tracks the number of points assigned to each cluster
		Point centroids[i];
		findCentroid(i, listSize, centroids, cities);
		assignToCentroid(i, listSize, centroids, cities);
		
		// loop through list of cities and display info
		for (int j=0; j < listSize; j++) {
         	        cout << "----City:  " << j << "---- " << endl;
			cout << "Lat: " << cities[j].coord[0] << endl;
                	cout << "Long: " << cities[j].coord[1] << endl;
			cout << "kValue: " << cities[j].kValue << endl;
                	cout << endl;
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

// calculate distance between 2 points
double distanceFormula(Point coord1, Point coord2) {
	double x1 = coord1.coord[0];
	double y1 = coord1.coord[1];
	double x2 = coord2.coord[0];
        double y2 = coord2.coord[1];

	return sqrt( pow( (x2 - x1), 2.0 ) + pow( (y2 - y1), 2.0 ) );
}
