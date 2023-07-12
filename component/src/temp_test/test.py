
f = open('CMakeCache.txt',"br+",1024)
lines = f.readlines()

f_data = b''
for i in lines:
    f_data += i

print(" f_data line :")
print(f_data.hex()) 
print(bytes.fromhex(f_data.hex())) 
print(" f_data line .")

f2 = open('CMakeCache222.txt',"w",1024)
f2.write(f_data.hex())
f2.close()

s = "\n"
for i in range(0,1000):
    s += "-------------------------------------------"

bs = bytes(s,'utf-8')

f.close()