import itertools
import math

trials = 1000

def prime_sieve(n):
    nums = [ True ] * (n+1)
    nums[0] = nums[1] = nums[2] = False

    yield 2
    for i in range(4, n+1, 2):
        nums[i] = False

    for (i, is_prime) in enumerate(nums):
        if is_prime:
            yield i
            for n in range(i*i, n+1, 2*i):
                nums[n] = False

max_exp = math.ceil(math.log(trials, 2))
primes = [ 1 ] * (max_exp-1)
primes.extend(list(prime_sieve(trials)))
for c in itertools.combinations(primes, max_exp):
    print(c)
