from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout, CMakeDeps
from conan.tools.scm import Git


class jlib(ConanFile):
    name = "jlib"
    version = "!!TODO"

    # Optional metadata
    author = "Joseph Holten joseph@holten.com"
    description = "My Lib"

    # Binary configuration
    settings = "os", "compiler", "build_type", "arch"

    exports_sources = "*" # with "!not_this" we can ignore packages

    def set_version(self):
        git = Git(self)

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
