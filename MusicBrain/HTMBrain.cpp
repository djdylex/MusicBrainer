#include "HTMBrain.h"

HTMLayer::HTMLayer(int columns, int cells, int inputRange) : columns_(columns), cells_(cells), inputRange_(inputRange), 
	active_(columns, cells), predictive_(columns, cells), gen_(rd_()) {

	segments_ = vector<vector<vector<segment>>>(
		columns_, vector<vector<segment>>(
			cells_, vector<segment>(
				segmentsCount_, segment{})
		)
	);

	createColumnConverter();
	resetSegments();
	resetActive();
	resetPredictive();
}

int HTMLayer::randInt(int min, int max) {
	std::uniform_int_distribution<> dist(min, max);
	return dist(rd_);
}

float HTMLayer::randFloat() {
	std::uniform_real_distribution<float> dist(0, 1);
	return dist(rd_);
}

MatrixXd DecToBinVec(int dec) {
	int size = log2(dec);
	int rem = dec;
	MatrixXd vec(1, size + 1);
	for (int i = size; i >= 0; i--) {
		if (pow(2, i) > rem) {
			vec(0, i) = 0;
			continue;
		} else {
			rem -= pow(2, i);
			vec(0, i) = 1;
		}
	}
}

// In the feed forward, input is converted to a sparse selection of minicolumns, for which all cells in the minicolumn have the exact same receptive field. (e.g will activate on seeing the same symbol)
void HTMLayer::createColumnConverter() {
	/*// convert input to binary number < no of minicolumns using some kind of or random
	double A = (sqrt(5.0) - 1.0) / 2.0;
	int tableSize = pow(2, columns_);

	// elimnate duplicates
	// create dictionary for these numbersive neuron matrix
	for (int i = 0; i < inputRange_; i++) {
		int hash = tableSize * (i * A);

		columnConverter_[i] = DecToBinVec(hash);
	}*/

	int k = 40; //cols to be activated during feed forward
	for (int inputVal = 0; inputVal < inputRange_; inputVal++) {
		vector<int> nums(columns_);

		for (int i = 0; i < columns_; i++) {
			nums[i] = i;
		}

		for (int i = 0; i < k; i++) {
			int swapIndx = randInt(0, columns_ - 1);
			swap(nums[i], nums[swapIndx]);
			columnConverter_[inputVal][i] = nums[i];
		}
	}
}

void HTMLayer::feedForward(int symbol) {
	auto activeCols = columnConverter_[symbol];

	for (int col = 0; col < activeCols.size(); col++) {
		for (int cell = 0; cell < cells_; cell++) {
			for (int seg = 0; seg < segmentsCount_; seg++) { // Update predicted just for relevant columns
				int sum = 0;
				for (const auto& [key, value] : segments_[col][cell][seg].connections) {
					sum += ceil(value - permThresh) * active_(col, cell);
				}

				if (sum > predictThresh) {
					predictive_(col, cell) = 1;
				}
			}
		}

		bool predicted = false;
		for (int cell = 0; cell < cells_; cell++) {
			if (predictive_(col, cell) == 1) {
				active_(col, cell) = 1;
				predicted = true;
			}
		}

		if (!predicted) {
			for (int cell = 0; cell < cells_; cell++) {
				active_(col, cell) = 1;
			}
		}
	}

	// Predictive networks (WHY DONT I JUST DO THIS FIRST - LAZY CHECKING BASICALLY)
	// multiply hardman - activation network by segments
	// 
	// All cells in minicolumn share same feed forward receptive field.
	// If a cell's feedforward is above threshold and was pre
	// on feed forward, convert binary number to actdicted then that cell is set as active
	// If no cells in a column were predicted, then all cells are set as active
}

void HTMLayer::resetSegments() {
	for (int col = 0; col < segments_.size(); col++) {
		for (int cell = 0; cell < segments_[0].size(); cell++) {
			for (int seg = 0; seg < segmentsCount_; seg++) {
				for (int con = 0; con < maxSynapses_; con++) {
					segments_[col][cell][seg].connections[{randInt(0, segmentsCount_), randInt(0, cells_), seg}] = randFloat();
				}
			}
		}
	}
	// Iterate through each segment for each cell for every column
	// Make sure each permenance value is set to zero
	// Select s connections in each segment to have non zero permenance values, assigning a value between 0-1
	// values more than threshold (usually 0.3) will be considered connections
}

void HTMLayer::pruneConnections(int pruneAmount) {
	// Iterate through all non zero connections for every segment in every cell
	// Subtract a small value p for each value
}

void HTMLayer::resetActive() {
	for (int c = 0; c < active_.cols(); c++) {
		for (int r = 0; c < active_.rows(); r++) {
			active_[r, c] = 0;
		}
	}
}

void HTMLayer::resetPredictive() {
	for (int c = 0; c < active_.cols(); c++) {
		for (int r = 0; c < active_.rows(); r++) {
			predictive_[r, c] = 0;
		}
	}
}