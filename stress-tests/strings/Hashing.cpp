#include "../utilities/template.h"

#include "../../content/strings/Hashing.h"

#include <sys/time.h>
int main() {
	assert((H(1)*2+1-3).get() == 0);

	rep(it,0,10000) {
		int n = rand() % 10;
		int alpha = rand() % 10 + 1;
		string s;
		rep(i,0,n) s += (char)('a' + rand() % alpha);
		HashInterval hi(s);
		set<string> strs;
		set<ull> hashes;

		// HashInterval
		rep(i,0,n) rep(j,i,n) {
			string sub = s.substr(i, j - i + 1);
			ull hash = hashString(sub).get();
			assert(hi.hashInterval(i, j).get() == hash);
			hashes.insert(hash);
			strs.insert(sub);
		}

		// getHashes
		rep(le,1,n+1) {
			auto ve = getHashes(s, le);
			assert(sz(ve) == n-le+1);
			rep(i,0,n-le+1) {
				assert(ve[i].get() == hi.hashInterval(i, i + le - 1).get());
			}
		}

		// No collisions
		assert(sz(strs) == sz(hashes));
	}
	cout<<"Tests passed!"<<endl;
}
