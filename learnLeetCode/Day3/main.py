from two_sum_ii import two_sum
from remove_duplicates_sorted_array import remove_duplicates
from move_zeroes import move_zeroes
from container_with_most_water import max_area


def demo_two_sum():
    print("Two Sum II:")
    numbers = [2, 7, 11, 15]
    target = 9
    print(" input:", numbers, "target:", target)
    print(" output:", two_sum(numbers, target))


def demo_remove_duplicates():
    print("\nRemove Duplicates from Sorted Array:")
    nums = [0, 0, 1, 1, 1, 2, 2, 3, 3, 4]
    print(" input:", nums)
    k = remove_duplicates(nums)
    print(" output k:", k, ", nums[:k] =", nums[:k])


def demo_move_zeroes():
    print("\nMove Zeroes:")
    nums = [0, 1, 0, 3, 12]
    print(" input:", nums)
    move_zeroes(nums)
    print(" output:", nums)


def demo_container_with_most_water():
    print("\nContainer With Most Water (Bonus):")
    height = [1, 8, 6, 2, 5, 4, 8, 3, 7]
    print(" input:", height)
    print(" output max area:", max_area(height))


if __name__ == "__main__":
    demo_two_sum()
    demo_remove_duplicates()
    demo_move_zeroes()
    demo_container_with_most_water()
