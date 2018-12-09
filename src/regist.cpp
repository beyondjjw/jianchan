// #include "regist.h"

// void Func1_BaoHan(int nCount, float *pOut, float *pIn, float *pHigh, float *pLow)
// {
//     float *pDirection = new float[nCount];
//     float *pOutHigh = new float[nCount];
//     float *pOutLow = new float[nCount];
//     float *pInclude = new float[nCount];

    

//     BaoHan(nCount, pDirection, pOutHigh, pOutLow, pInclude, pHigh, pLow);

//     for (int i = 0; i < nCount; i++)
//     {
//         pOut[i] = pInclude[i];
//     }

//     delete []pDirection;
//     delete []pOutHigh;
//     delete []pOutLow;
//     delete []pInclude;
// }

// static TdxPluginFuncInfo Info[] =
// {
//     { 1, &Func1_BaoHan},
//     { 0, NULL}
// };

// bool RegisterTdxFunc(TdxPluginFuncInfo **pInfo)
// {
//     if (*pInfo == NULL)
//     {
//         *pInfo = Info;

//         return TRUE;
//     }

//     return FALSE;
// }