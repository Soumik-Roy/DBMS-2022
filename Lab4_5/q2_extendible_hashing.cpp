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

class ExtendibleHashing : BasicHashFunctions {
    private:
        map<string,vector <int>> mp;
        int bucket_size;

        void splitAtIndex(map<string,vector <int>>::iterator ptr_to_split){
            pair<string,vector<int>> p = *ptr_to_split;
            string str = p.first;
            vector <int> v = p.second;
            int len = str.size();
            
            mp["0"+str] = {};
            mp["1"+str] = {};

            for(auto num:v){
                string idx = dec_to_bin(num,len+1);
                mp[idx].push_back(num);
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

        void print() {
            cout<<"Extendible Hashing Table :-"<<"\n";
            for(auto p : mp){
                cout<<p.first<<" : ";
                printDataStructure(p.second);
            }
            cout<<"\n";
        }
};

class ExtendibleHashing2 : BasicHashFunctions {
    private:
        map<string,set <int>> mp;
        int bucket_size;

        void splitAtIndex(map<string,set <int>>::iterator ptr){
            pair<string,set<int>> p = *ptr;
            string str = p.first;
            set <int> v = p.second;
            int len = str.size();

            mp["0"+str]={};
            mp["1"+str]={};

            for(auto num:v){
                string idx = dec_to_bin(num,len+1);
                mp[idx].insert(num);
            }
            mp.erase(ptr);

        }

    public:
        ExtendibleHashing2(int _bucket_size){
            mp["0"]={};
            mp["1"]={};
            bucket_size = _bucket_size;
        }

        ExtendibleHashing2(int _bucket_size, vector <int> nums){
            mp["0"]={};
            mp["1"]={};
            bucket_size = _bucket_size;

            for(auto x:nums){
                insertNewValue(x);
            }
        }

        void insertNewValue(int num) {            
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
                        splitAtIndex(mp.find(temp));
                    }
                    break;
                }
            }
        }

        void print() {
            cout<<"Extendible Hashing 2 (using set) Table:-"<<"\n";
            for(auto p : mp){
                cout<<p.first<<" : ";
                printDataStructure(p.second);
                
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
    


    // Q2 a.
    cout << "\nQ2 A\n";
    ExtendibleHashing ex_hash(4, hashed_book_ids);
    ex_hash.print();

    cout<<"--------------------------------------------\n\n";

    // Q2 b.
    cout << "Q2 B\n";

    for (int b_size = 3; b_size < 6; b_size++)
    {
        cout << "\nBucket size "<<b_size<<" :-\n";
        ExtendibleHashing ex_hash_(b_size, hashed_book_ids);
        ex_hash_.print();
        cout<<endl;
    }

    cout<<"--------------------------------------------\n\n";

    // Q2 c.
    cout << "Q2 C\n";
    ExtendibleHashing2 ex_hash2(4, hashed_book_ids);
    ex_hash2.print();

    return 0;
}
