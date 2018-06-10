def query(tree,info):   
    def evaluator(lst):
        if lst[0]=="in":
            return d[lst[1]] in lst[2]
        if lst[0]=="not":
            return not evaluator(lst[1])
        if lst[0]=="and":
            res=1
            for i in range(1,len(lst)-1):
                res*=evaluator(lst[i]) and evaluator(lst[i+1])
            return bool(res)        
        if lst[0]=="or":
            res=0
            for i in range(1,len(lst)-1):
                res+=evaluator(lst[i]) or evaluator(lst[i+1])
            return bool(res)
        if lst[0]=="<":
            if type(lst[2])!=str:
                return d[lst[1]]<lst[2]
            else:
                return d[lst[1]]<d[lst[2]]    
        if lst[0]==">":
            if type(lst[2])!=str:
                return d[lst[1]]>lst[2]
            else:
                return d[lst[1]]>d[lst[2]] 
        if lst[0]=="==":
            if type(lst[2])!=str:
                return d[lst[1]]==lst[2]
            else:
                return d[lst[1]]==d[lst[2]] 
        if lst[0]=="!=":
            if type(lst[2])!=str:
                return d[lst[1]]!=lst[2]
            else:
                return d[lst[1]]!=d[lst[2]] 
    def dictionary(lst):
        d={}
        for i in lst:
            d[i[0]]=i[1]
        return d
    d=dictionary(info)
    def recurs(tree):
        if type(tree)==str:
            return tree
        if evaluator(tree[0]):
            return recurs(tree[1])
        else:
            return recurs(tree[2])
    return recurs(tree)
