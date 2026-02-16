# MIST\_EagleForces ICPC Team Notebook

## Prerequisites

- [Python 3](https://www.python.org/)
- A LaTeX distribution with `pdflatex` (e.g., TeX Live)

### Install required packages (Ubuntu/Debian)

```bash
sudo apt-get update
sudo apt-get install -y python3 texlive-latex-base texlive-latex-extra texlive-fonts-recommended
```

The `minted` package (used for syntax highlighting) requires [Pygments](https://pygments.org/):

```bash
pip install Pygments
```

Or via apt:

```bash
sudo apt-get install -y python3-pygments
```

## Generating the PDF

```bash
python3 generate_pdf.py
```

This script will:
1. Scan the `code/` directory for source files
2. Generate `contents.tex` with all code sections sorted alphabetically
3. Run `pdflatex -shell-escape notebook.tex` three times to properly build the table of contents and references

The output PDF will be `notebook.pdf`.

## Project Structure

```
├── notebook.tex          # Main LaTeX template
├── generate_pdf.py       # PDF generation script
├── contents.tex          # Auto-generated code listings (do not edit manually)
├── math/                 # Math reference sheets (combinatorics, probability, etc.)
└── code/                 # Source code organized by category
    ├── Data Structure/
    ├── Dynamic Programming/
    ├── Game Theory/
    ├── Geometry/
    ├── Graph/
    ├── Misc/
    ├── Number Theory/
    ├── Some Algorithms/
    └── String/
```

## Adding New Code

1. Place your source file in the appropriate `code/<Category>/` directory
2. Supported extensions: `.c`, `.cc`, `.cpp` (C++), `.java` (Java), `.py` (Python). Other files are included as plain text.
3. Run `python3 generate_pdf.py` to regenerate the PDF

## Acknowledgments

The Python script is a fork of the Stanford ICPC team's notebook generator.
