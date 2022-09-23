#include<bits/stdc++.h>
using namespace std;

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

        void print() {
            cout<<"Linear Hashing Table :"<<"\n";
            for(int i = 0;i<v.size();i++){
                cout<<i<<" : ";
                printDataStructure(v[i]);
            }
            cout<<"\n";
        }
};


class LinearHashing2 : BasicHashFunctions {
    private:
        vector<set<int>> v;
        int bucket_size;
        int split_index = 0;
        int mod_val;
        int k;

        void splitAt_split_index(){
            set <int> temp = v[split_index];
            v[split_index]={};

            if(split_index==0) v.resize(mod_val+k);

            for(auto x:temp){
                int insert_ind = x%(mod_val+k);
                v[insert_ind].insert(x);
            }

            split_index++;

            if(split_index==v.size()){
                mod_val += k;
                split_index=0;
            }
        }

    public:
        LinearHashing2(int _bucket_size, int _mod_val){
            mod_val = _mod_val;
            k = _mod_val;
            bucket_size = _bucket_size;

            v = vector<set<int>> (mod_val);
        }

        LinearHashing2(int _bucket_size, int _mod_val, vector <int> nums){
            mod_val = _mod_val;
            k = _mod_val;
            bucket_size = _bucket_size;

            v = vector<set<int>> (mod_val);

            for(auto x:nums){
                insertNewValue(x);
            }
        }

        void insertNewValue(int num){
            int insert_ind = num%mod_val;

            if(insert_ind<split_index){
                insert_ind = num%(mod_val+k);
            }
            v[insert_ind].insert(num);

            if(v[insert_ind].size() > bucket_size){
                splitAt_split_index();
            }
        }

        void print() {
            cout<<"Linear Hashing Table (using set) :"<<"\n";
            for(int i = 0;i<v.
            size();i++){
                cout<<i<<" : ";
                printDataStructure(v[i]);
            }
            cout<<"\n";
        }
};

int N = 100003 ;

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

    // Q3 b.
    cout << "\nQ3 B\n";
    int bucket_size = 4;
    int n = 5;
    LinearHashing lin_hash(bucket_size, n, hashed_book_ids);
    lin_hash.print();

    cout<<"--------------------------------------------\n\n";

    // Q3 c.
    cout << "Q3 C\nBucket size = "<<bucket_size<<endl;
    for (int _n = n-1; _n <= n+1; _n++)
    {
        cout << "\nGlobal Order "<<_n<<" :-\n";
        LinearHashing lin_hash_(bucket_size, _n, hashed_book_ids);
        lin_hash_.print();
        cout<<endl;
    }

    cout<<"--------------------------------------------\n\n";

    // Q3 d.
    cout << "Q3 D\nGlobal Order = "<<n<<endl;
    for (int b_size = bucket_size-1; b_size <= bucket_size+1; b_size++)
    {
        cout << "\nBucket size "<<b_size<<" :-\n";
        LinearHashing lin_hash_(b_size, n, hashed_book_ids);
        lin_hash_.print();
        cout<<endl;
    }

    cout<<"--------------------------------------------\n\n";

    // Q3 e.
    cout << "Q3 E\n";
    LinearHashing2 lin_hash_set(bucket_size, n, hashed_book_ids);
    lin_hash_set.print();

    return 0;
}
