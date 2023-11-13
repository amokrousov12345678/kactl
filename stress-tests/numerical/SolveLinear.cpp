#include "../utilities/template.h"

const int nmax = 4, mmax = 4, nmmax = 10;

#include "../../content/numerical/SolveLinearModPrime.h"
#include "../../content/numerical/MatrixInverse-mod.h"

template<class F>
void rec(int i, int j, vector<vi>& A, F f) {
	if (i == sz(A)) {
		f();
	}
	else if (j == sz(A[i])) {
		rec(i+1, 0, A, f);
	}
	else {
		rep(v,0,mod) {
			A[i][j] = v;
			rec(i, j+1, A, f);
		}
	}
}

template<class F>
void rec2(int i, vi& A, F f) {
	if (i == sz(A)) f();
	else {
		rep(v,0,mod) {
			A[i] = v;
			rec2(i+1, A, f);
		}
	}
}

int main() {
	rep(n,0,nmax+1) rep(m,0,mmax+1) {
		int nm = n*m;
		if (nm > nmmax) continue;
		vector<vi> A(n, vi(m));
		vi b(n), x(m), theX(m);
		rec(0, 0, A, [&]() {
			rec2(0, b, [&]() {
				int sols = 0;
				rec2(0, x, [&]() {
					rep(i,0,n) {
						int v = 0;
						rep(j,0,m) v += A[i][j] * x[j];
						if (v % mod != b[i]) return;
					}
					sols++;
					if (sols == 1) theX = x;
				});
				vector<vi> A2 = A;
				vi x2 = x, b2 = b;
				int r = solveLinear(A2, b2, x2);
				if (sols == 0) assert(r == -1);
				else if (sols == 1) {
					assert(r == m);
					if (n == m) {
						A2 = A;
						auto r2 = matInv(A2);
						assert(r2 == n);
						rep(i,0,n) {
							rep(j,0,n) {
								assert(A2[i][j] >= 0 && A2[i][j] < mod);
							}
						}
						rep(i,0,n) {
							rep(j,0,n) {
								int acc = 0;
								rep(k, 0, n) {
									acc += (1ll*A[i][k]*A2[k][j]) % mod;
									acc %= mod;
								}
								if (i==j) {
									assert(acc==1);
								} else {
									assert(acc==0);
								}
							}
						}
					}
				}
				else assert(r < m);
				if (sols == 1) assert(x2 == theX);
			});
		});
	}
	cout<<"Tests passed!"<<endl;
}
