import bisect

def get_data():
    n, _ = map(int, input().split())
    starts = []
    ends = []
    for _ in range(n):
        start, end = map(int, input().split())
        starts.append(start)
        ends.append(end)
    points = list(map(int, input().split()))
    return starts, ends, points

def main():
    starts, ends, points = get_data()

    starts.sort()
    ends.sort()

    for point in points:
        cnt_ends_less_than_pnt = bisect.bisect_left(ends, point)
        cnt_strts_less_or_eq_to_pnt = bisect.bisect_right(starts, point)
        print(cnt_strts_less_or_eq_to_pnt - cnt_ends_less_than_pnt, end = " ")
        
if __name__ == "__main__":
    main()