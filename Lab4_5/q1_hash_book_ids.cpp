#include<bits/stdc++.h>
using namespace std;

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


int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    vector <string> book_ids;

    /* Taking input from file where book Ids where inserted */
    string bookId;
    ifstream inputFile("bookIDs.txt");

    while (getline (inputFile, bookId)) 
    {
        if(bookId.size()>0)
        {
            bookId.pop_back();
            book_ids.push_back(bookId);
        }
    }
    inputFile.close();

    int n = book_ids.size();

    // Q1 b.
    /* Converting book Ids to integers */

    vector <int> hashed_book_ids;
    cout<<"Hashed book Ids : \n";
    
    for(auto book_id:book_ids){
        hashed_book_ids.push_back(hash_string(book_id,N));
        cout<<book_id<<" -> "<<hashed_book_ids.back()<<"\n";
    }

    return 0;
}
