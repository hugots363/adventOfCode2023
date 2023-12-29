import urllib.request
import re
from collections import OrderedDict
 
def getInput(url, session_cookie):
    input_name = "input.txt"

    getter = urllib.request.build_opener()
    getter.addheaders.append(("Cookie", f"session={session_cookie}"))
    urllib.request.install_opener(getter)
 
    try:
        response, _ = urllib.request.urlretrieve(url, input_name)
        return input_name
    except urllib.error.HTTPError as e:
        return None
    
def getNumbers(line):
    nums = re.findall(r"\d+",line)
    numInts = []
    for num in nums:
        numInts.append(int(num))
    return numInts

def getSeeds(line): 
    numbers = getNumbers(line)
    dict = OrderedDict()
    for num in sorted(numbers):
        dict[num] = num
    print(dict)
    return dict

def isMap(line):
    if re.search("map",line):
        return True
    return False

def fillMap(line,map):
    positions = getNumbers(line)
    it = 0
    for x in range(positions[0],positions[0]+positions[2]+1):
        map[x] = positions[1]+it
        it = it +1

def advanceLevel(seeds,map):
    print(map)
    for key in seeds:
        if key in map:
            orgSeed = seeds[key]
            del seeds[key]
            seeds[map[key]] = orgSeed

def generateMap():

    return map

def iterateDicts(lines,listOfMaps):
    map = OrderedDict()
    #TODO
    for line in lines:
        if isMap(line):
            map.clear()
        elif line == '\n':
            map = generateMap(line)
        else:
            fillMap(line,map)
            listOfMaps.append(map)
    return listOfMaps

def getLowestSeed(seeds):
    lowestSeed = list(seeds.keys())[0]
    for seed in seeds:
        if seeds[seed] < seeds[lowestSeed]:
            lowestSeed = seeds[lowestSeed]
    return lowestSeed
 
 
def main():
    #url = "https://adventofcode.com/2023/day/3/input"
    #session_cookie = "53616c7465645f5f18facde817a82dbe29570bcb5b59eb4b14d3bc50b5b3820085ff017df59c46f31767f786c266b7431fcfb1fbe5ed22a29e980753ba4e7fb2"
 
    #file = getInput(url,session_cookie)
    #file = "input.txt"
    file = "/home/hugots/projects/leisure/adventOfCode2023/day5_py/aux.txt"
    f = open(file, 'r')
    lines = f.readlines()
    f.close()
    #Get data
    seeds = getSeeds(lines[0])
    lines = lines[2:]
    lines.append('\n')
    listOfMaps = iterateDicts(lines)
    print(listOfMaps)
    #lowestSeed = getLowestSeed(seeds)
    #print("The seed with lowest position is "+ lowestSeed + "with value" + seeds[lowestSeed] )

 
if __name__ == "__main__":
    main()