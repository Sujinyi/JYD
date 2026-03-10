import re

def reconstruct_display(trace_path):
    SEG_MAP = {
        '3f':'0', '06':'1', '5b':'2', '4f':'3', '66':'4', 
        '6d':'5', '7d':'6', '07':'7', '7f':'8', '6f':'9',
        '77':'A', '7c':'b', '39':'C', '5e':'d', '79':'E', '71':'F', '00': ' '
    }
    
    # Selection pattern to digit position (based on typical 8-digit scan)
    # fe: 11111110 (Digit 0 - Rightmost)
    # fd: 11111101 (Digit 1)
    # fb: 11111011 (Digit 2)
    # f7: 11110111 (Digit 3)
    # ef: 11101111 (Digit 4)
    # df: 11011111 (Digit 5)
    # bf: 10111111 (Digit 6)
    # 7f: 01111111 (Digit 7 - Leftmost)
    
    pos_to_char = {i: '?' for i in range(8)}
    selectors = {
        'fe': 0, 'fd': 1, 'fb': 2, 'f7': 3, 
        'ef': 4, 'df': 5, 'bf': 6, '7f': 7
    }

    try:
        # We look for virtual_seg values in the trace. 
        # Typically these are written to a specific address like 0x80200000 in this SoC.
        # But since we have the hex values from the user, we'll scan for them.
        with open(trace_path, 'r') as f:
            content = f.read()
            
        # Find all WDATA values written to the segment address if possible, 
        # or just find all hex patterns that look like 10-char segments.
        # Since I don't know the exact address used for segments in this trace format 
        # (user provided the raw hex values though), I'll look for those patterns.
        
        # Pattern: WDATA: [0-9a-f]{10}
        matches = re.finditer(r'WDATA: ([0-9a-fA-F]{8,10})', content)
        
        for m in matches:
            val = m.group(1).lower()
            if len(val) < 4: continue
            
            sel = val[-4:-2]
            seg = val[-2:]
            
            if sel in selectors:
                pos = selectors[sel]
                char = SEG_MAP.get(seg, f"[{seg}]")
                pos_to_char[pos] = char
                
        display = "".join(pos_to_char[i] for i in range(7, -1, -1))
        # Format as "XX XXXXXX" (TestCount Time)
        return f"当前显示内容: {display[:2]} {display[2:]}"
        
    except Exception as e:
        return f"错误: {str(e)}"

# Given the users trace is in JYD2025_Contest-Template\digital_twin.sim\my_trace.txt
path = r"C:\Users\21186\Desktop\verify\JYD2025_Contest-Template\digital_twin.sim\my_trace.txt"
print(reconstruct_display(path))
