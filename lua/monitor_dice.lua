--Calculate % chance of success to hit target with roll------------------
function TargetCalc()
    local CalcPercTable = {}
    local ways = {}
    local min=0
    local minraw=0
    local maxval=0
    local maxvalraw=0
    local outcomes=1
    local resultmessage=""
    local perc=0
    print("-----")
    for _, die in ipairs(currentDice) do
        if die ~= nil then
            --Get die type
            local dSides = ""
            local dieCustomInfo = die.getCustomObject()
            if next(dieCustomInfo) then
                dSides = ref_customDieSides_rev[dieCustomInfo.type+1]
            else
                dSides = tonumber(string.match(tostring(die),"%d+"))
            end
            --Add to table
            table.insert(CalcPercTable, {sides=dSides})
        end
    end

    for index, data in ipairs(CalcPercTable) do
        for key, value in pairs(data) do
            print(index," | ",value)
            maxvalraw = maxvalraw + value
            outcomes = outcomes * value
        end
    end

    minraw = #CalcPercTable -- for _ in pairs(CalcPercTable) do minraw = minraw + 1 end
    if plus ~= nil then
        min = minraw + plus
        maxval = maxvalraw + plus
    end

    if target>maxval then
        resultmessage="** No possibility of hitting at least the target. **"
    else
        Rollpct(CalcPercTable,plus,target)
    end

    print("Additional = ",plus)
    print(min," <= range => ",maxval)
    print("Target result is = ",target)
    print("Number of outcomes = ",outcomes)
    print(resultmessage)
    print("results complete")
    print("-----")
end

--Monitors dice to come to rest
function monitorDice(color)
    function coroutine_monitorDice()
        repeat
            local allRest = true
            for _, die in ipairs(currentDice) do
                if die ~= nil and die.resting == false then
                    allRest = false
                end
            end
            coroutine.yield(0)
        until allRest == true

        --Announcement
        if announce_total==true or announce_each==true then
            displayResults(color)
        end

        wait(0.1)
        rollInProgress = false

        --Auto die removal
        if removalDelay ~= -1 then
            --Timer starting
            Timer.destroy("clickRoller_cleanup_"..self.getGUID())
            Timer.create({
                identifier="clickRoller_cleanup_"..self.getGUID(),
                function_name="cleanupDice", function_owner=self,
                delay=removalDelay,
            })
        end

        return 1
    end
    startLuaCoroutine(self, "coroutine_monitorDice")
end

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
    rmin, rmax, ways = MakeWays(cpt, plus or 0)

    local ways_total = 0
    local ways_match = 0
    for rt = rmin,rmax do
        ways_total = ways_total + ways[rt]
        if target and rt >= target then ways_match = ways_match + ways[rt] end
    end
    return string.format("%.0f", ways_match * 100.0 / ways_total)
end


-- added code at the bottom to try to test the addon code

-- test 101: nominal case for RollPct
local cpt = {}
table.insert(cpt, {sides=6})
table.insert(cpt, {sides=6})
table.insert(cpt, {sides=6})
local plus = 4
local target = 16
print("hello, rollPct returns "..RollPct(cpt, plus, target));

-- test 102: nominal case for RollPct
cpt = {}
table.insert(cpt, {sides=12})
table.insert(cpt, {sides=4})
table.insert(cpt, {sides=4})
plus = 4
target = 16

print("second rollPct returns "..RollPct(cpt, plus, target));

-- test 103: nominal case for RollPct
cpt = {}
table.insert(cpt, {sides=12})
table.insert(cpt, {sides=4})
table.insert(cpt, {sides=4})
plus = -4
target = 16

print("third rollPct returns "..RollPct(cpt, plus, target));

-- test 111: plus is nil
local cpt = {}
table.insert(cpt, {sides=6})
table.insert(cpt, {sides=6})
table.insert(cpt, {sides=6})
local plus = nil
local target = 16
print("hello, rollPct returns "..RollPct(cpt, plus, target));

-- test 111: target is nil
local cpt = {}
table.insert(cpt, {sides=6})
table.insert(cpt, {sides=6})
table.insert(cpt, {sides=6})
local plus = 4
local target = nil
print("hello, rollPct returns "..RollPct(cpt, plus, target));
