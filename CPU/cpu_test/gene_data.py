import random
import os
import shutil


def insert_label(filepath):
    with open(filepath, 'r+') as f:
        lines = f.readlines()
        for i in range(10):
            pos = random.randint(110, len(lines)-1)
            lines.insert(pos, 'loop'+str(i)+':\n')
        f.seek(0, 0)  # 将指针移到开头清空后重新写入即可覆盖原文档
        f.truncate()
        tag = 0
        for line in lines:
            if(line[0:5] == '.text'):
                tag = 1
                f.write('.text\n')
                f.write('li $28 0\n')
                f.write('li $29 0\n')
                continue
            if(tag == 0):
                f.writelines(line)
            elif(line[0].isalpha() != 0):
                f.writelines(line)


def insert_alu(filepath):
    ins_set = ['add', 'sub', 'addi']
    with open(filepath, 'r+') as f:
        lines = f.readlines()
        for i in range(10):
            pos = random.randint(50, len(lines)-1)
            index = random.randint(0, 2)
            rs = random.randint(0, 31)
            rt = random.randint(0, 31)
            rd = random.randint(0, 31)
            if(index == 2):
                lines.insert(pos, 'addi '+'$'+str(rt)+' '+'$' +
                             str(rs)+' '+str(random.randint(0, 5000))+'\n')
            else:
                lines.insert(
                    pos, ins_set[index]+' $'+str(rd)+' '+'$'+str(rs)+' '+'$'+str(rt)+'\n')

        f.seek(0, 0)  # 将指针移到开头重新写入即可覆盖原文档
        f.truncate()
        f.writelines(lines)


def insert_md(filepath):
    ins_set = ['div', 'divu']
    with open(filepath, 'r+') as f:
        lines = f.readlines()
        for i in range(10):
            pos = random.randint(110, len(lines)-1)
            index = random.randint(0, 1)
            rs = random.randint(0, 31)
            rt = random.randint(1, 31)
            rt_val = 0
            while rt_val == 0:
                rt_val = random.randint(-30000, 50000)
            lines.insert(pos-1, 'li'+' $'+str(rt)+' '+str(rt_val)+'\n')
            lines.insert(pos, ins_set[index]+' ' +
                         '$'+str(rs)+' '+'$'+str(rt)+'\n')

        f.seek(0, 0)  # 将指针移到开头重新写入即可覆盖原文档
        f.truncate()
        f.writelines(lines)


def insert_jump(filepath):
    PC_change_set = ['j', 'jal', 'beq', 'bne', 'blez', 'bltz', 'bgez', 'bgtz']
    ins_set = ['j', 'jal']
    with open(filepath, 'r+') as f:
        lines = f.readlines()
        pos = 110
        for i in range(10):
            while(lines[pos-1].split(' ')[0] in PC_change_set or lines[pos].split(' ')[0] in PC_change_set or lines[pos+1].split(' ')[0] in PC_change_set):
                pos = random.randint(110, len(lines)-2)
            index = random.randint(0, 1)
            lines.insert(pos, ins_set[index]+' loop' +
                         str(random.randint(0, 9))+'\n')

        f.seek(0, 0)  # 将指针移到开头重新写入即可覆盖原文档
        f.truncate()
        f.writelines(lines)


def insert_branch(filepath):
    PC_change_set = ['j', 'jal', 'beq', 'bne', 'blez', 'bltz', 'bgez', 'bgtz']
    ins_set = ['beq', 'bne', 'blez', 'bltz', 'bgez', 'bgtz']
    with open(filepath, 'r+') as f:
        lines = f.readlines()
        pos = 110
        for i in range(30):
            while(lines[pos-1].split(' ')[0] in PC_change_set or lines[pos].split(' ')[0] in PC_change_set or lines[pos+1].split(' ')[0] in PC_change_set):
                pos = random.randint(120, len(lines)-2)
            rs = random.randint(0, 31)
            rt = random.randint(0, 31)
            index = random.randint(0, 5)
            if(index == 0 or index == 1):
                lines.insert(pos, ins_set[index]+' $'+str(rs)+' ' +
                             '$'+str(rt)+' loop'+str(random.randint(0, 9))+'\n')
            else:
                lines.insert(
                    pos, ins_set[index]+' $'+str(rs)+' loop'+str(random.randint(0, 9))+'\n')
        f.seek(0, 0)  # 将指针移到开头重新写入即可覆盖原文档
        f.truncate()
        f.writelines(lines)


def insert_cp0(filepath):
    ins_set = ['mtc0', 'mfc0']
    with open(filepath, 'r+') as f:
        lines = f.readlines()
        for i in range(10):
            pos = random.randint(50, len(lines)-1)
            index = random.randint(0, 2)
            rt = random.randint(0, 31)
            while True:
                rd = random.randint(0, 31)
                if(rd!=15):
                    break
            if(index == 2):
                lines.insert(pos, 'mfc0 '+'$'+str(rt)+' '+'$'+str(rd)+'\n')
            else:
                lines.insert(pos, 'mtc0 '+'$'+str(rt)+' '+'$'+str(rd)+'\n')

        f.seek(0, 0)  # 将指针移到开头重新写入即可覆盖原文档
        f.truncate()
        f.writelines(lines)


def count(filepath):
    with open(filepath, 'r+') as f:
        lines = f.readlines()
        f.seek(0, 0)
        f.truncate()
        pc = 0x3000
        tag = 0
        for line in lines:
            if(line[0:5] == '.text'):
                tag = 1
            if(line[0:5] == '.text' or line[0:4] == 'loop' or line[0:4] == 'tail' or len(line) <= 2):
                f.writelines(line)
            elif(tag == 0):
                f.writelines(line)
            elif(tag == 1):
                f.writelines('#'+hex(pc)+'\n')
                pc += 4
                f.writelines(line)


def gene():
    shutil.rmtree('testdata')
    os.system('coklr testdata --instr_set c4 --n_case 90 --k_instr 948')


def main():
    gene()
    names = os.listdir('testdata')
    for name in names:
        name = 'testdata/'+name
        filepath = name
        insert_cp0(filepath)
        insert_branch(filepath)
        insert_jump(filepath)
        insert_md(filepath)
        insert_label(filepath)
        count(filepath)


if __name__ == '__main__':
    main()
