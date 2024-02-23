'''
Theoretical approach
Terms:
m = number of lines in the input (commands)
n = each instruction a command generates 

The total cost of the algorithm is O(mn*1000), since this loop is done that number of times.
 Therefore, the cost is O(mn)

'''
class Module:
    name = ""
    type = ""
    outMods = {}
    state = "off"

    def __init__(self,name,type,outMods={},state="off"): 
        self.name = name
        self.type = type
        self.outMods = outMods
        self.memMods = {}

    def printData(self):
        print("name:"+self.name)
        print("type:"+self.type)
        print(self.outMods)
        print(self.memMods)
        print("           ")

def extractModule(line):
    halfs = line.split(" -> ")
    if(halfs[0][0] == "%"):
        type = "flipflop"
        name = halfs[0][1:]
    elif(halfs[0][0] == "&"):
        type = "conjunction"
        name = halfs[0][1:]
    else:
        type = "broadcaster"
        name = "broadcaster"

    outMods = halfs[1].split(", ")


    return Module(name,type,outMods)

def moduleLoader(inputPath):
    modules = {}
    conjunctions = set()
    try:
        with open(inputPath, 'r') as file:
            for line in file:
                line = line.rstrip()
                module = extractModule(line)
                modules[module.name] = module
                if(module.type == "conjunction"):
                    conjunctions.add(module.name)
    except FileNotFoundError:
        print(f"The file '{inputPath}' was not found.")

    for module in modules:
        for input in modules[module].outMods:
            if input in conjunctions:
                modules[input].memMods[module] = "low"

    return  modules

def processCommands(modules):
    totalLows = 0
    totalHighs = 0
    commands = [("button","low","broadcaster")]
    
    while(commands):
        command = commands[0]
        origin,pulse, destination  = commands.pop(0)
        if(not destination in modules):
            modules[destination] = Module(destination,"None")
        type = modules[destination].type
        
        if(pulse == "low"):
            totalLows+= 1
        else:
            totalHighs+= 1

        if(type == "broadcaster"):
            for outMod in modules["broadcaster"].outMods:
                commands.append((destination,pulse,outMod))
        elif(type == "flipflop"):
            if(pulse == "low"):
                if modules[destination].state == "high":
                    modules[destination].state = "low"
                else:
                    modules[destination].state = "high"
                for out in modules[destination].outMods:
                    commands.append((destination,modules[destination].state,out))
        else:
            modules[destination].memMods[origin] = pulse
            pulse = "low"    
            for dest,_ in modules[destination].memMods.items():
                if modules[destination].memMods[dest] == "low":
                    pulse = "high"
                    break
            for out in modules[destination].outMods:
                commands.append((destination,pulse,out))

            
    return totalHighs,totalLows

def main():
    modules = moduleLoader("/home/hutarsan/projects/leisure/advent_code_2023/day20_py/input.txt")
    totalHighs = 0
    totalLows = 0
    for x in range (0,1000):
        highs,lows = processCommands(modules)
        totalHighs+= highs
        totalLows += lows
    
    total = totalHighs*totalLows
    print("Total: "+str(total))
    
    
 
if __name__ == "__main__":
    main()