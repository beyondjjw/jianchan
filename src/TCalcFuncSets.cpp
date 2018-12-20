#include "stdafx.h"
#include "TCalcFuncSets.h"
#include "KLine.h"
#include "jc_log.h"
 
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include "KLine.h"
using namespace std;

void dll_log(int nCount, float *pOut, float *pIn, float *pHigh, float *pLow, const char* name)
{
	ofstream outFile; 
	outFile.open(".\\T0002\\dlls\\"+ string(name) + ".log");  

	outFile << "ncount�� " << nCount << endl;

	for(int i = 0; i < nCount; i++)
	{
		outFile << fixed; //С�����ʽ��ʾdouble 
		outFile.precision(2); 
		//���þ��� 
		outFile.setf(ios_base::showpoint); 
		//ǿ����ʾС�������� 
		outFile<<"{ "<< pLow[i] << "," << pHigh[i] << " }" <<endl; 
	}
	outFile.close(); 
}



//���ɵ�dll���������dll�뿽����ͨ���Ű�װĿ¼��T0002/dlls/����,���ڹ�ʽ���������а�
void GetKLineDirection(int count, float *out, float *in, float *high, float *low)
{
	dll_log(count, out, in, high, low, "GetKLineDirection");

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
	dll_log(count, out, in, high, low, "GetIncludedRelation");

	vector<KLine*> k = MakeK(count, low, high);
	HandleIncludeRelation(k);

	for (int i = 0; i < count; i++)
	{
		out[i] = (float)(k[i]->IsIncluded());
	}
}
void GetHighAfterIncluded(int count, float *out, float *in, float *high, float *low)
{
	dll_log(count, out, in, high, low, "GetHighAfterIncluded");

	vector<KLine*> k = MakeK(count, low, high);
	HandleIncludeRelation(k);

	for (int i = 0; i < count; i++)
	{
		out[i] = (float)(k[i]->HighAfterHandleInclude());
	}
}
void GetLowAfterIncluded(int count, float *out, float *in, float *high, float *low)
{
	dll_log(count, out, in, high, low, "GetLowAfterIncluded");

	vector<KLine*> k = MakeK(count, low, high);
	HandleIncludeRelation(k);

	for (int i = 0; i < count; i++)
	{
		out[i] = (float)(k[i]->LowAfterHandleInclude());
	}
}


//���صĺ���
PluginTCalcFuncInfo g_CalcFuncSets[] = 
{
	{1,(pPluginFUNC)&GetKLineDirection},
	{2,(pPluginFUNC)&GetIncludedRelation},
	{3,(pPluginFUNC)&GetHighAfterIncluded},
	{4,(pPluginFUNC)&GetLowAfterIncluded},
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

