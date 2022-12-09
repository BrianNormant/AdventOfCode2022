import std/sets
from std/strutils import splitLines

proc pushKeepSize[T](on: var seq[T], a : T)=
    for i in 1..<len(on):
        on[i-1] = on[i]
    on[^1] = a

proc p1=
    let input = open("input6.txt")
    for line in lines(input):
        var last4 = newSeq[char]()
        for i, l in line:
            if i < 4:
                last4.add(l)
            else:
                last4.pushKeepSize(l)
                var s = toHashSet(last4)
                if len(s) == 4:
                    echo "Found 4 non repeating letters at ", (i+1)
                    echo last4
                    break

proc p2=
    let input = open("input6.txt")
    for line in lines(input):
        var last14 = newSeq[char]()
        for i, l in line:
            if i < 14:
                last14.add(l)
            else:
                last14.pushKeepSize(l)
                var s = toHashSet(last14)
                if len(s) == 14:
                    echo "Found 14 non repeating letters at ", (i+1)
                    echo last14
                    break

when isMainModule:
    p1()
    p2()