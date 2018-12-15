#include "stdafx.h"
#include "TCalcFuncSets.h"
#include "KLine.h"
#include <vector>
using namespace std;

//���ɵ�dll���������dll�뿽����ͨ���Ű�װĿ¼��T0002/dlls/����,���ڹ�ʽ���������а�

void GetKLineDirection(int count, float *out, float *in, float *high, float *low)
{
	vector<KLine> k ;
	k = make_k(count, low, high);
	HandleIncludeRelation(k);

    for (int i = 0; i < k.size(); i++)
    {
        out[i] = k[i].Direction();
    }
}
void TestPlugin2(int DataLen,float* pfOUT,float* pfINa,float* pfINb,float* pfINc)
{
	for(int i=0;i<DataLen;i++)
	{
		pfOUT[i]=pfINa[i]+pfINb[i]+pfINc[i];
		pfOUT[i]=pfOUT[i]/3;
	}
}


//���صĺ���
PluginTCalcFuncInfo g_CalcFuncSets[] = 
{
	{1,(pPluginFUNC)&GetKLineDirection},
	{2,(pPluginFUNC)&TestPlugin2},
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

