#include "regist.h"
#include "KLine.h"
#include <vector>
using namespace std;

void func1(int count, float *out, float *in, float *high, float *low)
{
	vector<KLine> k ;
	k = MakeK(count, low, high);
	HandleIncludeRelation(k);

    for (int i = 0; i < k.size(); i++)
    {
        out[i] = k[i].Direction();
    }
}

static TdxPluginFuncInfo Info[] =
{
    { 1, &func1},
    { 0, NULL}
};

bool RegisterTdxFunc(TdxPluginFuncInfo **pInfo)
{
    if (*pInfo == NULL)
    {
        *pInfo = Info;

        return true;
    }

    return false;
}