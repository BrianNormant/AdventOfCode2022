#import std/[strutils, sequtils, sugar]

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
    NestedSeq = ref object
        self: int
        next: seq[NestedSeq]

proc flatten(n:NestedSeq):iterator():int =
    result = iterator():int =
        yield n.self
        for i in n.next:
            for nn in toItr(flatten(i)):
                yield nn

var s = new(NestedSeq)
s.self = -1
s.next= @[
    NestedSeq(self: 7, next: @[
        NestedSeq(self: 8, next: newSeq[NestedSeq](0)),
        NestedSeq(self: 9, next: @[
            NestedSeq(self: 200, next: @[
                NestedSeq(self: -10, next: newSeq[NestedSeq](0))
            ])
        ]),
    ]),
    NestedSeq(self: 10, next: newSeq[NestedSeq](0)),
    NestedSeq(self: 11, next: newSeq[NestedSeq](0)),
    NestedSeq(self: 12, next: newSeq[NestedSeq](0))
    ]
for e in toItr(flatten(s)):
    echo e