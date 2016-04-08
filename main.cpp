// CIS 365 Project 3
// use 'clang++ main.cpp -o output' to compile

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <iomanip>
#include "functions.h"

#include "koolplot.h"

using namespace std;

int main() {
	int listSize = findFileSize();
    
	Point cities[listSize];
	// fills cities[] with the values from the file
	readFile(cities);

	// for each set of centroids (or k clusters)
	for (int i = 3; i <= 5; i++) {
		// Display Header
		cout << "===========================================================" << endl;
		cout << "=======================================================" << endl;
		cout << "===================================================" << endl;
		cout << "===============================================" << endl;
		cout << "===========================================" << endl;
		cout << "NUMBER OF CLUSTERS: " << i << endl;
		cout << "===========================================" << endl;
		cout << "===============================================" << endl;
		cout << endl << endl;

		// tracks the number of points assigned to each cluster
		Point centroids[i];
		Point newCentroids[i];
		bool isCentroidSame = false;
		int centroidReassignmentCounter = 0;
        
		findCentroid(i, listSize, centroids, cities);
        
        // start while loop
		while ( !isCentroidSame ) {
			assignToCentroid(i, listSize, centroids, cities);
            calcNewCentroid(i, listSize, newCentroids, cities);
            isCentroidSame = compareCentroid(i, centroids, newCentroids);
			// if compare returns false then centroids = newCentroids
			if ( !isCentroidSame ) {
				updateCentroid(i, centroids, newCentroids);
				centroidReassignmentCounter++;

				cout << endl;
               			for (int j = 0; j < i; j++) {
                        		cout << "Itteration Centroid " << j << ": Lat = " << centroids[j].coord[0] << "      Long = " << centroids[j].coord[1] << endl;
                		}
			}
		}

		cout << endl;
		for (int j = 0; j < i; j++) {
			cout << "Final Centroid " << j << ": Lat = " << centroids[j].coord[0] << "	Long = " << centroids[j].coord[1] << endl;
		}

		cout << endl;
		cout << "Number of times the centroids were updated: " << centroidReassignmentCounter << endl;

		cout << endl;	
		cout << "City" << setw(13) << "Lat" << setw(13) << "Long" << setw(10) << "kValue" << endl;
		cout << "----" << setw(13) << "-------" << setw(13) << "-------" << setw(10) << "------" << endl;
		// loop through list of cities and display the final state for each city
		for (int j=0; j < listSize; j++) {
            cout << j << setw(15) <<  cities[j].coord[0] << setw(13) << cities[j].coord[1] << setw(10) << cities[j].kValue << endl;
            addMark(x, y, cities[j].coord[0], cities[j].coord[1]);
        }
        plot(x, y);
		cout << endl << endl;
	}

	return 0;
}