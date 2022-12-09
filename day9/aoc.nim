import std/[strutils, sequtils, sugar]

proc sign(a:int):int=
    return a div abs(a)

type Position = tuple[x:int, y:int]
type Direction = enum
    UP #= 0b01
    RIGHT #= 0b10
    DOWN #= -0b01
    LEFT #= -0b10

proc initPosition(x, y : int):Position=
    result = (x:x, y:y)

proc parseDirection(c:char):Direction=
    case c
    of 'R':RIGHT
    of 'L':LEFT
    of 'U':UP
    of 'D':DOWN
    else :
        raise newException(Exception, "\e[31mCouldn't parse the character \e[0m" & c)
    # This work because the case is not a statement, its parsed as a expression

proc show(knots: seq[Position], visited:seq[Position])=
    const size = 10
    echo "Showing the plateau"
    for j in -size..size:
        for i in -size..size:
            if (knots[0].x == i and knots[0].y == -j):
                stdout.write 'H'
            elif (knots[1..^1]).anyIt(it.x == i and it.y == -j):
                for k, knot in knots:
                    if knot.x == i and knot.y == -j:
                        stdout.write k
                        break;
            elif (visited.anyIt(it.x == i and it.y == -j)):
                stdout.write '#'
            elif (i == 0 and j == 0):
                stdout.write 's'
            else : stdout.write '*'
        stdout.write '\n'

proc p1(f:File)=
    var 
        visited: seq[Position] = newSeq[Position](0) 
        head = initPosition(0,0)
        tail = initPosition(0,0)
    for line in lines(f):
        #show(head, tail, visited)
        let dir = parseDirection(line[0])
        let nb = parseInt($line[2..^1])
        for _ in 0..<nb:
            case dir
            of RIGHT:head.x += 1
            of LEFT:head.x -= 1
            of UP:head.y += 1
            of DOWN:head.y -= 1

            #Then let the tail follow
            let distance = abs(tail.x - head.x) + abs(tail.y - head.y)

            case distance
            of 0, 1:discard
            of 2:
                if abs(tail.x - head.x) > 1:
                    tail.x -= sign(tail.x - head.x)
                if abs(tail.y - head.y) > 1:
                    tail.y -= sign(tail.y - head.y)
            of 3:
                tail.x -= sign(tail.x - head.x)
                tail.y -= sign(tail.y - head.y)
            else: 
                raise newException(Exception, "\e[31mSomething did go wrong\e[0m")
            if (visited.allIt(it != tail)): 
                visited.add(deepCopy(tail));
            #show(head, tail, visited)
    echo len(visited), " positions visited for the tail";

proc p2(f:File)=
    var 
        visited: seq[Position] = newSeq[Position](0) 
        knots:seq[Position] = collect():
            for _ in 0..9:
                initPosition(0,0)
    for line in lines(f):
        #show(head, tail, visited)
        let dir = parseDirection(line[0])
        let nb = parseInt($line[2..^1])
        for _ in 0..<nb:
            case dir
            of RIGHT:knots[0].x += 1
            of LEFT:knots[0].x -= 1
            of UP:knots[0].y += 1
            of DOWN:knots[0].y -= 1

            #Then let the each knot follow the last
            for i in 1..9:
                let distance = abs(knots[i].x - knots[i-1].x) + abs(knots[i].y - knots[i-1].y)

                case distance
                of 0, 1:discard
                of 2:
                    if abs(knots[i].x - knots[i-1].x) > 1:
                        knots[i].x -= sign(knots[i].x - knots[i-1].x)
                    if abs(knots[i].y - knots[i-1].y) > 1:
                        knots[i].y -= sign(knots[i].y - knots[i-1].y)
                of 3,4,5:
                    knots[i].x -= sign(knots[i].x - knots[i-1].x)
                    knots[i].y -= sign(knots[i].y - knots[i-1].y)
                else: 
                    raise newException(Exception, "\e[31mSomething did go wrong\e[0m")
            if (visited.allIt(it != knots[^1])): 
                visited.add(deepCopy(knots[^1]));
            #show(knots, visited)
    echo len(visited), " positions visited for the tail";

proc main=
    var file:File
    
    echo "For 1:"
    file = open("input.txt")
    p1(file)
    close(file)

    echo "For 2:"
    file = open("input.txt")
    p2(file)
    close(file)

when isMainModule:
    main()