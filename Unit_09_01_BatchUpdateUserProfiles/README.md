# Unit_09_01_BatchUpdateUserProfiles


C++ program that processes user profile JSON files, updates fields based on a replacement map, and writes results to a new timestamped directory.

## Requirements implemented

- Accepts the path to the `user_profiles` directory as a **command-line argument**.
- Replaces all emails ending with `@company.com` with `@newcompany.com`.
- Replaces string values using this map:
  - `"enabled"`   → `{ "status": "enabled",  "since": "2024-10-01" }`
  - `"disabled"`  → `{ "status": "disabled", "since": "2024-10-01" }`
  - `"manage_users"` → `{ "permission": "manage_users", "granted_at": "2024-10-05", "level": "full" }`
  - `"view_content"` → `{ "permission": "view_content", "granted_at": "2024-09-25", "level": "read-only" }`
- Uses **nlohmann::json** to parse and modify JSON.
- Uses **std::filesystem** to recursively traverse directories.
- On JSON parsing errors, copies the original file unchanged to the output directory.
- Non-JSON files are copied as-is.

## Folder structure

```text
Unit_08_01_UserProfileUpdater/
├── main.cpp
├── json.hpp              # nlohmann/json single-header library (already placed here)
├── user_profiles/
│   ├── admins/
│   │   ├── admin1.json
│   │   └── admin2.json
│   ├── editors/
│   │   └── editor1.json
│   └── viewers/
│       └── viewer1.json
└── sample_output/
    └── (you can place one generated output folder here)
```

## How to build and run (Xcode)

1. Open **Xcode**.
2. Create a new **Command Line Tool** project.
3. Set the project location to this folder: `Unit_08_01_UserProfileUpdater`.
4. Add `main.cpp` and make sure it is part of the target.
5. Make sure the C++ standard is set to **C++17** in *Build Settings*.
6. `json.hpp` is already in this folder (nlohmann/json header).
7. In **Scheme → Edit Scheme → Run → Arguments Passed On Launch**, add the full path to the `user_profiles` directory as the first argument.

Example argument:

```text
/path/to/CSC-284-WB/assignments/JSON/Unit_08_01_UserProfileUpdater/user_profiles
```

## Command-line usage (if built via terminal)

```bash
./UserProfileUpdater <path-to-user_profiles>
```

Example:

```bash
./UserProfileUpdater ./user_profiles
```

The program will create a folder named like:

```text
user_profiles_updated_YYYYMMDD_HHMMSS
```

next to the input directory.
