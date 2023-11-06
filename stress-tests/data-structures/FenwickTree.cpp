#include "../utilities/template.h"

#include "../../content/data-structures/FenwickTree.h"

int main() {
	rep(it,0,100000) {
		int N = rand() % 10;
		FT fw(N);
		vi t(N);
		rep(i,0,N) {
			int v = rand() % 3;
			fw.update(i, v);
			t[i] += v;
		}
		int q = rand() % 20;
		int ind = fw.lower_bound(q);
		int res = -1, sum = 0;
		rep(i,0,N+1) {
			if (sum < q) res = i;
			if (i != N) sum += t[i];
		}
		assert(res == ind);

		if (N) {
			int r = rand() % N;
			int acc = 0;
			rep(i, 0, r + 1) {
				acc += t[i];
			}
			assert(acc == fw.query(r));
		}
	}
	cout<<"Tests passed!"<<endl;
}
