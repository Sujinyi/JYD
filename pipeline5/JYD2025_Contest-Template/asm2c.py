import sys
import re

def r(reg_name):
    # keep register names as is for pseudo-C
    return reg_name

def decompile(dump_file, out_file):
    with open(dump_file, 'r', encoding='utf-8') as f:
        lines = f.readlines()

    instructions = []
    # Identify jump targets to create labels
    labels = set()
    
    # Regex for a line like: "  3c:	00008067          	ret	"
    # or "  0:	00108117          	auipc	sp, 0x108"
    line_re = re.compile(r'\s*([0-9a-fA-F]+):\s*[0-9a-fA-F]+\s+([a-zA-Z0-9_.]+)\s*(.*)')

    for line in lines:
        m = line_re.match(line)
        if m:
            addr = int(m.group(1), 16)
            mnemonic = m.group(2)
            op_str = m.group(3).strip()
            instructions.append((addr, mnemonic, op_str))
            
            # Check for branch/jump targets
            if mnemonic in ['jal', 'j', 'beq', 'bne', 'blt', 'bge', 'bltu', 'bgeu', 'beqz', 'bnez', 'blez', 'bgez', 'bltz', 'bgtz']:
                ops = [x.strip() for x in op_str.split(',')]
                target_str = ops[-1]
                # Sometimes it's absolute hex (like 0x5a0), sometimes relative/decimal
                try:
                    target_addr = int(target_str, 16) if target_str.startswith('0x') or target_str.startswith('-0x') else int(target_str)
                    
                    # Capstone prints relative offsets for some branches if not fully resolved, but we used absolute offset in our generation script
                    # Wait, our dump generation script outputs absolute targets for bne etc. if possible, or offsets?
                    # Let's assume absolute targets from Capstone
                    if not target_str.startswith('0x') and '-' in target_str:
                         # Handle negative hex? Capstone directly outputs 0x... or -0x...
                         pass
                    
                    if target_str.startswith('-0x'):
                        target_addr = addr - int(target_str[3:], 16)
                    elif target_str.startswith('0x'):
                        target_addr = int(target_str, 16)
                    else:
                        target_addr = int(target_str)

                    labels.add(target_addr)
                except ValueError:
                    pass

    with open(out_file, 'w', encoding='utf-8') as f:
        f.write("#include <stdint.h>\n\n// Pseudo-C translation of RISC-V assembly\n\n")
        f.write("void program() {\n")
        f.write("    uint32_t zero = 0, ra = 0, sp = 0, gp = 0, tp = 0;\n")
        f.write("    uint32_t t0 = 0, t1 = 0, t2 = 0, t3 = 0, t4 = 0, t5 = 0, t6 = 0;\n")
        f.write("    uint32_t s0 = 0, s1 = 0, s2 = 0, s3 = 0, s4 = 0, s5 = 0, s6 = 0, s7 = 0, s8 = 0, s9 = 0, s10 = 0, s11 = 0;\n")
        f.write("    uint32_t a0 = 0, a1 = 0, a2 = 0, a3 = 0, a4 = 0, a5 = 0, a6 = 0, a7 = 0;\n")
        f.write("    uint32_t pc = 0;\n\n")
        
        for addr, mnemonic, op_str in instructions:
            if addr in labels:
                f.write(f"\nLOC_{addr:x}:\n")
            
            ops = [x.strip() for x in op_str.split(',')]
            c_code = ""

            try:
                if mnemonic == 'auipc':
                    c_code = f"{ops[0]} = 0x{addr:x} + {ops[1]};"
                elif mnemonic == 'lui':
                    val = int(ops[1], 16) if ops[1].startswith('0x') else int(ops[1])
                    c_code = f"{ops[0]} = 0x{val:x} << 12;"
                elif mnemonic in ['add', 'addw']:
                    c_code = f"{ops[0]} = {ops[1]} + {ops[2]};"
                elif mnemonic in ['addi', 'addiw']:
                    c_code = f"{ops[0]} = {ops[1]} + {ops[2]};"
                elif mnemonic in ['sub', 'subw']:
                    c_code = f"{ops[0]} = {ops[1]} - {ops[2]};"
                elif mnemonic == 'sll':
                    c_code = f"{ops[0]} = {ops[1]} << ({ops[2]} & 0x1F);"
                elif mnemonic in ['slli', 'slliw']:
                    c_code = f"{ops[0]} = {ops[1]} << {ops[2]};"
                elif mnemonic == 'srl':
                    c_code = f"{ops[0]} = (uint32_t){ops[1]} >> ({ops[2]} & 0x1F);"
                elif mnemonic in ['srli', 'srliw']:
                    c_code = f"{ops[0]} = (uint32_t){ops[1]} >> {ops[2]};"
                elif mnemonic == 'sra':
                    c_code = f"{ops[0]} = (int32_t){ops[1]} >> ({ops[2]} & 0x1F);"
                elif mnemonic in ['srai', 'sraiw']:
                    c_code = f"{ops[0]} = (int32_t){ops[1]} >> {ops[2]};"
                elif mnemonic == 'and':
                    c_code = f"{ops[0]} = {ops[1]} & {ops[2]};"
                elif mnemonic == 'andi':
                    c_code = f"{ops[0]} = {ops[1]} & {ops[2]};"
                elif mnemonic == 'or':
                    c_code = f"{ops[0]} = {ops[1]} | {ops[2]};"
                elif mnemonic == 'ori':
                    c_code = f"{ops[0]} = {ops[1]} | {ops[2]};"
                elif mnemonic == 'xor':
                    c_code = f"{ops[0]} = {ops[1]} ^ {ops[2]};"
                elif mnemonic == 'xori':
                    c_code = f"{ops[0]} = {ops[1]} ^ {ops[2]};"
                elif mnemonic == 'slt':
                    c_code = f"{ops[0]} = ((int32_t){ops[1]} < (int32_t){ops[2]}) ? 1 : 0;"
                elif mnemonic == 'slti':
                    c_code = f"{ops[0]} = ((int32_t){ops[1]} < (int32_t){ops[2]}) ? 1 : 0;"
                elif mnemonic == 'sltu':
                    c_code = f"{ops[0]} = ((uint32_t){ops[1]} < (uint32_t){ops[2]}) ? 1 : 0;"
                elif mnemonic == 'sltiu':
                    c_code = f"{ops[0]} = ((uint32_t){ops[1]} < (uint32_t){ops[2]}) ? 1 : 0;"
                    
                # Loads
                elif mnemonic in ['lb', 'lh', 'lw', 'lbu', 'lhu']:
                    m = re.match(r'(-?0x[0-9a-fA-F]+|-?\d+)?\((.*?)\)', ops[1])
                    if m:
                        offset = m.group(1) or '0'
                        base = m.group(2)
                        typ = {'lb': 'int8_t', 'lh': 'int16_t', 'lw': 'int32_t', 'lbu': 'uint8_t', 'lhu': 'uint16_t'}[mnemonic]
                        c_code = f"{ops[0]} = *({typ}*)({base} + {offset});"
                    else:
                        c_code = f"{ops[0]} = MEM[{ops[1]}];"
                
                # Stores
                elif mnemonic in ['sb', 'sh', 'sw']:
                    m = re.match(r'(-?0x[0-9a-fA-F]+|-?\d+)?\((.*?)\)', ops[1])
                    if m:
                        offset = m.group(1) or '0'
                        base = m.group(2)
                        typ = {'sb': 'uint8_t', 'sh': 'uint16_t', 'sw': 'uint32_t'}[mnemonic]
                        c_code = f"*({typ}*)({base} + {offset}) = {ops[0]};"
                    else:
                        c_code = f"MEM[{ops[1]}] = {ops[0]};"
                        
                # Branches
                elif mnemonic in ['beq', 'bne', 'blt', 'bge', 'bltu', 'bgeu']:
                    target = ops[2]
                    try:
                        t_addr = int(target, 16) if target.startswith('0x') else int(target)
                        target = f"LOC_{t_addr:x}"
                    except:
                        if target.startswith('-0x'):
                            target = f"LOC_{(addr - int(target[3:], 16)):x}"
                    
                    op_map = {'beq': '==', 'bne': '!=', 'blt': '<', 'bge': '>=', 'bltu': '<', 'bgeu': '>='}
                    cast = "(uint32_t)" if mnemonic.endswith('u') else "(int32_t)"
                    c_code = f"if ({cast}{ops[0]} {op_map[mnemonic]} {cast}{ops[1]}) goto {target};"
                
                # Pseudoinstructions / Jumps
                elif mnemonic == 'j':
                    target = ops[0]
                    try:
                        if target.startswith('-0x'):
                            t_addr = addr - int(target[3:], 16)
                        else:
                            t_addr = int(target, 16) if target.startswith('0x') else int(target)
                        target = f"LOC_{t_addr:x}"
                    except: pass
                    c_code = f"goto {target};"
                elif mnemonic == 'jal':
                    if len(ops) == 1: # jal offset (ra is implicit)
                        rd = 'ra'
                        target = ops[0]
                    else:
                        rd = ops[0]
                        target = ops[1]
                        
                    try:
                        if target.startswith('-0x'):
                            t_addr = addr - int(target[3:], 16)
                        else:
                            t_addr = int(target, 16) if target.startswith('0x') else int(target)
                        target = f"LOC_{t_addr:x}"
                    except: pass
                    c_code = f"{rd} = 0x{(addr+4):x}; goto {target}; // Call"
                elif mnemonic == 'jalr':
                    if len(ops) == 1:
                        c_code = f"pc = {ops[0]}; ra = 0x{(addr+4):x}; // Return or Indirect Call"
                    else:
                        c_code = f"pc = {ops[1]}; {ops[0]} = 0x{(addr+4):x}; // Indirect Call"
                elif mnemonic == 'ret':
                    c_code = "goto *ra; // Return"
                elif mnemonic == 'mv':
                    c_code = f"{ops[0]} = {ops[1]};"
                elif mnemonic == 'li':
                    c_code = f"{ops[0]} = {ops[1]};"
                elif mnemonic == 'nop':
                    c_code = "// nop"
                elif mnemonic == 'ebreak':
                    c_code = "break; // ebreak"
                elif mnemonic == 'ecall':
                    c_code = "syscall(); // ecall"
                elif mnemonic == 'bnez':
                    target = ops[1]
                    try:
                        if target.startswith('-0x'):
                            t_addr = addr - int(target[3:], 16)
                        else:
                            t_addr = int(target, 16) if target.startswith('0x') else int(target)
                        target = f"LOC_{t_addr:x}"
                    except: pass
                    c_code = f"if ({ops[0]} != 0) goto {target};"
                elif mnemonic == 'beqz':
                    target = ops[1]
                    try:
                        if target.startswith('-0x'):
                            t_addr = addr - int(target[3:], 16)
                        else:
                            t_addr = int(target, 16) if target.startswith('0x') else int(target)
                        target = f"LOC_{t_addr:x}"
                    except: pass
                    c_code = f"if ({ops[0]} == 0) goto {target};"
                elif mnemonic == 'seqz':
                    c_code = f"{ops[0]} = ({ops[1]} == 0) ? 1 : 0;"
                elif mnemonic == 'snez':
                    c_code = f"{ops[0]} = ({ops[1]} != 0) ? 1 : 0;"
                elif mnemonic == 'neg':
                    c_code = f"{ops[0]} = -{ops[1]};"
                elif mnemonic == 'not':
                    c_code = f"{ops[0]} = ~{ops[1]};"
                else:
                    c_code = f"// Unhandled: {mnemonic} {op_str}"
            except Exception as e:
                c_code = f"// Error parsing: {mnemonic} {op_str} ({str(e)})"
            
            f.write(f"    /* {addr:5x} */  {c_code:<40} // {mnemonic} {op_str}\n")
        
        f.write("}\n")
    print(f"Decompiled to {out_file}")

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print(f"Usage: python {sys.argv[0]} <input.dump> <output.c>")
        sys.exit(1)
    decompile(sys.argv[1], sys.argv[2])
