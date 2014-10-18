# Exercise 1, SW2

Write a program that takes two operands for an arithmetic operation from
the addresses $00C0 and $00C1. The result has to be written to the X 
register. Furthermore the flags VZNC have to be written to the LEDs as 
specified in the following table.

Register | Port | LED
---------|------|-----
V        | PTFO | B FL
Z        | PTF1 | R FL
V        | PTE7 | B FR
N        | PTF2 | R FR

 
