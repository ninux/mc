# Exercise 3

The following code has to be reassembled with the HCS08 instruction set.

    $0960 -------- -------- --A60FB7 0BA680B7
    $0970 09A6EFB7 C1B70A48 484848B7 08AEFFA6
    $0980 FF4E0602 4E06024E 06024E06 025A26F1
    $0990 AEFF4BED B6C149B7 C1B70A48 484848B7
    $09A0 0820DA-- -------- -------- -------- 

# Solution

As a first step, the table can be ordered into a clear address
table, so that every byte is addressed correctly.

Address | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | A | B | C | D | E | F  
--------|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---
$0960   | --| --| --| --| --| --| --| --| --| A6| 0F| B7| 0B| A6| 80| B7
$0970   | 09| A6| EF| B7| C1| B7| 0A| 48| 48| 48| 48| B7| 08| AE| FF| A6
$0980 	| FF| 4E| 06| 02| 4E| 06| 02| 4E| 06| 02| 4E| 06| 02| 5A| 26| F1
$0990   | AE| FF| 4B| ED| B6| C1| 49| B7| C1| B7| 0A| 48| 48| 48| 48| B7
$09A0   | 08| 20| DA| --| --| --| --| --| --| --| --| --| --| --| --| --



Address | Mnemonic | OpCode | Operand 1 | Operand 2 | Comment
--------|----------|--------|-----------|-----------|--------
0x
