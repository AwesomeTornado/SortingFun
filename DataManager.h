#pragma once


class DataManager
{
public:
	enum randomizer {
		Reversed,
		Sorted,
		Random,
		None,
	};

	DataManager(int elements);

	void scramble(randomizer scrambleType, int seed = 0);

	float* histogram(int bins, float* result);

	bool isSorted();

	int length;

	int* data;

private:
	int reversed();
	int sorted(int seed);
	int random(int seed);
};

