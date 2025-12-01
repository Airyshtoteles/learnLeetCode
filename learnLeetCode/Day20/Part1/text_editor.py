# LC 2296 — Design a Text Editor
# Two stacks: left (text left of cursor), right (text right of cursor)

class TextEditor:
    def __init__(self):
        self.left = []   # list of chars
        self.right = []  # list of chars (top is next char to the right)

    def addText(self, text: str) -> None:
        for ch in text:
            self.left.append(ch)

    def deleteText(self, k: int) -> int:
        cnt = 0
        while self.left and k > 0:
            self.left.pop()
            k -= 1
            cnt += 1
        return cnt

    def _last10(self) -> str:
        # return up to last 10 chars on the left side of cursor
        L = len(self.left)
        start = max(0, L - 10)
        return ''.join(self.left[start:L])

    def cursorLeft(self, k: int) -> str:
        while k > 0 and self.left:
            self.right.append(self.left.pop())
            k -= 1
        return self._last10()

    def cursorRight(self, k: int) -> str:
        while k > 0 and self.right:
            self.left.append(self.right.pop())
            k -= 1
        return self._last10()

if __name__ == "__main__":
    ed = TextEditor()
    ed.addText("leetcode")
    print(ed.deleteText(4))       # 4
    ed.addText("practice")
    print(ed.cursorRight(3))      # etpractice
    print(ed.cursorLeft(8))       # leet
    print(ed.deleteText(10))      # 4
