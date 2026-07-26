import hashlib, sys

def verify(file, expected_file, algo):
    h = hashlib.new(algo)
    with open(file, 'rb') as f:
        h.update(f.read())
    digest = h.hexdigest()
    with open(expected_file) as f:
        expected = f.read().split()[0]
    if digest != expected:
        sys.exit(f"{algo.upper()} mismatch! Expected {expected}, got {digest}")
    print(f"{algo.upper()} verified ✅")

if __name__ == "__main__":
    verify("capsule_manifest.json", "expected.sha256", "sha256")
    verify("capsule_manifest.json", "expected.sha512", "sha512")