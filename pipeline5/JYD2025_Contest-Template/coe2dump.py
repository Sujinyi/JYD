import sys
import os
try:
    from capstone import Cs, CS_ARCH_RISCV, CS_MODE_RISCV32, CS_MODE_LITTLE_ENDIAN
except ImportError:
    print("Error: capstone library is not installed. Please run 'pip install capstone' first.")
    sys.exit(1)

def coe_to_dump(input_coe, output_dump):
    try:
        with open(input_coe, 'r', encoding='utf-8') as f:
            lines = f.readlines()
    except FileNotFoundError:
        print(f"Error: Could not find '{input_coe}'")
        sys.exit(1)

    radix = 16
    vector_started = False
    hex_values = []

    for line in lines:
        line = line.strip()
        if not line:
            continue
        if line.lower().startswith("memory_initialization_radix"):
            try:
                radix = int(line.split('=')[1].replace(';', '').strip())
                if radix != 16:
                    print(f"Warning: radix is {radix}, but this script currently expects hex (16). Output may be incorrect.")
            except Exception:
                pass
        elif line.lower().startswith("memory_initialization_vector"):
            vector_started = True
        elif vector_started:
            # removing commas and semicolons
            tokens = line.replace(';', ',').split(',')
            for t in tokens:
                t = t.strip()
                if t:
                    hex_values.append(t)

    if not hex_values:
        print("Error: No hex values found in the data vector.")
        sys.exit(1)

    code = bytearray()
    for h in hex_values:
        if len(h) != 8:
            # pads to 8 characters if necessary
            h = h.zfill(8)
        try:
            # Little endian
            code += bytes.fromhex(h)[::-1]
        except ValueError:
            print(f"Error parse hex value: {h}")
            sys.exit(1)

    md = Cs(CS_ARCH_RISCV, CS_MODE_RISCV32 | CS_MODE_LITTLE_ENDIAN)
    
    # Optional: we can enable detail mode if we want, but not needed for basic dump
    # md.detail = True
    
    with open(output_dump, 'w', encoding='utf-8') as f:
        f.write(f"\n{os.path.basename(output_dump).split('.')[0]}:     file format binary-littleriscv\n\n\n")
        f.write("Disassembly of section .text:\n\n")
        f.write("00000000 <_start>:\n")
        
        offset = 0
        for i in md.disasm(code, 0x0):
            # Hex representation of instruction
            # It's better to show it in big-endian hex (like 0040006f) to match objdump
            instr_hex = ''.join(f'{b:02x}' for b in reversed(i.bytes))
            
            # Format:  offset:  instr_hex   mnemonic op_str
            # example:   4:	00000093          	addi	x1,x0,0
            f.write(f"  {i.address:x}:\t{instr_hex}          \t{i.mnemonic}\t{i.op_str}\n")
            
            offset += 4
            
        # If there are data words that failed to decode
        if offset < len(code):
            print(f"Warning: Only disassembled {offset} bytes out of {len(code)} bytes. Some data may not be valid instructions.")

    print(f"Successfully converted {input_coe} to {output_dump}")

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print(f"Usage: python {sys.argv[0]} <input.coe> <output.dump>")
        sys.exit(1)
        
    input_file = sys.argv[1]
    output_file = sys.argv[2]
    coe_to_dump(input_file, output_file)
