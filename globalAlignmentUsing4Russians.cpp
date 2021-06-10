#include<bits/stdc++.h>
using namespace std;

enum Neucliotide{A=0,T=1,G=2,C=3};
enum direction{RIGHT,BOTTOM,DIAGONAL};
char getCharFromNum(int num)
{
    if(num==0)
    {
        return 'A';
    }
    else if(num==1)
    {
        return 'T';
    }
    else if(num==2)
    {
        return 'G';
    }
    else if(num==3)
    {
        return 'C';
    }
    else
    {
        return 'K';
    }
}

string calculateString(int ind,int t)
{
    char *str = new char[t+1];
    str[t] = '\0'; // null charecter to indicate end of string
    for(int i=0;i<t;i++)
    {
        int rem = ind%4; // len(A,T,G,C) == 4
        ind = ind/4;
        char tempChar = getCharFromNum(rem);
        str[t-1-i] = tempChar;
    }
    return string(str);
}

int lcsLengthMemoryEfficient(string a, string b)
{
    vector<int> prev(b.size()+1);
    vector<int> next(b.size()+1);
    for(int i=0;i<b.size()+1;i++)
    {
        prev[i] = 0;
    }
    for(int i=1;i<a.size()+1;i++)
    {
        for(int j=0;j<b.size()+1;j++)
        {
            if(j==0)
            {
                next[j] = 0;
                continue;
            }

            if(a[i-1]==b[j-1])
            {
                next[j] = prev[j-1] + 1;
            }
            else if(next[j-1]>prev[j])
            {
                next[j] = next[j-1];
            }
            else
            {
                next[j] = prev[j];
            }
        }
        prev = next;
    }
    return next[b.size()];
}

void calculate(int i, int j, int t, vector<vector<int>> &hTable)
{
    
    string rowString = calculateString(i,t);
    string colString = calculateString(j,t);
    // cout<<rowString<<" "<<colString<<endl;
    hTable[i][j] = lcsLengthMemoryEfficient(rowString,colString);
}

int getValueFromChar(char t)
{
    if(t=='A')
    {
        return 0;
    }
    else if(t=='T')
    {
        return 1;
    }
    else if(t=='G')
    {
        return 2;
    }
    else if(t=='C')
    {
        return 3;
    }
    else 
    {
        cout<<"error in getValueFromChar"<<endl;
        return INT_MIN;
    }
}

int getHash(string str)
{
    int t = str.size();
    int hash = 0;
    for(int i=0;i<t;i++)
    {
        char tempChar = str[t-1-i];
        hash += pow(4,i) * getValueFromChar(tempChar); 
    }
    return hash;
}

int main()
{
    // cout<<"kill meh"<<endl;
    srand(time(0));
    int n = 4096;
    int t = log2(n)/4;
    if(pow(2,t*4)!=n)
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
            temp.push_back(-5); // initing with -5 
        }
        hTable.push_back(temp);
    }

    
    for(int i=0;i<pow(4,t);i++)
    {
        
        for(int j=0;j<pow(4,t);j++)
        {
            calculate(i,j,t,hTable); // claculate and assigne value for index (i,j)
        }
        
    }

    

    // penalty for inserting or deleting an entire block is sigma(i,j)
    // we are building that sigmaTable and currently initializing all the 
    // cell with 0 for initial phase anybody can give useful value other than 0
    // if they want to use their own penalty metrics set for that particulat experiment
    vector<vector<int>> sigmaTable;
    for(int i=0;i<pow(4,t);i++)
    {
        vector<int> temp;
        for(int j=0;j<pow(4,t);j++)
        {
            temp.push_back(0);
        }
        sigmaTable.push_back(temp);
    }

    // generate random test cases
    int stringLen = n;
    char *u1 = new char[stringLen+1];
    char *v1 = new char[stringLen+1];
    u1[stringLen+1] = '\0';
    v1[stringLen+1] = '\0';
    for(int i=0;i<stringLen;i++)
    {
        int rand1 = rand()%4;
        int rand2 = rand()%4;
        int rand3 = rand();
        char c1 = getCharFromNum(rand1);
        char c2 = getCharFromNum(rand2);
        if(rand3%2==0)
        {
            u1[i] = c1;
            v1[i] = c1;
        }
        else
        {
            u1[i] = c1;
            v1[i] = c2;
        }
        
    }
    string u(u1);
    string v(v1);
    // cout<<"String u: "<<u<<endl<<endl;
    // cout<<"String v: "<<v<<endl<<endl;

    // for(int i=0;i<pow(4,t);i++)
    // {
       
    //     for(int j=0;j<pow(4,t);j++)
    //     {
    //         cout<<hTable[i][j]<<" "; 
    //     }
    //     cout<<endl;
    // }

    vector<vector<int>> s;
    vector<vector<int>> p;
    int dpTableSize = (n/t) + 1;
    for(int i=0;i<dpTableSize;i++)
    {
        vector<int> temp;
        for(int j=0;j<dpTableSize;j++)
        {
            temp.push_back(-5);
        }
        s.push_back(temp);
        p.push_back(temp);
    }
    for(int i=0;i<s.size();i++)
    {
        s[i][0] = 0;
    }
    for(int i=0;i<s[0].size();i++)
    {
        s[0][i] = 0;
    }

    for(int i=1;i<s.size();i++)
    {
        for(int j=1;j<s[0].size();j++)
        {
            string rowString = u.substr(t*(i-1),t);
            string colString = v.substr(t*(j-1),t);
            int rowStringHash = getHash(rowString);
            int colStringHash = getHash(colString);
            int sigma = sigmaTable[rowStringHash][colStringHash];
            int beta = hTable[rowStringHash][colStringHash];
            int t1 = s[i-1][j]-sigma;
            int t2 = s[i][j-1]-sigma;
            int t3 = s[i-1][j-1]+beta;
            int val = max(t1, max(t2, t3));
            if(val==t3)
            {
                s[i][j] = t3;
                p[i][j] = DIAGONAL; 
            }
            else if(val==t1)
            {
                s[i][j] = t1;
                p[i][j] = BOTTOM; 
            }
            else if(val==t2)
            {
                s[i][j] = t2;
                p[i][j] = RIGHT;
            }

        }
    }

    cout<<"Alignment Score: "<<s[s.size()-1][s.size()-1]<<endl;
    cout<<"from lcs score we get: "<<lcsLengthMemoryEfficient(u,v)<<endl;
    // for(int i=0;i<s.size();i++)
    // {
    //     for(int j=0;j<s[0].size();j++)
    //     {
    //         cout<<s[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }


    
}