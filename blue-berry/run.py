import os

def main() -> None:
    os.system("make")
    os.system("rm -rf *.o")
    os.system("./exec")
    os.system("rm exec")

if __name__ == "__main__":
    main()