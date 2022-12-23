import std/[sequtils, sugar, strutils]

type Tile = enum
    CASE
    WALL
    BORDER
    VOID
    ERROR

type Orientation = enum
    RIGHT = 0
    DOWN = 1
    LEFT = 2
    UP = 3

type Map = seq[seq[Tile]]

proc parseMap(map:File):Map=
    # We get the dimension and parse the map
    var 
        rawData:seq[seq[char]]
        width = -1
        height = 0
    
    var line = ""
    while readLine(map, line):
        width = max(width, len(line))
        height += 1;
    
    rawData = collect():
        for _ in 0..<height:
            collect():
                for _ in 0..<width:
                    ' '
    map.setFilePos(0)
    let lines = ("map.txt").readLines(height)
    for i, line in lines:
        for j, l in line:
            rawData[i][j] = l

    # We construct an array big enough to hold all the data
    result = collect():
        for _ in 1..height:
            newSeq[Tile](width)
    
    # We parse the raw data
    var raw = ""
    for line in rawData:
        for c in line:
            raw.add(c)
    
    for i in 0..<len(raw):
        result[i div width][i mod width] = (
            case raw[i]
            of '.': CASE
            of '#': WALL
            of ' ':
                if (raw[if i != 0:i-1 else: i] == ' ' and raw[if i+1 != len(raw):i+1 else: i] == ' ' and raw[if i div width != 0: i - width else: i] == ' '  and raw[if (i div width)+1 != height: i + width else: i] == ' '):
                    VOID
                else:
                    BORDER
            else:
                ERROR
        )
proc showMap(map:Map)=
    for row in map:
        for tile in row:
            stdout.write (
                case tile
                of CASE:'*'
                of WALL:'#'
                of BORDER:'+'
                of VOID: ' '
                of ERROR: 'E'
            )
        stdout.write '\n'

proc p1(map, path:File)=
    let parsedMap = parseMap(map)
    parsedMap.showMap()

    let instruction = readAll(path)
    # We start at the leftmost and uppermost position and facing RIGHT
    var 
        posX = -1
        posY = 0
        orientation = RIGHT
    for i, tile in parsedMap[0]:
        if tile == CASE:
            posX = i
            break

    echo "First Position is "
    echo "\tx:", $posX, " y:", $posY, " orientation:", $orientation

    proc advance()=
        #echo "\tx:", $posX, " y:", $posY, " orientation:", $orientation
        var 
            nextX:int
            nextY:int
        # I know this can be done with mod by i can't be asked
        case orientation
        of RIGHT:
            nextY = posY
            if posX == len(parsedMap[0])-1:
                nextX = 0
            else:
                nextX = posX + 1
        of LEFT:
            nextY = posY
            if posX == 0:
                nextX = len(parsedMap[0])-1
            else:
                nextX = posX - 1
        of UP:
            nextX = posX
            if posY == 0:
                nextY = len(parsedMap)-1
            else:
                nextY = posY - 1
        of DOWN:
            nextX = posX
            if posY == len(parsedMap)-1:
                nextY = 0
            else:
                nextY = posY + 1

        case parsedMap[nextY][nextX]
        of CASE:
            posX = nextX
            posY = nextY
        of WALL:
            discard #Well, we are trying to run into a wall
        of BORDER, VOID:
            while parsedMap[nextY][nextX] == BORDER or parsedMap[nextY][nextX] == VOID:
                case orientation
                of RIGHT:
                    if nextX == len(parsedMap[0])-1:
                        nextX = 0
                    else:
                        nextX = nextX + 1
                of LEFT:
                    if nextX == 0:
                        nextX = len(parsedMap[0])-1
                    else:
                        nextX = nextX - 1
                of UP:
                    if nextY == 0:
                        nextY = len(parsedMap)-1
                    else:
                        nextY = nextY - 1
                of DOWN:
                    if nextY == len(parsedMap)-1:
                        nextY = 0
                    else:
                        nextY = nextY + 1
            if parsedMap[nextY][nextX] != WALL:
                posX = nextX
                posY = nextY
        of ERROR:
            echo "\e[31mFuck\e[31m"
            quit(-1)

    var number = "0"
    for l in instruction:
        case l
        of 'R':# Turn right
            let i = parseInt(number)
            echo "Advancing ", i , " times"
            for _ in 1..i: advance()
            number = ""
            case orientation
            of RIGHT: orientation = DOWN
            of UP: orientation = RIGHT
            of LEFT: orientation = UP
            of DOWN: orientation = LEFT
        of 'L':# Turn left
            let i = parseInt(number)
            echo "Advancing ", i , " times"
            for _ in 1..i: advance()
            number = ""
            case orientation
            of RIGHT: orientation = UP
            of UP: orientation = LEFT
            of LEFT: orientation = DOWN
            of DOWN: orientation = RIGHT
        
        else:# This is a number
            number &= l
    
    # If the last instruction is a number we need to advance again
    # The last instruction will always be a number
    let i = parseInt(number)
    for _ in 1..i: advance()
    number = ""

    echo "Last Position is "
    echo "\tx:", $posX, " y:", $posY, " orientation:", $orientation
    echo "score is: ", $(1000 * (posY+1) + 4 * (posX+1) + ord(orientation))


proc p2(map, path:File)=
    discard

proc main=
    var 
        map:File
        path:File
    
    echo "For 1:"
    map = open("map.txt")
    path = open("path.txt")
    p1(map, path)
    close(map)
    close(path)

    echo "For 2:"
    map = open("map.txt")
    path = open("path.txt")
    p2(map, path)
    close(map)
    close(path)

when isMainModule:
    main()