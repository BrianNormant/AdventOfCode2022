from std/strutils import join, isUpperAscii
import std/enumerate

proc p1=
    let input = open("input3.txt")
    var sum:int = 0
    for line in lines(input):
        let containers:array[2, string]=[
            line[0..len(line) div 2-1].join(),
            line[len(line) div 2..^1].join(),
        ]
        for l in 'A'..'z':
            if l in containers[0] and l in containers[1]:
                sum += ord(l) - ( if l.isUpperAscii(): 38 else: 96 )
                break
    echo sum

proc p2=
    let input = open("input3.txt")
    var sum:int = 0
    var data: seq[string] = newSeq[string]()
    for i, line in enumerate(lines(input)):
        data.add(line)
        if len(data) == 3:
            for l in 'A'..'z':
                if l in data[0] and l in data[1] and l in data[2]:
                    sum += ord(l) - ( if l.isUpperAscii(): 38 else: 96 )
                    break
            data = newSeq[string]()
    echo sum

when isMainModule:
    echo "Hello world!"
    p2()