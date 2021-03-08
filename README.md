This is work in progress... don't expect too much of the documentation.
Currently this code base targets the Raspberry Pi 4 (which has a ARM Cortex-A72).
I might add support for more hardware later.


# Installation

You will need python3, make, and gcc installed.

# Currently working

```
./test.py
./benchmarks.py
```

e.g.,

```
./test.py kyber768
./benchmarks.py -i 1000 kyber768
```

#TODOs
 - Fast Keccak/SHA2/AES
 - stack benchmark
 - size benchmark
 - testvectors (current mupq setup runs it on the host and on the board and compares; as host==board in this case, this does not make any sense)
 - get some existing NEON implementation in
 - get the m4 code to run on here as well
 - reporting average cycle count is probably not sufficient on this platform. We may want to also report Median and quantiles
 - write docu
