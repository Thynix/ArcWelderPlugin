# #################################################################################
# Arc Welder: Anti-Stutter
#
# A plugin for OctoPrint that converts G0/G1 commands into G2/G3 commands where possible and ensures that the tool
# paths don't deviate by more than a predefined resolution.  This compresses the gcode file sice, and reduces reduces
# the number of gcodes per second sent to a 3D printer that supports arc commands (G2 G3)
#
# Copyright (C) 2020  Brad Hochgesang
##################################################################################
import ntpath
import os


def remove_extension_from_filename(filename):
    return os.path.splitext(filename)[0]


def get_filename_from_path(filepath):
    head, tail = ntpath.split(filepath)
    return tail or ntpath.basename(head)


def get_extension_from_filename(filename):
    head, tail = ntpath.split(filename)
    file_name = tail or ntpath.basename(head)
    split_filename = os.path.splitext(file_name)
    if len(split_filename) > 1:
        extension = split_filename[1]
        if len(split_filename) > 1:
            return extension[1:]
    return ""


def dict_encode(d):
    # helpers for dealing with bytes (string) values delivered by the converter
    # socks.js doesn't like mixed encoding
    def dict_key_value_encode(s):
        if isinstance(s, dict):
            return dict_encode(s)

        if isinstance(s, bytes):
            return str(s, errors="ignore", encoding="utf-8")
        return s

    return {dict_key_value_encode(k): dict_key_value_encode(v) for k, v in d.iteritems()}
