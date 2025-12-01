# DNA of the Culprit
# Choose candidate with minimal Hamming distance to dna_scene, requiring diff <= k; return index or -1 if none.
from typing import List

def dna_match_index(dna_scene: str, candidates: List[str], k: int) -> int:
    best_idx = -1
    best_diff = 10**9
    for i, c in enumerate(candidates):
        if len(c) != len(dna_scene):
            continue  # assuming equal length; could extend to sliding match if needed
        diff = sum(1 for a,b in zip(dna_scene, c) if a!=b)
        if diff <= k and diff < best_diff:
            best_diff = diff
            best_idx = i
    return best_idx

if __name__ == "__main__":
    dna_scene = "ATGCC"
    candidates = ["ATGCA", "ATACC", "TTGCC"]
    print(dna_match_index(dna_scene, candidates, 1))  # 0
