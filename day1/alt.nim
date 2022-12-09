import std/[strutils, sequtils, algorithm]

const data = """
1000
2000
3000

4000

5000
6000

7000
8000
9000

10000"""

proc p1=
    echo data
        .split("\n\n")
        .mapIt(
            it  .split("\n")
                .mapIt(parseInt(it))
                .foldl(a + b))
        .foldl(max(a,b))

proc p2=
    echo data
        .split("\n\n")
        .mapIt(
            it  .split("\n")
                .mapIt(parseInt(it))
                .foldl(a + b))
        .sorted(system.cmp[int], Descending)[0..<3]
        .foldl(a + b)

when isMainModule:
    p1()
    p2()