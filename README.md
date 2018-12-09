# wreckme2

writeup for wreckme (2017):
```
gdb -q --ex 'break *0x405420' --ex 'r' --ex 'set $rip = 0x4079e0' --ex 'c' -ex 'q' ./spain
```

This year:
- Not Haskell
- Not a crackme

Therefore it must be realy baby, right?

additional information:
wreckme2 has been patched to incooperate some anti debugging
