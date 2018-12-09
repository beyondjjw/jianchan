#include "KLine.h"
#include <vector>
using namespace std;

KLine makeNewKWhenExistIncludeRelation( KLine& front,  KLine& back)
{
	if(back.IncludeFront(front))
	{
		if(front.IsDown())
		{// 属于下跌过程的包含，两个K线合并产生新K线，但是原来的K线位置保留
			return KLine(back.Low(), front.High(), K_LINE_INCLUDED, front.Direction());
		}
		else
		{// 剩下的是上涨包含关系
			return KLine(front.Low(), back.High(), K_LINE_INCLUDED, front.Direction());
		}
	}
	else if(back.IsIncludedByFrontK(front))
	{
		if(front.IsDown())
		{// 属于下跌过程的包含，两个K线合并产生新K线，但是原来的K线位置保留
			return KLine(front.Low(), back.High(), K_LINE_INCLUDED, front.Direction());
		}
		else
		{// 剩下的是上涨包含关系
			return KLine(back.Low(), front.High(), K_LINE_INCLUDED, front.Direction());
		}
	}
    return back;
}

/*
包含关系处理之后，按照此逻辑处理K线，原K线还保留，这样保留的走势的时间信息
经过包含关系处理后，会生成K线组，K线组中的K线，确定其高低点，K线属于什么走势方向，是否是包含关系
这样处理完后的K线，可以交给笔生成器去生成笔。
*/
void HandleIncludeRelation(vector<KLine> &k)
{
	if(k.size() < 2) return ;

	//先处理前两根K线，定初始方向
    if (k[1] > k[0])
    { 
		k[0].Up();
		k[1].Up();
    }
    else if (k[1] < k[0])
    { 
        k[0].Down();
		k[1].Down();
    }
	else 
	{//K线关系，要么涨，要么跌，要么是包含关系
		KLine newk = makeNewKWhenExistIncludeRelation(k[0], k[1]);
		k[1] = newk;
		// k[0] = k[1];
	}

    for (size_t i = 2; i < k.size(); i++)
    {
        //上涨
        if (k[i] > k[i-1])
        {
			k[i].Up();
        }
        //下跌
        else if (k[i] < k[i-1])
        {
			k[i].Down();
        }
        else
        {      
			int cur = i;
			while (cur >=0 )
			{
				KLine newk = makeNewKWhenExistIncludeRelation(k[cur-1], k[cur]);
				k[cur] = newk;
				// k[i-1] = k[i];
				if (!k[cur].IsIncluded())
				{
					break;
				}
				cur--;
			}
        }
    }
}

vector<KLine> make_k(int count, float *low, float *high)
{
	vector<KLine> k;
	for(int i = 0; i < count; i++)
	{
		k.push_back(KLine(low[i], high[i], i));
	}
    return k;
}


