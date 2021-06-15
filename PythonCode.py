import re
import string

FileInputName = "List.txt"
FileOutputName = "frequency.dat"

InputFile = open(FileInputName)     #Opens list.txt and frequency.dat for reading and editing, in .dat's case
OutFile = open (FileOutputName, 'w')
dictItemList = {}    #Will be used to get frequency data throughout the program
textLines = []

def SetFeqFileName(fileName):
    FileOutputName = fileName
    return 0

def PrintAllDict():                          #Prints each item and value in the dictionary
    for item, freq in dictItemList.items():
        print(" {}: {}".format(item, freq))

def GetFreqItem(item):                       #Gets and returns the frequency of an item
    if item in dictItemList.keys():          #Looks for the item first. If the item isnt in the list, it returns a 0
        return dictItemList[item]
    else:
        return 0

def TxtToDat():                              #Writes the items and freq of item to a file
    for item, freq in dictItemList.items():  #Goes through the dictionary and writes a line for each item
        OutFile.write(item)
        OutFile.write(" ")
        OutFile.write(str(freq))
        OutFile.write('\n')

def CloseFiles():                           #Is called to close both files in Python
    InputFile.close()
    OutFile.close()



for line in InputFile:                      #Removes the newline at the end of each line in the text file
    line = line.rstrip()
    textLines.append(line)
                                          
for line in textLines:                      #Compares each string in textLines list with the dictionary. If the key is not in the dictionary, it adds a new one
    if line in dictItemList:                #with a value of 1. If the key does exist, it adds 1 to the value
        dictItemList[line] += 1             
    elif line not in dictItemList:
        dictItemList[line] = 1