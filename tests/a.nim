import sequtils
import sugar

proc isPrime(a: int64):bool=
    let mid = a div 2
    for i in 2..mid:
        if a mod i == 0:
            return false
    true

const input:int64 = 600851475143

#echo toSeq[int64](1'i64..input/2).filterIt(isPrime(it)).filterIt(input mod it == 0).foldl(max(a,b))
for i in countdown(600851475143 div 2, 2):
    if isPrime(i):
        if input mod i == 0:
            echo i, "\ndone!"
            break;
    

#////////////////////////////////////////////////////////////////
