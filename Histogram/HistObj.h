#ifndef LAVA_STATISTICS_HISTOBJ_H
#define LAVA_STATISTICS_HISTOBJ_H

#include <list>
#include <ostream>
#include <vector>


namespace Statistics
{

class HistObj
{




public:
		// Number of bins
	int nBins;
	// Edges of bins (size: nBins+1)
	double* binEdges;
	// Histogram count for bins (size: nBins)
	int*	binCount;
	// Identifying name
	std::string name;
	HistObj()
	{

	}

	~HistObj()
	{
		
	}
};


};

#endif
