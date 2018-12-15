#ifndef ___JIANCHAN__KLINE_H__
#define ___JIANCHAN__KLINE_H__

#include "common.h"
#include <vector>
using namespace std;


const int K_LINE_INCLUDED = 1;
const int K_LINE_NOT_INCLUDED = 0;
const int INVALID_INDEX = -1;

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
	KLine():m_high(0), m_low(0), m_index(0)
	{
		m_included = K_LINE_NOT_INCLUDED; //初始化为没有包含关系
		m_direction = DOWN;//初始化为下跌
		m_classification = RELAY_CLASS; //初始化就是中继，一开始无法确定是底分型还是顶分型
	}

	KLine(float low, float high, int index):m_high(high),m_low(low),m_index(index)
	{
		m_included = K_LINE_NOT_INCLUDED; //初始化为没有包含关系
		m_direction = DOWN;//初始化为下跌
		m_classification = RELAY_CLASS; //初始化就是中继，一开始无法确定是底分型还是顶分型
	}

	//因为包含关系，产生新的K线
	KLine(float low, float high, int include, int dir):m_high(high),m_low(low),m_included(include),m_direction(dir)
	{
		m_index = INVALID_INDEX;
		m_classification = RELAY_CLASS; //包含关系的K线肯定不是分型
	}

	~KLine(void){}

	void Up(){  m_direction = UP; }
	void Down() { m_direction = DOWN; }
	bool IsUp() { return m_direction == UP; }
	bool IsDown() { return m_direction == DOWN; }

	int Direction(){ return m_direction; }
	void Direction(int value){ m_direction = value; }
	void SetIncluded(int value = K_LINE_INCLUDED) { m_included = K_LINE_INCLUDED; }
	int IsIncluded() { return m_included; }

	float High() { return m_high; }
	void  High(float value) { m_high = value; }
	float Low() { return m_low; }
	void Low(float value) { m_low = value; }

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
		m_index = m_index;
		m_classification = k.m_classification;

		return *this;
	}
 
	// 和前面的K线比较是否是上涨
	bool operator>(const KLine &front)
	{
		return m_high > front.m_high && m_low > front.m_low;
	}

	bool TurnUp(const KLine *front) {
		return *this > *front;
	}
	
	// 和前面的K线比较是否是下跌
	bool operator<(const KLine &front)
	{
		return m_high < front.m_high && m_low < front.m_low;
	}

	bool TurnDown(const KLine *front) {
		return *this < *front;
	}

	// 确定包含前面的K线
	bool IncludeFront(const KLine *front){
		return (m_high >= front->m_high && m_low <= front->m_low) ;
	}

	// 确定是否被前K线包含
	bool IsIncludedByFrontK(const KLine *front){
		return (m_high <= front->m_high && m_low >= front->m_low) ;
	}
};


vector<KLine*> MakeK(int count, float *low, float *high);
void HandleIncludeRelation(vector<KLine*> &k);
void ensure_classification(vector<KLine*> &k);


#endif