#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

using std::string;

// A tool to make recipe formats/templates for the omi package manager

namespace fs = std::filesystem;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "No package name specified.\n";
        return 1;
    }

    string command = argv[1];
    if (command == "--help" || command == "-h") {
        std::cout << "rmfo - help for noobies 101\n\n";
        std::cout << "Usage:\n";
        std::cout << "rmfo <package-name>\n";
        std::cout << "rmfo <package-name> --cmake\n";
        std::cout << "rmfo <package-name> --meson\n";
        std::cout << "rmfo --help or -h";
        std::cout << "Options:\n";
        std::cout << "  --cmake  Set a package build system to cmake\n";
        std::cout << "  --meson  Set a package build system to meson\n";
        std::cout << "  --go     Set a package build system to go\n";
        std::cout << "  --cargo  Set a package build system to cargo\n";
        std::cout << "  --waf    Set a package build system to waf\n";
        return 0;
    }
    bool use_cmake = false;
    bool use_meson = false;
    bool use_go = false;
    bool use_cargo = false;
    bool use_waf = false;

    for (int i = 2; i < argc; i++) {
        string arg = argv[i];

        if (arg == "--cmake") {
            use_cmake = true;
        } else if (arg == "--meson") {
            use_meson = true;
        } else if (arg == "--go") {
            use_go = true;
        } else if (arg == "--cargo") {
            use_cargo = true;
        } else if (arg == "--waf") {
            use_waf = true;
        } else {
            std::cerr << "Unknown option: " << arg << '\n';
            std::cout << "Use: rmfo --help for more options.\n";
            return 1;
        }
    }
    // We can reassign argv[1] to packagename now that we did help command.
    string packagename = argv[1];

    string build_system = "make";
    fs::create_directories("packages");

    fs::path pkgdir = fs::path("packages") / packagename;

    if (!fs::create_directory(pkgdir)) {
        std::cerr << "Error: Cannot create package directory '" << pkgdir
                  << "' (already exists).\n";
        return 1;
    }

    std::ofstream packagefile(pkgdir / "package.toml");
    if (!packagefile) {
        std::cerr << "Cannot create package.toml.\n";
        return 1;
    }

    if (use_cmake) {
        build_system = "cmake";
    } else if (use_meson) {
        build_system = "meson";
    } else if (use_meson && use_cmake) {
        std::cerr<<"Cannot select both meson and cmake.\n";
        return 1;
    } else if (use_go) {
        build_system = "go";
    } else if (use_cargo) {
        build_system = "cargo";
    } else if (use_go && use_cargo) {
        std::cerr<<"Cannot select both go and cargo.\n";
        return 1;
    } else if (use_waf) {
        build_system = "waf";
    }

    if (packagefile.is_open()) {
        packagefile << "[package]\n";
        packagefile << "name = \"" << packagename << "\"\n";
        packagefile << "version = \"\"\n\n";

        packagefile << "[source]\n";
        packagefile << "url = \"\"\n";
        packagefile << "sha256 = \"\"\n\n";

        packagefile << "[build]\n";
        packagefile << "system = \"" << build_system << "\"\n";
    }

    std::cout<<"Created recipe template for: "<<packagename<<" in "<<pkgdir.c_str()<<"/package.toml"<<" using: "<<build_system<<'\n';

    return 0;
}
