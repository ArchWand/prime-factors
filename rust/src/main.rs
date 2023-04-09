use std::collections::BTreeSet;
use std::collections::BTreeMap;
use std::env;

fn main() {
    // Get the first argument
    let n = env::args().nth(1).unwrap()
        .parse::<usize>().unwrap();

    // DP cache
    let mut cache = vec![BTreeMap::new(); n+1];

    // Prime sieve
    let primes = prime_sieve(n);

    // Loop through and store the results
    for i in 2..n+1 {
        print_factors(i, &factorization(&mut cache, &primes, i));
    }
}

// Function that returns a hashset of the primes less than n
fn prime_sieve(n: usize) -> BTreeSet<usize> {
    let mut sieve = vec![true; n];
    let mut primes = BTreeSet::new();
    for i in 2..n {
        if sieve[i] {
            for j in (i*i..n).step_by(i) {
                sieve[j] = false;
            }
            primes.insert(i);
        }
    }
    primes
}

fn factorization(cache: &mut Vec<BTreeMap<usize, usize>>, primes: &BTreeSet<usize>,
                 n: usize) -> BTreeMap<usize, usize> {
    // Dynamic programming
    if cache[n] != BTreeMap::new() {
        return cache[n].clone();
    }

    // Base case: n is prime
    if primes.contains(&n) {
        let mut set = BTreeMap::new();
        set.insert(n, 1);
        cache[n] = set.clone();
        return set;
    }

    // Recursive case: n is not prime
    // We loop through all the primes until we find the first one that divides n
    for p in primes {
        if n % p != 0 { continue; }

        // We divide n by p and recurse
        let mut set = factorization(cache, &primes, n/p);
        *set.entry(*p).or_insert(0) += 1;
        cache[n] = set.clone();
        return set;
    }

    cache[n].clone()
}

fn print_factors(n: usize, factors: &BTreeMap<usize, usize>) {
    // Handle primes
    if factors.len() == 1 && factors.values().nth(0).unwrap() == &1 {
        println!("{} is prime", n);
        return;
    }

    let mut s = String::new();
    for (p, e) in factors {
        if e == &1 {
            s.push_str(&format!("{} * ", p));
        } else {
            s.push_str(&format!("{}^{} * ", p, e));
        }
    }
    // Trim the last " * "
    s.truncate(s.len() - 3);

    println!("{} = {}", n, s);
}
