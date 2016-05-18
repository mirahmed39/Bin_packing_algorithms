/*******************************************************************
 * @file        : TestBinPackingAlgorithms.cpp                     *
 * @author      : Mir Ahmed										   *
 * @description : The following program tests three types of bin   *
 				  packing algorithms : Next fit, First Fit and     *
 				  First Fit Decreasing with random numbers between *
 				  range [0.0 - 1.0]. Finally, it prints the total  *
 				  number of bins needed to fit those numbers.      *
 * @date created: 05/10/2016									   *
********************************************************************/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <vector>
using namespace std;

vector<double> GenerateRandomNumbers(int num) {
	vector<double> random_numbers;
	srand(time(0));
	for (int i = 0; i < num; ++i) { 
 		const double random_variable = (double) rand() / (double) RAND_MAX;
 		random_numbers.push_back(random_variable);	
	}
	return random_numbers;
}

int NextFitBinPacking(const vector<double> &random_numbers) {
	vector<double> bins;
	bins.push_back(random_numbers[0]);
	double bin_capacity = 1;
	for (unsigned int j = 1, i = 0; j < random_numbers.size(); ++j) {
		if (bins[i] + random_numbers[j] <= bin_capacity)
			bins[i] += random_numbers[j];
		else {
			bins.push_back(random_numbers[j]);
			++i;
		}
	}
	return bins.size();
}

int FirstFitBinPacking(vector<double> random_numbers) {
	vector<double> bins;
	bins.push_back(random_numbers[0]);
	double bin_capacity = 1.0;
	// now we check to space starting from the beginning upto the last item in the bin.
	for(unsigned int j = 1; j < random_numbers.size(); ++j) {
		for (unsigned int i = 0; i < bins.size(); ++i){
			if(random_numbers[j] + bins[i] <= bin_capacity) {
				bins[i] += random_numbers[j];
				break;
			}
			else {
				// this checks for the if we reached the end of the bins
				// if yes then we haven't found space and create an extra bin
				// otherwise continue to the next iteration through the bins.
				if (i == bins.size() - 1) {
					bins.push_back(random_numbers[j]);
					break;
				}
			}
		}
	}
	return bins.size();
}

int main(int argc, char const *argv[])
{
	if (argc != 2) {
		cout << "Input Format: <Filename> <number of items>";
		return 0;
	}
	const int number_of_items = atoi(argv[1]);
	auto random_numbers = GenerateRandomNumbers(number_of_items);
	const int number_of_bins_next_fit = NextFitBinPacking(random_numbers);
	const int number_of_bins_first_fit = FirstFitBinPacking(random_numbers);
	std::sort(random_numbers.begin(), random_numbers.end(), std::greater<double>());
	const int number_of_bins_first_fit_decreasing = FirstFitBinPacking(random_numbers);
	cout << "Next fit             : "<< number_of_bins_next_fit << endl;
	cout << "First fit            : "<< number_of_bins_first_fit << endl;
	cout << "First Fit Decreasing : "<< number_of_bins_first_fit_decreasing << endl;

	return 0;
}