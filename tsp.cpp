#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <math.h>  

using namespace std;

float dist( int k, int j, vector<float> x, vector<float> y) {
	x[k] - x[j];
	y[k] - y[j];
	int n = x.size();
	float result = sqrt((x[k] - x[j]) * (x[k] - x[j]) + (y[k] - y[j]) * (y[k] - y[j]));
	return result;
}

// computes the cost of the tour
float tourCost(vector<float> tour, vector<float> x, vector<float> y) {
	int n = tour.size();
	float result = 0.0f;
	for (int i = 1; i < n; ++i) {
		result += dist(tour[i-1], tour[i], x, y);
	}
	result += dist(tour[n-1], tour[0], x, y);
	return result;
}


vector<float> opt2(vector<float> tour, int swap1, int swap2, vector<float> x, vector<float> y) {
	int n = tour.size();
	vector<float> newTour;
	newTour.resize(n);
	//swapping
	for (int i = 1; i < swap1; ++i) {

		newTour[i-1] = tour[i-1];
		newTour[i] = tour[i];
	}
	int ptr = 0;
	for (int i = swap2; i >= swap1; --i) {
		newTour[swap1 + ptr] = tour[i];
		++ptr;
	}
	for (int i = swap2+1; i < n; ++i) {
		newTour[i] = tour[i];
	}
	return newTour;
}

vector<float> greedyTour() {
	int n = 0;
	cin >> n;
	vector<float> x; 
	x.resize(n);
	vector<float> y; 
	y.resize(n);
	for (int i = 0; i < n; ++i) {
		string xline = "";
		string yline = "";
		cin >> xline;
		cin >> yline;
		x[i] = stof(xline);
		y[i] = stof(yline);
		//cout << x[i] << "---" << y[i] << endl;
	}


	// Naive algorithm for TSP (GreedyTour)
	vector<float> tour; 
	tour.resize(n);
	vector<bool> used; 
	used.resize(n);
	tour[0] = 0;
	used[0] = true;
	int best;
	for (int i = 1; i < n; ++i) {
		best = -1;
		for (int j = 0; j < n; ++j) {
			if ((!used[j]) && ((best == -1) || (dist(tour[i-1],j, x, y) < dist(tour[i-1], best, x, y)))) {
				
				best = j;
			}
		}
		tour[i] = best;
		used[best] = true;
	}
	//cout << tourCost(tour ,x,y) << endl;
	float cmp = tourCost(tour ,x,y);
	vector<float> newTour; 
	newTour.resize(n);
	for (int i = 1; i < n-2; ++i) {
		for (int j = 1; i+j < n; ++j) {
			newTour = opt2(tour, i, i+j, x, y);
			float cmp2 = tourCost(newTour ,x,y);
			if(cmp > cmp2) {
				tour = newTour;
				cmp = cmp2;
			}
		}
	}
	cout << tourCost(tour ,x,y) << endl;
	return tour;
}

int main() {
	vector<float> tour; 

	tour = greedyTour();
	int n = tour.size();
	for (int i = 0; i < n; ++i) {
		cout << tour[i] << endl;
	}

	return 0;
}

