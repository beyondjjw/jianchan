#ifndef ___JIANCHAN__KLINE_H__
#define ___JIANCHAN__KLINE_H__

#include "common.h"
#include <vector>
using namespace std;


#define K_LINE_INCLUDED 1
#define K_LINE_NOT_INCLUDED 0
#define INVALID_INDEX -1

class KLine
{
protected:
	float m_high;
	float m_low;
	int   m_index;    // 原始数据中的Index
	int   m_included;  // 是否是包含关系
	int   m_direction;// 1：涨，-1：跌
	Classification   m_classification;
public:
	KLine(float low, float high, int index):m_high(high),m_low(low),m_index(index)
	{
		m_included = K_LINE_NOT_INCLUDED; //初始化为没有包含关系
		m_direction = DOWN;//初始化为下跌
		m_classification = RELAY_CLASS; //初始化就是中继，一开始无法确定是底分型还是顶分型
	}

	//因为包含关系，产生新的K线
	KLine(float low, float high, int include, int dir):m_high(high),m_low(low),m_included(include),m_direction(dir)
	{
		m_index = INVALID_INDEX; //包含关系生成新的高地点，不产生图形上的K线，图形上原K线的位置不动
		m_classification = RELAY_CLASS; //包含关系的K线肯定不是分型
	}

	~KLine(void){}

	void Up(){  m_direction = UP; }
	void Down() { m_direction = DOWN; }
	bool IsUp() { return m_direction == UP; }
	bool IsDown() { return m_direction == DOWN; }

	int Direction(){ return m_direction; }
	void Direction(int value){ m_direction = value; }
	void Included() { m_included = K_LINE_INCLUDED; }
	bool IsIncluded() { return m_included == K_LINE_INCLUDED; }

	float High() { return m_high; }
	void  High(float value) { m_high = value; }
	float Low() { return m_low; }
	float Low(float value) { m_low = value; }

	int   Index() { return m_index; }

	void BottomClassification() { m_classification = BOTTOM_CLASS; }
	void TopClassification() { m_classification = TOP_CLASS; }
	void Relay() { m_classification = RELAY_CLASS; }
	Classification GetClassification() { return m_classification; }

	// K 线复制，不复制K线的索引,因为不产生新的K线，仅仅是包含关系产生新的高低点
	KLine& operator=(const KLine& k)
	{
		m_high = k.m_high;
		m_low = k.m_low;
		m_included = k.m_included;  
		m_direction = k.m_direction; 

		return *this;
	}
 
	// 和前面的K线比较是否是上涨
	bool operator>(const KLine &front)
	{
		return m_high > front.m_high && m_low > front.m_low;
	}
	
	// 和前面的K线比较是否是下跌
	bool operator<(const KLine &front)
	{
		return m_high < front.m_high && m_low < front.m_low;
	}

	// 确定包含前面的K线
	bool IncludeFront(const KLine &front){
		return (m_high >= front.m_high && m_low <= front.m_low) ;
	}

	// 确定是否被前K线包含
	bool IsIncludedByFrontK(const KLine &front){
		return (m_high <= front.m_high && m_low >= front.m_low) ;
	}
};


vector<KLine> make_k(int count, float *low, float *high);
void HandleIncludeRelation(vector<KLine> &k);
void ensure_classification(vector<KLine> &k);


#endif