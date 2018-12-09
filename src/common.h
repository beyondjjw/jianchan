#ifndef __COMMON_H__
#define __COMMON_H__

#define UP 1   //上涨
#define DOWN -1   //下跌

enum Classification{
	RELAY_CLASS= 1, // 中继
	BOTTOM_CLASS, //底分型
	TOP_CLASS    //顶分型
};


enum BuySellType
{
	BUY_1,
	BUY_2,
	BUY_3,
	SELL_1,
	SELL_2,
	SELL_3
};
 
#endif
