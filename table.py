import operator

def processDict(file):
    IpPref = {}
    for line in file:
        if line[0] != "#":
            line = line[:-1]
            temp = line.split("\t")
            # print(temp)
            stupid = str(temp[2])
            if '_' in stupid:
                temp2 = temp[2].split("_")
                # temp.remove(temp[2])
                for x in temp2:
                    if x not in IpPref.keys():
                        IpPref[str(x)] = [[temp[0], temp[1]]]
                    else:
                        y = [temp[0], temp[1]]
                        IpPref[str(x)].append(y)
            else:
                if temp[2] not in IpPref.keys():
                    IpPref[str(temp[2])] = [[temp[0], temp[1]]]
                else:
                    y = [temp[0], temp[1]]
                    IpPref[str(temp[2])].append(y)
    return IpPref


def storeDatasetTwo(file):
    ASData={}
    for line in file:
        if line[0] != "#":
            temp = line.split("|")
            '''Skips lines that aren't p2c'''
            if int(temp[2]) != 0:
                if temp[0] not in ASData.keys():
                    ASData[str(temp[0])] = [str(temp[1])]
                else:
                    ASData[str(temp[0])].append(str(temp[1]))
    return ASData

def recursive(ASData, customers, temp):
    for cust in customers:
        if cust in ASData.keys():
            temp = recursive(ASData, ASData[cust], temp)
        else:
            return customers + temp
    return customers + temp

# def recursive2(ASData, customers, IpPrefDict, ctr):
#     for cust in customers:
        

def processCone(ASData):
    cone = {}
    custList = []
    for key in ASData.keys():
        # print(key)
        temp = []
        custList = recursive(ASData, ASData[key], temp)
        cone[key] = custList
    return cone


def main():
    file = open("20201001.as-rel.txt")
    # file = open("table2.txt")
    ASData = storeDatasetTwo(file)
    cone = processCone(ASData)
    # i = 0
    # for key in cone.keys():
    #     if i == 15:
    #         break
    #     print(key, end=": ")
    #     for val in cone[key]:
    #         print(val, end=", ")
    #     print("\n")
    #     i+=1

    # i = 0
    map1 = {}
    for key in cone.keys():
        # if i == 15:
            # break;
        map1[key] = len(cone[key])
        # i+=1

    sortedMap = dict(sorted(map1.items(), key=operator.itemgetter(1), reverse=True))

    # print("9809: "+ str(map1["9809"]))
    print("6762: "+ str(map1["6762"]))
    print("4826"+": "+ str(map1["4826"]))
    print("1239: "+ str(map1["1239"]))
    # i = 0
    # for key in sortedMap.keys():
    #     if i == 15:
    #         break
    #     print(key+": "+ str(sortedMap[key]))
    #     i+=1


    file2 = open("asprefix.txt")
    IpPrefDict = processDict(file2)

    asprefsize = 0
    for key in IpPrefDict.keys():
        asprefsize+=len(IpPrefDict[key])

    j = 0
    ASPREF = {}

    top15 = [174, 3356, 3549,7018, 1299, 3257, 49515, 8289, 6461, 6939, 2914, 209, 701, 6453, 3491]
    for key in top15:
        if j == 15:
            break
        
        ctr = 0
        for cust in cone[str(key)]:
            # ctr = 0
            if cust in IpPrefDict.keys():
                ctr+=len(IpPrefDict[cust])

        ASPREF[str(key)] = ctr
        j+=1

    ASip = {}
    for key in top15:
        ctr = 0
        for cust in cone[str(key)]:
            if cust in IpPrefDict.keys():
                for ippref in IpPrefDict[cust]:
                    diff = 32 - int(ippref[1])
                    ctr += pow(2,diff)

        ASip[str(key)] = ctr


    coneIPdict = {}
    for key in cone.keys():
        ctr = 0
        for cust in cone[key]:
            if cust in IpPrefDict.keys():
                for ippref in IpPrefDict[cust]:
                    diff = 32 - int(ippref[1])
                    ctr += pow(2,diff)
        coneIPdict[key] = ctr

    sortedConeIpDict = dict(sorted(coneIPdict.items(), key=operator.itemgetter(1), reverse=True))
    
    # i = 0
    # for key in sortedConeIpDict.keys():
    #     if i == 15:
    #         break
    #     print(key+": "+ str(sortedConeIpDict[key]))
    #     i+=1
    ASPREF2 = {}
    j = 0
    for key in sortedConeIpDict.keys():
        if j == 15:
            break
        
        ctr = 0
        for cust in cone[str(key)]:
            # ctr = 0
            if cust in IpPrefDict.keys():
                ctr+=len(IpPrefDict[cust])

        ASPREF2[str(key)] = ctr
        j+=1

    
    print("Number of prefixes:")
        
    for key in ASPREF2.keys():
        print(key + ": " + str(ASPREF2[key]))
    
    # for key in ASPREF.keys():
    #     print(key + ": " + str(ASPREF[key]))

    # print("Number of IPs: ")
    # for key in ASip.keys():
    #     print(key + ": " + str(ASip[key]))

    
    # print("prefix size: "+str(asprefsize))

# 2^(32-24)

main()