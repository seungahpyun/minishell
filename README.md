# Minishell

**"As beautiful as a shell"**

A bash-like shell implementation written in C as part of the 42 curriculum. This project recreates the basic functionality of a Unix shell, handling command execution, pipes, redirections, environment variables, and built-in commands.

## ✨ Features

### Core Functionality
- **Interactive command prompt** with custom PS1
- **Command history** using readline library
- **Signal handling** (Ctrl-C, Ctrl-D, Ctrl-\)
- **Environment variable management**
- **Path resolution** for executables
- **Process management** with fork/exec

### Advanced Features
- **Pipes** (`|`) for command chaining
- **Redirections** (`<`, `>`, `>>`, `<<`)
- **Here-documents** with variable expansion
- **Logical operators** (`&&`, `||`) with parentheses for precedence
- **Wildcard expansion** (`*`)
- **Quote handling** (single and double quotes)
- **Variable expansion** (`$VAR`, `$?`)

## 🚀 Installation

### Prerequisites
- GCC compiler
- Make
- Readline library development headers

### Ubuntu/Debian
```bash
sudo apt-get update
sudo apt-get install build-essential libreadline-dev
```

### macOS
```bash
# Using Homebrew
brew install readline
```

### Build
```bash
git clone [repository-url]
cd minishell
make
```

## 💡 Usage

### Starting Minishell
```bash
./minishell
```

### Basic Commands
```bash
# Simple command execution
ls -la

# Using pipes
ls | grep .c | wc -l

# Redirections
echo "Hello World" > output.txt
cat < input.txt
ls >> logfile.txt

# Here-documents
cat << EOF
This is a here-document
Variables like $USER work here
EOF

# Logical operators
ls && echo "Success" || echo "Failed"

# Subshells with parentheses
(cd /tmp && ls) | head -5

# Background processes (bonus)
sleep 10 &
```

### Environment Variables
```bash
export NAME=value
echo $NAME
echo $?  # Exit status of last command
unset NAME
```

### Wildcards
```bash
ls *.c
echo file*.txt
rm temp*
```

## 🔧 Built-in Commands

| Command | Description | Options |
|---------|-------------|---------|
| `echo` | Display text | `-n` (no newline) |
| `cd` | Change directory | Supports `~`, `-`, relative/absolute paths |
| `pwd` | Print working directory | No options |
| `export` | Set environment variables | No options |
| `unset` | Unset environment variables | No options |
| `env` | Display environment | No options |
| `exit` | Exit the shell | Optional exit code |

### Built-in Examples
```bash
# Echo command
echo "Hello, World!"
echo -n "No newline"

# Directory navigation
cd /home/user
cd ..
cd ~
cd -  # Go to previous directory

# Environment management
export PATH="/usr/local/bin:$PATH"
export GREETING="Hello"
echo $GREETING
unset GREETING

# Exit
exit
exit 42  # Exit with code 42
```

## 🎯 Supported Features

### ✅ Mandatory Features
- [x] Interactive prompt display
- [x] Working history
- [x] Executable search and launch
- [x] Global variable limitation (only for signals)
- [x] Quote handling (`'` and `"`)
- [x] Redirections (`<`, `>`, `<<`, `>>`)
- [x] Pipes (`|`)
- [x] Environment variables (`$VAR`)
- [x] Exit status (`$?`)
- [x] Signal handling (Ctrl-C, Ctrl-D, Ctrl-\)
- [x] All built-in commands

### ✅ Bonus Features
- [x] Logical operators (`&&`, `||`)
- [x] Parentheses for precedence
- [x] Wildcard expansion (`*`)

### ❌ Not Implemented
- Backslash escaping (`\`)
- Semicolon (`;`)
- Advanced wildcards (`?`, `[...]`)
- Job control
- Aliases

## 📁 Project Structure

```
minishell/
├── Makefile
├── include/
│   ├── minishell.h      # Main header
│   ├── lexer.h          # Tokenization
│   ├── parser.h         # AST parsing
│   ├── executor.h       # Command execution
│   ├── expander.h       # Variable/wildcard expansion
│   ├── env.h            # Environment management
│   ├── builtin.h        # Built-in commands
│   └── common.h         # Shared utilities
├── src/
│   ├── main.c           # Entry point
│   ├── lexer/           # Tokenization logic
│   ├── parser/          # AST creation and validation
│   ├── executor/        # Command execution
│   ├── expander/        # Variable and wildcard expansion
│   ├── env/             # Environment variable management
│   ├── builtin/         # Built-in commands
│   └── common/          # Utilities and signal handling
└── lib/                 # Libft library
```

## 🔧 Implementation Details

### Architecture Overview
The shell follows a classic interpreter pattern:

1. **Lexical Analysis (Tokenizer)**
   - Breaks input into tokens
   - Handles quotes and operators
   - Validates syntax

2. **Parsing (Parser)**
   - Creates Abstract Syntax Tree (AST)
   - Handles operator precedence
   - Validates command structure

3. **Expansion (Expander)**
   - Variable expansion (`$VAR`, `$?`)
   - Wildcard expansion (`*`)
   - Quote removal

4. **Execution (Executor)**
   - Traverses AST
   - Handles pipes and redirections
   - Manages processes

### Key Design Decisions

#### Signal Handling
- Uses only one global variable for signal state
- Implements proper signal masking
- Handles different signal contexts (interactive, heredoc, child)

#### Memory Management
- No memory leaks in user code
- Proper cleanup on exit
- Custom memory utilities for complex operations

#### Quote Handling
- Distinguishes between single and double quotes
- Supports mixed quoting
- Proper quote removal after parsing

#### Wildcard Expansion
- POSIX-compliant pattern matching
- Hidden file handling (files starting with `.`)
- Sorted output

## 🧪 Testing

### Manual Testing
```bash
# Test basic commands
echo "test"
ls -la
pwd

# Test pipes
ls | wc -l
cat file.txt | grep "pattern" | sort

# Test redirections
echo "hello" > test.txt
cat < test.txt
ls >> output.log

# Test here-documents
cat << END
Line 1
Line 2 with $USER
END

# Test logical operators
true && echo "success"
false || echo "fallback"

# Test wildcards
echo *.c
ls file*

# Test built-ins
export TEST=value
echo $TEST
cd /tmp
pwd
```

### Memory Testing
```bash
# Using valgrind with readline suppression
valgrind --suppressions=minishell.supp --leak-check=full ./minishell

# Basic memory check
valgrind --leak-check=full --show-leak-kinds=all ./minishell
```

### Comparison with Bash
Test identical commands in both bash and minishell to ensure compatibility:

```bash
# Create test script
echo 'echo "test" | cat' > test.sh

# Run in bash
bash test.sh

# Run in minishell
./minishell < test.sh
```

## 🗑️ Memory Management

### Key Principles
- Every `malloc` has a corresponding `free`
- Proper cleanup on all exit paths
- No leaks except readline (allowed by subject)
- Signal-safe memory operations

### Memory Utilities
- Custom `mem_realloc` for dynamic arrays
- `mem_split` for custom delimiter splitting
- Comprehensive cleanup functions for AST and tokens

### Valgrind Suppressions
The project includes a suppression file (`minishell.supp`) for readline-related memory that cannot be freed.

## 📚 Learning Outcomes

This project teaches:
- **System Programming**: Process management, signals, file descriptors
- **Parser Design**: Tokenization, AST construction, syntax validation
- **Shell Internals**: How shells work under the hood
- **Memory Management**: Complex data structures and cleanup
- **UNIX Philosophy**: Pipes, redirections, process composition

## 🐛 Known Issues

- Readline memory leaks are expected and suppressed
- Some edge cases in complex quote nesting may not match bash exactly
- Performance may be slower than bash for very large inputs

## 👥 Team

This project was developed in collaboration with **[Bell](https://github.com/wtpbell)**.

