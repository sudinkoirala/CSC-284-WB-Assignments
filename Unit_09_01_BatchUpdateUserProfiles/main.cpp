#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <chrono>
#include <iomanip>
#include <sstream>

#include "json.hpp" // nlohmann::json header

namespace fs = std::filesystem;
using json = nlohmann::json;

// ------------------ Replacement helpers ------------------

// Checks and replaces @company.com -> @newcompany.com at end of string
std::string replaceCompanyEmailDomain(const std::string &s) {
    const std::string oldDomain = "@company.com";
    const std::string newDomain = "@newcompany.com";

    if (s.size() >= oldDomain.size() &&
        s.compare(s.size() - oldDomain.size(), oldDomain.size(), oldDomain) == 0) {
        return s.substr(0, s.size() - oldDomain.size()) + newDomain;
    }
    return s;
}

// Applies the assignment's replacement map to json values
void applyReplacementMap(json &j) {
    if (!j.is_string()) {
        return;
    }

    std::string value = j.get<std::string>();

    // Email replacement
    std::string updatedEmail = replaceCompanyEmailDomain(value);
    if (updatedEmail != value) {
        j = updatedEmail;
        return;
    }

    // Other replacements (exact matches)
    if (value == "enabled") {
        j = {
            {"status", "enabled"},
            {"since", "2024-10-01"}
        };
    } else if (value == "disabled") {
        j = {
            {"status", "disabled"},
            {"since", "2024-10-01"}
        };
    } else if (value == "manage_users") {
        j = {
            {"permission", "manage_users"},
            {"granted_at", "2024-10-05"},
            {"level", "full"}
        };
    } else if (value == "view_content") {
        j = {
            {"permission", "view_content"},
            {"granted_at", "2024-09-25"},
            {"level", "read-only"}
        };
    }
}

// Recursively walk the json and apply replacements
void transformJson(json &j) {
    if (j.is_object()) {
        for (auto &item : j.items()) {
            transformJson(item.value());
        }
    } else if (j.is_array()) {
        for (auto &elem : j) {
            transformJson(elem);
        }
    } else if (j.is_string()) {
        applyReplacementMap(j);
    }
}

// ------------------ Utility: timestamp + paths ------------------

std::string makeTimestamp() {
    using namespace std::chrono;

    auto now = system_clock::now();
    std::time_t tt = system_clock::to_time_t(now);
    std::tm local_tm{};

#if defined(_WIN32) || defined(_WIN64)
    localtime_s(&local_tm, &tt);
#else
    localtime_r(&tt, &local_tm);
#endif

    std::ostringstream oss;
    oss << std::put_time(&local_tm, "%Y%m%d_%H%M%S");
    return oss.str();
}

// ------------------ Core file processing ------------------

void processJsonFile(const fs::path &inputPath, const fs::path &outputPath) {
    try {
        std::ifstream inFile(inputPath);
        if (!inFile) {
            throw std::runtime_error("Failed to open input file");
        }

        json j;
        inFile >> j;
        inFile.close();

        transformJson(j);

        std::ofstream outFile(outputPath);
        if (!outFile) {
            throw std::runtime_error("Failed to open output file");
        }

        outFile << std::setw(4) << j << std::endl;
    } catch (const std::exception &ex) {
        std::cerr << "Error processing JSON file '" << inputPath
                  << "': " << ex.what()
                  << "\nCopying file as-is.\n";

        // On any error, copy the original file unchanged
        try {
            fs::copy_file(inputPath, outputPath,
                          fs::copy_options::overwrite_existing);
        } catch (const std::exception &copyEx) {
            std::cerr << "Failed to copy original file '" << inputPath
                      << "': " << copyEx.what() << '\n';
        }
    }
}

void processDirectory(const fs::path &inputRoot, const fs::path &outputRoot) {
    for (const auto &entry : fs::recursive_directory_iterator(inputRoot)) {
        const fs::path &path = entry.path();
        fs::path relative = fs::relative(path, inputRoot);
        fs::path outPath = outputRoot / relative;

        if (entry.is_directory()) {
            fs::create_directories(outPath);
        } else if (entry.is_regular_file()) {
            fs::create_directories(outPath.parent_path());

            if (path.extension() == ".json") {
                processJsonFile(path, outPath);
            } else {
                // Non-JSON files: copy as-is
                try {
                    fs::copy_file(path, outPath,
                                  fs::copy_options::overwrite_existing);
                } catch (const std::exception &ex) {
                    std::cerr << "Error copying file '" << path
                              << "': " << ex.what() << '\n';
                }
            }
        }
    }
}

// ------------------ main ------------------

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0]
                  << " <path-to-user_profiles-directory>\n";
        return 1;
    }

    fs::path inputDir = argv[1];

    if (!fs::exists(inputDir) || !fs::is_directory(inputDir)) {
        std::cerr << "Error: '" << inputDir << "' is not a valid directory.\n";
        return 1;
    }

    // Output folder name: user_profiles_updated_YYYYMMDD_HHMMSS
    std::string timestamp = makeTimestamp();
    std::string outputFolderName = "user_profiles_updated_" + timestamp;

    fs::path parent = inputDir.parent_path();
    if (parent.empty()) {
        parent = fs::current_path();
    }

    fs::path outputDir = parent / outputFolderName;

    try {
        fs::create_directories(outputDir);
    } catch (const std::exception &ex) {
        std::cerr << "Failed to create output directory '"
                  << outputDir << "': " << ex.what() << '\n';
        return 1;
    }

    std::cout << "Input directory : " << inputDir << "\n";
    std::cout << "Output directory: " << outputDir << "\n";

    processDirectory(inputDir, outputDir);

    std::cout << "Processing complete.\n";
    return 0;
}
