# BinaryDiff
List all the UInt32 differences between two binary files of the same size

Usage: BinaryDiff binaryFileA binaryFileB

Output Example
```
0x345c  0x0 -> 0x5 ( 0x5 )
0x34a4  0x0 -> 0x2 ( 0x2 )
0x37ec  0x0 -> 0x1 ( 0x1 )
0x3810  0x2 -> 0x3 ( 0x1 )
0x3814  0x2 -> 0x4 ( 0x2 )
0x382c  0x8 -> 0xd ( 0x5 )
0x383c  0x40ad86a6 -> 0x4191b72d ( 0xe43087 )
0x3844  0x41a9d51c -> 0x41c889df ( 0x1eb4c3 )
0x3848  0x441814c8 -> 0x446acab0 ( 0x52b5e8 )
0x3850  0x10101cd -> 0x1010101 ( 0xcc )
0x391c  0x3 -> 0x4 ( 0x1 )
```