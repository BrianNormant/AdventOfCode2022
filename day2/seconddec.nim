#[ 
ROCK 1
PAPER 2
SCISSOR 3

0 For loss
3 For tie
6 For win
 ]#

type Hand = enum
    ERROR = -1
    ROCK = 1
    PAPER = 2
    SCISSOR = 3


proc main()=
    let input = open("input2.txt")
    
    var score = 0
    for line in lines(input):
        #Read what the opponent while play
        let opp = (
            case line[0]
            of 'A':ROCK
            of 'B':PAPER
            of 'C':SCISSOR
            else:ERROR
        )
        if opp == ERROR: 
            echo "\e[31m Error while parsing data \e[31m", "0:",line[0], " 2:", line[2]
            quit(-1)
        

        #Now determine what we should play depending on the outcome
        let me = (
            case line[2]
            of 'X':#We need to lose
                case opp
                of ROCK:SCISSOR
                of PAPER:ROCK
                of SCISSOR:PAPER
                else:ERROR
            of 'Y':#We need to tie
                opp
            of 'Z':#We need to win
                case opp
                of ROCK:PAPER 
                of PAPER:SCISSOR
                of SCISSOR:ROCK
                else:ERROR   
            else:ERROR
        )
        if me == ERROR:quit(-1)
        
        # Plat the game
        score += ord(me)
        score += (
            if me == opp:
                3 #Tie
            elif (ord(opp)-ord(me)) in [-1, 2]:
                6 #Win
            else: 
                0 #Loss
        )
    echo "Score:", score
    close(input)

when isMainModule:
    echo "Hello world!"
    main()