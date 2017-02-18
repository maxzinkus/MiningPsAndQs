txt = open('output.txt', 'r').read()
out = open('mods.txt', 'w')

for line in txt.split('\n'):
   print(line)
   out.write(str(int(''.join(line.split(':')), 16)))
   out.write('\n')
out.close()
