#include "blur.h"
#include "zeros.h"

#include <future>
#include <iostream>
#include <chrono>

using namespace std;

// OPTIMIZATION: Pass large variable by reference
//vector < vector <float> > blur(vector < vector < float> > &grid, float blurring) {
void blur(vector < vector < float> > &grid) {
//void blur(vector < vector < float> > &grid, float blurring) {

	// OPTIMIZATION: window, DX and  DY variables have the 
    // same value each time the function is run.
  	// It's very inefficient to recalculate the vectors
    // every time the function runs. 
    // 
    // The const and/or static operator could be useful.
  	// Define and declare window, DX, and DY using the
    // bracket syntax: vector<int> foo = {1, 2, 3, 4} 
    // instead of calculating these vectors with for loops 
    // and push back
  
  	const static float blurring = 0.12f;
  	const static float center = 1.0f - blurring, corner = blurring / 12.0f, adjacent = blurring / 6.0f;
  
  	const int height = grid.size();;
	const int width = grid[0].size();;
	

	//const static float kernel[3][3] = { {corner, adjacent, corner},
	//								   {adjacent, center, adjacent},
	//								   {corner, adjacent, corner} };


  	
  
	vector<vector<float> > newGrid(height, vector<float>(width));

  	
	for (int i = 1; i < height - 1; ++i)
	{
		int cy = i,
			py = i - 1,
			ny = i + 1;

		float *gpy = grid[py].data(), * gcy = grid[cy].data(), * gny = grid[ny].data(), * ngi = newGrid[i].data();
		float *gpypx = gpy, *gpycx = gpy+1, *gpynx = gpy+2;
        float *gcypx = gcy, *gcycx = gcy+1, *gcynx = gcy+2;
      	float *gnypx = gny, *gnycx = gny+1, *gnynx = gny+2;
		for (int j = 1; j < width - 1; ++j)
		{
			//int cx = j,
			//	px = j - 1,
			//	nx = j + 1;

          	*++ngi = corner * *gpypx + adjacent * *gpycx + corner * *gpynx
				+ adjacent * *gcypx + center * *gcycx + adjacent * *gcynx
				+ corner * *gnypx + adjacent * *gnycx + corner * *gnynx;
          
          	gpypx = gpycx;
          	gpycx = gpynx;
          	++gpynx;
          
          	gcypx = gcycx;
          	gcycx = gcynx;
          	++gcynx;
          
          	gnypx = gnycx;
          	gnycx = gnynx;
          	++gnynx;
			//newGrid[i][j] 
          	
			//*++ngi = corner * gpy[px] + adjacent * gpy[cx] + corner * gpy[nx]
			//	+ adjacent * gcy[px] + center * gcy[cx] + adjacent * gcy[nx]
			//	+ corner * gny[px] + adjacent * gny[cx] + corner * gny[nx];

			
			//newGrid[i][j] = corner * grid[py][px] + adjacent * grid[py][cx] + corner * grid[py][nx]
			//	+ adjacent * grid[cy][px] + center * grid[cy][cx] + adjacent * grid[cy][nx]
			//	+ corner * grid[ny][px] + adjacent * grid[ny][cx] + corner * grid[ny][nx];
		}
	}

	// left side
	for (int i = 1; i < height - 1; ++i)
		newGrid[i][0] = corner * grid[i - 1][width - 1] + adjacent * grid[i][width - 1] + corner * grid[i+1][width - 1]
			+ adjacent * grid[i - 1][0] + center * grid[i][0] + adjacent * grid[i + 1][0]
			+ corner * grid[i - 1][1] + adjacent * grid[i][1] + corner * grid[i + 1][1];
	
	// top side
	//float* topSide = newGrid[0].data();
	for (int i = 1; i < width - 1; ++i)
		//*++topSide 
      	newGrid[0][i] 
      		= corner * grid[height - 1][i - 1] + adjacent * grid[height - 1][i] + corner * grid[height - 1][i+1]
			+ adjacent * grid[0][i - 1] + center * grid[0][i] + adjacent * grid[0][i + 1]
			+ corner * grid[1][i - 1] + adjacent * grid[1][i] + corner * grid[1][i + 1];

	
	// right side
	for (int i = 1; i < height - 1; ++i)
		newGrid[i][width - 1] = corner * grid[i - 1][0] + adjacent * grid[i - 1][0] + corner * grid[i + 1][0]
			+ adjacent * grid[i - 1][width - 1] + center * grid[i][width - 1] + adjacent * grid[i + 1][width - 1]
			+ corner * grid[i - 1][width - 2] + adjacent * grid[i][width - 2] + corner * grid[i + 1][width - 2];

	
	// bottom side
	//float* bottomSide = newGrid[height - 1].data();
	for (int i = 1; i < width - 1; ++i)
      	//*++bottomSide = 
		newGrid[height - 1][i] =
			corner * grid[height - 2][i - 1] + adjacent * grid[height - 2][i] + corner * grid[height - 2][i + 1]
			+ adjacent * grid[height - 1][i - 1] + center * grid[height - 1][i] + adjacent * grid[height - 1][i + 1]
			+ corner * grid[0][i - 1] + adjacent * grid[0][i] + corner * grid[0][i + 1];

  
	// top left corner
	newGrid[0][0] = corner * grid[height - 1][width - 1] + adjacent * grid[0][width - 1] + corner * grid[1][width - 1]
		+ adjacent * grid[height - 1][0] + center * grid[0][0] + adjacent * grid[1][0]
		+ corner * grid[height - 1][1] + adjacent * grid[0][1] + corner * grid[1][1];

	// top right corner
	newGrid[0][width - 1] = corner * grid[height - 1][width - 2] + adjacent * grid[height - 1][width - 1] + corner * grid[height - 1][0]
		+ adjacent * grid[0][width - 2] + center * grid[0][width - 1] + adjacent * grid[0][0]
		+ corner * grid[1][width - 2] + adjacent * grid[1][width - 1] + corner * grid[1][0];

	// bottom right corner
	newGrid[height - 1][width - 1] = corner * grid[height - 2][width - 2] + adjacent * grid[height - 2][width - 1] + corner * grid[height - 2][0]
		+ adjacent * grid[height - 1][width - 2] + center * grid[height - 1][width - 1] + adjacent * grid[height - 1][0]
		+ corner * grid[0][width - 2] + adjacent * grid[0][width - 1] + corner * grid[0][0];

	// bottom left corner
	newGrid[height - 1][0] = corner * grid[height - 2][width - 1] + adjacent * grid[height - 2][0] + corner * grid[height - 2][1]
		+ adjacent * grid[height - 1][width - 1] + center * grid[height - 1][0] + adjacent * grid[height - 1][1]
		+ corner * grid[0][width - 1] + adjacent * grid[0][0] + corner * grid[0][1];
		
  
  	newGrid.swap(grid);
  
    /*
	for (int i = 0; i < height; ++i)
	{
      	//float *prow = grid[i].data(), pcol = prow;
      
		for (int j = 0; j < width; ++j)
		{
          
			int cy = i, cx = j, 
				//py = (i - 1 + height) % height, px = (j - 1 + width) % width, 
          		py = (i - 1) == -1 ? height-1 : i-1,
          		px = (j - 1) == -1 ? width-1 : j-1,
				//ny = (i + 1) % height, nx = (j + 1) % width;
          		ny = (i+1) == height ? 0 : i+1,
          		nx = (j+1) == width ? 0 : j+1;

			//newGrid[i][j] = kernel[0][0]*grid[py][px] + kernel[0][1]*grid[py][cx] + kernel[0][2]*grid[py][nx] 
			//			+	kernel[1][0]*grid[cy][px] + kernel[1][1]*grid[cy][cx] + kernel[1][2]*grid[cy][nx] 
			//			+	kernel[2][0]*grid[ny][px] + kernel[2][1]*grid[ny][cx] + kernel[2][2]*grid[ny][nx];
          	newGrid[i][j] = corner*grid[py][px] + adjacent*grid[py][cx] + corner*grid[py][nx] 
						+	 adjacent*grid[cy][px] + center*grid[cy][cx] + adjacent*grid[cy][nx] 
						+	 corner*grid[ny][px] + adjacent*grid[ny][cx] + corner*grid[ny][nx];
		}
	}
	*/
	
  
  	/*
  	const int height = grid.size();;
	const int width = grid[0].size();;
	const float center = 1.0 - blurring, corner = blurring / 12.0, adjacent = blurring / 6.0;
  
  	const static float window[3][3] = {{corner, adjacent, corner},
                                       {adjacent, center, adjacent},
                                       {corner, adjacent, corner}};
	
  	//vector < vector <float> > newGrid;
		
	//const static vector <int> DX = { -1, 0, 1}, DY = {-1, 0, 1};
  	const static int DX[] = {-1, 0, 1}, DY[] = {-1, 0, 1};
	
	
	// OPTIMIZATION: Use your improved zeros function
	vector<vector<float> > newGrid = zeros(height, width);

  	
	for (int i=0; i<height; ++i ) 
    {
		for (int j=0; j<width; ++j ) 
        {
			float val = grid[i][j];
			//newVal = val;
			//for (int ii=0; ii<3; ++ii) 
          	for (int dy: DY)
            {
				//int dy = DY[ii];
              	int new_i = (i + dy + height) % height;
              
				//for (int jj=0; jj<3; ++jj) 
              	for (int dx: DX)
                {
					//int dx = DX[jj];
					
					int new_j = (j + dx + width) % width;
					//multiplier = window[ii][jj];
					//newGrid[new_i][new_j] += val * window[ii][jj];
                  	newGrid[new_i][new_j] += val * window[1+dy][1+dx];
				}
			}
		}
	}
	*/
  
  	/*
  	future<void> handles[height];
  	//vector<future<void> > handles;
  
  	for (int i=0; i<height; ++i ) 
    {
      	handles[i] = std::async(std::launch::async, [=, &grid, &newGrid](int i)
      	//auto handle = std::async(std::launch::async, [=, &grid, &newGrid](int i)
        {
          //cout << "CALLED" << i << endl;
          //std::this_thread::sleep_for(chrono::seconds(5));
          
          for (int j=0; j<width; ++j ) 
          {
              float val = grid[i][j];
              //newVal = val;
              for (int ii=0; ii<3; ++ii) 
              {
                  int dy = DY[ii];
                  for (int jj=0; jj<3; ++jj) 
                  {
                      int dx = DX[jj];
                      int new_i = (i + dy + height) % height;
                      int new_j = (j + dx + width) % width;
                      //multiplier = window[ii][jj];
                      newGrid[new_i][new_j] += val * window[ii][jj];
                  }
              }
          }
          
          //cout << "FINISHED" << i << endl;
        }, i);
      
      	//handles.push_back(std::move(handle));
	}
  	*/
	//return newGrid;
}


/*
vector < vector <float> > blur(vector < vector < float> > grid, float blurring) {

	// OPTIMIZATION: window, DX and  DY variables have the 
    // same value each time the function is run.
  	// It's very inefficient to recalculate the vectors
    // every time the function runs. 
    // 
    // The const and/or static operator could be useful.
  	// Define and declare window, DX, and DY using the
    // bracket syntax: vector<int> foo = {1, 2, 3, 4} 
    // instead of calculating these vectors with for loops 
    // and push back
  	vector < vector <float> > window;
	vector < vector <float> > newGrid;
	vector <float> row;
	vector <float> newRow;

	int height;
	int width;
	float center, corner, adjacent;

	height = grid.size();
	width = grid[0].size();

	center = 1.0 - blurring;
	corner = blurring / 12.0;
	adjacent = blurring / 6.0;

	int i, j;
	float val;

	for (i=0; i<3; i++) {
		row.clear();
		for (j=0; j<3; j++) {
			switch (i) {
				case 0: 
				switch (j) {
					case 0: 
					val = corner;
					break;

					case 1: 
					val = adjacent;
					break;

					case 2: 
					val = corner;
					break;
				}
				break; 

				case 1:
				switch (j) {
					case 0: 
					val = adjacent;
					break;

					case 1: 
					val = center;
					break;
					
					case 2: 
					val = adjacent;
					break;
				}
				break;

				case 2:
				switch(j) {
					case 0: 
					val = corner;
					break;

					case 1: 
					val = adjacent;
					break;
					
					case 2: 
					val = corner;
					break;
				}
				break;
			}
			row.push_back(val);
		}
		window.push_back(row);
	}


	vector <int> DX;
	vector <int> DY;

	DX.push_back(-1); DX.push_back(0); DX.push_back(1);
	DY.push_back(-1); DY.push_back(0); DY.push_back(1);

	int dx;
	int dy;
	int ii;
	int jj;
	int new_i;
	int new_j;
	float multiplier;
	float newVal;

	// OPTIMIZATION: Use your improved zeros function
	for (i=0; i<height; i++) {
		newRow.clear();
		for (j=0; j<width; j++) {
			newRow.push_back(0.0);
		}
		newGrid.push_back(newRow);
	}

	for (i=0; i< height; i++ ) {
		for (j=0; j<width; j++ ) {
			val = grid[i][j];
			newVal = val;
			for (ii=0; ii<3; ii++) {
				dy = DY[ii];
				for (jj=0; jj<3; jj++) {
					dx = DX[jj];
					new_i = (i + dy + height) % height;
					new_j = (j + dx + width) % width;
					multiplier = window[ii][jj];
					newGrid[new_i][new_j] += newVal * multiplier;
				}
			}
		}
	}

	return newGrid;
}

*/