import std/[strutils, sugar, strformat]

proc `+`[T](a,b :seq[T]):seq[T]=
    result = a[0..^1]
    for e in b:
        result.add(e)

proc p1=
    # Read the piles drawing from the     
    let data = """
        [H]         [H]         [V]    
        [V]         [V] [J]     [F] [F]
        [S] [L]     [M] [B]     [L] [J]
        [C] [N] [B] [W] [D]     [D] [M]
    [G] [L] [M] [S] [S] [C]     [T] [V]
    [P] [B] [B] [P] [Q] [S] [L] [H] [B]
    [N] [J] [D] [V] [C] [Q] [Q] [M] [P]
    [R] [T] [T] [R] [G] [W] [F] [W] [L]
    """

    proc getSize:int=
        for i, l in data:
            if l == '\n':
                echo "size = ", i div 4
                return i div 4
    let nbPile = getSize()

    var piles = collect():
        for _ in 1..nbPile:
            newSeq[char]()

    for line in splitLines(data):
        for i, l in line:
            if i mod 4 == 1:
                if l != ' ':piles[i div 4 - 1].add(l)

    for pile in piles:
        echo pile
    #now start reading the instruction from the file
    let input = open("input5.txt")
    defer:close input
    for line in lines(input):
        var 
            mve:int
            frm:int
            to:int
            n:int = 0
        var str = ""
        for l in line:
            if isDigit(l):
                str.add(l)
            else:
                case n
                of 5: mve = parseInt(str)
                of 11: frm = parseInt(str)
                else:discard
                str = ""
                n += 1
        to = parseInt(str)
        #echo &"move {mve} from {frm} to {to}"
        for _ in 1..mve:
            piles[to-1].insert(piles[frm-1][0], 0)
            piles[frm-1] = piles[frm-1][1..^1]
    var str = ""
    for pile in piles:
        str.add(pile[0])
    echo "Final is ", str

proc p2=
    # Read the piles drawing from the     
    let data = """
        [H]         [H]         [V]    
        [V]         [V] [J]     [F] [F]
        [S] [L]     [M] [B]     [L] [J]
        [C] [N] [B] [W] [D]     [D] [M]
    [G] [L] [M] [S] [S] [C]     [T] [V]
    [P] [B] [B] [P] [Q] [S] [L] [H] [B]
    [N] [J] [D] [V] [C] [Q] [Q] [M] [P]
    [R] [T] [T] [R] [G] [W] [F] [W] [L]
    """

    proc getSize:int=
        for i, l in data:
            if l == '\n':
                echo "size = ", i div 4
                return i div 4
    let nbPile = getSize()

    var piles = collect():
        for _ in 1..nbPile:
            newSeq[char]()

    for line in splitLines(data):
        for i, l in line:
            if i mod 4 == 1:
                if l != ' ':piles[i div 4 - 1].add(l)

    for pile in piles:
        echo pile
    #now start reading the instruction from the file
    let input = open("input5.txt")
    defer:close input
    for line in lines(input):
        var 
            mve:int
            frm:int
            to:int
            n:int = 0
        var str = ""
        for l in line:
            if isDigit(l):
                str.add(l)
            else:
                case n
                of 5: mve = parseInt(str)
                of 11: frm = parseInt(str)
                else:discard
                str = ""
                n += 1
        to = parseInt(str)
        #echo &"move {mve} from {frm} to {to}"
        piles[to-1] = piles[frm-1][0..<mve] + piles[to-1]
        piles[frm-1] = piles[frm-1][mve..^1]
    
    var str = ""
    for pile in piles:
        str.add(pile[0])
    echo "P2: Final is ", str

when isMainModule:
    p1()
    p2()