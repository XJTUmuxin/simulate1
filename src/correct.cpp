#include<bits/stdc++.h>
#include"correcting_seq.h"
#include"map_result.h"
using namespace std;
string corrected_path = "./../corrected/";
string map_result_path = "./../map_result/";
string mis_seq_path = "./../mis_seq/";
string sub_seq_path = "./../sub_seq/";

int main(){
    string seq;
    ifstream ifs(mis_seq_path+"mis_seq.fasta");
    getline(ifs,seq);
    getline(ifs,seq);
    ifs.close();
    ifs.clear();
    int seq_len = seq.size();
    unordered_map<char,int> base_map{{'A',0},{'C',1},{'G',2},{'T',3},{'N',4}};
    vector<vector<pair<char,int>>> base_count(seq_len,
    vector<pair<char,int>>{make_pair('A',0),make_pair('C',0),make_pair('G',0),make_pair('T',0),make_pair('N',0)});
    
    ifs.open(map_result_path+"map_result.out");
    string line;
    getline(ifs,line);
    //int reads_num = 0;
    correcting_seq cor_seq(seq);
    while(ifs){
        getline(ifs,line);
        map_result result(line);
        if(result.matchPercentage>=0.8 && (result.tStrand == result.qStrand)){
            //reads_num++;
            int q_index = 0;
            int t_index = 0;
            int t_real_index = result.tStart;
            while(q_index<result.qAlignedSeq.size() && t_index<result.tAlignedSeq.size()){
                if(result.qAlignedSeq[q_index]=='-'){
                    cor_seq.deletion[t_real_index]++;
                    cor_seq.map_num[t_real_index]++;
                    q_index++;
                    t_index++;
                    t_real_index++;
                }
                else if(result.tAlignedSeq[t_index]=='-'){
                    int i=0;
                    while(t_index<result.tAlignedSeq.size() && result.tAlignedSeq[t_index]=='-'){
                        if(i>=cor_seq.insertion[t_real_index-1].size()){
                            cor_seq.insertion[t_real_index-1].push_back(
                            vector<pair<char,int>>{make_pair('A',0),make_pair('C',0),make_pair('G',0),make_pair('T',0),make_pair('N',0)});    
                        }
                        cor_seq.insertion[t_real_index-1][i][base_map[result.qAlignedSeq[q_index]]].second++;
                        q_index++;
                        t_index++;
                        i++;
                    }
                }
                else{
                    cor_seq.base_count[t_real_index][base_map[result.qAlignedSeq[q_index]]].second++;
                    cor_seq.map_num[t_real_index]++;
                    q_index++;
                    t_index++;
                    t_real_index++;
                }
            }          
        }
    }
    //cout<<reads_num<<endl;
    string corrected_seq;
    for(int i=0;i<cor_seq.seq_len;++i){
        if(cor_seq.deletion[i]>cor_seq.map_num[i]/2){   //delete

        }
        else{
            sort(cor_seq.base_count[i].begin(),cor_seq.base_count[i].end(),
            [](const pair<char,int>&p1,const pair<char,int>&p2){return p1.second>p2.second;});
            if(cor_seq.base_count[i][0].second>0){
                corrected_seq += cor_seq.base_count[i][0].first;
            }
        }
        //insertion
        for(auto &v:cor_seq.insertion[i]){
            sort(v.begin(),v.end(),[](const pair<char,int>&p1,const pair<char,int>&p2){return p1.second>p2.second;});
            int num=0;
            for(auto &p:v){
                num += p.second;
            }
            if(num>=cor_seq.map_num[i]/2){
                corrected_seq+=v[0].first;
            }
            else{
                break;
            }
        }
    }
    ifs.close();
    ifs.clear();
    ofstream ofs(corrected_path+"corrected.fasta");
    ofs<<">corrected"<<endl;
    ofs<<corrected_seq<<endl;
    ofs.close();
    ofs.clear();
}