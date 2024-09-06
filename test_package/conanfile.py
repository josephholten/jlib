from conan import ConanFile
from conan.tools.cmake import CMake, cmake_layout
from conan.tools.build import can_run

import tempfile
import os
from pathlib import Path

class TestPackage(ConanFile):
    name = "jlib_test_package"
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "CMakeToolchain"

    def requirements(self):
        self.requires(self.tested_reference_str)
        self.requires("fmt/[>=11]")

    def layout(self):
        cmake_layout(self)

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def test(self):
        if can_run(self):
            tests = list(Path(self.source_folder).glob("test_*.cpp"))
            self.output.info(f"Running tests: {tests}")

            for test in tests:
                with open(str(test) + ".out", "r") as file:
                    expected_output = file.read().strip()

                # Creating a temporary file to capture the output
                with tempfile.NamedTemporaryFile() as tmp:
                    cmd = os.path.join(self.cpp.build.bindir, "test_bigint")
                    # redirect to output file
                    self.run(cmd, env="conanrun", stdout=tmp)

                    # Rewinding the file and reading the output
                    tmp.seek(0)
                    output = tmp.read().decode().strip()

                    if output == expected_output:
                        self.output.success("TEST PASSED")
                    else:
                        self.output.warning(f"TEST {test} FAILED: output did not match expected")
                        self.output.warning(f"    Expected '{expected_output}'")
                        self.output.warning(f"    Actual   '{output}'")
