#include "stdafx.h"
#include "TCalcFuncSets.h"
#include "KLine.h"
#include "jc_log.h"
 
#include <vector>
using namespace std;


//���ɵ�dll���������dll�뿽����ͨ���Ű�װĿ¼��T0002/dlls/����,���ڹ�ʽ���������а�

void GetKLineDirection(int count, float *out, float *in, float *high, float *low)
{
	dll_log(count, out, in, high, low, "direction");

	vector<KLine*> k = MakeK(count, low, high);
	HandleIncludeRelation(k);
	

    for (size_t i = 0; i < k.size(); i++)
    {
        out[i] = (float)k[i]->Direction();
		delete k[i];
    }
	
}
void GetIncludedRelation(int count, float *out, float *in, float *high, float *low)
{
	
	dll_log(count, out, in, high, low, "include_data");

	vector<KLine*> k = MakeK(count, low, high);
	HandleIncludeRelation(k);

	// dll_log(k, "include");

    for (size_t i = 0; i < k.size(); i++)
    {
		out[i] = (k[i]->IsIncluded()) ? 1.00 : 0.00;
		delete k[i];
    }
}


//���صĺ���
PluginTCalcFuncInfo g_CalcFuncSets[] = 
{
	//{1,(pPluginFUNC)&GetKLineDirection},
	{1,(pPluginFUNC)&GetIncludedRelation},
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

