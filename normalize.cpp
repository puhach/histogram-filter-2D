#include "headers/normalize.h"
using namespace std;

// OPTIMIZATION: Pass variable by reference
vector< vector<float> > normalize(vector< vector <float> > &grid) {

  	// OPTIMIZATION: Avoid declaring and defining 				// intermediate variables that are not needed.
	float total = 0.0;
	int height = grid.size(), width = grid[0].size();
  
	for (int i = 0; i < height; ++i)
	{
		for (int j=0; j<width; ++j)
		{
			//oldProb = row[j];
			//total += oldProb;
          	total += grid[i][j];
		}
	}

	/*vector< vector<float> > newGrid;

	for (i = 0; i < grid.size(); i++) {
		vector<float> row = grid[i];
		newRow.clear();
		for (j=0; j< row.size(); j++) {
			float oldProb = row[j];
			float newProb = oldProb / total;
			newRow.push_back(newProb);
		}
		newGrid.push_back(newRow);
	}
	*/
  
  	for (int i = 0; i < height; ++i)
      for (int j = 0; j < width; ++j)
        grid[i][j] /= total;
  
	return grid;
}
