import re 
import urllib.request

def get_input(url, session_cookie):
    input_name = "input.txt"

    getter = urllib.request.build_opener()
    getter.addheaders.append(("Cookie", f"session={session_cookie}"))
    urllib.request.install_opener(getter)

    try:
        response, _ = urllib.request.urlretrieve(url, input_name)
        return input_name
    except urllib.error.HTTPError as e:
        return None;

def get_recordBeating(time,maxDistance):
    recordBeatings = 0
    half = int(time / 2)
    for i in range(0,half+1):
        distance = i*(time -i)
        if(distance > maxDistance):
            recordBeatings = recordBeatings + 1
    if(time%2 != 0):
        return (recordBeatings*2)
    else:
        return (recordBeatings*2 -1)

def get_number(line):
    ints = []
    regex = r"\d+"
    totalNumber= ""

    pattern = re.compile(regex, re.IGNORECASE)
    nums = pattern.findall(line)
    for num in nums:
        totalNumber += num
    return int(totalNumber)

def get_total_ways_of_breaking_record(file):
    first_line = True
    times = 0
    distances = 0
    res = 1
    cont = 0
    try:
        with open(file, 'r') as file:
            for line in file:
                if first_line:
                    times = (get_number(line))
                    first_line = False
                else:
                    distances = get_number(line)
    except FileNotFoundError:
        print(f"The file '{file}' was not found.")
    except IOError as e:
        print(f"Error opening the file '{file}': {e}")

    return get_recordBeating(times,distances)

def main():
    url = "https://adventofcode.com/2023/day/6/input"
    session_cookie = "53616c7465645f5f18facde817a82dbe29570bcb5b59eb4b14d3bc50b5b3820085ff017df59c46f31767f786c266b7431fcfb1fbe5ed22a29e980753ba4e7fb2"

    total = get_total_ways_of_breaking_record(get_input(url,session_cookie))
    #total = get_total_ways_of_breaking_record("aux.txt")
    print("Result:" + str(total))

if __name__ == "__main__":
    main()
    