/**
 * Author: Per Austrin, Simon Lindholm
 * Date: 2004-02-08
 * License: CC0
 * Description: Solves $A * x = b$ modulo prime mod. If there are multiple solutions, an arbitrary 
 * one is returned. Returns rank, or -1 if no solutions. Data in $A$ and $b$ is lost.
 * Time: O(n^2 m)
 * Status: bruteforce-tested mod 3 and 5 for n,m <= 3
 */
#pragma once

#include "../number-theory/ModPow.h"

int solveLinear(vector<vi>& A, vi& b, vi& x) {
	int n = sz(A), m = sz(x), rank = 0, br, bc;
	if (n) assert(sz(A[0]) == m);
	vi col(m); iota(all(col), 0);

	rep(i,0,n) {
		int v, bv = 0;
		rep(r,i,n) rep(c,i,m)
			if ((v = abs(A[r][c])) > bv)
				br = r, bc = c, bv = v;
		if (bv == 0) {
			rep(j,i,n) if (b[j]) return -1;
			break;
		}
		swap(A[i], A[br]);
		swap(b[i], b[br]);
		swap(col[i], col[bc]);
		rep(j,0,n) swap(A[j][i], A[j][bc]);
		bv = modpow(A[i][i], mod-2);
		rep(j,i+1,n) {
			int fac = A[j][i] * bv % mod;
			b[j] = (b[j] - 1ll * fac * b[i] % mod + mod) % mod;
			rep(k,i+1,m) A[j][k] = (A[j][k] - 1ll*fac*A[i][k] % mod + mod) % mod;
		}
		rank++;
	}

	x.assign(m, 0);
	for (int i = rank; i--;) {
		b[i] = (1ll*b[i]*modpow(A[i][i], mod-2)) % mod;
		x[col[i]] = b[i];
		rep(j,0,i) b[j] = (b[j] - 1ll*A[j][i] * b[i] % mod + mod) % mod;
	}
	return rank; // (multiple solutions if rank < m)
}