# 🔣 Cypher Language – A Toy Programming Language Front-End

Cypher is a **semi-compiler front-end** for a custom toy programming language designed to practice and demonstrate the core concepts of compiler construction. It includes:

- ✅ Lexical Analysis (Scanner)
- ✅ Syntax Analysis (Parser)
- ❌ Semantic Analysis (Type & Scope Checking) - Soon
- ❌ No Code Generation or Execution (front-end only)

This project is built using C and serves as an educational tool for understanding how compilers analyze and verify source code.

---

## 🚀 Language Features

Cypher supports a minimal yet expressive syntax with the following features:

### 🧾 Data Types
- `int` — Whole numbers
- `string` — Text strings

### 📌 Variable Assignments (Type Inference)
```cypher
x = 1;
y = "Hello World!";
z = z;
w = y;
```

### 📤 Output (Printing)
```cypher
print x;
print "Hello";
```

### 🔁 Loops

**For Loop**
```cypher
i = 1;
for i; i < 5; i++ {
    print i;
}
```
or
```cypher

for i = 1; i < 5; i++ {
    print i;
}

---

## 🎭 Grammar Rules (BNF)

```bnf
<program> ::= "main" <block>

<block> ::= "{" <statements> "}"

<statements> ::= <statement> <statements> | ε

<statement> ::= <assignment> | <print> | <for-loop>

<assignment> ::= <identifier> "=" <value> ";"

<value> ::= <number> | <string> | <identifier>

<print> ::= "print" (<value> | <identifier>) ";"

<for-loop> ::= "for" <identifier> ";" <expression> ";" <update> <block>

<expression> ::= <value> <operator> <value>

<operator> ::= "==" | "!=" | "<" | "<=" | ">" | ">="

<update> ::= <identifier> "++" | <identifier> "--"
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
- Additional Datatypes (bool, decimal/float, etc)
- Nested scopes
- Type inference improvements
- AST visualization tool
- Interpreter or virtual machine backend

---

## 🤝 Contributing

This is a personal learning project, but feel free to fork or suggest features, ideas, or improvements via issues or PRs.

---

## 📜 License

MIT License – feel free to use or build upon this for educational purposes.

