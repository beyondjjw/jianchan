#include "KLine.h"
#include "jc_log.h"
#include <vector>
#include <exception>
using namespace std;

KLine* makeNewKWhenExistIncludeRelation( KLine* front,  KLine* back)
{
	if(back->IncludeFront(front))
	{
		if(front->IsDown())
		{// 属于下跌过程的包含，两个K线合并产生新K线，但是原来的K线位置保留
			return new KLine(back->Low(), front->High(), K_LINE_INCLUDED, front->Direction());
		}
		else
		{// 剩下的是上涨包含关系
			return new KLine(front->Low(), back->High(), K_LINE_INCLUDED, front->Direction());
		}
	}
	else if(back->IsIncludedByFrontK(front))
	{
		if(front->IsDown())
		{// 属于下跌过程的包含，两个K线合并产生新K线，但是原来的K线位置保留
			return new KLine(front->Low(), back->High(), K_LINE_INCLUDED, front->Direction());
		}
		else
		{// 剩下的是上涨包含关系
			return new KLine(back->Low(), front->High(), K_LINE_INCLUDED, front->Direction());
		}
	}
    return NULL;
}

/*
包含关系处理之后，按照此逻辑处理K线，原K线还保留，这样保留的走势的时间信息
经过包含关系处理后，会生成K线组，K线组中的K线，确定其高低点，K线属于什么走势方向，是否是包含关系
这样处理完后的K线，可以交给笔生成器去生成笔。
*/
void HandleIncludeRelation(vector<KLine*> &k)
{
	if(k.size() < 2) return ;

	//先处理前两根K线，定初始方向
	if (k[1]->TurnUp(k[0]))
	{ 
		k[0]->Up();
		k[1]->Up();
	}
	else if (k[1]->TurnDown(k[0]))
	{ 
		k[0]->Down();
		k[1]->Down();
	}
	else 
	{//K线关系，要么涨，要么跌，要么是包含关系
		KLine *newk = makeNewKWhenExistIncludeRelation(k[0], k[1]);
		*(k[1]) = *newk;
		//*(k[0]) = *newk;
		delete newk;
	}

	for (size_t i = 2; i < k.size(); i++)
	{
		//上涨
		if (k[i]->TurnUp(k[i-1]))
		{
			k[i]->Up();
		}
		//下跌
		else if (k[i]->TurnDown(k[i-1]))
		{
			k[i]->Down();
		}
		else
		{      
			int cur = i;
			while (cur - 1 >= 0 )
			{
				KLine *incK = makeNewKWhenExistIncludeRelation(k[cur-1], k[cur]);
				if(incK && incK->IsIncluded())
				{
					*(k[cur]) = *incK;
					//*(k[cur-1]) = *incK;
					delete incK;
				}
					
				if (!k[cur]->IsIncluded())
				{
					break;
				}
				cur--;
			}
		}
	}
	
	
}

vector<KLine*> MakeK(int count, float *low, float *high)
{
	vector<KLine*> k;
	for(int i = 0; i < count; i++)
	{
		k.push_back(new KLine(low[i], high[i], i));
	}
    return k;
}

bool IsRealBottomClass(vector<KLine*> &k, int pos)
{
	bool result = true;

	if(k.size() - pos < 5)
	{//最后不足5根K线，如果前已经有5根K线下跌了，那这里可能就是底分，对走势生长可以作判断
		for(int i = 1; i < 5; i++)
		{// 如果可能底分型，那前面必须有4根下跌的K线
			result &= k[pos - i]->IsDown();
		}
		return result;
	}
	else{
		for(int i = 1; i < 5; i++)
		{//以及发生的K线图，后面有4根K线上涨，那这就底分了。
			result &= k[pos + i]->IsUp();
		}
		return result;
	}

	return false;
}

bool IsRealTopClass(vector<KLine*> &k, int pos)
{
	bool result = true;

	if(k.size() - pos < 5)
	{//最后不足5根K线，如果前已经有5根K线上涨了，那这里可能就是顶分，对走势生长可以作判断
		for(int i = 1; i < 5; i++)
		{// 如果可能顶分，那前面必须有4根上涨的K线
			result &= k[pos - i]->IsUp();
		}
		return result;
	}
	else{
		for(int i = 1; i < 5; i++)
		{//以及发生的K线图，后面有4根K线上涨，那这就顶分了。
			result &= k[pos + i]->IsDown();
		}
		return result;
	}
	return false;
}

void ensure_classification(vector<KLine*> &k)
{
	for(size_t i = 1; i < k.size() - 1; i++)
	{
		// if(k[i].IsIncluded()) continue;
		if(*(k[i-1]) > *(k[i]) && *(k[i]) < *(k[i+1]))
		{
			if(IsRealBottomClass(k, i)){
				k[i]->BottomClassification();
			}else{
				k[i]->Relay();
			}
			continue;
		}

		if(*(k[i-1]) < *(k[i]) && *(k[i]) > *(k[i+1]))
		{
			if(IsRealTopClass(k, i)){
				k[i]->TopClassification();
			}else{
				k[i]->Relay();
			}
			continue;
		}
	}
}

