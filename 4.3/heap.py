class Heap:

    _heap = []

    def insert(self, x):
        self._heap.append(x)
        x_pos = len(self._heap) - 1
        while x_pos:
            parent_pos = (x_pos-1)//2
            if self._heap[x_pos] <= self._heap[parent_pos]:
                break
            self._heap[x_pos], self._heap[parent_pos] = self._heap[parent_pos], self._heap[x_pos]
            x_pos = parent_pos

    def extract_max(self):
        max = self._heap[0]
        last_leaf = self._heap.pop()
        if(not self._heap):
            return max
        self._heap[0] = last_leaf
        pos = 0

        while pos*2+2 < len(self._heap):
            max_child_pos = pos*2+1 if self._heap[pos*2+1] > self._heap[pos*2+2] else pos*2+2
            if self._heap[pos] >= self._heap[max_child_pos]:
                break
            self._heap[pos], self._heap[max_child_pos] = self._heap[max_child_pos], self._heap[pos]
            pos = max_child_pos

        if (pos*2+1 < len(self._heap)):
            child_pos = pos*2+1
            if self._heap[pos] < self._heap[child_pos]:
                self._heap[pos], self._heap[child_pos] = self._heap[child_pos], self._heap[pos]
        return max

heap = Heap()
for _ in range(int(input())):
    raw = input().split()
    if raw[0] == 'Insert':
        heap.insert(int(raw[1]))
    elif raw[0] == 'ExtractMax':
        print(heap.extract_max())