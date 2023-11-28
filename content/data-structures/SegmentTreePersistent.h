/**
 * Author: Anton Mokrousov
 * Date: 2023-11-08
 * License: CC0
 * Source: folklore
 * Description: Zero-indexed persistent max-tree. Indexes can be up to $10^9$ thanks to lazy construction
 * Remove v = new Node(*v) to remove persistence
 * Time: O(\log N)
 * Status: stress-tested
 */
#pragma once

typedef int T;
struct Node {
	static constexpr T unit = INT_MIN;
	T f(T a, T b) { return max(a, b); } // (any associative fn)
	Node *l = 0, *r = 0; T val = unit; int lo, hi;
	Node(int sz): Node(0, sz-1) {}
	Node(int lo, int hi): lo(lo), hi(hi) {}
};

Node* update(Node* v, int pos, T val) {
	v = new Node(*v);
	if (v->lo == v->hi) {
		v->val = val; return v;
	}
	int m = (v->lo + v->hi)/2;
	if (!v->l) v->l = new Node(v->lo, m);
	if (!v->r) v->r = new Node(m + 1, v->hi);
	if (pos <= m) {
		v->l = update(v->l, pos, val);
	} else {
		v->r = update(v->r, pos, val);
	}
	v->val = v->f(v->l->val, v->r->val);
	return v;
}
T query(Node* v, int l, int r) {
	if (v->lo > r || v->hi < l) return v->unit;
	if (l <= v->lo && v->hi <= r) return v->val;
	int m = (v->lo + v->hi)/2;
	if (!v->l) v->l = new Node(v->lo, m);
	if (!v->r) v->r = new Node(m + 1, v->hi);
	return v->f(query(v->l, l, r), query(v->r, l, r));
}
