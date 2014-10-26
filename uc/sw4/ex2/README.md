# Exercise 2, SW2

Write a program that clears the carry-flag in the CCR register with a 
bit-mask.

# CCR register

Bit 	| 7        | 6 | 5 | 4          | 3         | 2        | 1    | 0
--------|----------|---|---|------------|-----------|----------|------|-------------
Name	| V        | - | - | H          | I         | N        | Z    | C
Meaning	| Overflow | - | - | Half carry | Interrupt | Negative | Zero | Carry/borrow
