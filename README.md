# Compute probability the sum of dice meets or exceeds a threshold

Given a description of a collection of dice, report the probability
that their sum is at least a given threshold.

This is a decision support tool. It reports probabilities as a
percentage, and additional decimal places aren't useful for the
intended use case.

## Usage

    bin/pct <threshold> <dice-or-bonus> ...

## Options

The first parameter, the threshold for success, is the integer value
that you want the roll to meet or exceed.

The remaining parameters are either a signed integer which is a bonus
to add to the roll, or a form like "3d6" saying roll some number of
dice with a specified number of faces.

## Example

    bin/pct 14 1d12 4 2d4

would output:

    chances of rolling 14 or higher: 128 in 192 or 66%

