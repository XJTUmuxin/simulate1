#include<bits/stdc++.h>
using namespace std;
string corrected_path = "./../corrected/";
string map_result_path = "./../map_result/";
string mis_seq_path = "./../mis_seq/";
string sub_seq_path = "./../sub_seq/";
class map_result{
public:
    string qName;
    int qLength;
    int qStart;
    int qEnd;
    bool qStrand;
    string tName;
    int tLength;
    int tStart;
    int tEnd;
    bool tStrand;
    int score;
    int numMatch;
    int numMismatch;
    int numIns;
    int numDel;
    int mapQV;
    float matchPercentage;
    string qAlignedSeq;
    string matchPattern;
    string tAlignedSeq;
    map_result(const string &str){
        stringstream strstream(str);
        char temp;
        strstream>>qName>>qLength>>qStart>>qEnd;
        strstream>>temp;
        qStrand = temp=='+'?true:false;
        strstream>>tName>>tLength>>tStart>>tEnd;
        strstream>>temp;
        tStrand = temp=='+'?true:false;
        strstream>>score>>numMatch>>numMismatch>>numIns>>numDel>>mapQV
        >>qAlignedSeq>>matchPattern>>tAlignedSeq;
        matchPercentage = ((float)numMatch/(float)(qEnd-qStart));
        //cout<<qName<<qLength<<qStart<<qEnd<<qStrand<<tName<<tLength<<tStart<<tEnd<<tStrand<<score<<numMatch<<numMismatch<<numIns<<numDel<<mapQV<<qAlignedSeq<<matchPattern<<tAlignedSeq<<endl;
    }
};
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
    while(ifs){
        getline(ifs,line);
        map_result result(line);
        if(result.matchPercentage>=0.8 && result.numIns==result.numDel && (result.tStrand == result.qStrand)){
            //reads_num++;
            int index = 0;
            for(int i=result.tStart;i<result.tEnd;++i){
                while(result.qAlignedSeq[index]=='-')index++;
                if(index>=result.qAlignedSeq.size())break;
                base_count[i][base_map[result.qAlignedSeq[index]]].second++;
                index++;
            }           
        }
    }
    //cout<<reads_num<<endl;
    for(int i=0;i<seq_len;++i){
        sort(base_count[i].begin(),base_count[i].end(),[](const pair<char,int>p1,const pair<char,int>p2){return p1.second>p2.second;});
        if(base_count[i][0].second>0){
            seq[i] = base_count[i][0].first;
        }
    }
    ifs.close();
    ifs.clear();
    ofstream ofs(corrected_path+"corrected.fasta");
    ofs<<">corrected"<<endl;
    ofs<<seq<<endl;
    ofs.close();
    ofs.clear();
}