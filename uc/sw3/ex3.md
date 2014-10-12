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

Now we can read the data much efficently.

Address | Mnemonic | OpCode | Operand 1 | Operand 2 | Comment
--------|----------|--------|-----------|-----------|--------
0x0960  |          |        |           |           |     
0x0961	|          |        |           |           |
0x0962  |          |        |           |           |
0x0963  |          |        |           |           |
0x0964  |          |        |           |           |
0x0965  |          |        |           |           |
0x0966  |          |        |           |           |
0x0967  |          |        |           |           |
0x0968  |          |        |           |           |
0x0969  | LDA      | 0xA6   |           |           | Load value to accumulator 
0x096A  |          |        | 0x0F      |           |     value = 0x0F (15d)
0x096B  | STA      | 0xB7   |           |           | Store accumulator to memory address
0x096C  |          |        | 0x0B      |           | ... address = 0x0B
0x096D  | LDA      | 0xA6   |           |           | Load value to accumulator
0x096E  |          |        | 0x80      |           | ... value = 0x80 (128d)
0x096F  | STA      | 0xB7   |           |           | Store accumulator to memory address
0x0970  |          |        | 0x09      |           | ... address = 0x09
0x0971  | LDA      | 0xA6   |           |           | Load value to accumulator
0x0972  |          |        | 0xEF      |           | ... value = 0xEF (239d)
0x0973  | STA      | 0xB7   |           |           | Store accumulator to memory address
0x0974  |          |        | 0xC1      |           | ... address = 0xC1
0x0975  | STA      | 0xB7   |           |           | Store accumulator to memory address
0x0976  |          |        | 0x0A      |           | ... address = 0x0A
0x0977  | LSLA     | 0x48   |           |           | Shift accumulator bitwise left
0x0978  | LSLA     | 0x48   |           |           | Shift accumulator bitwise left
0x0979  | LSLA     | 0x48   |           |           | Shift accumulator bitwise left
0x097A  | LSLA     |        |           |           | Shift accumulator bitwise left
0x097B  | STA      | 0xB7   |           |           | Store accumulator to memory address
0x097C  |          |        | 0x08      |           | ... address = 0x08
0x097D  | LDX      | 0xAE   |           |           | Load index register X from memory address
0x097E  |          |        | 0xFF      |           | ... address = 0xFF
0x097F  | LDA      | 0xA6   |           |           | Load value to accumulator
0x0980  |          |        | 0xFF      |           | ... value = 0xFF
0x0981  | MOV      | 0x4E   |           |           | Move value from address 1 to address 2
0x0982  |          |        | 0x06      |           | ... address 1 = 0x06
0x0983  |          |        | 0x02      |           | ... address 2 = 0x02
0x0984  | MOV      | 0x4E   |           |           | Move value from address 1 to address 2
0x0985  |          |        | 0x06      |           | ... address 1 = 0x06
0x0986  |          |        | 0x02      |           | ... address 2 = 0x02
0x0987  | MOV      | 0x4E   |           |           | Move value from address 1 to address 2
0x0988  |          |        | 0x06      |           | ... address 1 = 0x06
0x0989  |          |        | 0x02      |           | ... address 2 = 0x02
0x098A  | MOV      | 0x4E   |           |           | Move value from address 1 to address 2
0x098B  |          |        | 0x06      |           | ... address 1 = 0x06
0x098C  |          |        | 0x02      |           | ... address 2 = 0x02
0x098D  | DECX     | 0x5A   |           |           |
0x098E  | BNE      | 0x26   |           |           |
0x098F  |          |        | 0xF1      |           |
0x0990  | LDX      | 0xAE   |           |           |
0x0991  | STX      | 0xFF   |           |           |
0x0992  | DBNZA    | 0x4B   |           |           |
0x0993  |          |        | 0xED      |           |
0x0994  | LDA      | 0xB6   |           |           |
0x0995  |          |        | 0xC1      |           |
0x0996  | ROLA     | 0x49   |           |           |
0x0997  | STA      | 0xB7   |           |           |
0x0998  |          |        | 0xC1      |           |
0x0999  | STA      | 0xB7   |           |           |
0x099A  |          |        | 0x0A      |           |
0x099B  | LSLA     | 0x48   |           |           |
0x099C  | LSLA     | 0x48   |           |           |
0x099D  | LSLA     | 0x48   |           |           |
0x099E  | LSLA     | 0x48   |           |           |
0x099F  | STA      | 0xB7   |           |           |
0x09A0  |          |        | 0x08      |           |
0x09A1  | BRA      | 0x20   |           |           |
0x09A2  |          |        | 0xDA      |           |
0x09A3  |          |        |           |           |
0x09A4  |          |        |           |           |
0x09A5  |          |        |           |           |
0x09A6  |          |        |           |           |
0x09A7  |          |        |           |           |
0x09A8  |          |        |           |           |
0x09A9  |          |        |           |           |
0x09AA  |          |        |           |           |
0x09AB  |          |        |           |           |
0x09AC  |          |        |           |           |
0x09AD  |          |        |           |           |
0x09AE  |          |        |           |           |
0x09AF  |          |        |           |           |
