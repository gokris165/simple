from typing import List

def coinChange(coins: List[int], amount: int) -> int:

    # DP Bottom-up with loop iteration (faster)
    cache = [99999] * (amount + 1)
    cache[0] = 0

    for i in range(1, amount + 1):
        for coin in coins:
            if i - coin < 0:
                continue
            cache[i] = cache[i - coin] + 1 if cache[i - coin] + 1 < cache[i] else cache[i]
    return cache[amount] if cache[amount] < amount + 1 else -1

    # DP Top-down solution with recursion (slower)
    '''
    cache = {}
    cache[0] = 0

    def solver(target: int) -> int:
        if target in cache:
            return cache[target]
        if target < 0:
            return -1
        min_steps = 9999999
        for coin in reversed(coins):
            result = solver(target - coin)
            if result != -1:
                min_steps = min(min_steps, result + 1)
        cache[target] = min_steps
        return min_steps
    
    sol = solver(amount)
    return sol if sol <= amount else -1
    '''

'''
----------- TEST SUITE -----------
'''
test1 = [1,2,5]             # target = 11,      sol = 3
test2 = [2]                 # target = 3,       sol = -1
test3 = [1]                 # target = 0,       sol = 0
test4 = [2,5,10,1]          # target = 27,      sol = 4
test5 = [186,419,83,408]    # target = 6249,    sol = 20
test6 = [1, 10, 11]         # target = 20,      sol = 2
test_targets = [11,3,0,27,6249,20]
test_sols = [3,-1,0,4,20,2]

for i in range(6):
    func = locals()["test" + str(i + 1)]
    sol = coinChange(func, test_targets[i])
    status = "PASSED" if sol == test_sols[i] else "FAILED"
    print(f"Test {i + 1}: Expected = {test_sols[i]} \t| Actual = {sol} \t| Status = {status}")
