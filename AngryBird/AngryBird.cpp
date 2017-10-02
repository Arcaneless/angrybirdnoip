// AngryBird.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

class Bird {
public:
	float x, y;
	Bird(float x, float y) {
		this->x = x, this->y = y;
	}

	bool operator== (const Bird& other) {
		return x == other.x && y == other.y;
	}
};

// Calculation of trajectory
float findB(float x1, float y1, float x2, float y2) {
	return (y2*x1*x1 - y1*x2*x2) / (x2*x1*x1 - x1*x2*x2);
}

float findA(float x1, float y1, float x2, float y2) {
	return (y1 - findB(x1, y1, x2, y2)*x1) / x1*x1;
}

vector<int> BFS_find_largest(vector<vector<int>> list) {
	int max = list[0].size();
	vector<int> largest_vec = list[0];
	for (vector<vector<int>>::iterator i = list.begin(); i != list.end(); i++) {
		if (max < (*i).size()) max = (*i).size(), largest_vec = *i;
	}
	return largest_vec;
}

void BFS_delete_specific(vector<Bird> list, Bird value) {
	vector<Bird>::iterator pos = find(list.begin(), list.end(), value);
	if (pos != list.end()) list.erase(pos);
}

int BFS(vector<Bird> birds) {
	if (birds.size() == 0) return 0;

	vector<vector<int>> list_scan_index;
	for (vector<Bird>::iterator i = birds.begin(); i != birds.end(); i++) {
		Bird b1 = *i;
		vector<int> scan_index;
		float ca = 0, cb = 0;

		for (vector<Bird>::iterator j = birds.begin(); j != birds.end(); j++) {
			if (i == j) {
				scan_index.push_back(distance(birds.begin(), j));
				continue;
			}
			Bird b2 = *j;

			float b = findB(b1.x, b1.y, b2.x, b2.y);
			float a = findA(b1.x, b1.y, b2.x, b2.y);

			if (ca == 0 && cb == 0) ca = a, cb = b;
			if (ca == a && cb == b && a < 0) {
				scan_index.push_back(distance(birds.begin(), j));
			}
		}
		list_scan_index.push_back(scan_index);
	}
	vector<int> largest_scan_index = BFS_find_largest(list_scan_index);

	vector<Bird> copyb(birds);
	for (vector<int>::iterator i = largest_scan_index.begin(); i != largest_scan_index.end(); i++) {
		vector<Bird>::iterator pos = find(birds.begin(), birds.end(), copyb.at(*i));
		if (pos != birds.end()) birds.erase(pos);
	}
	
	

	return 1 + BFS(birds);
}



int main() {
	int stage, birdNum, mode;

	ifstream input("angrybirds.in");
	ofstream output("angrybirds.out");
	string line;

	input >> stage;
	for (int i = 0; i < stage; i++) {
		input >> birdNum >> mode;
		vector<Bird> list;

		for (int j = 0; j < birdNum; j++) {
			float x, y;
			input >> x >> y;
			Bird holder(x, y);
			list.push_back(holder);
		}

		output << BFS(list) << endl;
	}
	input.close();
	output.close();


    return 0;
}

