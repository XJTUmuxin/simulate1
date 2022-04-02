#include<bits/stdc++.h>
using namespace std;
int expect_len = 10000;
int min_mic_len = 1000; 
int substrings_len = 100;
int substrings_num = 20;
int max_repeat_num = 60;
int mic_num = 5;
int error_rate = 15;
char bases[5] = {'A','C','G','T','N'};
vector<string> motifs = {"AC","TCAT","AGAG","ATCATC","TATATA"};

void create_init_seq(string& init_seq){
    vector<int> m_indexs(mic_num);
    for(int i=0;i<mic_num;++i){
        int temp = rand()%expect_len;
        m_indexs[i] = temp;
    }
    sort(m_indexs.begin(),m_indexs.end());
    m_indexs.push_back(INT_MAX);
    int m_num = 0;
    int m_index = m_indexs[m_num];
    
    while(init_seq.size()<expect_len || mic_num>0){
        if(init_seq.size()>m_index){
            string motif = motifs[m_num];
            int repeat_num;
            if(mic_num == 1 && min_mic_len>0){
                repeat_num = min_mic_len/motif.size()+1;
            }
            else{
                repeat_num = 2+rand()%(max_repeat_num-2);
            }
            cout<<"index: "<<init_seq.size()<<endl<<"motif: "<<motif<<endl<<"repeat_num: "<<repeat_num<<endl;
            for(int i=0;i<repeat_num;++i){
                init_seq += motif;
            }
            mic_num--;
            min_mic_len -= (motif.size()*repeat_num);
            m_index = m_indexs[++m_num];
        }
        int temp = rand()%4;
        init_seq += bases[temp];
    }
} 

void create_mis_seq(string& init_seq,string& mis_seq){
    int real_len = init_seq.size();
    for(int i=0;i<real_len;++i){
        int temp = rand()%100;
        if(temp<error_rate){
            char base;
            while(true){
                base = bases[rand()%5];
                if(base != init_seq[i])break;
            }
            mis_seq += base;
        }
        else{
            mis_seq += init_seq[i];
        }
    }
}

void get_substrings(string& init_seq,vector<string>& substrings){
    for(int i=0;i<substrings_num;++i){
        int start_index;
        while(true){
            start_index = rand()%init_seq.size();
            if(start_index+substrings_len<=init_seq.size())break;
        }
        substrings.emplace_back(init_seq,start_index,substrings_len);
    }
}

int main(){
    
    srand(static_cast<unsigned>(time(0)));
    string init_seq = "";
    string mis_seq = "";
    vector<string> substrings;
    create_init_seq(init_seq);
    create_mis_seq(init_seq,mis_seq);
    get_substrings(init_seq,substrings);
    cout<<"seq size: "<<init_seq.size()<<endl;
    ofstream ofs("init_seq.out");
    ofs<<init_seq;
    ofs.close();
    ofs.clear();
    ofs.open("mis_seq.out");
    ofs<<mis_seq;
    ofs.close();
    ofs.clear();
    ofs.open("sub_seq.out");
    for(auto &str:substrings){
        ofs<<str<<endl;
    }
    ofs.close();
    ofs.clear();
}
