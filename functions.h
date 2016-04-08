struct Point {
    double coord[2];
    int kValue;
    char name[25];
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
