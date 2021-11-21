#List functions
def mostFrequent(list1):
    highest = 0
    count =0
    for i in list1:
        c = list1.count(i)
        if c >= count :
            count = c
            highest = i

    return highest

def Intersection(list1, list2):
    list3 = []
    for i in list1:
        if i in list2:
            if i not in list3:
                list3.append(i)
    
    return list3
def Difference(list1,list2): # list1-list2
    "list1 - list2"
    
    for i in list2:
        if i in list1:
            count = list1.count(i)
            if count > 1:
                for _ in range(0,count):
                    list1.remove(i)
            else:  list1.remove(i)  

    return list1

def Union(list1,list2):
    list3 = [] 
    for i in list1:
        if i not in list3:
            list3.append(i)
    for i in list2:
        if i not in list3:
            list3.append(i)
    return list3        
