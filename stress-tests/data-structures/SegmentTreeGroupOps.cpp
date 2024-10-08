#include "../utilities/template.h"

#include "../../content/data-structures/SegmentTreeGroupOps.h"

static unsigned R;
int ra() {
	R *= 791231;
	R += 1231;
	return (int)(R >> 1);
}

volatile int res;
int main() {
	int N = 10;
	vi v(N);
	iota(all(v), 0);
	random_shuffle(all(v), [](int x) { return ra() % x; });
	SegTree st(v);
	rep(i,0,N) rep(j,0,N) if (i <= j) {
		int ma = -inf;
		rep(k,i,j+1) ma = max(ma, v[k]);
		assert(ma == st.query(i,j));
	}
	rep(it,0,1000000) {
		int i = ra() % N, j = ra() % N;
		if (i > j) swap(i, j);
		int x = (ra() % 10) - 5;

		int r = ra() % 100;
		if (r < 50) {
			::res = st.query(i, j);
			int ma = -inf;
			rep(k,i,j+1) ma = max(ma, v[k]);
			assert(ma == ::res);
		}
		else {
			st.update(i, j, x);//assign
			rep(k,i,j+1) v[k] = x;
		}
	}
	cout<<"Tests passed!"<<endl;
}
