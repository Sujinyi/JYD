import sys
import struct
import capstone

def disassemble_coe(coe_path, out_path):
    try:
        md = capstone.Cs(capstone.CS_ARCH_RISCV, capstone.CS_MODE_RISCV32 | capstone.CS_MODE_RISCVC)
    except Exception as e:
        print("Capstone init failed:", e)
        return
        
    hex_data = []
    in_vector = False
    with open(coe_path, 'r', encoding='utf-8') as f:
        for line in f:
            line = line.strip()
            if not line: continue
            if 'memory_initialization_vector=' in line:
                in_vector = True
                continue
            if in_vector:
                val = line.replace(',', '').replace(';', '').strip()
                if val:
                    hex_data.append(val)

    code = b''
    for h in hex_data:
        val = int(h.zfill(8), 16)
        code += struct.pack('<I', val)

    base_addr = 0x80000000
    with open(out_path, 'w', encoding='utf-8') as f:
        for i in md.disasm(code, base_addr):
            f.write("0x%x:\t%s %s\t// 0x%08x\n" % (i.address, i.mnemonic, i.op_str, struct.unpack('<I', i.bytes)[0]))

if __name__ == '__main__':
    disassemble_coe(sys.argv[1], sys.argv[2])
