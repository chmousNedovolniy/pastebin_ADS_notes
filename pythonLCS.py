def find_lcs(a, b):
    # array of size len(a) + 1, len(b) + 1
    lcs = [[0] * (len(b) + 1) for i in range(len(a) + 1)]
    for i in range(1, len(a) + 1):
        for j in range(1, len(b) + 1):
            if a[i - 1] == b[j - 1]:
                lcs[i][j] = lcs[i - 1][j - 1] + 1
            else:
                lcs[i][j] = max(lcs[i - 1][j], lcs[i][j - 1])
    print_lcs(a, b, lcs)


def print_lcs(a, b, lcs):
    i, j = len(a), len(b)
    answer = ''
    while i > 0 and j > 0:
        if lcs[i][j] == lcs[i - 1][j - 1] + 1:
            answer = a[i - 1] + answer
            i -= 1
            j -= 1
        elif lcs[i][j] == lcs[i - 1][j]:
            i -= 1
        else:
            j -= 1
    for row in lcs:
        for elem in row:
            print(elem, end=' ')
        print()
    print('Lenght of LCS is', lcs[len(a)][len(b)])
    print(answer)


a = 'abcdefgh'
b = 'abdfghi'
find_lcs(a, b)