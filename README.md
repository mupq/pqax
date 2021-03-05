This is work in progress... don't expect too much of the documentation.

# Currently working

```
./test.py
./benchmarks.py
```

e.g.,

```
./test.py kyber768
./benchmarks.py
```

#TODOs
 - kernel module to enable access to cycle counts
 - proper randombytes
 - Fast Keccak/SHA2/AES
 - stack benchmark
 - size benchmark
 - testvectors (current mupq setup runs it on the host and on the board and compares; as host==board in this case, this does not make any sense)
 - get some existing NEON implementation in
 - get the m4 code to run on here as well
 - reporting average cycle count is probably not sufficient on this platform. We may want to also report Median and quantiles
 - write docu
