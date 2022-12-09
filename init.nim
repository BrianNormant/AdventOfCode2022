import std/os

#Simple script to initialise all folders and put default code in them
for i in 9..24:
    var name = "day";
    name.add($i)

    #Create the directory
    discard existsOrCreateDir(name);

    #Create the input.txt file
    let input = "./" & name & "/input.txt"
    let file =  open(input, fmWrite)
    close(file)

    let dirName = "./" & name & "/";
    #copy the default .c and .nim and .bat file into the dir
    #removeFile(dirName & "aoc.c")
    #copyFile("./default.c", dirName & "aoc.c")
    #removeFile(dirName & "aoc.nim")
    #copyFile("./default.nim", dirName & "aoc.nim")
    removeFile(dirName & "make.bat")
    copyFile("./make.bat", dirName & "make.bat")