def edit_distance(str1, str2):
    # столбцы отвечают за str2, строки - за str1
    # "str1 слева, str2 сверху"
    distances = [[100] * (len(str2) + 1) for _ in range(len(str1) + 1)]
    for i in range(len(str1) + 1):
        distances[i][0] = i
    for j in range(len(str2) + 1):
        distances[0][j] = j
    for i, ch1 in enumerate(str1, 1):
        for j, ch2 in enumerate(str2, 1):
            c = int(ch1 != ch2)
            distances[i][j] = min(distances[i - 1][j] + 1,
                                  distances[i][j - 1] + 1,
                                  distances[i - 1][j - 1] + c)
    return distances[len(str1)][len(str2)]

if __name__ == "__main__":
    str1, str2 = input(), input()
    print (edit_distance(str1, str2))