#include "fileio.hpp"

namespace fs = std::filesystem;

static std::string
search_in_dir_tree(const fs::path& dir, const std::string& file_name,
    size_t max_depth)
{
    try {
        fs::path full_path = dir / file_name;
        if (fs::is_regular_file(full_path))
            return full_path.string();

        if (max_depth == 0)
            return "";

        for (const auto& entry : fs::directory_iterator(dir)) {
            if (fs::is_directory(entry)) {
                std::string result = search_in_dir_tree(
                    entry.path(), file_name, max_depth - 1);
                if (!result.empty())
                    return result;
            }
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << e.what() << std::endl;
    }
    return "";
}

std::string
fileio_getpath(const std::string& file_path, size_t max_depth)
{
    fs::path base_dir = fs::current_path();
    for (size_t depth = 0; depth <= max_depth; ++depth) {
        std::string result = search_in_dir_tree(base_dir, file_path, max_depth);
        if (!result.empty())
            return result;

        if (depth == max_depth)
            break;

        fs::path parent_dir = base_dir.parent_path();
        if (parent_dir == base_dir)
            break;

        base_dir = parent_dir;
    }

    return "";
}