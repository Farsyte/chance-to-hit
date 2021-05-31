function MakeWays(cpt, plus)
    local ways = {}
    local rmin = plus
    local rmax = plus

    -- cpt is a table containing one entry per die.
    -- each entry is itself a table, with the "sides"
    -- member set to the number of sides.

    ways[plus] = 1

    for _, die in pairs(cpt) do

        -- work from high to low so we can use a single table.

        -- zero the new possible sums
        for d=die.sides,1,-1 do
            ways[rmax+d] = 0
        end

        -- from each old number of ways,
        -- add in the new numbers of ways.

        for ot = rmax,rmin,-1 do
            for f = die.sides,1,-1 do
                ways[ot+f] = ways[ot] + ways[ot+f]
            end
            ways[ot] = 0
        end

        -- a bit of cleanup
        ways[rmin] = nil

        -- update bookkeeping
        rmax = rmax + die.sides
        rmin = rmin + 1
    end
    return rmin, rmax, ways
end

function RollPct(cpt, plus, target)
    local rmin, rmax, ways
    rmin, rmax, ways = MakeWays(cpt, plus)

    local ways_total = 0
    local ways_match = 0
    for rt = rmin,rmax do
        ways_total = ways_total + ways[rt]
        if rt >= target then ways_match = ways_match + ways[rt] end
    end
    print("chances are "..ways_match.." in "..ways_total)
    return string.format("%.0f%%", ways_match * 100 / ways_total)
end

local cpt = {}
table.insert(cpt, {sides=6})
table.insert(cpt, {sides=6})
table.insert(cpt, {sides=6})
local plus = 4
local target = 16
print("hello, rollPct returns "..RollPct(cpt, plus, target));

cpt = {}
table.insert(cpt, {sides=12})
table.insert(cpt, {sides=4})
table.insert(cpt, {sides=4})
plus = 4
target = 16

print("second rollPct returns "..RollPct(cpt, plus, target));

cpt = {}
table.insert(cpt, {sides=12})
table.insert(cpt, {sides=4})
table.insert(cpt, {sides=4})
plus = -4
target = 16

print("third rollPct returns "..RollPct(cpt, plus, target));
print("μαθηματα παθηματα")
print("γνωθε σεαυτον")

