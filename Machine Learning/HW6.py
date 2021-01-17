import numpy as np 
import random
import math


i = 0
input = np.zeros((1000, 11))
with open ("train.txt") as trainingData :
    for line in trainingData:
        input[i] = line.split(" ")
        print ("What")
        i = i + 1
