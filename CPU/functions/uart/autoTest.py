import operator, os

def GenerateData(path_asm):
    ###     xxx.asm生成code.txt     ###
    #path_asm = input("输入测试所用.asm文件路径:")
    os.system("java -jar Mars_debug.jar mc CompactDataAtZero a \
dump .text HexText code.txt " + path_asm)
    os.system("java -jar Mars_debug.jar mc CompactDataAtZero a \
dump 0x00004180-0x00004fffc HexText code_handler.txt " + path_asm)
    
    coe_data = '''
memory_initialization_radix=16;
memory_initialization_vector=
'''
    print(coe_data)
    code_txt = open('code.txt', 'r').readlines()
    code_count = len(code_txt)
    for line in code_txt:
        coe_data += line[:-1] + ',\n'
    for i in range(1120 - code_count):
        coe_data += '00000000,\n'
    handlercode_txt = open('code_handler.txt', 'r').readlines()
    for line in handlercode_txt:
        coe_data += line[:-1] + ',\n'
    coe_data += '00000000;\n'

    with open(r"E:\practice\ipcore_dir\init_IM.coe", "w") as f:
        f.write(coe_data)
    print(coe_data)

    
    
GenerateData('mips1.asm')
