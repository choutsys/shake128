# A `SHAKE128` implementation 

*The Makefile builds a program called `shake128` that computes the digest of the stream of bytes present in the standard input. The size of the digest is chosen by the user and is expressed in bytes, and the program prints the digest as a hexadecimal string.* 
## Building the program

To build this program, navigate to directory where this file is present and run
```sh-session
$ make
```

**Dependencies** : `gcc`, `make`, and `gmp`.

If built successfully, the program appears alongside this `README` file.

## Running the program

The program expects **one argument** : a positive integer, not greater than a million. 
SHAKE128 being an Extendable Output hash function, digests of arbitrary sizes can be computed and that argument indicates the number of **bytes** of the digest the program should compute and print out. 
However, we consider that the user of the program will not need a digest of more 1,000,000 bytes.
This arbitrary limit is more than enough for various applications since outputs starting from 32 bytes are considered secure.
### Live hashing
Once built, one can launch the program with this command : 

```sh-session
$ ./shake128 32
```
The program will wait for you to complete your input stream, that is the bytes you provide via the keyboard, before outputting the digest. 
The end of the stream is signalled to the program by pressing `Ctrl+D`.

### Hashing a file
Running the program as described in the previous section limits the input bytes to those that can be typed. 
One could want to hash large streams of bytes that would be a hassle to type, or streams of bytes that are nearly impossible to type (e.g. the stream of bytes of an image file).

One can redirect the standard input of the program to a file by running

```sh-session
$ ./shake128 42 < /path/to/file
```
For instance this `README` file can be hashed by typing 
```sh-session
$ ./shake128 42 < README.md
```

One can also pass the output of a command to the standard input of the program through piping : 
```
$ [command] | ./shake128 57
```

For instance this `README` file can be hashed by piping the output of the command that prints it to `shake128`.
```sh-session
$ cat README.md | ./shake128 57
```


## Building the interface

The hashing function is prototyped in `shake128.h`. One might want to use it in a larger C project : 

```C
int shake128(FILE *message, int digestSize, uint8_t *hash);
```

By running 
```sh-session
$ make interface
```
the generated object files can be linked alongside those of another project that aims at using this function. 

## Using the interface

The return value of this function indicates whether the hash was successfully computed. 
If so, the function returns `0`.
If the given digest size is not valid (i.e. larger than a million or negative) or if the file pointer is not valid (that is, `message` wasn't initialized with `fopen`), the function returns `-1`.  

The `hash` pointer should be **initialized** and **allocated** with `digestSize` bytes before passing it to the function, otherwise the behavior of the program is undefined. When passed to the `shake128` function, its content is discarded and replaced by a big number, representing the digest on `8*digestSize` bits.
A segmentation fault might occur if the file `message` is not **open for reading**.

## Sponge tweaks

One might want to adapt the code to implement other Keccak sponges. 
All relevant constants to the internal state are in `state.h`. The terminology and lowercase notations used in the comments are the ones of [NIST FIPS 202](https://nvlpubs.nist.gov/nistpubs/FIPS/NIST.FIPS.202.pdf). 

Table 1 of the standard gives possible state dimensions for the Keccak sponge. In the case of `shake128` the relevant values are those of the last column but can be replaced as long as the new values are compatible with the dimensions of a given column. 

For instance, to use a 800-bit state instead of 1600, redefine the `LANE_SIZE` macro, the `N_ROUNDS` macro and the `Lane` type accordingly :

```C
#define LANE_SIZE 32 // w in FIPS 202
#define N_ROUNDS  22 // 12 + 2l in FIPS 202
typedef uint32_t Lane;
```

One might want to use different rates and capacities for a custom sponge, but should always have `RATE + CAPACITY = WIDTH = 25`, keeping in mind that these macros are expressed in lanes, that is `r = LANE_SIZE*RATE` and `c = LANE_SIZE*CAPACITY`.
