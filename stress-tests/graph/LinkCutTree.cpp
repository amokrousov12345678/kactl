#include "../utilities/template.h"

#include "../../content/graph/LinkCutTree.h"
#include "../../content/data-structures/UnionFind.h"

void dfs(const vector<vi>& g, vi& pars, vi& roots, int v, int par, int root) {
	if (roots[v] != -1) return;
	roots[v] = root;
	pars[v] = par;
	for (auto& it: g[v]) {
		dfs(g, pars, roots, it, v, root);
	}
}

int main() {
	srand(2);
	LinkCut lczero(0);
	rep(it,0,10000) {
		int N = rand() % 20 + 1;
		LinkCut lc(N);
		UF uf(N);
		vector<pii> edges;
		rep(it2,0,1000) {
			int v = (rand() >> 4) & 3;
			if (v == 0 && !edges.empty()) { // remove
				int r = (rand() >> 4) % sz(edges);
				pii ed = edges[r];
				swap(edges[r], edges.back());
				edges.pop_back();
				if (rand() & 16)
					lc.cut(ed.first, ed.second);
				else
					lc.cut(ed.second, ed.first);
			} else {
				int a = (rand() >> 4) % N;
				int b = (rand() >> 4) % N;
				uf.e.assign(N, -1);
				for(auto &ed: edges) uf.join(ed.first, ed.second);
				bool c = uf.sameSet(a, b);
				if (!c && v != 1) {
					lc.link(a, b);
					edges.emplace_back(a, b);
				} else {
					assert(lc.connected(a, b) == c);
				}
			}
			vector<vi> g(N);
			vi par(N, -1), root(N, -1);
			int newRoot = (rand() >> 4) % N;
			lc.makeRoot(newRoot);
			for (auto &ed: edges) {
				g[ed.first].push_back(ed.second);
				g[ed.second].push_back(ed.first);
			}
			dfs(g, par, root, newRoot, -1, newRoot);
			rep(i,0,N) {
				if (root[i] == -1) {
					assert(lc.getRoot(i) != newRoot);
					continue;
				}
				assert(lc.getRoot(i) == newRoot);
				assert(lc.getPar(i) == par[i]);
			}
		}
	}

	cout<<"Tests passed!"<<endl;
}
