from pymavlink.generator import mavgen
from pymavlink.generator import mavparse
import os
import shutil


def run(definition, out_val, language):
    opts = mavgen.Opts(out_val, wire_protocol=mavgen.DEFAULT_WIRE_PROTOCOL,
                       language=language, validate=True, error_limit=5)
    mavgen.mavgen(opts, [definition])


def create_sub_dir(dirpath, sub_dir):
    path = dirpath + "/" + sub_dir
    if os.path.exists(path):
        shutil.rmtree(path)
    os.makedirs(path)

dirpath = os.path.dirname(os.path.abspath(__file__))

# XML Def
definition = dirpath + "/cju_swcho.xml"

# C
language = "C"
out_val = dirpath + "/C"
create_sub_dir(dirpath, "C")
run(definition, out_val, language)

