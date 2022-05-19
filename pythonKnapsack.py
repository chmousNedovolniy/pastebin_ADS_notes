class Item:
    def __init__(self, name, weight, value):
        self.name = name
        self.weight = weight
        self.value = value


def unbounded_knapsacks(w, n, items, knapsacks):
    ans = [0] * (w + 1)
    for x in range(1, w + 1):
        for item in range(1, n + 1):
            if items[item - 1].weight <= x:
                if ans[x - items[item - 1].weight] + items[item - 1].value > ans[x]:
                    ans[x] = ans[x - items[item - 1].weight] + items[item - 1].value
                    knapsacks[x] = list(knapsacks[x - items[item - 1].weight])
                    knapsacks[x].append(items[item - 1])

    for x in range(0, w + 1):
        print('weight is', x, end=' ')
        print('value is', ans[x])
        print('items:', end=' ')
        if len(knapsacks[x]) == 0:
            print('empty', end='')
        for item in knapsacks[x]:
            print(item.name, end=' ')
        print()


w = 3
n = 3
items = [Item('heart', 1, 1), Item('diamond', 2, 4), Item('cross', 3, 6)]
knapsacks = [list() for x in range(w + 1)]
unbounded_knapsacks(w, n, items, knapsacks)
