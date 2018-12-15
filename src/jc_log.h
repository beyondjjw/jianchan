#ifndef __JIANCHAN_LOG__
#define __JIANCHAN_LOG__

#include <vector>
using namespace std;

void dll_log(int count, float *out, float *in, float *high, float *low, const char* name);
void dll_log(vector<KLine> &k, string name);

#endif