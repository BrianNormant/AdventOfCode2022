import std/[sequtils, algorithm]
from std/strutils import parseInt, replace

proc insert(s: var seq[int], x:int)=
    s.add(x)
    s.sort(DESCENDING)
    s = s[0..^2]

proc main()=
    let input = open("input1.txt")
    var
        mxs = @[0, 0, 0]
        current = 0
    for line in lines(input):
        if len(line) == 0:
            mxs.insert(current)
            current = 0
        else:
            current += parseInt line
    close(input)
    echo "The biggest number is ", (@mxs).foldl(a+b)

when isMainModule:
    echo "hello world"
    main()