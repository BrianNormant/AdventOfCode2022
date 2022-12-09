import std/[strutils, sequtils, strformat, sugar]

#Macro to make a recursive iterator
import macros
macro toItr(x: ForLoopStmt): untyped =
  let expr = x[0]
  let call = x[1][1] # Get foo out of toItr(foo)
  let body = x[2]
  result = quote do:
    block:
      let itr = `call`
      for `expr` in itr():
          `body`

type
    Dir = ref object
        name:string
        size:int
        parent: Dir
        subdir:seq[Dir]

proc `$`(d:Dir):string=
    return &"Dir(name={d.name}, parent={(if d.parent == nil:\"None\" else: d.parent.name)})\n" & "\tSubdirs: " & (if len(d.subdir) > 0: $d.subdir else: "None")

proc initDir(name:string, size:int = 0):Dir=
    result = new(Dir)
    result.name = name
    result.size = size
    result.parent = nil
    result.subdir = newSeq[Dir](0)

proc addSubDir(to, sub:var Dir)=
    to.subdir.add(sub)

proc getSubDir(frm: Dir, name:string):Dir =
    result = nil;
    for subdir in frm.subdir:
        if subdir.name == name:
            result = subdir
            break;
    if result == nil:
        echo "Failed to get the sub directory named ", name
        quit(-1)

proc getSize(d:var Dir):int = 
    if len(d.subdir) == 0:#This is a file or a empty directory
        return d.size
    if d.size == 0 :
        for e in mitems(d.subdir):
            discard e.getSize()
        d.size = d.subdir.mapIt(it.size).foldl(a+b)
    return d.size

proc flatten(n:Dir):iterator():Dir =
    result = iterator():Dir =
        yield n
        for i in n.subdir:
            for nn in toItr(flatten(i)):
                yield nn
iterator items(n:Dir):Dir = 
    for i in toItr(flatten(n)):
        yield n

proc p1(input:File)=
    var outerMost = initDir("/");
    var current = outerMost;
    for line in lines(input):
        if line == "$ ls" : discard
        elif "$ cd" in line: # We move the current directory to this directory
            var name = line.split(" ")[2]
            case name
            of "/":current = outerMost #This is the first instruction of the file
            of "..": #We get the parent directory
                current = current.parent
            else: #We move the the specified subdirectory
                current = current.getSubDir(name)
        elif "dir " in line: # We add this directory to the current one
            var d = initDir(line.split(" ")[1])
            d.parent = current
            current.addSubDir(d);
        elif isDigit(line[0]): # This is a file so we add it as a directory without subdir
            let s = line.split(" ")
            let size:int = parseInt(s[0])
            let name:string = s[1]
            var d = initDir(name, size)
            d.parent = current
            current.addSubDir(d);
    # When we finish parsing the file, we ask the outmost directory to calculate his size recursively 
    echo "Size of the outermost directory is ", outerMost.getSize()
    var folders = collect():
        for e in toItr(flatten(outerMost)):
            if e.name != "/":e


    let sum = folders
        .filterIt(it.size < 100_000 and len(it.subdir) != 0)
        .mapIt(it.size)
        .foldl(a + b)
        
    echo "Sum of the size of is ", sum

proc p2(input:File)=
    var outerMost = initDir("/");
    var current = outerMost;
    for line in lines(input):
        if line == "$ ls" : discard
        elif "$ cd" in line: # We move the current directory to this directory
            var name = line.split(" ")[2]
            case name
            of "/":current = outerMost #This is the first instruction of the file
            of "..": #We get the parent directory
                current = current.parent
            else: #We move the the specified subdirectory
                current = current.getSubDir(name)
        elif "dir " in line: # We add this directory to the current one
            var d = initDir(line.split(" ")[1])
            d.parent = current
            current.addSubDir(d);
        elif isDigit(line[0]): # This is a file so we add it as a directory without subdir
            let s = line.split(" ")
            let size:int = parseInt(s[0])
            let name:string = s[1]
            var d = initDir(name, size)
            d.parent = current
            current.addSubDir(d);
    # When we finish parsing the file, we ask the outmost directory to calculate his size recursively 
    
    const
        DISK_SPACE:int = 70_000_000
        MIN_NEEDED:int = 30_000_000

    echo "Size of the outermost directory is ", outerMost.getSize()
    let sizeToFree = outerMost.size + MIN_NEEDED - DISK_SPACE
    echo "Size to Free = ", sizeToFree
    var folders = collect():
        for e in toItr(flatten(outerMost)):
            if e.name != "/":e
    
    let m = folders
        .filterIt(it.size >= sizeToFree and len(it.subdir) != 0)
        .mapIt(it.size)
        .foldl(min(a, b))
        
    echo "Min size of the file to delete is  ", m

proc main=
    var file:File
    file = open("input.txt")
    p1(file)
    close(file)

    file = open("input.txt")
    p2(file)
    close(file)
    
when isMainModule:
    main();