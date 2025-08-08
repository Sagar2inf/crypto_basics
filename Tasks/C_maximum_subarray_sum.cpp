#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds; 

typedef long double ld;
typedef long long ll;
typedef vector<int> vi;
typedef vector<long long> vll;
typedef pair<long long,long long> pll;
typedef pair<int,int> pii;

#define pb push_back
#define mp make_pair
#define lb lower_bound
#define ub upper_bound
#define ff first
#define ss second
#define setbits(x) __builtin_popcount(x)
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update> // for multiset: less_equal
#define all(x, l, r) x.begin() + l, x.begin() + r
#define rall(x, l, r) x.rbegin() + l, x.rbegin() + r 
#define psort(x, n) partial_sort(x.begin(), x.begin() + n, x.end())
#define mxe *max_element
#define mne *min_element

const ll inf = 1e18;
const ll mod0 = 1e9 + 7;
const ll mod1 = 998244353;
const char nl = '\n';


void solve(){
	int n, k; cin >> n >> k;
	string s; cin >> s;
	vector<ll> a(n);		
	for(auto & it: a){
		cin >> it;
	}
	int j = -1;
	// for(int i = 0; i < n; i++){
	// 	if(s[i] == '0'){
	// 		ll sum = 0, f = 0;
	// 		for(int b = max(i - 1, 0); b > j; b--){
	// 			sum += a[b];
	// 			if(sum > 0) f = 1; break;
	// 		}
	// 		if(!f){
	// 			ll sum = 0;
	// 			int b = i + 1;
	// 			while(b < n){
	// 				if(s[b] == '0') break;
	// 				sum += a[b];
	// 				b += 1;
	// 			}
	// 			a[i] = k - sum;
	// 			s[i] = '1';
	// 		}
	// 		j = i;
	// 	}else if(i > 0 && s[i] == '0' && s[i - 1] == '0'){
	// 		int b = i + 1;
	// 		ll sum = 0;
	// 		while(b < n){
	// 			if(s[b] == '0') break;
	// 			sum += a[b];
	// 			b += 1;
	// 		}	
	// 		a[i] = k - sum;
	// 		s[i] = '1';
	// 	}
	// }
	for(int i = 0; i < n; i++){
		if(s[i] == '0'){
			a[i] = -1e15;
			s[i] = '1';
		}
	}	
	ll sum = 0, tmp = 0;
	for(int i = 0; i < n; i++){
		tmp += a[i];
		sum = max(tmp, sum);
		tmp = max(tmp, 0ll);
	}
	if(sum > k){
		cout << "NO" << nl;
	}else{
		cout << "YES" << nl;
		for(auto & it: a){
			cout << it << " ";
		}
		cout << nl;
	}
}


int main(){

#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

ios::sync_with_stdio(false);
cin.tie(nullptr);

int T = 1; cin >> T;
for(int testcase = 1; testcase <= T; testcase++){
	solve();
}

return 0;
}