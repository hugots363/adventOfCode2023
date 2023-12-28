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
    nums = re.findall(r"\d+",line)
    numInts = []
    for num in nums:
        numInts.append(int(num))
    return numInts

def getSeeds(line):
    return getNumbers(line)

def isMap(line):
    if re.search("map",line):
        return True
    return False

def getListedDicts(lines,dicts):
    nMap = 0
    for line in lines:
        print(line)
        if isMap(line):
            print(line)
        else:
            print(getNumbers(line))


 
 
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
    dicts = []
    lines = lines[2:]
    getListedDicts(lines,dict)

 
if __name__ == "__main__":
    main()