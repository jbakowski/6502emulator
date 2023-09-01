import os
import argparse
import shutil

BUILD_PATH = './build'
GCC_PATH = "C:/MinGW/bin/gcc"
GPP_PATH = "C:/MinGW/bin/g++"

parser = argparse.ArgumentParser()

parser.add_argument('-gcc', help="Build the 6502 emulator using GCC", action='store_true')
parser.add_argument('-clean', help="Clean the build directory", action='store_true')
parser.add_argument('-run', help="Run the executable after building the solution", action='store_true')
args = parser.parse_args()

if(args.clean):
    with os.scandir(BUILD_PATH) as entries:
        for entry in entries:
            if entry.is_dir() and not entry.is_symlink():
                shutil.rmtree(entry.path)
            else:
                os.remove(entry.path)
    os.chdir("..")

if(args.gcc):
    os.chdir(BUILD_PATH)
    os.system('cmake .. -G "Visual Studio 17 2022"')
    os.system('MSBuild.exe 6502emulator.sln')
    os.chdir("..")

if(args.run):
    os.chdir(BUILD_PATH)
    os.chdir("./Debug")
    if(args.gcc):
        print("#####\n\n\n")
    os.system('main.exe')