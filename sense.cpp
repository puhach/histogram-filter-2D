#include "headers/sense.h"
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
  
  	/*future<void> handles[height];
  	
  	for (int i = 0; i < height; ++i)
    {
      handles[i] = std::async(std::launch::async, [p_hit, p_miss, color, &grid, &beliefs, &new_beliefs, width](int i)
      {
        const char *gp = grid[i].data();
        const float *bp = beliefs[i].data();
        float *nbp = new_beliefs[i].data();
        for (int j = 0; j<width; ++j)
        {
          *nbp = *gp == color ? p_hit*(*bp) : p_miss*(*bp);
          ++nbp;
          ++gp;
          ++bp;
        }
      }, i); // lambda, async call      
      
    } // for i
  	*/
  
  	/*
  	for (int i = 0; i < height; ++i)
    {
      const char *gp = grid[i].data();
      const float *bp = beliefs[i].data();
      float *nbp = new_beliefs[i].data();
      for (int j = 0; j<width; ++j)
      {
        *nbp = *gp == color ? p_hit*(*bp) : p_miss*(*bp);
        ++nbp;
        ++gp;
        ++bp;
      }
    }*/
  
  	// try for_each or transform algorithm
  	/*
  	for (int i = 0; i < height; ++i)
    {
      std::transform(grid[i].begin(), grid[i].end(), beliefs[i].begin(), new_beliefs[i].begin(), [color, p_hit, p_miss](char c, float b){
        return c==color ? p_hit * b : p_miss * b;
      });
    }*/
    //});	
  
  	/*for (int i = 0; i < height; ++i)  
    {
      
      for (int j = 0; j < width; ++j)
      {
        new_beliefs[i][j] = grid[i][j] == color ? p_hit*beliefs[i][j] : p_miss*beliefs[i][j];        
      }
    }*/
  
  	/*vector<vector<float> >::iterator it_nbr = new_beliefs.begin();
  	vector<vector<char> >::const_iterator it_gr = grid.begin();
  	vector<vector<float>>::const_iterator it_br = beliefs.begin();
  	for (;it_gr != grid.end(); ++it_gr, ++it_br, ++it_nbr)
	//for (int i = 0; i < height; ++i)  
    {
      vector<float>::iterator it_nbc = it_nbr->begin();
      vector<char>::const_iterator it_gc = it_gr->begin();
      vector<float>::const_iterator it_bc = it_br->begin();
      
      for (;it_gc != it_gr->end(); ++it_gc, ++it_bc, ++it_nbc)
      //for (int j = 0; j < width; ++j)
      {
        //new_beliefs[i][j] = grid[i][j] == color ? p_hit*beliefs[i][j] : p_miss*beliefs[i][j];
        *it_nbc = *it_gc == color ? p_hit*(*it_bc) : p_miss*(*it_bc);
      }
    }*/
  
  	//return new_beliefs;
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
