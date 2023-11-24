# c-project-nicolas-nour

## Objective
The objective of this project is to code a method of statistical data compression that reduces the
length of the coding of an alphabet, i.e. such that the average length of a coded text is minimal.
This method is the basis of the Huffman code.

## Implementation
Our code relies on an internal occurence table which has the frequency of each letter in the alphabet depending on if we have an English or French text we want to encode.

## Commands

### Compile and run the program

#### Compile on Windows
Windows requires the installation of a third-party software to run commands like `gcc` or `make`.\
Enter: `mingw32-make`

#### Compile on Linux
Enter: `make`

#### Run the program
Simply type: `./EXEC`

### Commit a new change
* `$ git status`
* `$ git add filename.txt`
* `$ git commit -m "Description of the changes"`
* `$ git push`

### Work on a branch
* To create a new branch and switch to it at the same time, you can run `$ git checkout -b branch-name`
* To switch back to the main branch, run `$ git checkout main`
* To get changes from the main branch on your branch, run `$ git pull`
* To merge master with a branch, run `$ git merge branch-name`
