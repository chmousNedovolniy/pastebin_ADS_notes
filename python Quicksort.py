def hoare_partition(nums, left, right):
    pivot = nums[(left + right) // 2]
    i, j = left, right
    while i <= j:
        while nums[i] < pivot:
            i += 1
        while nums[j] > pivot:
            j -= 1
        if i >= j:
            break
        nums[i], nums[j] = nums[j], nums[i]
        i += 1
        j -= 1
    return j


def lomuto_partition(nums, left, right):
    pivot = nums[right]
    i = left - 1
    for j in range(left, right, 1):
        if nums[j] <= pivot:
            i += 1
            nums[i], nums[j] = nums[j], nums[i]
    nums[i + 1], nums[right] = nums[right], nums[i + 1]
    return i + 1


def quicksort(nums, left, right):
    if left < right:
        # Lomuto option.
        # partition_pos = lomuto_partition(nums, left, right)
        # quicksort(nums, left, partition_pos - 1)

        # Hoare option.
        partition_pos = hoare_partition(nums, left, right)
        quicksort(nums, left, partition_pos)

        quicksort(nums, partition_pos + 1, right)


n = int(input())
numbers = list(map(int, input().split()))
quicksort(numbers, 0, len(numbers) - 1)
print(*numbers)