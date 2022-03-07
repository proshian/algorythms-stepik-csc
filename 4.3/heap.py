def insert(x, heap):
    heap.append(x)
    x_pos = len(heap) - 1
    while x_pos:
        parent_pos = (x_pos-1)//2
        if heap[x_pos] <= heap[parent_pos]:
            break
        heap[x_pos], heap[parent_pos] = heap[parent_pos], heap[x_pos]
        x_pos = parent_pos

def extract_max(heap):
    max = heap[0]
    last_leaf = heap.pop()
    if(not heap):
        return max
    heap[0] = last_leaf
    pos = 0

    while pos*2+2 < len(heap):
        max_child_pos = pos*2+1 if heap[pos*2+1] > heap[pos*2+2] else pos*2+2
        if heap[pos] >= heap[max_child_pos]:
            break
        heap[pos], heap[max_child_pos] = heap[max_child_pos], heap[pos]
        pos = max_child_pos

    if (pos*2+1 < len(heap)):
        child_pos = pos*2+1
        if heap[pos] < heap[child_pos]:
            heap[pos], heap[child_pos] = heap[child_pos], heap[pos]
    return max

heap = []
for _ in range(int(input())):
    raw = input().split()
    if raw[0] == 'Insert':
        insert(int(raw[1]), heap)
    elif raw[0] == 'ExtractMax':
        print(extract_max(heap))