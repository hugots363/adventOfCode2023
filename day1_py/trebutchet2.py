import urllib.request
import regex as re

word_to_num = {
    "one": "1",
    "two": "2",
    "three": "3",
    "four": "4",
    "five": "5",
    "six": "6",
    "seven": "7",
    "eight": "8",
    "nine": "9"
}
def format_number_to_string(num):
    if len(num) > 1:
        return word_to_num[num]
    return num

def generate_combined_number(first, second):
    return int(format_number_to_string(first)+format_number_to_string(second))

def getInput(url, session_cookie):
    input_name = "input2.txt"

    getter = urllib.request.build_opener()
    getter.addheaders.append(("Cookie", f"session={session_cookie}"))
    urllib.request.install_opener(getter)

    try:
        response, _ = urllib.request.urlretrieve(url, input_name)
        return input_name
    except urllib.error.HTTPError as e:
        return None;
        
def sum_extremes_numbers(input_text):
    regex = r"(one|two|three|four|five|six|seven|eight|nine|[0-9])"
    pattern = re.compile(regex, re.IGNORECASE)
    matches = pattern.findall(input_text, overlapped=True)
    n_integers = len(matches)
    print(input_text)
    print(matches)
    if(n_integers == 0):
        print("0")
        return 0
    else:
        return generate_combined_number(matches[0],matches[n_integers-1])

def total_calibration_values(calibration_doc):
    sum = 0
    with open(calibration_doc) as file:
        for line in file:
            sum+= sum_extremes_numbers(line)
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
    ##Debug purposes##
    #print_calibration_sum_from_file("aux2.txt")
    #print_calibration_sum_from_file("aux.txt")
    #print_calibration_sum_from_file("input2.txt")
    
if __name__ == "__main__":
    main()
    

