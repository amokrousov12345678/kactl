/**
 * Author: Anton Mokrousov
 * Date: 2023-11-07
 * License: CC0
 * Source: me
 * Description: Segment tree with ability to assign on large intervals, and compute max of intervals.
 * Can be changed to other things (f, upd (how to apply def. update), combUpd (apply def. update from up))
 * Time: O(\log N).
 * Usage: SegTree st(vector<int>(15,0));
 * Status: stress-tested a bit
 */
#pragma once

const int inf = 1e9;
struct SegTree {
	using T = int; using PT = int;
	int n; vector<T> mas; vector<PT> def;
	const T unit = -inf;
	const PT punit = (-inf-1); //neutral for pushed op

	T upd(T val, PT push) {
		if (push!=punit) return push; return val;
	}
	T f(T l, T r) { return max(l,r); }
	PT stkUpd(PT cur, PT fromUp) {
		if (fromUp!=punit) return fromUp; return cur;
	}

	void build(const vector<T>& vals, int v, int l, int r) {
		if (l==r) { mas[v] = vals[l]; def[v] = punit; return; }
		int m = (l+r)/2;
		build(vals, 2*v, l, m); build(vals, 2*v+1, m+1, r);
		mas[v] = f(upd(mas[2*v], def[2*v]),
			upd(mas[2*v+1], def[2*v+1]));
		def[v] = punit;
	}
	void push(int v) {
		def[2*v] = stkUpd(def[2*v], def[v]);
		def[2*v+1] = stkUpd(def[2*v+1], def[v]); def[v] = punit;
	}
	void update(int rqL, int rqR, PT val, int v, int l, int r) {
		if (l > rqR || r < rqL) return;
		if (rqL <= l && r <= rqR) {
			def[v] = stkUpd(def[v], val); return;
		}
		push(v); int m = (l+r)/2;
		update(rqL, rqR, val, 2*v, l, m);
		update(rqL, rqR, val, 2*v+1, m+1, r);
		mas[v] = f(upd(mas[2*v], def[2*v]),
			upd(mas[2*v+1], def[2*v+1]));
	}
	T query(int rqL, int rqR, int v, int l, int r) {
		if (l > rqR || r < rqL) return unit;
		if (rqL <= l && r <= rqR) return upd(mas[v], def[v]);
		push(v); int m = (l+r)/2;
		auto ans = f(query(rqL, rqR, 2*v, l, m),
			query(rqL, rqR, 2*v+1, m+1, r));
		mas[v] = f(upd(mas[2*v], def[2*v]),
			upd(mas[2*v+1], def[2*v+1]));
		return ans;
	}

	SegTree(int n): SegTree(vector<T>(n, unit)) {}
	SegTree(const vector<T>& vals) : n(sz(vals)), mas(4*n, unit), def(4*n, punit) {
		build(vals, 1, 0, sz(vals)-1);
	}
	void update(int l, int r, PT val) {
		update(l, r, val, 1, 0, n-1);
	}
	T query(int l, int r) { return query(l, r, 1, 0, n-1); }
};