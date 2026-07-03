# MIST_EagleForces ICPC Team Notebook

This repository contains the ICPC team notebook source, including code snippets, math notes, and a build script that generates a PDF version of the notebook.

## 1. Clone the repository

From your terminal, clone the repository and move into it:

```bash
git clone <repository-url>
cd Code_Library
```

or latest version only
```bash
git clone --depth 1 <repository-url>
```
## 2. Install prerequisites

You need:

- Python 3
- A LaTeX distribution with `pdflatex` (for example TeX Live)

On Ubuntu/Debian, install them with:

```bash
sudo apt-get update
sudo apt-get install -y python3 python3-venv texlive-latex-base texlive-latex-extra texlive-fonts-recommended
```

## 3. Create a Python environment

It is recommended to use a virtual environment so the Python dependencies stay isolated:

```bash
python3 -m venv .venv
source .venv/bin/activate
python -m pip install --upgrade pip
python -m pip install -r requirements.txt
```

The Python dependency list is intentionally small and is defined in [requirements.txt](requirements.txt).

## 4. Generate the PDF

Run the build script from the repository root:

```bash
python3 generate_pdf.py
```

This will:

1. Scan the [code](code) directory for source files
2. Generate [contents.tex](contents.tex) with the notebook contents
3. Compile [notebook.tex](notebook.tex) with `pdflatex -shell-escape` three times so the table of contents and references are built correctly

The final output PDF will be [notebook.pdf](notebook.pdf).

## 5. How the project works

The repository is organized as follows:

```text
├── code/              # Contest code snippets grouped by topic
├── math/              # Math notes and LaTeX helper files
├── images/            # Images used by the notebook
├── generate_pdf.py    # Python script that builds the notebook
├── notebook.tex       # Main LaTeX document
├── contents.tex       # Auto-generated content file produced by the script
├── requirements.txt   # Python packages needed by the build script
└── README.md          # This guide
```

### What the build script does

- Walks through the folders under [code](code)
- Reads each source file and collects metadata such as filename, line count, and a short hash
- Writes a LaTeX-ready section into [contents.tex](contents.tex)
- Calls `pdflatex` repeatedly to generate the final PDF

## 6. Add new content

To add a new algorithm or note:

1. Place the source file in the appropriate folder inside [code](code)
2. Use a supported extension such as `.cpp`, `.cc`, `.c`, `.java`, or `.py`
3. Re-run:

```bash
python3 generate_pdf.py
```

The notebook will regenerate with your new content included.

## Acknowledgments

The Python script is based on the Stanford ICPC team notebook generator approach.
