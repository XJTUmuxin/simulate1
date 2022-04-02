#include<bits/stdc++.h>
using namespace std;
class microsatellite{
public:
    string motif;
    int left_index;
    int right_index;
    int repeate_num;
    microsatellite(string m,int l_index,int r_index,int re_num):motif(m),left_index(l_index),right_index(r_index),repeate_num(re_num){

    }
};
int max_motif_len = 6;
int min_repeat_num = 5;
void mic_count(string &seq){
    map<int,int> micro_area;     //key = left_index,value = right_index;
    vector<microsatellite> micros;
    for(int len=2;len<=max_motif_len;++len){
        string motif = seq.substr(0,len);
        int repeate_num = 1;
        int left_index = 0;
        int index = len;
        while(index+len<=seq.size()){
            string curr_str = seq.substr(index,len);
            if(curr_str == motif){
                repeate_num++;
            }
            else{
                if(repeate_num+1>=min_repeat_num){
                    for(int i=len-1;i>=1;--i){
                        if(left_index-i<0 || index-1+len-i>=seq.size())continue;
                        if(seq.substr(index,len-i)+seq.substr(left_index-i,i) == motif){
                            motif = seq.substr(left_index-i,i)+seq.substr(index,len-i);
                            left_index = left_index-i;
                            index = index+len-i;
                            repeate_num++;
                            break;
                        }
                    }
                    if(repeate_num>=min_repeat_num){
                        micro_area[left_index] = index-1;
                        micros.emplace_back(motif,left_index,index-1,repeate_num);
                    }
                }
                auto iter = micro_area.upper_bound(index);
                if(iter!=micro_area.begin()){
                    iter--;
                    if(iter->second>=index){
                        index = iter->second+1;
                    }
                }
                motif = seq.substr(index,len);
                left_index = index;
                repeate_num = 1;
            }
            index += len;
        }
        if(repeate_num+1>=min_repeat_num){
            for(int i=len-1;i>=1;--i){
                if(left_index-i<0 || index-1+len-i>=seq.size())continue;
                if(seq.substr(index,len-i)+seq.substr(left_index-i,i) == motif){
                    motif = seq.substr(left_index-i,i)+seq.substr(index,len-i);
                    left_index = left_index-i;
                    index = index+len-i;
                    repeate_num++;
                    break;
                }
            }
            if(repeate_num>=min_repeat_num){
                    micro_area[left_index] = index-1;
                    micros.emplace_back(motif,left_index,index-1,repeate_num);
            }
        }
    }
    ofstream ofs("result.out");
    for(auto &micro:micros){
        ofs<<micro.motif<<endl<<"left_index: "<<micro.left_index<<endl<<"right_index: "<<micro.right_index<<endl<<"repeate_num: "<<micro.repeate_num<<endl;
    }
    ofs.close();
    ofs.clear();
}
int main(){
    string seq;
    ifstream ifs("init_seq.out");
    ifs>>seq;
    ifs.close();
    ifs.clear();
    mic_count(seq);
}