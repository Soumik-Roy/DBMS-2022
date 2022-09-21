#include<bits/stdc++.h>
using namespace std;

class BasicFunctions {
    protected:
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

    public:
        long long hash_string(string s,int md){
            long long ans = 0;
            for(int i = 0;i<s.size();i++){
                ans+=((binpow(s[i],i,md))%md);
            }
            return ans;
        }

        template <class t>
        void printvector(vector <t>& v){
            int n = v.size();
            for(int i = 0;i<n;i++){
                cout<<v[i]<<" ";
            }
            cout<<"\n";
        }
};

int N = 100003 ;

class ExtendibleHashing : BasicFunctions {
    private:
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

        map<string,vector <int>> mp;
    public:
        ExtendibleHashing(int bucket_size, vector <int> nums){
            // map<string,vector <int>> mp;
            mp["0"]={};
            mp["1"]={};
            int len = 1;
            for(auto x:nums){
                insert_ex_hash(mp,x,bucket_size);
            }
            // return mp;
        }

        void print() {
            cout<<"Extendible Hashing"<<"\n";
            for(auto p : mp){
                cout<<p.first<<" : ";
                printvector(p.second);
                // cout<<"\n";
            }
            cout<<"\n";
        }
};

class ExtendibleHashing2 : BasicFunctions {
    private:
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

        void insert_ex_hash2(map <string,set <int>> &mp,int num, int bucket_size) {            
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

        map<string,set <int>> mp;
    public:
        ExtendibleHashing2(int bucket_size, vector <int> nums){
            mp["0"]={};
            mp["1"]={};
            int len = 1;
            for(auto x:nums){
                insert_ex_hash2(mp,x,bucket_size);
            }
        }

        void print() {
            cout<<"Extendible Hashing 2"<<"\n";
            for(auto p : mp){
                cout<<p.first<<" : ";
                // printvector(p.second);
                for (auto x : p.second) {
                    cout << x << " ";
                }
                cout<<"\n";
            }
            cout<<"\n";
        }
};


class LinearHashing : BasicFunctions {
    private:
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

        vector<vector<int>> v;
    public:
        LinearHashing(int bucket_size, int n, int k, vector <int> nums){
            int split_ind = 0;
            int md = k;

            v = vector<vector<int>> (n);
            for(auto x:nums){
                insert_lin_hash(v,split_ind,md,k,bucket_size,x);
            }
        }

        void print() {
            cout<<"Linear Hashing"<<"\n";
            for(int i = 0;i<v.size();i++){
                cout<<i<<" : ";
                printvector(v[i]);
            }
            cout<<"\n";
        }
};


class LinearHashing2 : BasicFunctions {
    private:
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

        vector<set<int>> v;
    public:
        LinearHashing2(int bucket_size, int n, int k, vector <int> nums){
            int split_ind = 0;
            int md = k;

            v = vector<set<int>> (n);
            for(auto x:nums){
                insert_lin_hash2(v,split_ind,md,k,bucket_size,x);
            }
        }

        void print() {
            cout<<"Linear Hashing 2"<<"\n";
            for(int i = 0;i<v.size();i++){
                cout<<i<<" : ";
                // printvector(v[i]);
                for (auto x : v[i]) {
                    cout << x << " ";
                }
                cout<<"\n";
            }
            cout<<"\n";
        }
};


class DistributedHashing : BasicFunctions {
    private: 
        vector<vector<int>> v;
    public:
        DistributedHashing(int k,vector <int> nums, int bucket_size){
            v = vector <vector<int>> (binpow(2,k,1e9+7));
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
        }

        void print() {
            cout<<"Distributed Hashing"<<"\n";
            for(int i = 0;i<v.size();i++){
                string temp = "";
                for(int k = 0;k<4;k++){
                    if(i&(1<<k)){
                        temp = "1"+temp;
                    }
                    else temp = "0"+temp;
                }
                cout<<temp<<" : ";
                printvector(v[i]);
            }            
            cout << "\n";
        }
};

int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    vector <string> book_ids;

    // Taking input from file where book Ids where inserted
    string bookId;
    ifstream inputFile("output.txt");

    while (getline (inputFile, bookId)) 
    {
        if(bookId.size()>0)
        {
            bookId.pop_back();
            book_ids.push_back(bookId);
        }
    }

    int n = book_ids.size();
    // Close the file
    inputFile.close();

    BasicFunctions bf;
    // Q1 b.

    // Converting book Ids to integers
    vector <int> hashed_book_ids;
    
    // set <long long> st;
    for(auto s:book_ids){
        hashed_book_ids.push_back(bf.hash_string(s,N));
        // st.insert(hashed_book_ids[hashed_book_ids.size()-1]);
    }
    // cout<<hashed_book_ids.size()<<" "<<st.size()<<"\n";
    
    bf.printvector(hashed_book_ids);


    // Q2 a.
    cout << "Q2 a\n";
    ExtendibleHashing ex_hash(4, hashed_book_ids);
    ex_hash.print();

    cout << "Q2 b\n";
    cout << "Bucket size 3:-\n";
    ExtendibleHashing ex_hash2(3, hashed_book_ids);
    ex_hash2.print();
    cout << "Bucket size 6:-\n";
    ExtendibleHashing ex_hash3(6, hashed_book_ids);
    ex_hash3.print();

    cout << "Q2 c\n";
    ExtendibleHashing2 ex_hash4(4, hashed_book_ids);
    ex_hash4.print();

    cout << "Q3 b\n";
    LinearHashing lin_hash(4, 16, 5, hashed_book_ids);
    lin_hash.print();

    cout << "Q4 b\n";
    DistributedHashing dist_hash(4, hashed_book_ids, 4);
    dist_hash.print();

    // cout<<dist_hash.size()<<"\n";
    return 0;
}
