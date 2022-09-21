#include<bits/stdc++.h>
using namespace std;


long long binpow(long long a,long long b, long long md){
    long long ans = 1;
    while(b){
        if(b&1){
            ans = (ans*a)%md;
        }
        a = (a*a)%md;
        b/=2;
    }
    return ans;
}

long long hash_string(string s,int md){
    long long ans = 0;
    for(int i = 0;i<s.size();i++){
        ans+=((binpow(s[i],i,md))%md);
    }
    return ans;
}

int N = 100003 ;

template <class t>
void printvector(vector <t>& v){
    int n = v.size();
    for(int i = 0;i<n;i++){
        cout<<v[i]<<" ";
    }
    cout<<"\n";
}

string dec_to_bin(int n, int k){
    string s = "";
    for(int i = 0;i<k;i++){
        if(n&(1<<i)){
            s+="1";
        }
        else{
            s+="0";
        }
    }
    reverse(s.begin(),s.end());
    return s;
}

void split_ex_hash(map <string,vector <int>> &mp, map<string,vector <int>>::iterator ptr){
    pair<string,vector<int>> p = *ptr;
    string str = p.first;
    vector <int> v = p.second;
    int len = str.size();
    for(auto num:v){
        mp[dec_to_bin(num,len+1)].push_back(num);
    }
    mp.erase(ptr);

}

void insert_ex_hash(map <string,vector <int>> &mp,int num, int bucket_size){
    
    string temp = "";
    for(int i = 0;i<31;i++){
        if(num&(1<<i)){
            temp = "1"+temp;
        }
        else{
            temp = "0"+temp;
        }
        if(mp.find(temp)!=mp.end()){
            mp[temp].push_back(num);
            if(mp[temp].size()>bucket_size){
                split_ex_hash(mp,mp.find(temp));
            }
            break;
        }
    }
}

map <string,vector <int>> ex_hasher(int bucket_size, vector <int> nums){
    map<string,vector <int>> mp;
    mp["0"]={};
    mp["1"]={};
    int len = 1;
    for(auto x:nums){
        insert_ex_hash(mp,x,bucket_size);
    }
    return mp;
}



void split_ex_hash2(map <string,set <int>> &mp, map<string,set <int>>::iterator ptr){
    pair<string,set<int>> p = *ptr;
    string str = p.first;
    set <int> v = p.second;
    int len = str.size();
    for(auto num:v){
        mp[dec_to_bin(num,len+1)].insert(num);
    }
    mp.erase(ptr);

}

void insert_ex_hash2(map <string,set <int>> &mp,int num, int bucket_size){
    
    string temp = "";
    for(int i = 0;i<31;i++){
        if(num&(1<<i)){
            temp = "1"+temp;
        }
        else{
            temp = "0"+temp;
        }
        if(mp.find(temp)!=mp.end()){
            mp[temp].insert(num);
            if(mp[temp].size()>bucket_size){
                split_ex_hash2(mp,mp.find(temp));
            }
            break;
        }
    }
}

map <string,set <int>> ex_hasher2(int bucket_size, vector <int> nums){
    map<string,set <int>> mp;
    mp["0"]={};
    mp["1"]={};
    int len = 1;
    for(auto x:nums){
        insert_ex_hash2(mp,x,bucket_size);
    }
    return mp;
}


void split_lin_hash(vector <vector <int>> v, int &split_ind, int &md, int k){
    // cout<<"splitting: "<<split_ind<<"\n";
    vector <int> temp = v[split_ind];
    v[split_ind]={};
    for(auto x:temp){
        // cout<<"x: "<<x<<"\n";
        int insert_ind = x%(md+k);
        v[insert_ind].push_back(x);
    }
    split_ind++;
    // cout<<"here split_ind: "<<split_ind<<"\n";

    if(split_ind==v.size()){
        md+=k;
        split_ind=0;
    }
}

void insert_lin_hash(vector <vector<int>> &v,int &split_ind, int md, int k, int bucket_size, int num){
    int insert_ind = num%md;
    // cout<<"split_ind: "<<split_ind<<"\n";
    if(insert_ind<split_ind){
        // cout<<"here num: "<<num<<"\n";
        insert_ind = num%(md+k);
    }
    v[insert_ind].push_back(num);
    if(v[insert_ind].size()> bucket_size){
        split_lin_hash(v,split_ind,md,k);
    }
}

vector <vector <int>> lin_hasher(int bucket_size, int n, int k, vector <int> nums){
    int split_ind = 0;
    int md = k;
    vector <vector <int>> v(n);
    for(auto x:nums){
        insert_lin_hash(v,split_ind,md,k,bucket_size,x);
    }
    
    return v;
}

void split_lin_hash2(vector <set <int>> v, int &split_ind, int &md, int k){
    set <int> temp = v[split_ind];
    v[split_ind]={};
    for(auto x:temp){
        int insert_ind = x%(md+k);
        v[insert_ind].insert(x);
    }
    split_ind++;
    if(split_ind==v.size()){
        md+=k;
        split_ind=0;
    }
}

void insert_lin_hash2(vector <set<int>> &v,int split_ind, int md, int k, int bucket_size, int num){
    int insert_ind = num%md;
    if(insert_ind<split_ind){
        insert_ind = num%(md+k);
    }
    v[insert_ind].insert(num);
    if(v[insert_ind].size()> bucket_size){
        split_lin_hash2(v,split_ind,md,k);
    }
}

vector <set <int>> lin_hasher2(int bucket_size, int n, int k, vector <int> nums){
    int split_ind = 0;
    int md = k;
    vector <set <int>> v(n);
    for(auto x:nums){
        insert_lin_hash2(v,split_ind,md,k,bucket_size,x);
    }
    
    return v;
}


vector <vector<int>> dist_hasher(int k,vector <int> nums, int bucket_size){
    vector <vector<int>> v(binpow(2,k,1e9+7));
    for(auto x: nums){
        int insert_ind = 0;
        int m = 31-__builtin_clz(x);
        // if(x==414622) cout<<"here m: "<<m<<'\n';
        // cout<<"m: "<<m<<"\n";
        for(int i = m-k+1;i<=m;i++){
            if(x&((long long)1<<i)){
                insert_ind|=((long long)1<<(i-(m-k+1)));
            }
        }
        v[insert_ind].push_back(x);
    }
    return v;
    

}

int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin>>n;
    vector <string> book_id;
    for(int i = 0;i<n;i++){
        string s;
        cin>>s;
        book_id.push_back(s);
    }
    vector <int> hashed_book_id;
    // set <long long> st;
    for(auto s:book_id){
        hashed_book_id.push_back(hash_string(s,N));
        // st.insert(hashed_book_id[hashed_book_id.size()-1]);
    }
    // cout<<hashed_book_id.size()<<" "<<st.size()<<"\n";
    
    printvector(hashed_book_id);
    cout<<"\n";
    cout<<"Extendible Hashing"<<"\n";
    map <string,vector <int>> ex_hash = ex_hasher(4,hashed_book_id);
    
    cout<<"\n";
    for(auto p:ex_hash){
        cout<<p.first<<" : ";
        printvector(p.second);
        cout<<"\n";
    }
    cout<<"Linear Hashing"<<"\n";
    vector <vector <int>> lin_hash = lin_hasher(4,16,5,hashed_book_id);
    for(int i = 0;i<n;i++){
        cout<<i<<" : ";
        printvector(lin_hash[i]);
    }
    cout<<"\n";
    cout<<"Distributed Hashing"<<"\n";
    vector <vector <int>> dist_hash = dist_hasher(4,hashed_book_id,4);
    for(int i = 0;i<dist_hash.size();i++){
        string temp = "";
        for(int k = 0;k<4;k++){
            if(i&(1<<k)){
                temp = "1"+temp;
            }
            else temp = "0"+temp;
        }
        cout<<temp<<" : ";
        printvector(dist_hash[i]);
    }
    // cout<<dist_hash.size()<<"\n";
    return 0;
}