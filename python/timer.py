import time as t


class MyTimer():
    def __init__(self):
        self.uint=['年','月','天','小时','分钟','秒']
        self.prompt="未开始计时！"
        self.lasted=[]
        self._start=0
        self._stop=0
        
        
    def __str__(self):
        return self.prompt
    __repr__ =__str__

    def __add__(self,other):
        prompt="总共运行了"
        result =[]
        for index in range(6):
            result.append(self.lasted[index]+other.lasted[index])
            if result[index]:
                prompt +=(str(result[index])+self.uint[index])
        print(prompt)
    
    #开始计时
    def start(self):
        self._start=t.localtime()
        self.prompt="提示：请先调用stop()停止计时！"
        print("计时开始")
        
    #停止计时
    def stop(self):
        if not self._start:
            print("提示：请先调用start()停止计时！")
        self._stop=t.localtime()
        self._calc()
        print("计时结束")

    #内部方法，计算时间
    def _calc(self):
        self.lasted=[]
        self.prompt="总共运行了"
        for index in range(6):
            self.lasted.append(self._stop[index]-self._start[index])
            if self.lasted[index]:
                self.prompt +=(str(self.lasted[index])+self.uint[index])
       # print(self.prompt)
       #为下一轮计时  初始化变量
        self._start=0
        self._stop=0




class A():
    def __str__(self):
        return "我是天才!"

class B():
    def __repr__(self):
        return "小甲鱼帅哥"

class Rectangle:
    def __init__(self,width=0,height=0):
        self.width = width
        self.height = height
        
    def __setattr__(self,name,value):
        if name == 'square':
            self.width = value
            self.height = value
        else:
            super().__setattr__(name,value)

    def getArea(self):
        return self.width*self.height
    





        
