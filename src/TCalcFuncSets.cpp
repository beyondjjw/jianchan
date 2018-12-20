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

	outFile << "ncount： " << nCount << endl;

	for(int i = 0; i < nCount; i++)
	{
		outFile << fixed; //小数点格式显示double 
		outFile.precision(2); 
		//设置精度 
		outFile.setf(ios_base::showpoint); 
		//强制显示小数点后的零 
		outFile<<"{ "<< pLow[i] << "," << pHigh[i] << " }" <<endl; 
	}
	outFile.close(); 
}



//生成的dll及相关依赖dll请拷贝到通达信安装目录的T0002/dlls/下面,再在公式管理器进行绑定
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


//加载的函数
PluginTCalcFuncInfo g_CalcFuncSets[] = 
{
	{1,(pPluginFUNC)&GetKLineDirection},
	{2,(pPluginFUNC)&GetIncludedRelation},
	{3,(pPluginFUNC)&GetHighAfterIncluded},
	{4,(pPluginFUNC)&GetLowAfterIncluded},
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

