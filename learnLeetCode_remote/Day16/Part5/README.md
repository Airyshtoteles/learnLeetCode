# Day 16 — Part 5: Count All Valid Pickup and Delivery Options (LC 1359)

Combinatorics formula:
- For each i from 1..n, multiply by i (ways to insert the i-th pickup among i blocks)
- Then multiply by (2i-1) (ways to place the delivery after its pickup)
- Take modulo 1e9+7.

Files:
- `pickup_delivery.py`
- `pickup_delivery.cpp`

Try:
```
python pickup_delivery.py
```
