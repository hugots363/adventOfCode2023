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

def isMap(line):
    return "map" in line

def fillMap(line,map):
    positions = getNumbers(line)
    it = 0
    map.append((positions[0],positions[1],positions[2]))

def iterateDicts(seed,lines):
    map = []
    auxSeed = seed
    for line in lines:
        if isMap(line):
            map.clear()
        elif line == '\n':
            auxSeed = advanceSeedData(auxSeed,map)
        else:
            fillMap(line, map)
    return auxSeed

def keyInMap(seedValue,maps):
    for map in maps:
        start, end = map[1], map[1] + map[2] + 1
        if seedValue in range(start, end):
            return map[0] + (seedValue - start)
    return -1

def advanceSeedData(seed,maps):
    mapped_value = keyInMap(seed, maps) 

    if mapped_value != -1:
        return mapped_value
    return seed

def getLowestSeed(seeds):
    return min(seeds.values(), default=None)
 
 
def main():
    url = "https://adventofcode.com/2023/day/5/input"
    session_cookie = "53616c7465645f5f18facde817a82dbe29570bcb5b59eb4b14d3bc50b5b3820085ff017df59c46f31767f786c266b7431fcfb1fbe5ed22a29e980753ba4e7fb2"
 
    #file = getInput(url,session_cookie)
    file = "/home/hutarsan/projects/leisure/advent_code_2023/day5_py/input.txt"
    #file = "/home/hutarsan/projects/leisure/advent_code_2023/day5_py/aux.txt"
    f = open(file, 'r')
    lines = f.readlines()
    f.close()

    #Get data
    lowestSeed = 999999999999999999
    nums = getNumbers(lines[0])
    lines = lines[2:]
    lines.append('\n')

    for i in range(0,len(nums),2):
        print("num: "+ str(i))
        for x in range(nums[i], nums[i]+nums[i+1]+1):
            seed = iterateDicts(x,lines)
            if seed < lowestSeed:
                lowestSeed = seed

    print("The lowest position in seeds is "+ str(lowestSeed ))

 
if __name__ == "__main__":
    main()