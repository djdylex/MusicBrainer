#ifndef HTMBrain_H
#define HTMBrain_H

#include <cstdlib>
#include <Eigen/Dense>
#include <vector>

using namespace std;
using namespace Eigen;


class HTMLayer {
private:
	void createColumnConverter(int CellsPerCol);
	vector<vector<MatrixXd>> segments_;
	MatrixXd columnConverter_; // columns x inputrange
	MatrixXd active_;
	MatrixXd predictive_;
	const int inputRange_;
	const int columns_ = 1024;
	const int ffCols_ = columns_ * 0.02; // Conversion of data to minicolumns (feedforward)
	const int cells_ = 32; // cells per column
	const int segments_ = 128; // segments per cell
	const int maxSynapses_ = 40;

public:
	HTMLayer(int columns, int cells, int inputRange);
	void resetSegments();
	void resetActive();
	void resetPredictive();
	void pruneConnections(int pruneAmount);
	void feedForward(int symbol);
};

#endif