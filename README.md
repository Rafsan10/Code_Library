MIST_EagleForces ICPC Team notebook
===================================

The team notebook is compiled from codes written by MIST_EagleForces team members (Syed Mafijul Islam, Saif Ahmed,and Rafsan Hasnan Ratul).

Generating team notebook
========================
The python script is a fork of the Stanford ICPC teams notebook generator. It currently hosts the team notebook. The included Python scripts differs from the original repository. Here, directories will be the section and file name without extension will be subsection. Now, code comment support latex math formating.

Generating PDF
--------------
Requires: [Python 2/3](https://www.python.org/), [latexmk](https://www.ctan.org/pkg/latexmk/)

Script for generating the PDF file is `generate_pdf.py`.
The LaTeX template that the script uses is `notebook.tex`. It recognizes common file extensions for C/C++/Java/Python and applies syntax highlighting. In order to change the color scheme or add additional languages, both `notebook.tex` and `generate_pdf.py` should be modified accordingly.
# MIST_EagleForces_Code_Library
