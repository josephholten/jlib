from conan import ConanFile
from conan.tools.cmake import CMake, cmake_layout

class TestPackage(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    requires = "jlib/[>=0.1.0-pre]", "fmt/[>=11]"
    generators = "CMakeDeps", "CMakeToolchain"

    def layout(self):
        cmake_layout(self)

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def test(self):
        # Assuming the test executable is called test_package
        self.run("./bin/test_bigint", run_environment=True)
