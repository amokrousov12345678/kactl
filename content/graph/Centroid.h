/**
 * Author: Somebody
 * Date: Somewhen
 * License: CC0
 * Description: Given tree at $g$ build centroid decomposition tree at $par$ ($par_{root} = -1$)
 * Time: $O(|V| \log |V|)$
 * Status: Tested at CodeForces
 * Usage: memset(level, -1, sizeof(level)); build(0, n, 0, -1);
 */
#pragma once

const int maxn = 1e5; vector<int> g[maxn];
int level[maxn], par[maxn];
int dfs(int v, int size, int& center, int p = -1) {
    int sum = 1; for (auto& it: g[v])
        if (level[it]==-1 && it!=p)
            sum += dfs(it, size, center, v);
    if (center == -1 && (2*sum >= size || p==-1)) center = v;
    return sum;
}
void build(int v, int size, int depth, int last) {
    int center = -1; dfs(v, size, center);
    level[center] = depth; par[center] = last; //do smth
    for (auto& it: g[center]) if (level[it] == -1)
        build(it, size/2, depth+1, center);
}//Second centroid: centroid child, s. t. 2*sz[ch] == n