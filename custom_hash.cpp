#include <bits/stdc++.h>
using namespace std;

//int
struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = 
            chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

//pair
struct custom_hash_pair {
    size_t operator()(pair<uint64_t,uint64_t> x) const {
        static const uint64_t FIXED_RANDOM =
            chrono::steady_clock::now().time_since_epoch().count();
        uint64_t h = x.first;
        h ^= x.second + 0x9e3779b97f4a7c15 + (h<<6) + (h>>2);
        return custom_hash::splitmix64(h + FIXED_RANDOM);
    }
};

//string
struct custom_hash_string {
    size_t operator()(const string &s) const {
        size_t h = 0;
        for(char c : s) {
            h = h * 31 + c;
        }
        return custom_hash::splitmix64(h);
    }
};



int main()
{
    unordered_map<int,int,custom_hash>mpp;
    return 0;
}