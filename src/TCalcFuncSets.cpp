#include "stdafx.h"
#include "TCalcFuncSets.h"
#include "KLine.h"
#include <vector>
using namespace std;

//生成的dll及相关依赖dll请拷贝到通达信安装目录的T0002/dlls/下面,再在公式管理器进行绑定

void GetKLineDirection(int count, float *out, float *in, float *high, float *low)
{
	vector<KLine> *k = MakeK(count, low, high);
	HandleIncludeRelation(*k);

    for (size_t i = 0; i < k->size(); i++)
    {
        out[i] = (float)(*k)[i].Direction();
    }
	delete k;
}
void GetIncludedRelation(int count, float *out, float *in, float *high, float *low)
{
	vector<KLine> *k = MakeK(count, low, high);
	HandleIncludeRelation(*k);

    for (size_t i = 0; i < k->size(); i++)
    {
		out[i] = (float)(*k)[i].IsIncluded();
    }
	delete k;
}


//加载的函数
PluginTCalcFuncInfo g_CalcFuncSets[] = 
{
	{1,(pPluginFUNC)&GetKLineDirection},
	{2,(pPluginFUNC)&GetIncludedRelation},
	{0,NULL},
};

//导出给TCalc的注册函数
BOOL RegisterTdxFunc(PluginTCalcFuncInfo** pFun)
{
	if(*pFun==NULL)
	{
		(*pFun)=g_CalcFuncSets;
		return TRUE;
	}
	return FALSE;
}



BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    return TRUE;
}

