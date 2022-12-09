proc p1(f:File)=
    for line in lines(f):
        discard

proc p2(f:File)=
    for line in lines(f):
        discard

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