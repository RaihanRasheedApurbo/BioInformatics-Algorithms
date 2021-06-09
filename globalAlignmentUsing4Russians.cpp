#include<bits/stdc++.h>
using namespace std;

enum Neucliotide{A=0,T=1,G=2,C=3};

int main()
{
    cout<<"kill meh"<<endl;\
    srand(time(0));
    int len = 256;
    int n = log2(len);
    if(pow(2,n)!=len)
    {
        n = n + 1;  //log2(100) = 6 but 2^6 = 64 so taking the ceiling
    }
    int t = n/4;
    if(t*4!=n)
    {
        cout<<"unhandled case so exiting"<<endl;
        return -5;
    }
    cout<<"n,t: "<<n<<","<<t<<endl;

    //create hash table to store 4^t * 4^t entries...
    //creating 2d array using vector
    

    vector<vector<int>> hTable;
    for(int i=0;i<pow(4,t);i++)
    {
        vector<int> temp;
        for(int j=0;j<pow(4,t);j++)
        {
            temp.push_back(-5); // -5 to denote unevaluated cell
        }
        hTable.push_back(temp);
    }

    // generate random test cases
    vector<char> u;
    vector<char> v;

    for(int i=0;i<n;i++)
    {
        int rand1 = rand()%4;//A->0 , T-> 1, C->2, G->3
        int rand2 = rand()%4;
        int rand3 = rand();
        if(rand3%2==0) // 50% probability that u[i] and v[i] is equal
        {
            u.push_back(rand1);
            v.push_back(rand1);
        }
        else
        {
            u.push_back(rand1);
            u.push_back(rand2);
        }
    }

    for(int i=0;i<5;i++)
    {
        cout<<rand()%4<<endl;
    }
}