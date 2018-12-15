
#include <fstream>
#include <iostream>
#include <string>
#include "KLine.h"
using namespace std;




void dll_log(int count, float *out, float *in, float *high, float *low, const char* name)
{
    ofstream outFile; 
    outFile.open(".\\T0002\\dlls\\"+ string(name) + ".log");  

    outFile << "count�� " << count << endl;

    for(int i = 0; i < count; i++)
    {
        outFile << fixed; //С�����ʽ��ʾdouble 
        outFile.precision(2); 
        //���þ��� 
        outFile.setf(ios_base::showpoint); 
        //ǿ����ʾС�������� 
        outFile<<"{ "<< low[i] << "," << high[i] << " }" <<endl; 
    }
    outFile.close(); 
}


void dll_log(vector<KLine> &k, string name)
{
    ofstream outFile; 
    outFile.open(".\\T0002\\dlls\\"+ name + ".log");  

    outFile << "count�� " << k.size() << endl;

    for(int i = 0; i < k.size() ; i++)
    {
        outFile << fixed; //С�����ʽ��ʾdouble 
        outFile.precision(2); 
        //���þ��� 
        outFile.setf(ios_base::showpoint); 
        //ǿ����ʾС�������� 
		float low = k[i].Low();
		float high = k[i].High();
		outFile<<"{ "<< low << "," << high << " } " << k[i].IsIncluded() <<endl; 
    }
    outFile.close(); 
}
