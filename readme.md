# TicTacToe

## 📦 Requirements
- C++17 or newer
- CMake (>= 3.10)
- SFML (included as a Git submodule)
- Ninja (optional, if using Ninja generator)

## 🛠️ Build Instructions (Linux)


Clone the repository with submodules:
```bash
git clone --recursive https://github.com/Kandax/TicTacToe.git
```
If SFML is missing:
```bash
git submodule update --init --recursive
```

Build:
```bash
cd TicTacToe
cmake -B build -G Ninja
cmake --build build
```
### ▶️ Run

```bash
./build/TicTacToe
```



