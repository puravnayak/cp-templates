#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std; 
using namespace __gnu_pbds;

#define int long long
#define endl '\n' 

#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>
// s.order_of_key(k) to find the number of elements smaller than k in O(logn)
// s.find_by_order(k) to find K-th element in a set (0-based index) in O(logn)


// IF YOU DONT WANT TO STORE UNIQUE VALUES ONLY USE
// #define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>
// AND MAKE IT {VAL,UNIQUE_ID}
// SEARCH USING s.order_of_key({k,-1}) 
// Assuming ID>=0


void solve()
{
    int n;
    cin>>n;
    vector<pair<int,int>>arr(n);
    for(int i=0;i<n;i++)
    {
        cin>>arr[i].first>>arr[i].second;
    }
    sort(arr.begin(),arr.end());
    ordered_set v;
    int ans=0;
    v.insert(arr[n-1].second);
    for(int i=n-2;i>=0;i--)
    {
        ans+=v.order_of_key(arr[i].second);
        v.insert(arr[i].second);
    }
    cout<<ans<<endl;
}

signed main(){
    ios_base::sync_with_stdio(0),cin.tie(NULL),cout.tie(NULL);
    int t=1;
    cin>>t;
    while(t--)
    {
        solve();
    }
    return 0;
}