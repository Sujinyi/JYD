import sys

def load_trace(filename):
    """Load trace as a list of lines"""
    with open(filename, 'r', encoding='utf-8') as f:
        return [line.strip() for line in f if line.strip()]

def main():
    if len(sys.argv) != 3:
        print("Usage: python verify_trace.py <golden_trace.txt> <your_trace.txt>")
        sys.exit(1)
        
    f1, f2 = sys.argv[1], sys.argv[2]
    
    try:
        trace1 = load_trace(f1)
        trace2 = load_trace(f2)
    except Exception as e:
        print(f"Error loading files: {e}")
        sys.exit(1)
        
    print(f"Loaded {len(trace1)} instructions from {f1}")
    print(f"Loaded {len(trace2)} instructions from {f2}")
    
    min_len = min(len(trace1), len(trace2))
    
    # Compare line by line
    errors = 0
    for i in range(min_len):
        if trace1[i] != trace2[i]:
            print(f"Mismatch at step {i+1}:")
            print(f"  Golden: {trace1[i]}")
            print(f"  Yours : {trace2[i]}")
            errors += 1
            if errors > 5: # stop after 5 errors
                print("Too many errors. Stopping comparison.")
                break
                
    if errors == 0:
        if len(trace1) == len(trace2):
            print("SUCCESS! Traces match perfectly.")
        else:
            print(f"Traces match up to {min_len} lines, but lengths differ.")
            print(f"  Golden extra lines: {len(trace1) - min_len}")
            print(f"  Yours extra lines: {len(trace2) - min_len}")

if __name__ == "__main__":
    main()
