
#include "kline_factory.h"


vector<KLine> make_k(int count, float *low, float *high)
{
	vector<KLine> k;
	for(int i = 0; i < count; i++)
	{
		k.push_back(KLine(low[i], high[i], i));
	}
    return k;
}


