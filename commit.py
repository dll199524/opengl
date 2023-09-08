import os
from git.repo import Repo
from git.repo.fun import is_git_dir
import datetime

##格式化 shift + alt + F
def commit(path):
    dirfile = os.path.abspath(path)
    repo = Repo(dirfile)

    g = repo.git
    g.add("--all")
    g.commit("-m commit")
    g.push()
    print("success push")

path  = r"E:\OpenGL"
commit(path)
