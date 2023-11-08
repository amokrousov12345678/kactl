#include "../utilities/template.h"

#include "../../content/data-structures/SegmentTreePersistent.h"

int main() {
	rep(n,1,10) {
		vector<Node*> roots{new Node(n)};
		vector<Node*> rootsBig{new Node(1'000'000'000)};
		int SHIFT = 333'222'444;
		vector<vi> v{vi(n, Node::unit)};
		rep(it,0,200000) {
			int i = rand() % n, j = rand() % n;
			int x = rand() % (n+2);

			int rev = rand() % sz(roots);

			int r = rand() % 100;
			if (r < 30) {
				int ma = Node::unit;
				rep(k,i,j+1) ma = max(ma, v[rev][k]);
				auto expected = query(roots[rev], i,j);
				assert(ma == expected);
				auto cur = rootsBig[rev];
				auto expectedBig = query(rootsBig[rev], i + SHIFT,j + SHIFT);
				assert(ma == expectedBig);
			}
			else {
				i = min(i, n-1);
				roots.push_back(update(roots[rev], i, x));
				rootsBig.push_back(update(rootsBig[rev], i + SHIFT, x));
				v.push_back(v[rev]);
				v.back()[i] = x;
			}
		}
	}
	cout<<"Tests passed!"<<endl;
}
