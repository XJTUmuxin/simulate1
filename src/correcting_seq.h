#include<bits/stdc++.h>
using namespace std;
class correcting_seq{
public:
    string seq;
    int seq_len;
    vector<vector<pair<char,int>>> base_count;
    vector<int> deletion;
    vector<vector<vector<pair<char,int>>>> insertion;
    vector<int> map_num;
    correcting_seq()=default;
    correcting_seq(const string& str){
        seq = str;
        seq_len = seq.size();
        base_count = vector<vector<pair<char,int>>>(seq_len,vector<pair<char,int>>
        {make_pair('A',0),make_pair('C',0),make_pair('G',0),make_pair('T',0),make_pair('N',0)});
        deletion = vector<int>(seq_len,0);
        insertion = vector<vector<vector<pair<char,int>>>>(seq_len,vector<vector<pair<char,int>>>());
        map_num = vector<int>(seq_len,0);
    }
    correcting_seq(const correcting_seq& c_seq){
        seq = c_seq.seq;
        seq_len = c_seq.seq_len;
        base_count = c_seq.base_count;
        deletion = c_seq.deletion;
        insertion = c_seq.insertion;
        map_num = c_seq.map_num;     
    }
    correcting_seq& operator=(const correcting_seq& c_seq){
        seq = c_seq.seq;
        seq_len = c_seq.seq_len;
        base_count = c_seq.base_count;
        deletion = c_seq.deletion;
        insertion = c_seq.insertion;
        map_num = c_seq.map_num; 
        return *this;
    }
};