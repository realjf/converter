#!/usr/bin/env python

import platform
import os
import sys
import io
import subprocess
import json
import getopt


DEBUG_OUTPUT = False


TOOL_COMMAND_PYTHON = "python"


if platform.system() == "Linux":
    TOOL_COMMAND_PYTHON = "python3"


def log(string):
    print("--- " + string)


def dlog(string):
    if DEBUG_OUTPUT:
        print("*** " + string)


def executeCommand(command, printCommand=False, quiet=False):
    printCommand = printCommand or DEBUG_OUTPUT
    out = None
    err = None

    if quiet:
        out = open(os.devnull, 'w')
        err = subprocess.STDOUT

    if printCommand:
        if DEBUG_OUTPUT:
            dlog(">>> " + command)
        else:
            log(">>> " + command)

    return subprocess.call(command, shell=True, stdout=out, stderr=err)


def dieIfNonZero(res):
    if res != 0:
        raise ValueError("Command returned non-zero status: " + str(res))


def findToolCommand(command, paths_to_search, required=False):
    command_res = command
    found = False

    for path in paths_to_search:
        command_abs = os.path.join(path, command)
        if os.path.exists(command_abs):
            command_res = command_abs
            found = True
            break

    if required and not found:
        log("WARNING: command " + command + " not found, but required by script")

    dlog("Found '" + command + "' as " + command_res)
    return command_res


def readJSONData(filename):
    try:
        json_data = open(filename).read()
    except:
        log("ERROR: Could not read JSON file " + filename)
        return None

    try:
        data = json.loads(json_data)
    except:
        log("ERROR: Could not parse JSON document")
        return None

    return data


def listLibraries(data):
    for library in data:
        name = library.get('name', None)
        if name is not None:
            print(name)


def installLibrary(name):
    executeCommand('sudo apt-get install ' + name + " -y")


def printOptions():
    print("--------------------------------------------------------------------------------")
    print("Install required libraries.")
    print("")
    print("Options:")
    print("  --list, -l                  List all required libraries")
    print("  --file, -f                  Specifies the required libraries file to be")
    print("                              installed")
    print("  --debug-output, -d          Enables extra debugging output")
    print("  --break-on-first-error, -b  Terminate script once the first error is encountered")
    print("--------------------------------------------------------------------------------")


def main(argv):
    global DEBUG_OUTPUT
    global TOOL_COMMAND_PYTHON

    try:
        opts, args = getopt.getopt(
            argv,
            "ln:N:cCb:h",
            ["list", "file=", "debug-output", "help", "break-on-first-error"])
    except getopt.GetoptError:
        printOptions()
        return 0

    list_libraries = False
    opt_file = ""

    break_on_first_error = False

    for opt, arg in opts:
        if opt in ("-h", "--help"):
            printOptions()
            return 0
        if opt in ("-l", "--list"):
            list_libraries = True
        if opt in ("-f", "--file"):
            opt_file = os.path.abspath(arg)
            log(opt_file)
        if opt in ("-b", "--break-on-first-error",):
            break_on_first_error = True
        if opt in ("-d", "--debug-output",):
            DEBUG_OUTPUT = True

    if platform.system() != "Windows":
        # Unfortunately some IDEs do not have a proper PATH environment variable set,
        # so we search manually for the required tools in some obvious locations.
        paths_to_search = os.environ["PATH"].split(
            ":") + ["/usr/local/bin", "/opt/local/bin", "/usr/bin"]
        TOOL_COMMAND_PYTHON = findToolCommand(
            TOOL_COMMAND_PYTHON, paths_to_search, required=True)

    if len(opt_file) == 0 or not os.path.exists(os.path.abspath(opt_file)):
        log("libraries.json not found")
        return -1

    # read canonical libraries data
    data = readJSONData(opt_file)
    if data is None:
        return -1

    # some sanity checking
    for library in data:
        if library.get('name', None) is None:
            log("ERROR: Invalid schema: library object does not have a 'name'")
            return -1

    if list_libraries:
        listLibraries(data)
        return 0

    failed_libraries = []

    for library in data:
        name = library.get('name', None)

        dlog("********** LIBRARY " + name + " **********")

        # install library
        count = installLibrary(name)
        if count > 0:
            failed_libraries.append(name)
            if break_on_first_error:
                break
        else:
            log("install " + name + " success")

    if failed_libraries:
        log("***************************************")
        log("FAILURE to install the following libraries:")
        log(', '.join(failed_libraries))
        log("***************************************")
        return -1

    log("Finished")

    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
