#include<bits/stdc++.h>
using namespace std;
string init_seq_path = "./../init_seq/";
string mis_seq_path = "./../mis_seq/";
string corrected_path = "./../corrected/";
float similar(const string &s1,const string &s2){
    int len1 = s1.size();
    int len2 = s2.size();
    if(len1!=len2)return -1;
    int similar_num = 0;
    for(int i=0;i<len1;++i){
        if(s1[i]==s2[i])similar_num++;
    }
    return (float)similar_num/(float)len1;
}
int main(){
    string init_seq;
    string mis_seq;
    string corrected_seq;
    ifstream ifs(init_seq_path+"init_seq.fasta");
    getline(ifs,init_seq);
    getline(ifs,init_seq);
    ifs.close();
    ifs.clear();
    ifs.open(mis_seq_path+"mis_seq.fasta");
    getline(ifs,mis_seq);
    getline(ifs,mis_seq);
    ifs.close();
    ifs.clear();
    ifs.open(corrected_path+"corrected.fasta");
    getline(ifs,corrected_seq);
    getline(ifs,corrected_seq);
    ifs.close();
    ifs.clear();
    cout<<"mis_seq's similar: "<<similar(init_seq,mis_seq)<<endl;
    cout<<"corrected_seq's similar: "<<similar(init_seq,corrected_seq)<<endl;
}