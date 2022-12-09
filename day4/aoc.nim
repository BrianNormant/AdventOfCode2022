import std/sets
from std/strutils import isDigit,parseInt
from std/sequtils import toSeq

proc p1=
    let input = open("input4.txt")
    defer: input.close()
    var result = 0
    for line in lines(input):
        var 
            str = ""
            numbers:array[4,int]

        #We read all numbers in the line
        var i = 0
        for l in line:
            if isDigit(l):
                str.add(l)
            else:
                numbers[i] = parseInt(str)
                str = ""
                i += 1
        numbers[i] = parseInt(str)

        #Now we get the ranges and verify if at least one is a a subset of the other
        let 
            s1 = toHashSet(
            toSeq(numbers[0]..numbers[1])
            )
            s2 = toHashSet(
            toSeq(numbers[2]..numbers[3])
            )

        if s1 <= s2 or s2 <= s1:
            result += 1
    echo $result, " pairs members fully contains the other"

proc p2=
    let input = open("input4.txt")
    defer: input.close()
    var result = 0
    for line in lines(input):
        var 
            str = ""
            numbers:array[4,int]

        #We read all numbers in the line
        var i = 0
        for l in line:
            if isDigit(l):
                str.add(l)
            else:
                numbers[i] = parseInt(str)
                str = ""
                i += 1
        numbers[i] = parseInt(str)

        #Now we get the ranges and verify if at least one is a a subset of the other
        let 
            s1 = toHashSet(
            toSeq(numbers[0]..numbers[1])
            )
            s2 = toHashSet(
            toSeq(numbers[2]..numbers[3])
            )

        if len(intersection(s1, s2)) != 0:
            result += 1
    echo $result, " pairs! intersect"

when isMainModule:
    p1()
    p2()