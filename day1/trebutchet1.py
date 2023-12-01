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
        return None;

def find_extremes_numbers(input_text):
    pattern = re.compile(r"\d", re.IGNORECASE)
    integers = pattern.findall(input_text)
    n_integers = len(integers)
    if(n_integers == 0):
        return 0
    elif(n_integers == 1):
        return (int(integers[0]+integers[0]))
    else:
        return int(integers[0]+integers[n_integers-1])

def total_calibration_values(calibration_doc):
    sum = 0
    with open(calibration_doc) as file:
        for line in file:
            sum+= find_extremes_numbers(line)
    return str(sum)

def print_calibration_sum_from_file(file_path):
    print("The sum of calibration values of {} is: {}".format(
    file_path,
    total_calibration_values(file_path)
))



def main():
    url = "https://adventofcode.com/2023/day/1/input"
    session_cookie = "53616c7465645f5f18facde817a82dbe29570bcb5b59eb4b14d3bc50b5b3820085ff017df59c46f31767f786c266b7431fcfb1fbe5ed22a29e980753ba4e7fb2"

    print_calibration_sum_from_file(getInput(url,session_cookie))
    #print_calibration_sum_from_file("aux.txt")


if __name__ == "__main__":
    main()
    

