#pragma once

#include <vector>
using namespace std;
#include "common.h"

#define K_LINE_INCLUDED 1
#define K_LINE_NOT_INCLUDED 0

class KLine
{
public:
	float m_high;
	float m_low;
	int   m_index;    // ԭʼ�����е�Index
	float m_included;  // �Ƿ��ǰ�����ϵ
	int   m_direction;// 1���ǣ�-1����
	FenXing   m_fenxing;
public:
	KLine(float low, float high, int index):m_high(high),m_low(low),m_index(index)
	{
		m_included = 0; //��ʼ��Ϊû�а�����ϵ
		m_direction = DOWN;//��ʼ��Ϊ�µ�
		m_index = -1;
		m_fenxing = ZHONGJI;
	}

	//��Ϊ������ϵ�������µ�K��
	KLine(float low, float high, int include, int dir):m_high(high),m_low(low),m_included(include),m_direction(dir)
	{
		m_index = -1; //ֱ���ǰ�����ϵ
		m_fenxing = ZHONGJI;
	}

	~KLine(void){}

	void Up(){  m_direction = UP; }
	void Down() { m_direction = DOWN; }
	int Direction(){ return m_direction; }
	void Direction(int value){ m_direction = value; }
	void Included() { m_included = 1; }
	bool IsIncluded() { return m_included == 1; }
	bool IsUp() { return m_direction == UP; }
	bool IsDown() { return m_direction == DOWN; }

	float High() { return m_high; }
	void  High(float value) { m_high = value; }
	float Low() { return m_low; }
	float Low(float value) { m_low = value; }
	int   Index() { return m_index; }

	void DiFenXing() { m_fenxing = FX_DI; }
	void DingFenXing() { m_fenxing = FX_DING; }
	FenXing fenxing() { return m_fenxing; }

	// K �߸��ƣ�������K�ߵ�����
	KLine& operator=(const KLine& k)
	{
		m_high = k.m_high;
		m_low = k.m_low;
		m_included = k.m_included;  
		m_direction = k.m_direction; 
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
