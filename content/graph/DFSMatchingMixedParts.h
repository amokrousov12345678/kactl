/**
 * Author: Anton Mokrousov
 * Date: 2023-11-08
 * License: CC0
 * Source: test on https://informatics.msk.ru/mod/statements/view.php?id=26196
 * Description: Simple bipartite matching algorithm (without explicit parts
 * separation. Graph $g$ should be undirected and $match$ should be a vector
 * full of -1's with TOTAL size of graph. Returns the size of the matching.
 * $match[i]$ will be the match for vertex $i$ on the other side,
 * or $-1$ if it's not matched. (j=match[i] implies i=match[j] if j not -1)
 * Time: O(VE)
 * Usage: vi match(n, -1); dfsMatching(g, match);
 * Status: works
 */
#pragma once

int cc;
bool dfs(int v, const vector<vi>& g, vi& match, vi& used) {
	if (used[v] == cc) return false;
	used[v] = cc;
	for (auto& it: g[v]) {
		if (match[it]==-1 || dfs(match[it], g, match, used)) {
			match[v] = it; match[it] = v; return true;
		}
	}
	return false;
}
int dfsMatchingMixed(vector<vi>& g, vi& match) {
	int n = sz(g); assert(n==sz(match)); vi used(n, -1);
	cc = 0;
	for (int i=0;i<n;i++) {
		if (match[i]!=-1) continue;
		if (dfs(i, g, match, used)) cc++;
	}
	return cc;
}
