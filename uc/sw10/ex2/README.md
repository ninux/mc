# NEC Protocoll

# Measured "S"

Segment	| Byte 1	| Byte 2	| Hex
--------|---------------|---------------|----
start	| -		| -		|
address	| 0110 0001	| 1101 1100	| 0x61DC
data	| 1000 0000	| -		| 0x80
!data	| 0111 1111	| -		| 0x7F

The bits are sent from LSB to MSB, LowByte to HighByte.

For further information about the NEC protocol, see 
[this](http://www.sbprojects.com/knowledge/ir/nec.php) summary.
