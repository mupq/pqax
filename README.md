**pqax** aims to make it easier to start optimizing post-quantum crypto using ARM NEON. Currently, it is only tested on the Raspberry Pi 4 (which has an ARM Cortex-A72).
I might add support for more hardware later.

**pqax** is based on [mupq](https://github.com/mupq/mupq) and works in the same manner as [pqm4](https://github.com/mupq/pqm4), except that we do not need to cross-compile and we don't need serial communication as we can just print to stdout. 
You can also just use [supercop](https://bench.cr.yp.to/supercop.html) which should give you similar functionality. 

# Installation

You will need python3, make, and gcc installed.

## Enable access to performance counters 

To run the benchmarking you will need to enable access to the performance counters from user mode. You'll need to load a kernel module for that. 
You can either write one yourself, use [someone else's code](https://github.com/rdolbeau/enable_arm_pmu), or simply use the one shipped in here by 
``` 
cd enable_ccr
make install
```

# Testing & Benchmarking 

**pqax** comes with most functionality supported by [pqm4](https://github.com/mupq/pqm4). Please refer to that documentation. 
I expect that the most common use-case of **pqax** is to benchmark a new NEON implementation and to test its compatibility with reference implementations. 
To do so, you want to place your implementation in `crypto_kem/<SCHEME_NAME>/<IMPLEMENTATION_NAME>` and then run the following scripts. 

## Testing 

To test if a key encapsulation mechanism is producing the same keys for both parties, you can use the `test.py` script. 
Similarly, for signature schemes, it will test that signatures for random messages will correctly verify. 

You can use it for either all schemes contained in **pqax** or for just a subset of schemes: 
```
./test.py 

# or 

./test.py kyber768
````


## Testvectors 

The provided testvectors script will run the scheme with a deterministic `randombytes` and make sure that the output matches the one produced by reference implementations coming from [PQClean](https://github.com/PQClean/PQClean) and [mupq](https://github.com/mupq/mupq). 

You can use it for either all schemes contained in **pqax** or for just a subset of schemes: 

```
./testvectors.py 

# or 

./testvectors.py kyber768
````

Note:  pqm4 would run the reference implementation on the host computer and then make sure that all implementations produce the same testvectors when running bare-metal on the Cortex-M4 board. This does not make sense in the case of Cortex-A, as we are not running bare metal. However, as of now, it is still implemented like that, it's just that host and board are the same device. 


## Benchmarks 

To benchmark the schemes, you can use the `benchmarks.py` script. It will run a given number of iterations. 
You can use it for either all schemes contained in **pqax** or for just a subset of schemes: 

```
./benchmarks.py --iterations 1000

# or 

./benchmarks.py --iterations 1000 kyber768
```


You can then convert the output to markdown or csv using
```
./convert_benchmarks.py md 

# or 

./convert_benchmarks.py md 
```

Note: pqm4 would usually output cycle count averages (and min and max) as there is no noise when running bare-metal. On the Cortex-A, we are competing with the operating system and other processes, so there will be some noise in the cycle counts we get. Hence, we report median cycle counts. 
