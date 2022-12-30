# Notes

Misc notes for works in progress. Subject to change.

## General

Value from tape read head is defined through stack language. Function is valid if one float ∈ [-1.0,1.0] is left on stack after full evaluation.

User input strings are interpreted to bytecode. There is mostly a literal mapping between chars and bytecode, but maybe some syntax improvements can be explored.

All stack values are function bytecodes or float literals. Negative floats are `_n` rather than `-n` to avoid operator ambiguity.

Spaces are generally not required, except to disambiguate neighboring literal numbers.

0.0 is false, and any other float value is true.

## Conditions

Conditional execution follows the form 

```
p?x:y;
```

where `x` is executed if `p` is true and `y` otherwise.

When a predicate is true, every procedure until `:` will run. `:` will ignore everything on the program tape until `;`. If a `?` is encountered during this ignore period, an internal `depth` value will be incremented, telling the `:` procedure not to honor any `;` from a nested condition. The ignore period will only stop until the outermost `;` is reached. Consider the need for this behavior in

```
p?x:p?y:z;1 1+;
```

An alternative could be compiling an expression with `JUMP` instructions rather than runtime scanning. So that the following string

```
100x<?1x+:xx+;
```

compiles to bytecode like

```
100.0f X GT IF 5.0f JUMP 1.0f X PLUS 3.0f JUMP X X PLUS
```

where if the predicate (here `100x<?`) holds true, the program will always skip the next two instructions (here `5.0f JUMP`) and evaluate the first branch. At the end of this branch, it will encounter a jump instruction (here `3.0f JUMP`) that will surpass the second branch. If the predicate is false, it will read the next two instructions (`5.0f JUMP`) and land at the start of the second branch.

A one-sided conditional can be performed with the no-op function `,`, like `p?x:,;`. Maybe some compiler intelligence can avoid the need for this?

## Loops

A while loop can be simulated by marking a position along the program tape with `(` and returning to it with `)`. Consider a simple loop like

```
(x100<?1x+):,;
```

Nested while loops are tracked with a stack of `(` memory addresses. When a new `(` is read, its address+1 is popped onto the stack. When `)` is encountered, its own address is stored as a `depth` variable. If the `depth` of the current `)` is equal to the stored `depth`, then the execution is still within the innermost loop, but if the current `depth` is greater than the stored `depth`, the stack is decremented and the loop returns to an outer address stored by an earlier `(`.

To prevent premature stack subtraction, probably need an additional bool `new` flag that is engaged when a `(` is encountered and disengaged the next time a `)` shows up. This allows recording a fresh `depth` value without comparing.

```
(x100<?(y100<?1y+):,;1x+):,;
```

- `(` adds address 1 to the stack. `new` is toggled to true.
- `x100<?` is evaluated and first branch is taken.
- `(` adds address 6 to the stack. `new` is toggled to true (no change).
- `y100<?` is evaluated and the first branch is taken.
- `1y+` is evaluated.
- `)` is encountered and because `new` is true, the `depth` is recorded as 13 without comparing to a previous value. `new` is toggled to false.
- Loop back to top of the stack, which is address 6. Run until the predicate is falsified.
- When `100y=`, conditional takes second no-op branch, breaks free, and evaluates `1x+`.
- `)` is encountered and the new `depth` is 20. Because `new` is false, `20 13>` is run. Because this is true, the stack is decremented and the tape loops back to the previously stored address of 1.
- `x100<?` is evaluated and the first branch is taken.
- `(` adds address 6 to the stack. `new` is toggled to true.
- ...

Loop syntax is not pretty, but not expecting much looping anyway.

Could also be written like

```
(x100<?(y100<?1y+):1x+);:,;
```

Does this work?
