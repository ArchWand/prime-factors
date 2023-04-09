#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
#define DEBUG 1
#define n 50
#define w 7
/* W table
 *  5: < 29
 *  7: < 209
 *  9: < 2309
 * 11: < 30029
 * 13: < 510509
 * 15: < 9699689
 * 17: < 223092869
 */
/* n: w
 *        20: 5
 *        50: 7
 *       100: 7
 *      1000: 9
 *   1000000: 15
 *  10000000: 17
 *  30000000: 17
 * 100000000: 17
 */


ull* factors;

enum IND { PROD, FACT1, EXP1, FACT2 };

void update_factors(ull i, ull d) {
	if (d == 1) return;

	// Update factors for all multiples of d
	for (ull j = i; j <= n; j += i) {
		ull* f = factors + j*w;
		f[PROD] *= d;

		if (f[FACT1] == 0) { // First factor
			f[FACT1] = d;
			f[EXP1] = 1;
			continue;
		}

		// Find the factor and increment its exponent
		ull k = FACT1;
		for (; f[k] != 0; k += 2) {
			if (f[k] == d) {
				f[k+1]++;
				break;
			}
		}
		if (f[k] == 0) { // New factor
			f[k] = d;
			f[k+1] = 1;
		}
	}
}

void print_factor(ull* f, ull num) {
	if (f[EXP1] == 1 && f[FACT2] == 0) { // Prime
		cout << num << " is prime\n";
	} else {
		cout << num << " = ";
		cout << f[FACT1];
		if (f[EXP1] > 1) { cout << "^" << f[EXP1]; }

		for (ull i = FACT2; i < w; i += 2) {
			if (f[i] == 0) break;
			cout << " * " << f[i];
			if (f[i+1] > 1) { cout << "^" << f[i+1]; }
		}
		cout << "\n";
	}
}

int main() {
	// Initialize factors
	factors = new ull[(n+1)*w];
	for (ull i = 0; i < (n+1)*w; i++) {
		factors[i] = 0;
	}
	for (ull i = 0; i < (n+1)*w; i += w) {
		factors[i] = 1;
	}

	// Find and print factors
	for (ull i = 2; i <= n; i++) {
		ull d = i / factors[i*w];
		update_factors(i, d);
		print_factor(factors+i*w, i);

	}

	if (DEBUG) {
		// Length of n as a string
		int len = 0;
		for (ull i = n; i > 0; i /= 10, len++);

		// The length of the maximum exponent
		int log = 0;
		int exp_len = 0;
		for (ull i = n; i > 0; i /= 2, log++);
		for (int i = log; i > 0; i /= 10, exp_len++);

		for (ull i = 2; i <= n; i++) {
			cout <<   setw(len) << right << i << ": ";
			cout << setw(len+2) << right << factors[i*w];

			for (ull j = FACT1; j < w; j += 2) {
				cout <<     setw(len+2) << right << factors[i*w+j];
				cout << setw(exp_len+2) << right << factors[i*w+j+1];
			}
			cout << endl;
		}
	}
}
