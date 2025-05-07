# 🐾 Muchku Language Compiler
<img src="https://github.com/user-attachments/assets/3025ca01-97fa-4d2d-9d5a-05c34ceb12cd" alt="MK" width="150" height="150" style="border-radius: 10% ;" />


This is the official compiler for **Muchku**, a custom programming language built in C. Muchku is a toy language created for learning how compilers work — from **lexing** to **parsing**, **code generation**, and execution.



----
# Structure
<img width="4013" alt="shapes at 25-05-07 19 44 45" src="https://github.com/user-attachments/assets/bb1f5a04-0a6c-49ff-a36d-2dad340d0fd7" />

---
# ✨ Features
- Lexical analysis (tokenization)
- Parsing into AST (Abstract Syntax Tree)
- Code generation into executable instructions
- Simple error reporting
- Supports basic language constructs (e.g., print, variables, arithmetic , if and for)

---
# 🧠 Learning Goals
This project was built to understand:
- Compiler architecture
- Lexers and parsers
- AST construction
- Code interpretation/generation

---

# 🛠 Dependencies
C Compiler (e.g., GCC)

POSIX-compliant terminal (Linux, macOS) or Git Bash/WSL (Windows)






## 🔧 How to Build

Ensure you have GCC installed.

### From the root directory:

```bash
cd compiler
gcc main.c lexer.c parser.c codegen.c -o muchku.exe
./muchku.exe ../main.muchku





