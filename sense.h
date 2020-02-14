#ifndef SENSE_H
#define SENSE_H

#include <vector>
#include <iostream>

std::vector< std::vector <float> > sense(char color, const std::vector< std::vector <char> > &grid, 
                                         /*const*/ std::vector< std::vector <float> > &beliefs,  float p_hit, float p_miss);

#endif /* SENSE.H */