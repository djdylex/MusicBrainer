#include "HTMBrain.h"

HTMLayer::HTMLayer(int columns, int cells, int inputRange) : columnConverter(columns, inputRange), active(columns, cells), predictive(columns, cells) {
	resetSegments();
	resetActive();
	resetPredictive;
}

// In the feed forward, input is converted to active a sparse selection of minicolumns, for which all cells in the minicolumn have the exact same receptive field. (e.g will activate on seeing the same symbol)
void HTMLayer::createColumnConverter(int CPC) {
	for int
}

void HTMLayer::feedForward(int symbol) {
	// All cells in minicolumn share same feed forward receptive field.
	// If a cell's feedforward is above threshold and was predicted then that cell is set as active
	// If no cells in a column were predicted, then all cells are set as active
}

void HTMLayer::resetSegments() {
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
	//Iterate through all active connections
	// Set to zero
}

void HTMLayer::resetPredictive() {
	// Iterate through all prediction connections
	// Set to zero
}