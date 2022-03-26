W, n = map(int, input().split())
gold = list(map(int, input().split()))

full_bag = [0]*(W+1)
full_bag[0] = 1

result = 0

for gold_weight in gold:
    for capacity in range(W, gold - 1, -1):
        if full_bag[capacity - gold_weight]:
            full_bag[capacity] = 1
            result = max(capacity, result)
print(result)