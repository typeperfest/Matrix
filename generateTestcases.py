import sys;
from random import randint
import numpy as np

INT_MAX = pow(2, 15) - 1
INT_MIN = -pow(2, 15)

def generateOperands(rows:int, columns:int, operation:chr):
    global firstOperandMatrix
    global secondOperandMatrix
    firstOperandMatrix = np.random.randint(INT_MIN, INT_MAX, (rows, columns))
    if (operation != 'm'):
        secondOperandMatrix = np.random.randint(INT_MIN, INT_MAX, (rows, columns))
    else:
        secondOperandMatrix = np.random.randint(INT_MIN, INT_MAX, (columns, rows))

def generateResult(operation:chr):
    global resultMatrix
    global operationChr
    if (operation == 'a'):
        operationChr = '+'
        resultMatrix = firstOperandMatrix + secondOperandMatrix
    elif (operation == 's'):
        operationChr = '-'    
        resultMatrix = firstOperandMatrix - secondOperandMatrix
    elif (operation == 'm'):
        operationChr = '*'
        resultMatrix = firstOperandMatrix.dot(secondOperandMatrix)
    return

def translateMatrix(matrix, name:str):
    resultStr = "IntMatrix " + name + '{'
    for i in range(len(matrix) - 1):
        resultStr += '{'
        for j in range(len(matrix[i]) - 1):
            resultStr += (str(matrix[i][j]) + ", ")
        resultStr += (str(matrix[i][-1]) + "}, ")
    resultStr += '{'
    for i in range(len(matrix[-1]) - 1):
        resultStr += (str(matrix[-1][i]) + ", ")
    resultStr += (str(matrix[-1][-i]) + "}")
    resultStr += "};\n"
    return resultStr

def outTestCaseToFile(testCaseNumber:int):
    firstNameGenerated = "firstOp" + str(testCaseNumber)
    secondNameGenerated = "secondOp" + str(testCaseNumber)
    resultNameGenerated = "result" + str(testCaseNumber)
    with open("generatedTests.txt", "a") as outFile:
        outFile.write("// Generated test " + str(testCaseNumber) + '\n')
        outFile.write(translateMatrix(firstOperandMatrix, firstNameGenerated))
        outFile.write(translateMatrix(secondOperandMatrix, secondNameGenerated))
        outFile.write(translateMatrix(resultMatrix, resultNameGenerated))
        outFile.write("EXPECT_EQ(" + str(firstNameGenerated) + ' '
                       + operationChr + ' ' + str(secondNameGenerated) + ", " + str(resultNameGenerated) + ");\n")

def runGeneration(rows:int, columns:int, operation:chr, testCaseCount:int):
    for i in range(1, testCaseCount + 1):
        generateOperands(rows, columns, operation)
        generateResult(operation)
        outTestCaseToFile(i)

def printHelp():
    print("Description:")
    print("\tSimple script to generate valid random testcase for matrix::IntMatrix emplmented by this repository.")
    print("\tReady to copy-paste in test source files.")
    print("Usage:")
    print("\tpython3 generateMatrix.py <rows:int> <columns:int> <operation:chr> <testCasesNumber>")
    print("\t\tWhere <operation>={m|a|s} stands for:")
    print("\t\t\t m - multiplication")
    print("\t\t\t a - addition")
    print("\t\t\t s - substraction")
    exit(1)

if __name__ == "__main__":
    if (len(sys.argv) != 5):
        printHelp()

    arg1, arg2, arg3, arg4 = int(sys.argv[1]), int(sys.argv[2]), sys.argv[3], int(sys.argv[4])
    runGeneration(arg1, arg2, arg3, arg4)
    