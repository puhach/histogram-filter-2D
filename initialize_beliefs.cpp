#include "headers/initialize_beliefs.h"

using namespace std;

// OPTIMIZATION: pass large variables by reference
vector< vector <float> > initialize_beliefs(const vector< vector <char> > &grid) {

  	int height = grid.size(), width = grid[0].size();
  	float prob_per_cell = 1.0 / ( (float) height*width) ;
  
	// OPTIMIZATION: Which of these variables are necessary?
	// OPTIMIZATION: Reserve space in memory for vectors
  	//vector< vector <float> > newGrid(height, vector<float>(width, 0.0));
	//vector<float> newRow;
	//int i, j, height, width, area;
	//float total, prob_per_cell;

	
 
	//area = height * width;

  	//prob_per_cell = 1.0 / ( (float) area) ;

  	// OPTIMIZATION: Is there a way to get the same results 	// without nested for loops?
	/*for (i=0; i<grid.size(); i++) {
		newRow.clear();
		for (j=0; j<grid[0].size(); j++) {
			newRow.push_back(prob_per_cell);
		}
		newGrid.push_back(newRow);
	}
	return newGrid;
    */
  
  	return vector< vector <float> >(height, vector<float>(width, prob_per_cell));
}