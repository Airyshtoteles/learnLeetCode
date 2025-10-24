# LC 23 — Merge k Sorted Lists
# Min-heap approach
from typing import List, Optional
import heapq

class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next
    def __repr__(self):
        return f"{self.val}->{self.next!r}"

class Solution:
    def mergeKLists(self, lists: List[Optional[ListNode]]) -> Optional[ListNode]:
        pq = []
        seq = 0
        for node in lists:
            if node:
                heapq.heappush(pq, (node.val, seq, node))
                seq += 1
        dummy = ListNode()
        cur = dummy
        while pq:
            _, _, node = heapq.heappop(pq)
            cur.next = node
            cur = cur.next
            if node.next:
                heapq.heappush(pq, (node.next.val, seq, node.next))
                seq += 1
        return dummy.next

if __name__ == "__main__":
    # Example: [[1,4,5],[1,3,4],[2,6]] -> [1,1,2,3,4,4,5,6]
    def build(lst):
        head = cur = ListNode(0)
        for v in lst:
            cur.next = ListNode(v)
            cur = cur.next
        return head.next
    lists = [build([1,4,5]), build([1,3,4]), build([2,6])]
    ans = Solution().mergeKLists(lists)
    out = []
    while ans:
        out.append(ans.val)
        ans = ans.next
    print(out)  # [1,1,2,3,4,4,5,6]
