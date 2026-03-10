"""将Vivado COE文件转换为 $readmemh 可用的纯hex格式"""
import sys
import re

def coe_to_hex(coe_path, hex_path):
    with open(coe_path, 'r') as f:
        content = f.read()
    
    # 移除注释和空行
    lines = content.split('\n')
    data_started = False
    hex_values = []
    
    for line in lines:
        line = line.strip()
        if not line or line.startswith('//'):
            continue
        if 'memory_initialization_vector' in line:
            data_started = True
            # 处理同一行可能有数据的情况
            parts = line.split('=')
            if len(parts) > 1 and parts[1].strip():
                val = parts[1].strip().rstrip(',').rstrip(';')
                if val:
                    hex_values.append(val)
            continue
        if data_started:
            # 移除逗号和分号，提取hex值
            vals = line.replace(';', ',').split(',')
            for v in vals:
                v = v.strip()
                if v and re.match(r'^[0-9a-fA-F]+$', v):
                    hex_values.append(v)
    
    with open(hex_path, 'w') as f:
        for val in hex_values:
            f.write(val + '\n')
    
    print(f"Converted {len(hex_values)} words: {coe_path} -> {hex_path}")

if __name__ == '__main__':
    if len(sys.argv) < 3:
        print(f"Usage: python {sys.argv[0]} input.coe output.hex")
        sys.exit(1)
    coe_to_hex(sys.argv[1], sys.argv[2])
