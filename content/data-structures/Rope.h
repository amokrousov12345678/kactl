/**
 * Author: Anton Mokrousov
 * Date: 2023-11-16
 * License: CC0
 * Source: folklore
 * Description: Like implicit treap but faster.
   Persistent! (allows not only move but copy segments)
 * Time: O(\log N)
 */
#pragma once

#include <ext/rope> /** keep-include */
using namespace __gnu_cxx;

void example() {
	rope<int> v(3,0);//rope<int> v(n) DOESN'T WORK
	v.push_back(1); v.push_back(2); v.push_back(3);
	int l = 2, r = 4;
	rope<int> part = v.substr(l, r-l+1);
	v.erase(l, r-l+1);
	v.insert(v.mutable_begin(), part);
	v.mutable_reference_at(4) = 7;
	vector<int> expected{0,1,2,0,7,3};
	for (int i=0;i<sz(v);i++) {
		assert(v[i]==expected[i]);//v[i] is RO
	}
}
