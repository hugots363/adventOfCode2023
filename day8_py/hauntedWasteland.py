import urllib.request


'''
Theoretical approach
Terms:
m = lines in the file (total nodes)
n = chars per line
t = number of instructions
r = number of times that is necessary to traverse all the instructions

The algorithmic cost of this solution is O(n)+ O(m*n) + O(m*n*t*r) = O(m*n*t*r)
'''


def get_input(url, session_cookie):
    input_name = "input.txt"

    getter = urllib.request.build_opener()
    getter.addheaders.append(("Cookie", f"session={session_cookie}"))
    urllib.request.install_opener(getter)

    try:
        response, _ = urllib.request.urlretrieve(url, input_name)
        return input_name
    except urllib.error.HTTPError as e:
        return None

def getTrail(input):
     with open(input) as f:
            trail = f.readline()
            return trail

def generateDict(input):
    header = 0
    nodes = {}
    with open(input) as f:
        for line in f:
            if(header != 2 ):
                header += 1
            else:
                nodes[line[0:3]] = (line[7:10],line[12:15])
    return nodes

def traverseTrail(nodes,trail):
    iterations = 0
    currentNode = "AAA"
    while(True):
        for dir in trail:
            if(dir == 'L' or dir == 'R' ):
                if(currentNode == "ZZZ"):
                    return iterations
                else:
                    iterations += 1
                    if dir == 'L':
                        currentNode = nodes[currentNode][0]
                    else:
                        currentNode = nodes[currentNode][1]

def main():
    url = "https://adventofcode.com/2023/day/8/input"
    session_cookie = "53616c7465645f5f18facde817a82dbe29570bcb5b59eb4b14d3bc50b5b3820085ff017df59c46f31767f786c266b7431fcfb1fbe5ed22a29e980753ba4e7fb2"

    input = get_input(url,session_cookie)
    #input = "aux2.txt"

    trail = getTrail(input)
    nodes = generateDict(input)
    iter = traverseTrail(nodes,trail)
    print("Total iterations: "+ str(iter))

if __name__ == "__main__":
    main()
    