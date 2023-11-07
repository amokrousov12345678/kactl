#include "../utilities/template.h"

#include "../../content/data-structures/RMQ.h"

int main() {
	srand(2);
	rep(N,0,100) {
		vi v(N);
		rep(i,0,N) v[i] = i;
		random_shuffle(all(v));
		RMQ<int> rmq(v);
		rep(i,0,N) rep(j,i+1,N) {
			int m = rmq.query(i,j);
			int n = 1 << 29;
			rep(k,i,j+1) n = min(n, v[k]);
			assert(n == m);
		}
	}
	cout<<"Tests passed!"<<endl;
}
