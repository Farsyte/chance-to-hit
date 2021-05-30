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
                dSides = ref_customDieSidesrev[dieCustomInfo.type+1]
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

    for  in pairs(CalcPercTable) do minraw = minraw + 1 end
    if plus ~= nil then
        min = minraw + plus
        maxval = maxvalraw + plus
    end

    if target>maxval then
        resultmessage=" No possibility of hitting at least the target. "
    else
        resultmessage=" There exists a ",perc,"% chance to hit at least the target. "
    end

    print("Additional = ",plus)
    print(min," <= range => ",maxval)
    print("Target result is = ",target)
    print("Number of outcomes = ",outcomes)
    print("results complete")
    print(resultmessage)
    print("-----")
end

