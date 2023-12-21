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
 
def create_matrix(file_path):
    matrix = []
 
    with open(file_path, 'r') as file:
        for line in file:
            char_list = list(line.strip())
            matrix.append(char_list)
    return matrix
 
def is_symbol(char):
    if(char != '.' and not char.isdigit()):
        return True
    return False
 
def get_numbers_and_positions_in_line(string):
    numbers_and_positions = []
 
    # Find all occurrences of numbers in the string
    matches = re.finditer(r'-?\d+', string)
 
    for match in matches:
        number = int(match.group())
        start, end = match.span()
        numbers_and_positions.append((number, start, max(end-1,0)))
 
    return numbers_and_positions
 
def create_nums_and_pos_matrix(file_path):
    nums_and_pos = []
    with open(file_path, 'r') as file:
        for line in file:
            nums_and_pos.append(get_numbers_and_positions_in_line(line))
    return nums_and_pos
 
def check_num_upper(matrix,number,b0,b1,line_number):
    chars = len(matrix[line_number -1])
    norm_border0 = max(0,b0 -1)
    norm_border1 = min(chars-1,b1+2) 
    
    for i in range(norm_border0,norm_border1):
        if(is_symbol(matrix[line_number -1][i])):
            return int(number)
    return 0
 
def check_num_down(matrix,number,b0,b1,line_number):
    chars = len(matrix[line_number -1])
    norm_border0 = max(0,b0 -1)
    norm_border1 = min(chars,b1+2)

    for i in range(norm_border0,norm_border1):
        if(is_symbol(matrix[line_number +1][i])):
            return int(number)
    return 0
 
def check_num_borders(matrix,number,b0,b1,line_number):
    chars = len(matrix[line_number])
    norm_border0 = b0 -1
    norm_border1 = b1+1
    if(norm_border0 >= 0 and is_symbol(matrix[line_number][norm_border0])):
        return int(number)
    if(norm_border1 <= (chars -1) and  is_symbol(matrix[line_number][norm_border1])):
        return int(number)
    return 0
 
def get_gears_sum(matrix, nums_and_pos):
    line_number = 0
    n_Lines = len(nums_and_pos)
    gears_sum = 0
    for line in nums_and_pos:
        print("NLine: " + str(line_number+1))
        if(line):
            if(line_number != 0 and line_number != n_Lines-1):
                for num in line:
                    value = check_num_upper(matrix,num[0],num[1],num[2],line_number)
                    if(value != 0):
                        gears_sum += value
                        print(value)
                        continue
                    value = check_num_borders(matrix,num[0],num[1],num[2],line_number)
                    if(value != 0):
                        gears_sum += value
                        print(value)
                        continue
                    value = check_num_down(matrix,num[0],num[1],num[2],line_number)
                    print(value)
                    gears_sum += value
            elif(line_number == 0):
                for num in line:
                    value = check_num_borders(matrix,num[0],num[1],num[2],line_number)
                    if(value != 0):
                        gears_sum += value
                        print(value)
                        continue
                    value = check_num_down(matrix,num[0],num[1],num[2],line_number)
                    print(value)
                    gears_sum += value
            else:
                for num in line:
                    value = check_num_borders(matrix,num[0],num[1],num[2],line_number)
                    if(value != 0):
                        gears_sum += value
                        print(value)
                        continue
                    value = check_num_upper(matrix,num[0],num[1],num[2],line_number)
                    print(value)
                    gears_sum += value
        line_number = line_number +1
        #print(gears_sum)
    return gears_sum
 
 
 
def main():
    url = "https://adventofcode.com/2023/day/3/input"
    session_cookie = "53616c7465645f5f18facde817a82dbe29570bcb5b59eb4b14d3bc50b5b3820085ff017df59c46f31767f786c266b7431fcfb1fbe5ed22a29e980753ba4e7fb2"
 
    #file = getInput(url,session_cookie)
    #file = "input.txt"
    file = "/home/hutarsan/projects/leisure/advent_code_2023/day3_py/input.txt"
    #file = "aux.txt"
    matrix = create_matrix(file)
    nums_and_pos = create_nums_and_pos_matrix(file) 
    print("total> " + str(get_gears_sum(matrix,nums_and_pos)))
 
if __name__ == "__main__":
    main()