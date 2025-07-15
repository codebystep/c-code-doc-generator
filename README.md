# C Code Documentation Generator

This is a simple ANSI C console application that parses documentation comments from C source files and generates LaTeX-formatted documentation.  
Inspired by tools like Doxygen and JavaDoc.

## Features

- Parses both `///`-style (line) and `/** ... */`-style (block) documentation comments from `.c` and `.h` files
- Outputs structured LaTeX documentation
- Supports sections like `Parameters`, `Returns`, and `Description`
- Easily extendable modular structure

## How to Compile

Use the provided `makefile` (for Linux/macOS) or `makefile.win` (for Windows) depending on your platform:

```bash
make
```

Alternatively, on Windows:

```bash
mingw32-make -f makefile.win
```

This will produce the executable `ccdoc.exe` (or `ccdoc` on Linux/macOS).

## How to Use

Once compiled, run the application with the following arguments:

```bash
./ccdoc <input_folder> <output_file>
```

- `<input_folder>` – path to the folder containing `.c` and `.h` files with documentation comments  
- `<output_file>` – name of the LaTeX file to generate

**Example:**

```bash
./ccdoc ./examples ./output.tex
```

This will scan all `.c` and `.h` files in the `./examples` directory and generate a LaTeX documentation file called `output.tex`.

You can then compile `output.tex` with a LaTeX engine like `pdflatex`:

```bash
pdflatex output.tex
```

## Documentation Format

The program recognizes two styles of documentation comments:

### 1. Line comments (`///`)

```c
/// Adds two integers.
///
/// Parameters:
///   - a: First integer
///   - b: Second integer
///
/// Returns:
///   Sum of a and b
```

### 2. Block comments (`/** ... */`)

```c
/**
 * Adds two integers.
 *
 * Parameters:
 *   - a: First integer
 *   - b: Second integer
 *
 * Returns:
 *   Sum of a and b
 */
int add(int a, int b);
```

## Output

The output is a LaTeX-formatted `.tex` file that can be further processed into a PDF. The structure includes:

- Function names and signatures
- Descriptions
- Return value descriptions

---

Created as a semester project. See `Dokumentace.pdf` for full technical details (note: document is written in Czech).
