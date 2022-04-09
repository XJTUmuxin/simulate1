#include<bits/stdc++.h>
#include"map_result.h"
using namespace std;
string compare_path = "./../compare/";
int main(){
    string line;
    ifstream ifs(compare_path+"corrected_compare.out");
    getline(ifs,line);
    getline(ifs,line);
    map_result result1(line);
    cout<<"corrected seq's accuracy:"<<endl;
    cout<<(float)result1.numMatch/(float)result1.tLength<<endl;
    ifs.close();
    ifs.clear();
    ifs.open(compare_path+"mis_compare.out");
    getline(ifs,line);
    getline(ifs,line);
    map_result result2(line);
    cout<<"mis seq's accuracy:"<<endl;
    cout<<(float)result2.numMatch/(float)result2.tLength<<endl;
    ifs.close();
    ifs.clear();
    return 0;
}