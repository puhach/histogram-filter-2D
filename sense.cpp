#include "sense.h"
#include <algorithm>
#include <future>

using namespace std;

// OPTIMIZATION: Pass larger variables by reference
// TODO: try reusing beliefs
vector< vector <float> > sense(char color, const vector< vector <char> > &grid, /*const*/ vector< vector <float> > &beliefs,  float p_hit, float p_miss) 
{
  	int height = grid.size(), width = grid.front().size();
  
  	//vector<vector<float> > new_beliefs(height, vector<float>(width, 0));
  
  	
  	for (int i = 0; i < height; ++i)
    {
      const char *gp = grid[i].data();
      float *bp = beliefs[i].data();
      //float *nbp = new_beliefs[i].data();
      for (int j = 0; j<width; ++j)
      {
        //*nbp = *gp == color ? p_hit*(*bp) : p_miss*(*bp);
        //++nbp;
        *bp = *gp == color ? p_hit*(*bp) : p_miss*(*bp);
        ++gp;
        ++bp;
      }
    }
  
  	return beliefs;
  
  	/*
	// OPTIMIZATION: Is the newGrid variable necessary?
  	// Could the beliefs input variable be updated directly?
  	vector< vector <float> > newGrid;
	vector<float> row, newRow;

	float prior, p;

	char cell;

	int i, j, height, width;
	height = grid.size();
	width = grid.size();

	for (i=0; i<grid.size(); i++) {
		newRow.clear();
		for (j=0; j<grid[0].size(); j++) {
          	// OPTIMIZATION: Which of these variables are 					needed?
			prior = beliefs[i][j];
			cell = grid[i][j];
			if (cell == color) {
				p = prior * p_hit;
			}
            // OPTIMIZATION: if else statements might be 
          	// 	faster than two if statements
			if (cell != color) {
				p = prior * p_miss;
			}
			newRow.push_back(p);
		}
		newGrid.push_back(newRow);
	}
	return newGrid;
    */
}
