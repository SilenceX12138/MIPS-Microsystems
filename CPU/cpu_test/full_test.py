import os

try:
    os.remove('output/full_cmp.txt')
except FileNotFoundError:
    print()
dirname = os.listdir('testdata')
for asm in dirname:
    os.system(
        'java -jar MARS_debug.jar a mc CompactDataAtZero dump .text HexText cpu/code.txt testdata/'+asm)
    os.system(
        'java -jar MARS_debug.jar a mc CompactDataAtZero dump .text HexText std_cpu/code.txt testdata/'+asm)
    os.system('java -jar MARS_debug.jar a mc CompactDataAtZero dump 0x00004180-0x00004FFC HexText cpu/code_handler.txt testdata/'+asm)
    os.system('java -jar MARS_debug.jar a mc CompactDataAtZero dump 0x00004180-0x00004FFC HexText std_cpu/code_handler.txt testdata/'+asm)
    os.system('test.bat')
    with open('output/cmp_result.txt', 'r') as f:
        s = f.readlines()
        with open('output/full_cmp.txt', 'a') as fp:
            fp.write('----------'+asm+'----------\n')
            fp.writelines(s)
            fp.write('\n')

os.chdir('output')
os.popen('full_cmp.txt')