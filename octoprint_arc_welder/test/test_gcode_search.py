# #################################################################################
# Arc Welder: Anti-Stutter
#
# A plugin for OctoPrint that converts G0/G1 commands into G2/G3 commands where possible and ensures that the tool
# paths don't deviate by more than a predefined resolution.  This compresses the gcode file sice, and reduces reduces
# the number of gcodes per second sent to a 3D printer that supports arc commands (G2 G3)
#
# Copyright (C) 2020  Brad Hochgesang
# Copyright (C) 2026  Steve Dougherty
# #################################################################################
# This program is free software:
# you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by
# the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Affero General Public License for more details.
#
# You should have received a copy of the GNU Affero General Public License
# along with this program.  If not, see the following:
# https://github.com/FormerLurker/ArcWelderPlugin/blob/master/LICENSE
#
# You can contact the author either through the git-hub repository, or at the
# following email address: FormerLurker@pm.me
##################################################################################
import unittest
from io import BytesIO

from octoprint_arc_welder import ArcWelderPlugin, utilities


def _gcode_file(text):
    # _search_gcode_file expects a binary file handle, like the one search_gcode_file opens
    return BytesIO(text.encode("utf-8"))


class TestGcodeSearch(unittest.TestCase):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.tag = ArcWelderPlugin.ARC_WELDER_GCODE_TAG
        self.settings = ArcWelderPlugin.ARC_WELDER_GCODE_PARAMETERS
        self.search_functions = [
            ArcWelderPlugin.SEARCH_FUNCTION_IS_WELDED,
            ArcWelderPlugin.SEARCH_FUNCTION_CURA_UPLOAD,
            ArcWelderPlugin.SEARCH_FUNCTION_SETTINGS,
        ]

    def test_file_search(self):
        # test is_welded
        test_string = """
            ; Postprocessed by [ArcWelder](https://github.com/FormerLurker/ArcWelderLib)
            ; Copyright(C) 2020 - Brad Hochgesang
            ; arc_welder_resolution_mm = 0.05
            ; arc_welder_g90_influences_extruder = False
        """
        self.assertDictEqual(
            utilities._search_gcode_file(_gcode_file(test_string), self.search_functions), {"is_welded": True}
        )

        # test cura
        test_string = """
            ; Comment
            ; Copyright(C) 2020 - Brad Hochgesang
            ; TESTCura-OctoPrintPluginTEST
            ; arc_welder_g90_influences_extruder = False
        """
        self.assertDictEqual(
            utilities._search_gcode_file(_gcode_file(test_string), self.search_functions),
            {"slicer_upload_type": "Cura-OctoPrintPlugin"},
        )

        # test is_welded auto exit (include cura string)
        test_string = """
            ; Comment
            ; Copyright(C) 2020 - Brad Hochgesang
            ; TESTCura-OctoPrintPluginTEST
            ; Postprocessed by [ArcWelder](https://github.com/FormerLurker/ArcWelderLib)
            ; arc_welder_g90_influences_extruder = False
        """
        self.assertDictEqual(
            utilities._search_gcode_file(_gcode_file(test_string), self.search_functions), {"is_welded": True}
        )

        # test settings
        test_string = """
            ; Comment
            ; Copyright(C) 2020 - Brad Hochgesang
            ;  ArcWelder   :POSTFIX= .aw, Prefix = \\\"arc\\,welded\\\", resolution-mm = 0.2
            ;
            ; arc_welder_g90_influences_extruder = False
        """
        self.assertDictEqual(
            utilities._search_gcode_file(_gcode_file(test_string), self.search_functions),
            {"settings": {"postfix": ".aw", "prefix": "arc,welded", "resolution_mm": 0.2}},
        )

    def test_parsing_ignore(self):
        test_string = ""
        self.assertFalse(utilities.parse_settings_comment(test_string, self.tag, self.settings))
        test_string = " True"
        self.assertFalse(utilities.parse_settings_comment(test_string, self.tag, self.settings))
        test_string = "ArcWelde"
        self.assertFalse(utilities.parse_settings_comment(test_string, self.tag, self.settings))
        test_string = " ArcWelde"
        self.assertFalse(utilities.parse_settings_comment(test_string, self.tag, self.settings))
        test_string = "Arcwelder "
        self.assertFalse(utilities.parse_settings_comment(test_string, self.tag, self.settings))
        test_string = " ArcWelder:"
        self.assertFalse(utilities.parse_settings_comment(test_string, self.tag, self.settings))
        test_string = " ArcWelder:     "
        self.assertFalse(utilities.parse_settings_comment(test_string, self.tag, self.settings))

    def test_boolean_parameter(self):
        # Test common non results
        test_string = " ArcWelder   :weld= true"
        self.assertDictEqual(utilities.parse_settings_comment(test_string, self.tag, self.settings), {"weld": True})
        test_string = "ArcWelder:weld=true"
        self.assertDictEqual(utilities.parse_settings_comment(test_string, self.tag, self.settings), {"weld": True})
        test_string = " ArcWelder:  weld=true"
        self.assertDictEqual(utilities.parse_settings_comment(test_string, self.tag, self.settings), {"weld": True})
        test_string = " ArcWelder:  weld = True"
        self.assertDictEqual(utilities.parse_settings_comment(test_string, self.tag, self.settings), {"weld": True})
        test_string = " ArcWelder:  weld = 1"
        self.assertDictEqual(utilities.parse_settings_comment(test_string, self.tag, self.settings), {"weld": True})
        test_string = " ArcWelder:  weld=fAlse"
        self.assertDictEqual(utilities.parse_settings_comment(test_string, self.tag, self.settings), {"weld": False})
        test_string = " ArcWelder:  weld = 0"
        self.assertDictEqual(utilities.parse_settings_comment(test_string, self.tag, self.settings), {"weld": False})
        test_string = " ArcWelder:  weld = N"
        self.assertDictEqual(utilities.parse_settings_comment(test_string, self.tag, self.settings), {"weld": False})

    def test_float_parameter(self):
        # Test common non results
        test_string = " ArcWelder   :resolution-MM= 1.0"
        self.assertDictEqual(
            utilities.parse_settings_comment(test_string, self.tag, self.settings), {"resolution_mm": 1.0}
        )
        test_string = "ArcWelder:resolution-mm=.2"
        self.assertDictEqual(
            utilities.parse_settings_comment(test_string, self.tag, self.settings), {"resolution_mm": 0.2}
        )
        test_string = " ArcWelder:  RESOLUTION-MM = 0"
        self.assertDictEqual(
            utilities.parse_settings_comment(test_string, self.tag, self.settings), {"resolution_mm": 0}
        )

    def test_percent_parameter(self):
        # An explicit "%" is taken as-is...
        test_string = " ArcWelder   :PATH-TOLERANCE-PERCENT= 5%"
        self.assertDictEqual(
            utilities.parse_settings_comment(test_string, self.tag, self.settings), {"path_tolerance_percent": 5.0}
        )
        # ...a bare value is treated as a fraction and scaled to a percentage.
        test_string = "ArcWelder:PATH-TOLERANCE-PERCENT= 0.05"
        self.assertDictEqual(
            utilities.parse_settings_comment(test_string, self.tag, self.settings), {"path_tolerance_percent": 5.0}
        )

    def test_string_parameter(self):
        # Test common non results
        test_string = " ArcWelder   :POSTFIX= .aw "
        self.assertDictEqual(utilities.parse_settings_comment(test_string, self.tag, self.settings), {"postfix": ".aw"})
        test_string = 'ArcWelder:POSTFIX=".aw"'
        self.assertDictEqual(utilities.parse_settings_comment(test_string, self.tag, self.settings), {"postfix": ".aw"})
        test_string = 'ArcWelder:POSTFIX=" . a w"'
        self.assertDictEqual(
            utilities.parse_settings_comment(test_string, self.tag, self.settings), {"postfix": " . a w"}
        )

    def test_multiple_parameters(self):
        # Test common non results
        test_string = ' ArcWelder   :POSTFIX= .aw, Prefix = "arc welded", resolution-mm= 0.2'
        self.assertDictEqual(
            utilities.parse_settings_comment(test_string, self.tag, self.settings),
            {"postfix": ".aw", "prefix": "arc welded", "resolution_mm": 0.2},
        )
        test_string = " ArcWelder   :POSTFIX= .aw, Prefix = arc welded, resolution-mm= 0.2"
        self.assertDictEqual(
            utilities.parse_settings_comment(test_string, self.tag, self.settings),
            {"postfix": ".aw", "prefix": "arc welded", "resolution_mm": 0.2},
        )
        test_string = ' ArcWelder   :POSTFIX= .aw, Prefix = \\"arc\\,welded\\", resolution-mm = 0.2'
        self.assertDictEqual(
            utilities.parse_settings_comment(test_string, self.tag, self.settings),
            {"postfix": ".aw", "prefix": "arc,welded", "resolution_mm": 0.2},
        )

        test_string = " ArcWelder   :POSTFIX= .aw, Prefix = arc\\,welded, resolution-mm = 0.2"
        self.assertDictEqual(
            utilities.parse_settings_comment(test_string, self.tag, self.settings),
            {"postfix": ".aw", "prefix": "arc,welded", "resolution_mm": 0.2},
        )

    def test_unicode(self):
        test_string = """
                    ; Postprocessed by [ArcWelder](https://github.com/FormerLurker/ArcWelderLib)
                    ; Copyright(C) 2020 - Brad Hochgesang
                    é; arc_welder_resolution_mm = 0.05 é
                    ; arc_welder_g90_influences_extruder = False
                """
        self.assertDictEqual(
            utilities._search_gcode_file(_gcode_file(test_string), self.search_functions), {"is_welded": True}
        )
