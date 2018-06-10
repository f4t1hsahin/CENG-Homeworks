import random
def hyphenate(x):
    L=[]
    ind=0
    unluler=[ "a" , "e", "I", "i", "O", "o", "U", "u"]
    while ind!=len(x)+1 and len(x)!=0:
        if x[ind] not in unluler:
            if ind==len(x)-1:
                L.append(x[:ind+1])
                break
            else:
                ind+=1
        else:
            if ind==len(x)-1:
                L.append(x[:ind+1])
                break
            else:
                ind+=1
                if x[ind] in unluler:
                    L.append(x[:ind])
                    x = x[ind:]
                    ind = 0
                else:
                    while ind!=0:
                        if ind==len(x)-1:#son
                            L.append(x[:ind+1])
                            x=x[ind+1:]
                            break
                        else:
                            ind+=1
                            if x[ind] in unluler:
                                L.append(x[:ind-1])
                                x = x[ind-1:]
                                ind = 0
    return L
def execute():
	sayilar=raw_input()#n ve m sayisi
	limitword=int(sayilar[:sayilar.index(" ")])
	limitchr=int(sayilar[sayilar.index(" ")+1:])
	ilksatir=raw_input()
	ilksatir=" "+ilksatir
	if ilksatir[-1]!="." and ilksatir[-1]!=" ":
		ilksatir=ilksatir+" "	
	while True:#input
		t=raw_input()
		if t=="=":
			break
		if t[-1]!="." and t[-1]!=" ":
			t=t+" "	
		ilksatir+=t		
	def ayirici(strg):#bosluga gore
		if strg=="":
			return []
		elif strg ==".":
			return strg
		L=strg.split(" ")
		uzunluk=len(L[:])
		i=0
		while i<uzunluk:
			if i%2==1:
				L.insert(i," ")
				uzunluk+=1
			i+=1	
		return L
	def nokta_ayirici(metin):#noktaya gore
		L=metin.split(".")
		uzunluk=len(L[:])
		i=0
		while i<uzunluk:
			if i%2==1:
				L.insert(i,".")
				uzunluk+=1
			i+=1	
		return L
	def cagirici(x):
		for i in range(len(x)):
			for j in range(len(x[i])):
				if len(x[i][j])>1:
					x[i][j]=hyphenate(x[i][j])
		return x	
	def ekleyici(a):#nested list cikaran
		L1=[]
		for i in range(len(a)):
			if len(a[i]):
				for j in (range(len(a[i]))):
					L1.append(a[i][j])
		return L1  
	def stats(heceler):#dictionary
		dd={}
		for i in range(len(heceler)-1):
			if heceler[i] not in dd:
				dd[heceler[i]]={}
				dd[heceler[i]][heceler[i+1]]=1
			else:
				if heceler[i+1] not in 	dd[heceler[i]]:
					dd[heceler[i]][heceler[i+1]]=1
				else:
					dd[heceler[i]][heceler[i+1]]+=1	
		return dd	
	def maxlar(dd):#maxlari bulan fonksiyon
		def getKey(tuples):#value ya gore siralama
			return tuples[1]
		L0=[]
		for i in dd:
			L_i=dd[i].items()
			L_i=sorted(L_i,key=getKey)
			L_i=[i]+L_i[-2:]
			L0.append(L_i)
		return L0		
	def randoms(strg,L):#random choice yapan fonksiyon
		if strg==".":
			return random.choice(L)
		for i in L:
			if i[0]==strg and len(i)==3:
				L=[i[1][0]]+[i[2][0]]
			elif i[0]==strg:
				L=[i[1][0]]	
		return random.choice(L)
	def generator(strng):#yeni hece ureten fonksiyon
		if strng==".":
			if "." in dic.keys():
				a=randoms(strng,dic["."].keys()+dic[" "].keys())
			else:a=randoms(strng,dic[" "].keys())	
		else:	
			a=randoms(strng,maxs)
		a=str(a)
		return a		  					
	dic=stats(ekleyici(ekleyici(cagirici(map(ayirici,nokta_ayirici(ilksatir))))))
	maxs=maxlar(dic)
	uzunluk=0
	kelime=-1
	if "." in dic.keys():
		ilkhece=random.choice(dic[" "].keys()+dic["."].keys())
	else:
		ilkhece=random.choice(dic[" "].keys())
	a=ilkhece
    	while True:#outputu ureten     
		hece=generator(ilkhece)
		a+=hece
		uzunluk+=len(hece)
		ilkhece=hece
		if hece=="." or hece==" ":
			kelime+=1
		if ((uzunluk>=limitchr) or (kelime>=limitword)) and (hece=="." or hece==" "):
			break
	print a
execute()

