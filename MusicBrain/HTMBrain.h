#ifndef HTMBrain_H
#define HTMBrain_H

#include <Eigen/Dense>
#include <vector>

using namespace std;
using namespace Eigen;


class HTMBrain {
private:
	vector<vector<MatrixXd>> segments;
	MatrixXd active;
	MatrixXd predictive;

};

#endif