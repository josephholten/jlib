from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout, CMakeDeps
from conan.tools.scm import Git

import re

class jlib(ConanFile):
    name = "jlib"

    # Optional metadata
    author = "Joseph Holten joseph@holten.com"
    description = "A collection of useful C++ software"

    requires = "fmt/[>=11]", "benchmark/[>=1.9]", "gtest/[>=1.15]", "cpptrace/[>=0.7.0]"

    # Binary configuration
    settings = "os", "compiler", "build_type", "arch"

    exports_sources = "*" # with "!not_this" we can ignore packages

    def set_version(self):
        git = Git(self)

        diff = git.run("status --short")
        if diff != "":
            self.output.error("working tree is not clean")
            exit(1)

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
                self.output.highlight(f"version = {version}")
                self.version = version

    def layout(self):
        cmake_layout(self)

    def generate(self):
        deps = CMakeDeps(self)
        deps.generate()

        tc = CMakeToolchain(self)
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()

    #def package_info(self):
    #    self.cpp_info.libs = ["jlib::bigint", "jlib::jassert"]
