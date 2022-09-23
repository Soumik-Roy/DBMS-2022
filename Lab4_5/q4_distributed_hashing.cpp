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

class DistributedHashing2 : BasicHashFunctions {
    private: 
        vector<set<int>> v;
        int bucket_size;
        int n_bits;

    public:
        DistributedHashing2(int _n_bits, int _bucket_size){
            v = vector <set<int>> (binpow(2,_n_bits,1e9+7));
            bucket_size = _bucket_size;
            n_bits = _n_bits;
        }

        DistributedHashing2(int _n_bits,vector <int> nums, int _bucket_size){
            v = vector <set<int>> (binpow(2,_n_bits,1e9+7));
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
            v[insert_ind].insert(num);
        }

        void print() {
            cout<<"Distributed Hashing (using set) Table"<<"\n";
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

    //Q4 b.
    cout << "\nQ4 B\n";
    int n_bits = 4, bucket_size = 4;
    DistributedHashing dist_hash(n_bits, hashed_book_ids, bucket_size);
    dist_hash.print();

    cout<<"--------------------------------------------\n\n";

    //Q4 c.
    cout << "Q4 C\n";
    cout << "\nBucket size "<<bucket_size<<"\n";

    for (int _n = n_bits-1; _n < n_bits+2; _n++)
    {
        cout << "\nn_bits = "<<_n<<" :-\n";
        DistributedHashing dist_hash_(_n, hashed_book_ids, bucket_size);
        dist_hash_.print();
    }

    cout<<"--------------------------------------------\n\n";

    //Q4 d.
    cout << "Q4 D\n";
    cout << "\nn_bits = "<<n_bits<<" :-\n";

    for (int b_size = bucket_size-1; b_size < bucket_size+2; b_size++)
    {
        cout << "\nBucket size "<<b_size<<"\n";
        DistributedHashing dist_hash_(n_bits, hashed_book_ids, b_size);
        dist_hash_.print();
    }

    cout<<"--------------------------------------------\n\n";

    //Q4 e.
    cout << "\nQ4 E\n";
    DistributedHashing2 dist_hash_set(n_bits, hashed_book_ids, bucket_size);
    dist_hash_set.print();

    return 0;
}
