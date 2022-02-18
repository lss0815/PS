#include <bits/stdc++.h>

using namespace std;

stack<int> s;

int main(void){
	string c;
	int t, n;
	ios::sync_with_stdio(false);
	cin >> t;
	while(t--){
		cin >> c;
		if(c == "push"){
			cin >> n;
			s.push(n);
		}
		else if(c == "pop"){
			if(s.empty())cout << -1 << '\n';
			else {
				cout << s.top() << '\n';
				s.pop();
			}
		}
		else if(c == "size"){
			cout << s.size() << '\n';
		}
		else if(c == "empty"){
			if(s.empty()) cout << 1 << '\n';
			else cout << 0 << '\n';
		}
		else if(c == "top"){
			if(s.empty()) cout << -1 << '\n';
			else cout << s.top() << '\n';
		}
		else {
			cout << "error occurred\n";
		}
	}
	return 0;
}
