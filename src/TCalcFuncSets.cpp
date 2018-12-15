#include "stdafx.h"
#include "TCalcFuncSets.h"
#include "KLine.h"
#include <vector>
using namespace std;

//���ɵ�dll���������dll�뿽����ͨ���Ű�װĿ¼��T0002/dlls/����,���ڹ�ʽ���������а�

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


//���صĺ���
PluginTCalcFuncInfo g_CalcFuncSets[] = 
{
	{1,(pPluginFUNC)&GetKLineDirection},
	{2,(pPluginFUNC)&GetIncludedRelation},
	{0,NULL},
};

//������TCalc��ע�ắ��
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

