#!/usr/bin/env python3
import hashlib
import os
import subprocess
from pathlib import Path

BASE_DIR = Path(__file__).resolve().parent
CODE_DIR = BASE_DIR / "code"


def get_sections():
    sections = []
    for root, _, files in os.walk(CODE_DIR):
        subsections = []
        section_name = os.path.basename(root)
        sections.append((section_name, subsections))
        for file_name in sorted(files):
            if file_name.startswith('.'):
                continue

            relative_path = Path(root, file_name)
            subsection_name = relative_path.stem
            with relative_path.open('r', encoding='utf-8', errors='replace') as handle:
                number_of_lines = sum(1 for _ in handle)

            hash_value = hashlib.md5(relative_path.read_bytes()).hexdigest()[:8]
            subsections.append((relative_path.relative_to(BASE_DIR).as_posix(), subsection_name, number_of_lines, hash_value))

    return sorted(sections[1:], key=lambda x: x[0])


def get_style(filename):
    ext = Path(filename).suffix.lower()
    if ext in ['.c', '.cc', '.cpp']:
        return 'c++'
    if ext == '.java':
        return 'java'
    if ext == '.py':
        return 'python'
    return 'text'


def texify(s):
    """Escape special LaTeX characters in strings."""
    s = s.replace('\\', '\\textbackslash{}')
    s = s.replace('&', '\\&')
    s = s.replace('%', '\\%')
    s = s.replace('$', '\\$')
    s = s.replace('#', '\\#')
    s = s.replace('_', '\\_')
    s = s.replace('{', '\\{')
    s = s.replace('}', '\\}')
    s = s.replace('~', '\\textasciitilde{}')
    s = s.replace('^', '\\textasciicircum{}')
    return s


def get_tex(sections):
    tex = ''
    for section_name, subsections in sections:
        tex += '\section{%s}\n' % texify(section_name)
        for relative_path, subsection_name, number_of_lines, hash_value in subsections:
            tex += '\subsection{\\small %s  \\scriptsize [%s lines] - %s}\n' % (
                texify(subsection_name), number_of_lines, hash_value
            )
            tex += '\inputminted{%s}{%s}\n' % (get_style(relative_path), relative_path)
        tex += '\n'
    return tex


def main():
    sections = get_sections()
    tex = get_tex(sections)
    with (BASE_DIR / 'contents.tex').open('w', encoding='utf-8') as handle:
        handle.write(tex)

    print('Running LaTeX compilation...')
    pdflatex_options = ['pdflatex', '-shell-escape', 'notebook.tex']
    for _ in range(3):
        subprocess.run(pdflatex_options, cwd=BASE_DIR, check=True)

    print('PDF generation complete!')


if __name__ == '__main__':
    main()

