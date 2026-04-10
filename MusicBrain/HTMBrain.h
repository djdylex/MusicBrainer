#ifndef HTMBrain_H
#define HTMBrain_H

#include <cstdlib>
#include <Eigen/Dense>
#include <vector>
#include <map>
#include <random>
#include <set>
#include <algorithm>

using namespace std;
using namespace Eigen;

struct segment {
	std::map<std::tuple<int, int, int>, float> connections;
};

class HTMLayer {
private:
	void createColumnConverter();
	int randInt(int min, int max);
	float randFloat();
	std::random_device rd_; 
	std::mt19937 gen_; 
	vector<vector<vector<segment>>> segments_; // segment per cell (i, j), n segments per cell, 
	//MatrixXd columnConverter_; // columns x inputrange
	MatrixXd active_;
	MatrixXd predictive_;
	std::map<int, std::vector<int>> columnConverter_;
	//std::map<int, 
	const int inputRange_; // e.g 36 notes
	const int columns_ = 1024;
	const int ffCols_ = columns_ * 0.02; // Conversion of data to minicolumns (feedforward)
	const int cells_ = 32; // cells per column
	const int segmentsCount_ = 128; // segments per cell
	const int maxSynapses_ = 40;
	const int predictThresh = 15;
	const int permThresh = 0.3;

public:
	HTMLayer(int columns, int cells, int inputRange);
	void resetSegments();
	void resetActive();
	void resetPredictive();
	void pruneConnections(int pruneAmount);
	void feedForward(int symbol);
};
#endif