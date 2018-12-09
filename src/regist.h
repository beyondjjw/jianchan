
#ifndef __JIANCHAN_REGIST_H__
#define __JIANCHAN_REGIST_H__


// 函数(数据个数,输出,输入a,输入b,输入c)
typedef void(*TdxPluginFunc)(int nCount, float *pOut, float *a, float *b, float *c);

typedef struct tagTdxPluginFuncInfo
{
    unsigned short   mark; // 函数编号
    TdxPluginFunc    callback; // 函数地址
} TdxPluginFuncInfo;


#endif