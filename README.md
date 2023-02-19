## LLC - Line Length Counter
Simple algorithm to count the number of lines in a large file with length of the line.

### How to build and run

- Clone code
```
git clone git@github.com:nguyenhien1994/LLC.git
```

- Build
```
mkdir build
cd build
cmake ..
make
```


#### Generate test input files with `generate_text_file`
```
USAGE: ./generate_text_file <filename> <file size in bytes>

e.g. ./generate_text_file input100MB.txt 104857600
```


#### Run tests: LineLengthCounter will run and compare the result with brute-force method
```
./LineLengthCounter ../tests/input100kb.txt 100
------------../tests/input100kb.txt---------
Runtime with LLC: 75 ms
Runtime with brute-force: 1 ms

./LineLengthCounter ../tests/input100MB.txt 1024000
------------../tests/input100MB.txt---------
Runtime with LLC: 320 ms
Runtime with brute-force: 429 ms

./LineLengthCounter ../tests/input1GB.txt 10240000
------------../tests/input1GB.txt---------
Runtime with LLC: 2950 ms
Runtime with brute-force: 3510 ms

./LineLengthCounter ../tests/input10GB.txt 102400000
------------../tests/input10GB.txt---------
Runtime with LLC: 5166 ms
Runtime with brute-force: 7214 ms
```

### Notes for improvements
- Use Thread Pool to avoid `Resource temporarily unavailable` when run with big input and small chunk sizes
- Instead of storing the chunk results in std::vector, we can write to temporary files when the input file too large
