import urllib.request
import re
 
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
    return [int(num) for num in re.findall(r"\d+", line)]


def getSeeds(line): 
    numbers = getNumbers(line)
    list = []
    for num in sorted(numbers):
        list.append(num)
    return list

def isMap(line):
    return "map" in line

def fillMap(line,map):
    positions = getNumbers(line)
    it = 0
    for x in range(positions[1],positions[1]+positions[2]):
        #map[x] = positions[1]+it
        map[x] = positions[0]+it
        it = it +1

def advanceLevel(seeds,map):
    for key in seeds:
        if key in map:
            orgSeed = seeds[key]
            del seeds[key]
            seeds[map[key]] = orgSeed

def iterateDicts(lines):
    listOfMaps = []
    map = {}

    for line in lines:
        if isMap(line):
            map = {}
        elif line == '\n':
            listOfMaps.append(map)
        else:
            fillMap(line, map)

    return listOfMaps

def findSeedLocation(seed, listOfMaps):
    key = seed
    #print("seed: "+str(key))
    for map in listOfMaps:
        if key in map:
            key = map[key]
    return key


def getLowestSeed(seeds,listOfMaps):
    lowestSeed = seeds[0]
    value = 9999999999
    for seed in seeds:
        auxValue = findSeedLocation(seed, listOfMaps)
        if auxValue < value:
            lowestSeed = seed
            value = auxValue
    return value
 
 
def main():
    url = "https://adventofcode.com/2023/day/5/input"
    session_cookie = "53616c7465645f5f18facde817a82dbe29570bcb5b59eb4b14d3bc50b5b3820085ff017df59c46f31767f786c266b7431fcfb1fbe5ed22a29e980753ba4e7fb2"
 
    file = getInput(url,session_cookie)
    file = "/home/hutarsan/projects/leisure/advent_code_2023/day5_py/input.txt"
    #file = "/home/hutarsan/projects/leisure/advent_code_2023/day5_py/aux.txt"
    f = open(file, 'r')
    lines = f.readlines()
    f.close()

    #Get data
    seeds = getSeeds(lines[0])
    lines = lines[2:]
    lines.append('\n')
    listOfMaps = iterateDicts(lines)
    lowestSeed = getLowestSeed(seeds,listOfMaps)
    print("The lowest position in seeds is "+ str(lowestSeed ))

 
if __name__ == "__main__":
    main()