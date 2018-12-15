#ifndef __JIANCHAN_LOG__
#define __JIANCHAN_LOG__

#include <vector>
#include <string>
#include "KLine.h"
using namespace std;

void dll_log(int nCount, float *pOut, float *pIn, float *pHigh, float *pLow, const char* name);
void dll_log(vector<KLine*> &k, string name);
void dll_log(string msg);

#endif