# Roll: track probability of roll results

## Initial State

When originally created, a Roll object represents the state
you are in before rolling any dice or adding any bonus values;
that is, there is only one possibility: the total is zero.

## Updating the State

### Roll a Die

Calling the "roll" method on the object will update it to reflect
the new possibilities added.

It does this by considering each possible result it already knows
about, adding to it each way the new die can roll, and accumulating
those totals into a new state.

So from the initial state (one possibility, totalling zero) adding
a single 6-sided die, we of course get one way to get each number
from 1 to 6. If we (for example) add another d6 to that, we end up
with the familiar pyramid: 1 way to roll 2, 2 ways to roll 3, and
so on up to 6 ways to roll 7, and back down to 1 way to roll 12.

Internally, the object stores the minimum that can be rolled, the
total number of possible combinations that could be rolled, and for
each possible total, the count of combinations with that total, in
an array where index zero has the number of ways to roll the minimum
value.

### Add a Bonus, or Subtract a penalty

If you are rolling "1d12 +4" this provides a way to add in the +4 bonus,
which goes right into the state, rather than have to handle the bonus
values separately. Seprate convenience methods are provided for adding
a bonus or subtracting a penalty, but the values added or subtracted
can be signed.

## Reading out results

### quick-and-dirty print method

For now, I'm just providing a "print" method that prints the
probability of meeting or exceeding a given threshold.

### get probability of achieving or exceeding a threshold [PLANNED]

Basically I'm going to refactor "print" to pull the computation out here,
because in the long run I'd prefer to NOT have library code directly
produce any output.
