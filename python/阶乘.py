

def factorial(n):
	result = n
	for i in range(1,n):
		result*=i
	return result


number = int(input('输入一个正整数:'))
result = factorial(number)
print('%d 阶乘结果:%d'% (number,result))


#递归实现阶乘，调用自己实现
def factorial2(n):
        if n==1:
                return 1
        else:
                print('次乘积:',3)
                return n*factorial(n-1)

        
number = int(input('递归阶乘请输入一个整数:'))
result = factorial(number)
print('%d 阶乘结果:%d'% (number,result))



#分治思想，但是递归会消耗大量计算机资源，因为要不停的开栈
#斐波那契数列
def fab(n):
        if n<1:
                print('输入有误！')
                return -1
        if n==1 or n==2:
                return 1
        else:
                return fab(n-1)+fab(n-2)


result =fab(20)
if result != -1:
        print('总共有%d对小兔崽子诞生！' % result)




#汉诺塔函数
def hanoi(n,x,y,z):
        if n==1:
                print(x,'-->',z)
        else:
                hanoi(n-1,x,z,y)#将前n-1个盘子从x移动到y上
                print(x,'-->',z)#将最底下的最后一个盘子从x移动到z上
                hanoi(n-1,y,x,z)#将y 上的n-1个盘子移动到z上

n = int(input(' 请输入汉诺塔的层数:'))
hanoi(n,'x','y','z')
                


#一个任务

def save_file(boy,girl,count):
        boy_file_name = 'boy_' + count + '.txt'
        girl_file_name = 'girl_' + count + '.txt'
                
        boy_file = open(boy_file_name,'w')
        girl_file = open(girl_file_name,'w')
                
        boy_file.writelines(boy)
        girl_file.writelines(girl)

        boy_file.close()
        girl_file.close()


def split_file(file_name):  
        f=open('record.txt')

        boy = []
        girl = []
        count = 1

        for each_line in f:
                if each_line[:6] != '======':
                        (role,line_spoken) = each_line.split(':',1)
                        if(role =='小甲鱼'):
                                boy.append() = line_spoken
                        if(role =='小客服'):
                                girl.append() = line_spoken
                else:
                        #保存文件
                        save_file(boy,girl,count)
                        boy = []
                        girl = []
                        count+=1


        save_file(boy,girl,count)

        f.close()





import random
secret = random.randint(1,10)


import pickle
my_list = [123,3.14,'小甲鱼',['another list']]
pickle_file=open('my_list.pkl')
pickle.dump(my_list,pickle_file)
pickle_file.close()

pickle_file=open('my_list.pkl','rb')
my_list2= pickle.load(pickle_file)







































        

        
