
#include <fstream>
#include <iostream>
#include <string>
#include "KLine.h"
using namespace std;


//
//
//
//void dll_log(int nCount, float *pOut, float *pIn, float *pHigh, float *pLow, const char* name)
//{
//    ofstream outFile; 
//    outFile.open("c://"+ string(name) + ".log");  
//
//    outFile << "ncount： " << nCount << endl;
//
//    for(int i = 0; i < nCount; i++)
//    {
//        outFile << fixed; //小数点格式显示double 
//        outFile.precision(2); 
//        //设置精度 
//        outFile.setf(ios_base::showpoint); 
//        //强制显示小数点后的零 
//        outFile<<"{ "<< pLow[i] << "," << pHigh[i] << " }" <<endl; 
//    }
//    outFile.close(); 
//
//    ofstream o;
//    o.open("c:\\"+ string("test.log"));
//    o << "ncount： " << nCount << endl;
//    o.close();
//
//
//}
//
//void dll_log(vector<KLine*> &k, string name)
//{
//    ofstream outFile; 
//    outFile.open(string(".\\T0002\\dlls\\") + name + ".log", ios::app);  
//
//    outFile << "count： " << k.size() << endl;
//
//    for(int i = 0; i < k.size() ; i++)
//    {
//		outFile << k[i]->IsIncluded() << endl; 
//    }
//    outFile.close(); 
//}
//
//
//void dll_log(string msg)
//{
//	ofstream outFile; 
//    outFile.open(string(".\\T0002\\dlls\\")  + string("error.log"), ios::app);  
//
//	outFile << msg << endl;
//  
//    outFile.close(); 
//}