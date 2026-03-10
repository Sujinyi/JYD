import sys
import struct
import subprocess

def main():
    coe_file = r"d:\26work\JYD2025_Contest-Template\digital_twin.srcs\sources_1\imports\test_src\irom.coe"
    bin_file = r"test_irom.bin"
    
    with open(coe_file, 'r') as f:
        lines = f.readlines()
        
    in_vector = False
    hex_data = []
    for line in lines:
        line = line.strip()
        if not line:
            continue
        if line.startswith('memory_initialization_vector='):
            in_vector = True
            continue
        if in_vector:
            val = line.rstrip(',;')
            if val:
                hex_data.append(val)
                
    with open(bin_file, 'wb') as f:
        for val in hex_data:
            num = int(val, 16)
            f.write(struct.pack('<I', num))
            
    print(f"Wrote {len(hex_data)} instructions to {bin_file}")
    
    tools = ['riscv64-unknown-elf-objdump', 'riscv32-unknown-elf-objdump', 'riscv-none-elf-objdump']
    for tool in tools:
        try:
            cmd = [tool, '-D', '-b', 'binary', '-m', 'riscv', bin_file]
            result = subprocess.run(cmd, capture_output=True, text=True)
            if result.returncode == 0:
                print(f"Successfully disassembled using {tool}:")
                with open("disasm_out.txt", "w") as out_f:
                    out_f.write(result.stdout)
                print(result.stdout[:2000])
                return
        except FileNotFoundError:
            pass
            
    print("Could not find riscv objdump. Trying pure python fallback using capstone...")
    subprocess.run([sys.executable, "-m", "pip", "install", "capstone"], capture_output=True)
    try:
        from capstone import Cs, CS_ARCH_RISCV, CS_MODE_RISCV32
        md = Cs(CS_ARCH_RISCV, CS_MODE_RISCV32)
        with open(bin_file, 'rb') as f:
            code = f.read()
        print("Disassembly:")
        count = 0
        with open("disasm_out.txt", "w") as out_f:
            for i in md.disasm(code, 0x0):
                line = "0x%x:\t%s\t%s" %(i.address, i.mnemonic, i.op_str)
                out_f.write(line + "\n")
                if count < 50:
                    print(line)
                count += 1
        print(f"Total disassembled instructions: {count}")
    except ImportError:
        print("Capstone not installed and failed to install.")

if __name__ == '__main__':
    main()
