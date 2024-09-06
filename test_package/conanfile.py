from conan import ConanFile
from conan.tools.cmake import CMake, cmake_layout
from conan.tools.scm import Git
from conan.tools.build import can_run

import re
import os

class TestPackage(ConanFile):
    name = "jlib_test_package"
    settings = "os", "compiler", "build_type", "arch"
    #requires = "jlib/[>=0.0.1]", "fmt/[>=11]"
    generators = "CMakeDeps", "CMakeToolchain"

    def requirements(self):
        self.requires(self.tested_reference_str)
        self.requires("fmt/[>=11]")

    def set_version(self):
        git = Git(self)
        descr = git.run("describe --tags")
        regex = r"(\d+(?:.\d+)*(?:-pre)?)(?:-(\d+)-((?:\d|\w)+))?"
        match = re.match(regex, descr)
        if match is None:
            raise Exception("tag doesn't match")
        else:
            groups = match.groups()
            if len(groups) == 1:
                self.version = descr
            if len(groups) == 2:
                raise Exception("tag shouldn't contain exactly 2 groups")
            if len(groups) == 3:
                tag, commits, h = groups
                version = f"{tag}.{commits}+{h}"
                print("version = ", version)
                self.version = version

    def layout(self):
        cmake_layout(self)

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def test(self):
        if can_run(self):
            cmd = os.path.join(self.cpp.build.bindir, "test_bigint")
            self.run(cmd, env="conanrun")
