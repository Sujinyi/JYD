import re

def parse_disasm(filepath):
    with open(filepath, 'r') as f:
        lines = f.readlines()
        
    for idx, line in enumerate(lines):
        if 'lui' in line and 'a5' in line:
            parts = line.split(',')
            val_str = parts[1].split('//')[0].strip()
            try:
                if '0x' in val_str:
                    val = int(val_str, 16)
                else:
                    val = int(val_str)
                print(f"[{idx}] {line.strip()} -> {hex(val << 12)}")
            except:
                pass
        if 'addi a5, a5' in line:
             print(f"[{idx}] {line.strip()}")
        if 'ori a5, a5' in line:
             print(f"[{idx}] {line.strip()}")
             
if __name__ == '__main__':
    parse_disasm(r'c:\Users\21186\Desktop\verify\disasm_out.txt')
