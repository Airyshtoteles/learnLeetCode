from typing import Optional, Dict

class TreeNode:
    def __init__(self, val: int = 0, left: 'Optional[TreeNode]' = None, right: 'Optional[TreeNode]' = None):
        self.val = val
        self.left = left
        self.right = right


def path_sum_count(root: Optional[TreeNode], target: int) -> int:
    def dfs(node: Optional[TreeNode], cur_sum: int, cnt: Dict[int, int]) -> int:
        if not node:
            return 0
        cur_sum += node.val
        res = cnt.get(cur_sum - target, 0)
        cnt[cur_sum] = cnt.get(cur_sum, 0) + 1
        res += dfs(node.left, cur_sum, cnt)
        res += dfs(node.right, cur_sum, cnt)
        cnt[cur_sum] -= 1
        if cnt[cur_sum] == 0:
            del cnt[cur_sum]
        return res

    cnt = {0: 1}
    return dfs(root, 0, cnt)


if __name__ == "__main__":
    # Example: [10,5,-3,3,2,null,11,3,-2,null,1], target = 8 => 3
    root = TreeNode(10,
        TreeNode(5,
            TreeNode(3, TreeNode(3), TreeNode(-2)),
            TreeNode(2, None, TreeNode(1))
        ),
        TreeNode(-3, None, TreeNode(11))
    )
    print(path_sum_count(root, 8))  # 3
