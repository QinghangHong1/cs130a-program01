#graph.py
import sys
import numpy as np
import matplotlib.pyplot as plt
plt.style.use('ggplot')
def loadData(jd, jr, js, pd, pr, ps, counter):
    jdData = np.loadtxt(jd)
    print(jdData.dtype)
    jrData = np.loadtxt(jr)
    jsData = np.loadtxt(js)
    pdData = np.loadtxt(pd)
    prData = np.loadtxt(pr)
    psData = np.loadtxt(ps)
    x = np.loadtxt(counter)
    plt.plot(x,jdData, label = "Jenkins and Division")
    plt.plot(x,jrData, label ="Jenkins and Reciprocal")
    plt.plot(x,jsData, label ="Jenkins and SquareRoot")
    plt.plot(x,pdData, label ="Pearson and Division")
    plt.plot(x,prData, label ="Pearson and Reciprocal")
    plt.plot(x,psData, label ="Pearson and SquareRoot")
    plt.legend(bbox_to_anchor=(1.05, 1), loc=2, borderaxespad=0.)
    plt.legend(loc='lower right')

    plt.xlabel("Number of items inserted")
    plt.ylabel("False positive rate")
    plt.title("False positive rate fixing m = 1000 and k = 10")
    plt.show()

    
if __name__ == "__main__":
    loadData(sys.argv[1],sys.argv[2],sys.argv[3],sys.argv[4],sys.argv[5],sys.argv[6],sys.argv[7])
