import operator

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

    i = 0
    for key in sortedMap.keys():
        if i == 15:
            break
        print(key+": "+ str(sortedMap[key]))
        i+=1
    

main()