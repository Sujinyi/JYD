#!/usr/bin/env python3
"""
生成与 $readmemh 兼容的 HEX 文件
支持分离的指令存储器和数据存储器文件
"""

import sys
import subprocess
import os
from pathlib import Path


def extract_section_to_hex(elf_file, section_name, output_hex, as_bytes=False):
    """
    从 ELF 文件提取指定段并生成 HEX 文件

    Args:
        elf_file: 输入的 ELF/OBJ 文件路径
        section_name: 段名称 (如 .text, .data)
        output_hex: 输出的 HEX 文件路径
        as_bytes: 是否按字节格式输出（用于数据存储器）
    """
    # 使用 objcopy 提取段到二进制
    temp_bin = output_hex + '.tmp'
    cmd_extract = ['riscv64-elf-objcopy', '-O', 'binary', '-j', section_name, elf_file, temp_bin]

    try:
        subprocess.run(cmd_extract, check=True, capture_output=True)
    except subprocess.CalledProcessError as e:
        print(f"Error extracting {section_name} from {elf_file}: {e}")
        return False

    # 读取二进制数据并转换为十六进制格式
    try:
        with open(temp_bin, 'rb') as f:
            binary_data = f.read()

        # 确保数据长度是 4 的倍数（32位对齐）
        if len(binary_data) % 4 != 0:
            print(f"Warning: {section_name} size {len(binary_data)} is not 4-byte aligned, padding with zeros")
            padding = 4 - (len(binary_data) % 4)
            binary_data += b'\x00' * padding

        # 写入 HEX 文件
        with open(output_hex, 'w') as f:
            if as_bytes:
                # 字节模式：每行一个字节（用于数据存储器）
                for byte in binary_data:
                    f.write(f'{byte:02X}\n')
                print(f"Generated {output_hex}: {len(binary_data)} bytes")
            else:
                # 字模式：小端模式，每行一个 32 位字（用于指令存储器）
                for i in range(0, len(binary_data), 4):
                    # 读取 4 个字节（小端模式）
                    word = binary_data[i:i+4]
                    hex_value = (word[3] << 24) | (word[2] << 16) | (word[1] << 8) | word[0]
                    f.write(f'{hex_value:08X}\n')
                print(f"Generated {output_hex}: {len(binary_data)//4} words ({len(binary_data)} bytes)")

        # 删除临时文件
        os.remove(temp_bin)
        return True

    except Exception as e:
        print(f"Error processing {section_name}: {e}")
        if os.path.exists(temp_bin):
            os.remove(temp_bin)
        return False


def get_section_info(elf_file, section_name):
    """获取段信息（地址和大小）"""
    cmd = ['riscv64-elf-objdump', '-h', '-j', section_name, elf_file]
    try:
        result = subprocess.run(cmd, capture_output=True, text=True, check=True)
        # 解析输出，格式类似：
        # Idx Name          Size      VMA       LMA       File off  Algn
        #   0 .text         000004c8  00001000  00001000  00002000  2**2
        lines = result.stdout.split('\n')
        for line in lines:
            if section_name in line:
                parts = line.split()
                if len(parts) >= 4:
                    size = int(parts[2], 16)
                    vma = int(parts[3], 16)
                    return vma, size
    except Exception as e:
        print(f"Error getting section info: {e}")
    return None, None


def process_test_file(obj_file, output_dir):
    """
    处理单个测试文件，生成分离的 HEX 文件

    Args:
        obj_file: 输入的 .o 文件路径
        output_dir: 输出目录
    """
    obj_path = Path(obj_file)
    base_name = obj_path.stem

    # 获取段信息
    text_addr, text_size = get_section_info(obj_file, '.text')
    data_addr, data_size = get_section_info(obj_file, '.data')

    print(f"\n{'='*60}")
    print(f"Processing: {obj_file}")
    print(f"{'='*60}")
    print(f"  .text: 0x{text_addr:08X} ({text_size} bytes)")
    print(f"  .data: 0x{data_addr:08X} ({data_size} bytes)")

    # 生成指令存储器 HEX 文件
    text_hex = Path(output_dir) / f"{base_name}_text.hex"
    if text_size > 0:
        if extract_section_to_hex(obj_file, '.text', str(text_hex)):
            print(f"  ✓ Generated instruction memory: {text_hex}")
        else:
            print(f"  ✗ Failed to generate instruction memory")
            return False

    # 生成数据存储器 HEX 文件（字节格式）
    data_hex = Path(output_dir) / f"{base_name}_data.hex"
    if data_size > 0:
        if extract_section_to_hex(obj_file, '.data', str(data_hex), as_bytes=True):
            print(f"  ✓ Generated data memory: {data_hex}")
        else:
            print(f"  ✗ Failed to generate data memory")
            return False

    return True


def main():
    if len(sys.argv) < 2:
        print("Usage: python3 generate_hex.py <test.o> [output_dir]")
        print("Example: python3 generate_hex.py rv32mi/sw.o ./hex_output")
        sys.exit(1)

    obj_file = sys.argv[1]
    output_dir = sys.argv[2] if len(sys.argv) > 2 else '.'

    if not os.path.exists(obj_file):
        print(f"Error: File not found: {obj_file}")
        sys.exit(1)

    os.makedirs(output_dir, exist_ok=True)

    if process_test_file(obj_file, output_dir):
        print(f"\n✓ Success! Generated HEX files in {output_dir}")
    else:
        print(f"\n✗ Failed to process {obj_file}")
        sys.exit(1)


if __name__ == '__main__':
    main()