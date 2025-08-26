#include<bits/stdc++.h>
using namespace std;


const int BUCKET_SIZE=3;
const int N=100;
int a[N];
map<set<pair<int, int>>, vector<int>> cat_buck;
bool belongTo(set<pair<int, int>> &st, int num)
{
    for(auto &it : st)
    {
        if(num%it.first==it.second) return true;
    }
    return false;
}
pair<int, int> getcat(set<pair<int, int>> &st, int num)
{
    for(auto &it : st)
    {
        if(num%it.first==it.second) return {it.first, it.second};
    }
    return {-1, -1};
}
pair<pair<int, int>, pair<int, int>> getSplitPairs(pair<int, int> p) 
{
    int x=p.first;
    int y=p.second;
    return {{2*x, y}, {2*x, y+x}};
}
bool isbelong_to_cat(pair<int, int> cat, int num)
{
    return num%cat.first==cat.second;
}
bool allbelong(pair<int, int> &thiscat, vector<int> &vals)
{
    for(int i : vals)
    {
        if(i%thiscat.first!=thiscat.second) return false;
    }
    return true;
};
bool isbelong(pair<int, int> &p, int num)
{
    return num%p.first==p.second;
};
int collision_count=0;
int main()
{   
    int n;
    cin>> n;
    //n should be atleast 3.
    for(int i=0;i<n;i++)
    {
        cin>> a[i];
    }
    cat_buck[{{1, 0}}]={a[0], a[1], a[2]};
    for(int i=3;i<n;i++)
    {
        for(auto &it : cat_buck)
        {
            set<pair<int, int>> this_set=it.first;
            int num=a[i];
            if(belongTo(this_set, a[i]))
            {
                if(it.second.size()<3) 
                {
                    cat_buck[this_set].push_back(a[i]);
                }
                else
                {       
                    collision_count++;
                    vector<int> vals=it.second;
                    vector<int> res1, res2;
                    auto thiscat=getcat(this_set, num);
                    set<pair<int, int>> new_set1;
                    for(auto &s : this_set)
                    {
                        if(s!=thiscat) new_set1.insert(s); 
                    }
                    vals.push_back(num);
                    while(allbelong(thiscat, vals))
                    {
                        pair<pair<int, int>, pair<int, int>> ps=getSplitPairs(thiscat);
                        bool f1=isbelong(ps.first, num);
                        bool f2=isbelong(ps.second, num);
                        if(f1)
                        {
                            new_set1.insert(ps.second);
                            thiscat=ps.first;
                        }
                        else 
                        {
                            new_set1.insert(ps.first);
                            thiscat=ps.second;
                        }
                    }
                    for(int i : vals)
                    {
                        if(isbelong_to_cat(thiscat, i))
                        {
                            res1.push_back(i);
                        }
                        else res2.push_back(i);
                    }
                    cat_buck.erase(this_set);
                    set<pair<int, int>> new_set2={thiscat};
                    cat_buck[new_set2]=res1;
                    if(!new_set1.empty()) cat_buck[new_set1]=res2;
                }
                break;
            }
        }
    }
    for(auto &it : cat_buck)
    {
        auto cat_set=it.first;
        auto vals=it.second;
        for(auto &it2 : cat_set)
        {
            int mod=it2.first, rem=it2.second;
            cout<< "("<< mod<< "k";
            if (rem != 0) cout<< "+"<< rem;
            cout<< ") ";
        }   
        cout<< " -> ";
        for(int vec : vals) cout<< vec<< " ";
        cout<< '\n';
    }
    cout << "Total collisions: " << collision_count << "\n";
    cout << "Collision rate: " << fixed << setprecision(2) << (100.0 * collision_count / n) << "%\n";
}