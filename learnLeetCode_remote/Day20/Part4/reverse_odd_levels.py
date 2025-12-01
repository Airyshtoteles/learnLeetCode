# LC 2415 — Reverse Odd Levels of Binary Tree
from collections import deque
from typing import Optional

class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

def reverseOddLevels(root: Optional[TreeNode]) -> Optional[TreeNode]:
    if not root:
        return root
    q = deque([root])
    level = 0
    while q:
        sz = len(q)
        nodes = []
        for _ in range(sz):
            node = q.popleft()
            nodes.append(node)
            if node.left: q.append(node.left)
            if node.right: q.append(node.right)
        if level % 2 == 1:
            i, j = 0, len(nodes)-1
            while i < j:
                nodes[i].val, nodes[j].val = nodes[j].val, nodes[i].val
                i += 1; j -= 1
        level += 1
    return root

if __name__ == "__main__":
    # Example: [2,3,5,8,13,21,34] -> [2,5,3,8,13,21,34]
    n8=TreeNode(8); n13=TreeNode(13); n21=TreeNode(21); n34=TreeNode(34)
    n3=TreeNode(3, n8, n13); n5=TreeNode(5, n21, n34)
    root=TreeNode(2, n3, n5)
    reverseOddLevels(root)
    print(root.left.val, root.right.val)  # 5 3
