# ai-project-3

This project reads a set of data, and clusters that data using k-means clustering.

When using a .cvs file or .txt file, the file must ONLY have 1 <string> and  2 <doubles> per line in that order. The City, Latitude and Longitude.
There cannot be blank lines between two rows, and there should be spaces between the cities, Latitude and Longitude.
However, there should be NO spaces in the city name itself.
Use underscores (_) as a spaces in city names. Any other character will prevent the file from being read properly.

To compile the program.
1. Can be run through EOS
2. Unzip the files
3. Command: clang++ main.cpp functions.cpp -o output

Executing the code:
1. ./output > outputFile.txt

If you would like to test different files, you will have change the file name in the two locations inside functions.cpp.
Two test files are included: us-cities-sample.csv and latLongData.txt
- Currently, the code is programmed to run us-cities-sample.csv
        - This file contains a list of 1008 cities in America.
- The latLongData.txt file contains a short list of 60 US cities.

