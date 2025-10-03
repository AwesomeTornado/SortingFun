#include "DataManager.h"
#include <random>



DataManager::DataManager(int elements) {
	data = new int[elements];
	length = elements;
}

/*
* Generates a histogram in the form of an array for easy visualization
* Args:
* bins, the number of elements in the array (columns in histogram)
* Returns:
* A pointer to the histogram array.
*/
float* DataManager::histogram(int bins, float* rvalue) {
	if (bins > length) {
		bins = length;
	}
	int elementsPerBin = length / bins;
	for (int i = 0; i < bins; i++) {// Initialize memory
		rvalue[i] = 0;
	}
	for (int i = 0; i < length; i++) {
		int bin = i / elementsPerBin; // calculate which bin we are currently in
		rvalue[bin] += (data[i] / (float)elementsPerBin); // Average together the elements in each bin
	}
	float maxBin = rvalue[0];
	for (int i = 1; i < bins; i++) { // Normalize the bins
		if (maxBin < rvalue[i]) { //find the max value
			maxBin = rvalue[i];
		}
	}
	for (int i = 0; i < bins; i++) {// Normalize the bins
		rvalue[i] = rvalue[i] / maxBin; //scale to unit vectors.
	}
	return rvalue;
}

bool DataManager::isSorted() {
	for (int i = 1; i < length; i++) {
		if (data[i] < data[i - 1]) {
			return false;
		}
	}
	return true;
}

/*
* Switches between the various starting conditions.
* Args:
* scrambletype, the initial state
* seed, the random seed if randomized.
*/
void DataManager::scramble(randomizer scrambleType, int seed) {
	switch (scrambleType) {
	case Random:
		random(seed);
		break;
	case Sorted:
		sorted(seed);
		break;
	case Reversed:
		reversed();
		break;
	}
}

/*
Initialize a reversed array.

Returns:
	int, 0 for no error.
Actions:
	Re orders class variable "data" with a random assignment.
*/
int DataManager::reversed() {
	for (int i = 0; i < length; i++) {
		data[i] = length - i;
	}
	return 0;
}

/*
Initialize a sorted array.

Returns:
	int, 0 for no error.
Actions:
	Re orders class variable "data" with a random assignment.
*/
int DataManager::sorted(int seed) {
	srand(seed);
	data[0] = abs(rand() % 10); // get a reasonable starting value.
	for (int i = 1; i < length; i++) {
		int increment = (abs(rand()) % 10000); // MAGIC NUMBERS: This is some random amount to increment, so that values are not all bunched together. Larger lists should have less spacing.
		data[i] = data[i - 1] + increment + 1; // add one to make sure we have no two equal values.
	}
	return 0;
}

/*
Initialize a randomized array.

Args:
	seed, the number to seed rand with
Returns:
	int, 0 for no error.
Actions:
	Re orders class variable "data" with a random assignment.
*/
int DataManager::random(int seed) {
	sorted(seed);
	
	for (int i = 0; i < length; i++) {
		//Gather coordinates
		int A = abs(rand()) % (i + 1);

		int temp = data[A]; // execute a swap
		data[A] = data[i];
		data[i] = temp;
	}
	return 0;
}