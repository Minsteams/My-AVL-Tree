import random
import time
import msvcrt
import os

k=0
log=open('log_avltree.txt','w')#日志

def logprint(content):
    global log
    print(content)
    log.write(content)

def loginput(content):
    global log
    log.write(content)
    result=input(content)
    log.write(result)
    log.write("\n")
    return result
    
def genRandomVector(fileName,dataCount,dataMax):
    global k
    outp=open(fileName,'w')
    outp.write("%i"%(k))
    outp.write("\n")
    i = 0
    while i<dataCount:
        j=0
        mLine=""
        while j<k:
            mLine+="%i "%(random.randint(0,dataMax))
            j+=1
        mLine+="\n"
        outp.write(mLine)
        i+=1
    outp.close()

if __name__ == "__main__":
    random.seed()
    k=eval(loginput('K:'))
    dataCount=eval(loginput('DataCount:'))#输入数据数量
    dataMax=eval(loginput('NumberMax:'))#输入最大数字
    
    start = time.time()
    genRandomVector('in_kdtree.txt',dataCount,dataMax)
    end = time.time()
    logprint('Test data created!\nUse time:%lf'%(end-start))
    
    os.system('kdTree.exe')
    stinfo=os.stat('out_kdtree.txt')
    logprint('\nBuilded!\nUse time:%f'%(stinfo.st_mtime - stinfo.st_atime))
    log.close()
    msvcrt.getch();
