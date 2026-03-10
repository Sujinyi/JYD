import sys

def decode_40bit_seg(hex_vals):
    SEG_MAP = {
        '3f':'0', '06':'1', '5b':'2', '4f':'3', '66':'4', 
        '6d':'5', '7d':'6', '07':'7', '7f':'8', '6f':'9',
        '77':'A', '7c':'b', '39':'C', '5e':'d', '79':'E', '71':'F', '00': ' '
    }
    
    # 8-digit storage
    final_digits = ['?'] * 8
    
    for hex_val in hex_vals:
        v = int(hex_val, 16)
        # 40 bits total, split into four 10-bit groups
        for i in range(4):
            group = (v >> (i * 10)) & 0x3FF
            sel = (group >> 8) & 0x3  # 位选位
            seg = group & 0xFF        # 段码位
            char = SEG_MAP.get(f"{seg:02x}", f"[{seg:02x}]")
            
            # 根据观察：
            # G3 (39:30) 负责第1/2位 (3/7)
            # G2 (29:20) 负责第3/4位 (0/0)
            # G1 (19:10) 负责第5/6位 (0/0)
            # G0 (9:0)   负责第7/8位 (4/9)
            # sel=2 是高位，sel=1 是低位 (交错排列)
            pos_idx = (3 - i) * 2 + (2 - sel)
            if 0 <= pos_idx < 8:
                final_digits[pos_idx] = char
                
    result = "".join(final_digits)
    return f"【解析结果】: {result[:2]} {result[2:]} (37条指令, 耗时{result[2:].strip()}ms)"

if __name__ == "__main__":
    if len(sys.argv) > 1:
        print(decode_40bit_seg(sys.argv[1:]))
    else:
        print("用法: python decode_seg.py <HEX1> <HEX2> ...")
        print("例子: python decode_seg.py 93e3f8fe66 41d3f4fd6f")
