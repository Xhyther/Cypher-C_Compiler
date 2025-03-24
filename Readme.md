
```markdown
# 🔣 Cypher Language – A Toy Programming Language Front-End

Cypher is a **semi-compiler front-end** for a custom toy programming language designed to practice and demonstrate the core concepts of compiler construction. It includes:

- ✅ Lexical Analysis (Scanner)
- ✅ Syntax Analysis (Parser)
- ✅ Semantic Analysis (Type & Scope Checking)
- ❌ No Code Generation or Execution (front-end only)

This project is built using C and serves as an educational tool for understanding how compilers analyze and verify source code.

---

## 🚀 Language Features

Cypher supports a minimal yet expressive syntax with the following features:

### 🧾 Data Types
- `int` — Whole numbers
- `string` — Text strings
- `char` — Single characters
- `bool` — Boolean values (`true` or `false`)

### 📌 Variable Declarations
```cypher
let x int := 1;
let y string := "Hello World!";
let z bool := true;
let a char := 'A';
```

### 📤 Output (Printing)
```cypher
out :: x;
out :: "Hello";
out :: true;
```

### 🔁 Loops

**For Loop**
```cypher
let i int := 1;
for i; i < 5; i++ {
    out :: i;
}
```

**While Loop**
```cypher
while (true) {
    out :: "Hello World";
}
```

---

## 🔧 Project Structure

| Folder/File         | Description |
|---------------------|-------------|
| `src/`              | Source code (scanner, parser, semantic analyzer) |
| `test.cypher`       | Sample Cypher source code |
| `README.md`         | Project overview |
| `docs/` *(optional)*| Language spec, grammar, and design notes |

---

## 🧠 Key Concepts Implemented

- Custom **recursive descent parser**
- Custom **tokenizer / lexer**
- Abstract Syntax Tree (AST) representation
- **Symbol table** for variable/type checking
- **Semantic rules** to catch type errors and scope violations

---

## 🛠️ Built With

- Language: `C`
- Tools: Custom-built parser and lexer (no Flex/Bison)

---

## 📚 Goals

This is an academic/learning project for:
- Practicing compiler front-end architecture
- Understanding parsing and semantic checking
- Preparing for building interpreters or full compilers in the future

---

## 🚧 Future Improvements

- Function support (`fn`, parameters, returns)
- Nested scopes
- Type inference or custom types
- AST visualization tool
- Interpreter or virtual machine backend

---

## 🤝 Contributing

This is a personal learning project, but feel free to fork or suggest features, ideas, or improvements via issues or PRs.

---

## 📜 License

MIT License – feel free to use or build upon this for educational purposes.

---

## 🙋‍♂️ Author

**@yourusername** – Second-year CS student passionate about compilers, systems, and language design.
```

---

Would you like a separate `docs/spec.md` for grammar rules and token definitions too? That can help guide your implementation while serving as internal documentation.