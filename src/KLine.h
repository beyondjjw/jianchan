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
	int   m_index;    // ԭʼ�����е�Index
	int   m_included;  // �Ƿ��ǰ�����ϵ
	int   m_direction;// 1���ǣ�-1����
	Classification   m_classification;
public:
	KLine(float low, float high, int index):m_high(high),m_low(low),m_index(index)
	{
		m_included = K_LINE_NOT_INCLUDED; //��ʼ��Ϊû�а�����ϵ
		m_direction = DOWN;//��ʼ��Ϊ�µ�
		m_classification = RELAY_CLASS; //��ʼ�������м̣�һ��ʼ�޷�ȷ���ǵ׷��ͻ��Ƕ�����
	}

	//��Ϊ������ϵ�������µ�K��
	KLine(float low, float high, int include, int dir):m_high(high),m_low(low),m_included(include),m_direction(dir)
	{
		m_index = INVALID_INDEX; //������ϵ�����µĸߵص㣬������ͼ���ϵ�K�ߣ�ͼ����ԭK�ߵ�λ�ò���
		m_classification = RELAY_CLASS; //������ϵ��K�߿϶����Ƿ���
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

	// K �߸��ƣ�������K�ߵ�����,��Ϊ�������µ�K�ߣ������ǰ�����ϵ�����µĸߵ͵�
	KLine& operator=(const KLine& k)
	{
		m_high = k.m_high;
		m_low = k.m_low;
		m_included = k.m_included;  
		m_direction = k.m_direction; 

		return *this;
	}
 
	// ��ǰ���K�߱Ƚ��Ƿ�������
	bool operator>(const KLine &front)
	{
		return m_high > front.m_high && m_low > front.m_low;
	}
	
	// ��ǰ���K�߱Ƚ��Ƿ����µ�
	bool operator<(const KLine &front)
	{
		return m_high < front.m_high && m_low < front.m_low;
	}

	// ȷ������ǰ���K��
	bool IncludeFront(const KLine &front){
		return (m_high >= front.m_high && m_low <= front.m_low) ;
	}

	// ȷ���Ƿ�ǰK�߰���
	bool IsIncludedByFrontK(const KLine &front){
		return (m_high <= front.m_high && m_low >= front.m_low) ;
	}
};


vector<KLine> make_k(int count, float *low, float *high);
void HandleIncludeRelation(vector<KLine> &k);
void ensure_classification(vector<KLine> &k);


#endif