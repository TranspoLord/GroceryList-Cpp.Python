# GroceryList-Cpp.Python

#What is?
It's the base code for taking in a list of items in txt file form in Python, finding out how many of one type of item there is, storing that data and giving it access to
the C++ code whenever it was requested. The C++ code, also, handled outputing the new info to a new freq.dat file.

#What went well and what went wrong?
I would have to say generally everything went well except the file system portion. It was relatively easy to code everything needed for the program. However, the file system for C++ got to me a little. The code worked, but whenever another option was choosen in the menu for the program, the freq.dat would have all its content removed. This caused no output for the histogram. I was able to get it to work after a while. I don't know how I did though. 

#What skills are transferable?
One thing that's transferable is the way I validated the user input. It may not work for other languages, but it only needs to be modified slightly. One way to validate input, as an idea, is to break up the input into a char list or vector, and validate each one against a list or "not-list" of valid inputs. It's a long process but it does work.

#How is it readable?
I made this program readable by including comments and background descriptions on functions I used. The built in functions were not changed. I included comments at every needed point, making sure who ever looks at it can follow the code. 

