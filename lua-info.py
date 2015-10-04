#!/usr/bin/env python3

# retrieve information in regards to Lua

import subprocess, sys

def run(command):
    cmd = command.split()
    rc = []
    try:
        rc = subprocess.check_output(cmd,
            stderr=subprocess.PIPE).encode("utf_8").split()
    except subprocess.CalledProcessError:
        print("Process Error")
        pass
    return rc

def get_version():
    rc = run("{0} --version".format(lua["bin"]))
    print(rc)
    return

def get_headers():
    print("headers")
    return

def get_libs():
    print("libs")
    return

def usage(kw):
    myname = sys.argv[0].split(sep='/')[-1]
    print("Usage: {0} <keyword>".format(myname))
    keywords = " ".join(iter(kw))
    print("keywords: {0}".format(keywords))
    sys.exit(2)
    return

func = {
    "version": get_version,
    "headers": get_headers,
    "libs":    get_libs
}
lua = {"bin": [], "include": [], "lib": []}
# need arguments or show usage
len(sys.argv) > 1 or usage(func)
# get location of lua and headers/libraries
rc = run("whereis lua")
# convert all return values to strings
for i in range(0, len(rc)):
    if "bin" in str(rc[i]):
        lua["bin"].append(str(rc[i]))
    elif "lib" in str(rc[i]):
        lua["lib"].append(str(rc[i]))
    elif "include" in str(rc[i]):
        lua["include"].append(str(rc[i]))
print(lua["bin"])
# iterate through arguments
for i in sys.argv[1:]:
    if i in func:
        func[i]()
    else:
        usage(func)
