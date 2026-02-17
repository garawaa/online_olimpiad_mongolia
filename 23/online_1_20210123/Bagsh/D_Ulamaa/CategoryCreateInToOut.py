import random
from operator import itemgetter

listcount = 100
for i in range(1,51):
    if listcount < 5000:
        pnum = 5000
    else:
        pnum = 50000
    pnum
    infile_name = '.in'
    outfile_name = '.out'
    infile_name = str(i//10)+str(i%10)+infile_name
    outfile_name = str(i//10)+str(i%10)+outfile_name
    in_file=open(infile_name,"w",encoding='utf-8')
    crilluseg = ['a','b','c','d','e','f','g','x','y','z','а','б','в','г','е','ё','ж','з','й','к','л','м','н','р','с','т','у','ү','п','ч','х']
    ue1 = ['Төр','Цэен','Улам','Цэнд','Ренчин','Мижид','Урт','Балжир','Бор','Пүрэв','Дорж','Ган','Долгор','Сүрэн','Бат','Хүрэл','Ядам','Сосор','Сэсээр','Гоо','Даш']
    ue2 = ['тогтох','баяр','сүрэн','насан','баатар','хүслэн','төгөлдөр','сумаа','марал','жав','хүү','маа','-Амгалан','туяа','-Ойдов','заяа','зул','зол','гэрэл']
    reguseg = ['AР','ИД','ИП','УС','ТА','УК','ИЖ','ИС','АВ','ПС','ЖР','ЖС','КЗ','УЛ','ИХ','ХИ','АН','АХ']
    utas = ['99','94','95','91','96','90','88','89','80','86']
    for lc in range(listcount):
        Sner = random.choice(ue1)+random.choice(ue2)
        Sovog = random.choice(ue1)+random.choice(ue2)
        Sregisternum = random.choice(reguseg)+str(random.randint(0,pnum))
        Sutas = random.choice(utas)+str(random.randint(100000,999999))
        if listcount < 5000:
            Sbaiguullaga = random.choice(crilluseg)
        else:
            Sbaiguullaga = random.choice(crilluseg)+random.choice(crilluseg)
        Sognoo = "2021-01-21 "+str(random.randint(0,23))+":"+str(random.randint(0,59))+":"+str(random.randint(0,59))
        S = Sner+","+Sovog+","+Sregisternum+","+Sutas+","+Sbaiguullaga+","+Sognoo
        in_file.write(S+"\n")
    in_file.close()
    in_file=open(infile_name,"r",encoding='utf-8')
    mylines = in_file.readlines()
    bgllg = {}
    for line in mylines:
        values = line.split(',')
        if values[4] in bgllg.keys():
            bgllg[values[4]].add(values[2])
        else:
            bgllg[values[4]] = set()
            bgllg[values[4]].add(values[2])
    regs = []
    for key in bgllg:
        regs.append({'baiguullaga':key,'num':len(bgllg[key])})
       
    out_file = open(outfile_name,'w',encoding='utf-8')
    regs.sort(key=itemgetter('baiguullaga'))
    regs.sort(key=itemgetter('num'), reverse=True)
    for row in regs:
        out_file.write(row['baiguullaga']+" "+str(row['num'])+"\n")
    in_file.close()
    out_file.close()
    listcount+=1000  