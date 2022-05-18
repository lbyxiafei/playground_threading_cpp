#include <bits/stdc++.h>
#include "sqlite3.h" 

using namespace std;

const int N=10000, M=100000, K=8, P=5;

struct Player{
    int score;
} players[N];

queue<int> q;
mutex qmu;

void match(){
    for(int i=0; i<M; i++){
        vector<int> arr;
        unique_lock<mutex> lk(qmu);
        while(arr.size()<P*2){
            if(q.size()){
                arr.push_back(q.front()); q.pop();
            }
        }
        lk.unlock();

        unordered_set<int> S;
        while(S.size()<P){
            int idx=rand()%(P*2);
            S.insert(idx);
        }

        lk.lock();
        for(int i=0; i<P*2; i++){
            if(S.count(i)){
                players[arr[i]].score+=10;

            }
            else{
                players[arr[i]].score-=10;
            }
            q.push(arr[i]);
        }
        lk.unlock();
    }
}

int main(int argc, char* argv[]) {
#ifdef _LBY
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    cout << "Host started...\n";
    for(int i=0; i<N; i++){
        q.push(i);
    }

    vector<thread> T;
    for(int i=0; i<K; i++){
        T.push_back(thread(match));
    }
    for(int i=0; i<K; i++){
        T[i].join();
    }

    int tot=0, maxx=-1e9, minx=1e9;
    map<int,int> freq;
    for(int i=0; i<N; i++){
        int t=players[i].score;
        freq[t]++;
        //cout << i << ':' << t << '\t';
        maxx=max(maxx, t), minx=min(minx, t);
    }
    for(auto it=freq.begin(); it!=freq.end(); it++){
        cout << it->first << ':' << it->second << '\n';
    }
    cout << endl;
    cout << "max:" << maxx << endl;
    cout << "min:" << minx << endl;
    cout << "gg" << endl;
    cout << tot << endl;

    return 0;
}