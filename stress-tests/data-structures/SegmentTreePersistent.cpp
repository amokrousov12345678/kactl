#include "../utilities/template.h"

#include "../../content/data-structures/SegmentTreePersistent.h"

int main() {
	rep(n,1,10) {
		vector<Node*> roots{new Node(n)};
		vector<vi> v{vi(n, Node::unit)};
		rep(it,0,1000000) {
			int i = rand() % n, j = rand() % n;
			int x = rand() % (n+2);

			int rev = rand() % sz(roots);

			int r = rand() % 100;
			if (r < 30) {
				int ma = Node::unit;
				rep(k,i,j+1) ma = max(ma, v[rev][k]);
				auto expected = query(roots[rev], i,j);
				assert(ma == expected);
			}
			else {
				i = min(i, n-1);
				auto newRoot = update(roots[rev], i, x);
				roots.push_back(newRoot);
				v.push_back(v[rev]);
				v.back()[i] = x;
			}
		}
	}
	cout<<"Tests passed!"<<endl;
}
