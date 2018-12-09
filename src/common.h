#ifndef __COMMON_H__
#define __COMMON_H__

#define UP 1   //上涨
#define DOWN -1   //下跌
#define FENXING 0 //分型
#define DIR_CONTINUE 1 //方向延续

enum FenXing{
	ZHONGJI = 1,
	FX_DI = 2, //底分型
	FX_DING    //顶分型
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
