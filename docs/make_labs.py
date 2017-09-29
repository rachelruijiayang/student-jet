import zipfile
import os
from os import listdir, makedirs
from os.path import isfile, join, dirname, exists

cwd = os.path.dirname(os.path.realpath(__file__))

build_dir = os.path.join(cwd, "build")
if not os.path.exists(build_dir):
    os.makedirs(build_dir)

template_path = join('support', 'template.tex')

os.system("pandoc -V geometry:margin=1in " + os.path.join(cwd, "Syllabus.md") + " -s -o " + os.path.join(build_dir, "Syllabus.pdf") + " --template='" + template_path + "'")
os.system("pandoc " + os.path.join(cwd, "Syllabus.md") + " -s -o " + os.path.join(build_dir, "Syllabus.docx") + " --template='" + template_path + "'")

projects_build_dir = os.path.join(build_dir, 'projects')
if not os.path.exists(os.path.join(build_dir, 'projects')):
    os.makedirs(projects_build_dir)

projects = [p for p in listdir(os.path.join(cwd, 'projects')) if '.md' in p]
for p in projects:
    os.system("pandoc -V geometry:margin=1in " + os.path.join(cwd, 'projects', p) + " -s -o " + os.path.join(projects_build_dir, p.replace(".md",".pdf")) + " --template='" + template_path + "'")
    os.system("pandoc " + os.path.join(cwd, 'projects', p) + " -s -o " + os.path.join(projects_build_dir, p.replace(".md",".docx")) + " --template='" + template_path + "'")


modules = [m for m in listdir(cwd) if "module" in m]
for m in modules:
    mod_build_dir = os.path.join(build_dir, m)
    if not os.path.exists(mod_build_dir):
        os.makedirs(mod_build_dir)

    if os.path.exists(os.path.join(cwd, m, "questions")):
        question_build_dir = os.path.join(mod_build_dir, "questions")

        if not os.path.exists(question_build_dir):
            os.makedirs(question_build_dir)

        qfiles = [q for q in listdir(os.path.join(cwd, m, "questions"))]
        for q in qfiles:
            os.system("pandoc -V geometry:margin=1in -f markdown-markdown_in_html_blocks " + os.path.join(cwd, m, "questions", q) + " -s -o " + os.path.join(question_build_dir, q.replace(".md",".pdf")) + " --template='" + template_path + "' --from markdown+markdown_in_html_blocks")
            os.system("pandoc -f markdown-markdown_in_html_blocks " + os.path.join(cwd, m, "questions", q) + " -s -o " + os.path.join(question_build_dir, q.replace(".md",".docx")) + " --template='" + template_path + "' --from markdown+markdown_in_html_blocks")

    # Build Lab Documentation and Code zips
    labs = [l for l in listdir(os.path.join(cwd, m)) if "lab" in l]
    for l in labs:
        lab_build_dir = os.path.join(mod_build_dir, l)
        if not os.path.exists(lab_build_dir):
            os.makedirs(lab_build_dir)

        # Compile markdown files to pdfs
        md_files = [md for md in listdir(os.path.join(cwd, m, l)) if ".md" in md]
        for md in md_files:
            os.system("pandoc -V geometry:margin=1in " + os.path.join(cwd, m, l, md) + " -s -o " + os.path.join(lab_build_dir, md.replace(".md",".pdf")) + " --template='" + template_path + "'")
            os.system("pandoc " + os.path.join(cwd, m, l, md) + " -s -o " + os.path.join(lab_build_dir, md.replace(".md",".docx")) + " --template='" + template_path + "'")

        # Zip the source directory
        if os.path.exists(os.path.join(cwd, m, l, "code")):
            zf = zipfile.ZipFile(os.path.join(lab_build_dir, l + "-code.zip"), "w", zipfile.ZIP_DEFLATED)
            src = os.path.join(cwd, m, l, "code")
            for dirname, subdirs, files in os.walk(src):
                for filename in files:
                    absname = os.path.abspath(os.path.join(dirname, filename))
                    arcname = absname[len(src) + 1:]
                    zf.write(absname, arcname)
            zf.close()

        # Zip the source directory
        if os.path.exists(os.path.join(cwd, m, l, "solution")):
            zf = zipfile.ZipFile(os.path.join(lab_build_dir, l + "-solution.zip"), "w", zipfile.ZIP_DEFLATED)
            src = os.path.join(cwd, m, l, "solution")
            for dirname, subdirs, files in os.walk(src):
                for filename in files:
                    absname = os.path.abspath(os.path.join(dirname, filename))
                    arcname = absname[len(src) + 1:]
                    zf.write(absname, arcname)
            zf.close()
