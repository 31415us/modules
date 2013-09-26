#!/usr/bin/env python3
"""
Patches a Makefile generated by Altera's NIOS-II SBT to comply with the
CVRA build process.
"""
import argparse, os

def main():
    """
    Program entry point. It is good practice to wrap all the code in a function
    to avoid exporting globals.
    """
    parser = argparse.ArgumentParser(
            description="""Patch an Altera-generated Makefile to
            setup the CVRA dev environment. It will output the patched
            Makefile to stdout.""")
    parser.add_argument("makefile", action="store",
            help="Path to the original Makefile.")
    parser.add_argument("source_dir", action="store",
            help="Path to the modules checkout directory.")
    args = parser.parse_args()

    modules_dir = os.path.join(args.source_dir, "modules")

    dir_list = [os.path.join(args.source_dir, "include/")]
    for directory in os.listdir(modules_dir):
        dir_list.append(os.path.join(modules_dir, directory))

    modules_dir = os.path.join(modules_dir, "math")
    for directory in os.listdir(modules_dir):
        dir_list.append(os.path.join(modules_dir, directory))

    with open(args.makefile) as makefile:
        for line in makefile:
            print(line, end="")
            if "ALT_INCLUDE_DIRS :=" in line:
                for i in dir_list:
                    print("ALT_INCLUDE_DIRS += {0}\r\n".format(i))
            if "ALT_CFLAGS :=" in line:
                print("ALT_CFLAGS += -DCOMPILE_ON_ROBOT")


if __name__ == "__main__":
    main()
