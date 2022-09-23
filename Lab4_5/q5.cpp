#include<bits/stdc++.h>
#include <chrono>
using namespace std::chrono;
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

class BasicHashFunctions {
    protected:
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
        template <class T>
        void printDataStructure(T &v){
            for(auto x:v){
                cout<<x<<" ";
            }
            cout<<"\n";
        }
};

class ExtendibleHashing : BasicHashFunctions {
    private:
        map<string,vector <int>> mp;
        int bucket_size;

        void splitAtIndex(map<string,vector <int>>::iterator ptr_to_split){
            pair<string,vector<int>> p = *ptr_to_split;
            string str = p.first;
            vector <int> v = p.second;
            int len = str.size();
            for(auto num:v){
                mp[dec_to_bin(num,len+1)].push_back(num);
            }
            mp.erase(ptr_to_split);

        }

    public:
        ExtendibleHashing(int _bucket_size){
            mp["0"]={};
            mp["1"]={};
            bucket_size = _bucket_size;
        }

        ExtendibleHashing(int _bucket_size, vector <int> nums){
            mp["0"]={};
            mp["1"]={};

            bucket_size = _bucket_size;

            for(auto x:nums){
                insertNewValue(x);
            }
        }

        void insertNewValue(int num){            
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
                        splitAtIndex(mp.find(temp));
                    }
                    break;
                }
            }
        }

        void searchValue(int value){
            auto start = high_resolution_clock::now();
            string temp = "";
            for(int i = 0;i<31;i++){
                if(value<(1<<i))
                    break;
                if(value&(1<<i)){
                    temp = "1"+temp;
                }
                else{
                    temp = "0"+temp;
                }
                if(mp.find(temp)!=mp.end()){
                    vector <int> v = mp[temp];
                    for(auto x:v){
                        if(x==value){
                            cout<<"Found in ";
                            auto stop = high_resolution_clock::now();
                            auto duration_ns = duration_cast<nanoseconds>(stop - start);
                            cout<<duration_ns.count()<<" nanoseconds\n";
                            return;
                        }
                    }
                }
            }
            cout<<"Not Found\n";
            return;
        }

        void print() {
            cout<<"Extendible Hashing Table :-"<<"\n";
            for(auto p : mp){
                cout<<p.first<<" : ";
                printDataStructure(p.second);
                // cout<<"\n";
            }
            cout<<"\n";
        }
};

class LinearHashing : BasicHashFunctions {
    private:
        vector<vector<int>> v;
        int bucket_size;
        int split_index = 0;
        int mod_val;
        int k;

        void splitAt_split_index(){
            vector <int> temp = v[split_index];
            v[split_index]={};

            if(split_index==0) v.resize(mod_val+k);

            for(auto x:temp){
                int insert_ind = x%(mod_val+k);
                v[insert_ind].push_back(x);
            }

            split_index++;

            if(split_index==v.size()){
                mod_val+=k;
                split_index=0;
            }
        }

    public:
        LinearHashing(int _bucket_size, int _mod_val){
            mod_val = _mod_val;
            k = mod_val;
            bucket_size = _bucket_size;

            v = vector<vector<int>> (mod_val);
        }

        LinearHashing(int _bucket_size, int _mod_val, vector <int> nums){
            mod_val = _mod_val;
            k = mod_val;
            bucket_size = _bucket_size;

            v = vector<vector<int>> (mod_val);

            for(auto x:nums){
                insertNewValue(x);
            }
        }

        void insertNewValue(int num){
            int insert_ind = num%mod_val;

            if(insert_ind<split_index){
                insert_ind = num%(mod_val+k);
            }
            v[insert_ind].push_back(num);

            if(v[insert_ind].size() > bucket_size){
                splitAt_split_index();
            }
        }

        void searchValue(int value){
            auto start = high_resolution_clock::now();
            int ind = value%mod_val;
            if(ind<split_index){
                ind = value%(mod_val+k);
            }
            for(auto x:v[ind]){
                if(x==value){
                    cout<<"Found in ";
                    auto stop = high_resolution_clock::now();
                    auto duration_ns = duration_cast<nanoseconds>(stop - start);
                    cout<<duration_ns.count()<<" nanoseconds\n";
                    return;
                }
            }
            cout<<"Not Found\n";
            return;
        }

        void print() {
            cout<<"Linear Hashing Table :"<<"\n";
            for(int i = 0;i<v.size();i++){
                cout<<i<<" : ";
                printDataStructure(v[i]);
            }
            cout<<"\n";
        }
};

class DistributedHashing : BasicHashFunctions {
    private: 
        vector<vector<int>> v;
        int bucket_size;
        int n_bits;

    public:
        DistributedHashing(int _n_bits, int _bucket_size){
            v = vector <vector<int>> (binpow(2,_n_bits,1e9+7));
            bucket_size = _bucket_size;
            n_bits = _n_bits;
        }

        DistributedHashing(int _n_bits,vector <int> nums, int _bucket_size){
            v = vector <vector<int>> (binpow(2,_n_bits,1e9+7));
            bucket_size = _bucket_size;
            n_bits = _n_bits;

            for(auto x: nums){
                insertNewValue(x);
            }
        }

        void insertNewValue(int num){
            int insert_ind = 0;
            int m = 31-__builtin_clz(num);

            for(int i = m-n_bits+1;i<=m;i++){
                if(num&((long long)1<<i)){
                    insert_ind|=((long long)1<<(i-(m-n_bits+1)));
                }
            }
            v[insert_ind].push_back(num);
        }

        void searchValue(int value){
            int ind = 0;
            int m = 31-__builtin_clz(value);
            auto start = high_resolution_clock::now();

            for(int i = m-n_bits+1;i<=m;i++){
                if(value&((long long)1<<i)){
                    ind|=((long long)1<<(i-(m-n_bits+1)));
                }
            }
            for(auto x:v[ind]){
                if(x==value){
                    cout<<"Found in ";
                    auto stop = high_resolution_clock::now();
                    auto duration_ns = duration_cast<nanoseconds>(stop - start);
                    cout<<duration_ns.count()<<" nanoseconds\n";
                    return;
                }
            }
            cout<<"Not Found\n";
            return;
        }

        void print() {
            cout<<"Distributed Hashing Table"<<"\n";
            for(int i = 0;i<v.size();i++){
                string temp = "";
                for(int k = 0;k<n_bits;k++){
                    if(i&(1<<k)){
                        temp = "1"+temp;
                    }
                    else temp = "0"+temp;
                }
                cout<<temp<<" : ";
                printDataStructure(v[i]);
            }            
            cout << "\n";
        }
};

int N = 100003 ;

long long hash_string(string s,int md){
    long long ans = 0;
    for(int i = 0;i<s.size();i++){
        ans+=((binpow(s[i],i,md))%md);
    }
    return ans;
}

void hash_all_values(string input_fname, vector<string> &origVals, vector<int> &hashedVals)
{
    /* Taking input from file where book Ids where inserted */
    string bookId;
    ifstream inputFile(input_fname);

    while (getline (inputFile, bookId)) 
    {
        if(bookId.size()>0)
        {
            bookId.pop_back();
            origVals.push_back(bookId);
        }
    }
    inputFile.close();

    int n = origVals.size();

    cout<<"Hashed book Ids : \n";
    
    for(auto val:origVals){
        hashedVals.push_back(hash_string(val,N));
        cout<<val<<" -> "<<hashedVals.back()<<"\n";
    }
}

int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    BasicHashFunctions bf;

    vector <string> book_ids;
    vector <int> hashed_book_ids;
    hash_all_values("bookIDs.txt",book_ids,hashed_book_ids);

    int bucket_size = 4;

    ExtendibleHashing ex_hash(bucket_size, hashed_book_ids);

    int mod_val = 5;
    LinearHashing lin_hash(bucket_size, mod_val, hashed_book_ids);

    int n_bits = 3;
    DistributedHashing dist_hash(n_bits, hashed_book_ids, bucket_size);

    /* Q5 B */
    string new_book_id = "Find_KY_1111";
    long long hashed_new_book_id = hash_string(new_book_id,N);

    int n_keys = 15000;

    cout<<"\nTime taken in inserting new book ids from "<<hashed_new_book_id-n_keys/2<<" to "<<hashed_new_book_id+n_keys/2<<" : \n\n";

    cout<<"Extendible Hashing -> ";
    auto start = high_resolution_clock::now();
    for (int val = hashed_new_book_id-n_keys/2; val <= hashed_new_book_id+n_keys/2; val++)
    {
        ex_hash.insertNewValue(val);
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout<<duration.count()<<" microseconds\n";

    cout<<"Linear Hashing -> ";
    start = high_resolution_clock::now();
    for (int val = hashed_new_book_id-n_keys/2; val <= hashed_new_book_id+n_keys/2; val++)
    {
        lin_hash.insertNewValue(val);
    }
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout<<duration.count()<<" microseconds\n";

    cout<<"Distributed Hashing -> ";
    start = high_resolution_clock::now();
    for (int val = hashed_new_book_id-n_keys/2; val <= hashed_new_book_id+n_keys/2; val++)
    {
        dist_hash.insertNewValue(val);
    }
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout<<duration.count()<<" microseconds\n";

    cout<<"\n--------------------------------------------\n";

    /* Q5 C */
    string search_book_id = "Anim_CS_0319";
    long long hashed_search_book_id = hash_string(search_book_id,N);

    cout<<"\nTime taken in Searching book id "<<hashed_search_book_id<<" : \n\n";

    cout<<"Extendible Hashing -> ";
    ex_hash.searchValue(hashed_search_book_id);

    cout<<"Linear Hashing -> ";
    lin_hash.searchValue(hashed_search_book_id);

    cout<<"Distributed Hashing -> ";
    dist_hash.searchValue(hashed_search_book_id);

    return 0;
}
