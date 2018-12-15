
#include <iostream>
#include <fstream>
#include <string>
#include "KLine.h"
#include "string.h"

using namespace std;

vector<string> split(const string& str, const string& delim) {
	vector<string> res;
	if("" == str) return res;
	//先将要切割的字符串从string类型转换为char*类型
	char * strs = new char[str.length() + 1] ; //不要忘了
	strcpy(strs, str.c_str()); 
 
	char * d = new char[delim.length() + 1];
	strcpy(d, delim.c_str());
 
	char *p = strtok(strs, d);
	while(p) {
		string s = p; //分割得到的字符串转换为string类型
		res.push_back(s); //存入结果数组
		p = strtok(NULL, d);
	}
 
	return res;
}


int main(int argc, char** argv)
{
    fstream f("../data/data.txt");
    vector<string> words; 
    vector<float> highs;
    vector<float> lows;

    string line; 
    while(getline(f,line))
    { 
        vector<string> parts = split(line, ",");
        lows.push_back(atof(parts[0].c_str())); 
        highs.push_back(atof(parts[1].c_str())); 
    } 
    f.close();
   
    

    vector<KLine> klines = MakeK(highs.size(), &lows[0], &highs[0]);
    HandleIncludeRelation(klines);
    ensure_classification(klines);


    ofstream of("../data/output.txt");
    for(int i = 0; i  < klines.size(); i++)
    {
        of << fixed;
        of.precision(2);
        of.setf(ios::showpoint);

        of << klines[i].Low() << "," << klines[i].High() ;
        if(klines[i].GetClassification() == TOP_CLASS) {
            of << "顶分" << endl;
        }else if(klines[i].GetClassification() == BOTTOM_CLASS){
            of << "底分" << endl;
        }else{
            of << endl;
        }
    }
    of.close();


    return 0;
}