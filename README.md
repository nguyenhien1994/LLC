Implement an algorithm to count the number of lines in a large file with length of the line.


### Generate test input files with `generate_text_file`
```
./generate_text_file input100MB.txt 104857600
```


```
hiennm@ads3v:~/projects/github/LargeFileReader/build$ ./bin/LineLengthCounter 
------------/home/hiennm/projects/github/LargeFileReader/tests/input1kb.txt---------
runtime ms with llc: 1 ms
runtime ms with normal: 0 ms
------------/home/hiennm/projects/github/LargeFileReader/tests/input100kb.txt---------
runtime ms with llc: 0 ms
runtime ms with normal: 0 ms
------------/home/hiennm/projects/github/LargeFileReader/tests/input100MB.txt---------
runtime ms with llc: 174 ms
runtime ms with normal: 201 ms
------------/home/hiennm/projects/github/LargeFileReader/tests/input1GB.txt---------
runtime ms with llc: 1334 ms
runtime ms with normal: 2271 ms
------------/home/hiennm/projects/github/LargeFileReader/tests/input10GB.txt---------
runtime ms with llc: 2612 ms
runtime ms with normal: 4617 ms
```