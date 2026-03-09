import re
import sys

def parse(filename):
    lines = open(filename).readlines()
    targets = {}
    
    for l in lines:
        match = re.match(r'(0x[0-9a-f]+):\s+(jal|j|b[a-z]*)\s+(.+?)\s*//', l)
        if match:
            addr = int(match.group(1), 16)
            insn = match.group(2)
            op = match.group(3).strip()
            
            # handle cases like 'jal -0x168' or 'bne t1, t2, 0x1c'
            parts = op.split(',')
            offset_str = parts[-1].strip()
            try:
                if offset_str.startswith('-0x'):
                    offset = -int(offset_str[3:], 16)
                elif offset_str.startswith('0x'):
                    offset = int(offset_str[2:], 16)
                else:
                    target = int(offset_str, 16) # like jal 0x5a0
                    if target == 0x414:
                        print(f"FOUND CALL to 0x80000414 from: {l.strip()}")
                    continue
            except:
                continue
                
            target = addr + offset
            if target == 0x80000414:
                print(f"FOUND CALL to 0x80000414 from: {l.strip()}")

if __name__ == '__main__':
    parse(sys.argv[1])
