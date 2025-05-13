#include "fileio.hpp"

std::string
fileio_getpath_r(const std::string& f, size_t md)
{
    namespace fs = std::filesystem;

    std::function<std::string(const fs::path&, const std::string&, size_t)> search_in_dir_tree; /* forward declaration for recursion */
    search_in_dir_tree =
        [&search_in_dir_tree](const fs::path& dir, const std::string& filename, size_t max_depth) -> std::string {
        try {
            fs::path full_path = dir / filename;
            if (fs::exists(full_path) && fs::is_regular_file(full_path))
                return full_path.string();

            if (max_depth == 0)
                return "";

            for (const auto& entry : fs::directory_iterator(dir)) {
                if (fs::is_directory(entry)) {
                    std::string result = search_in_dir_tree(entry.path(), filename, max_depth - 1);
                    if (!result.empty())
                        return result;
                }
            }
        } catch (const fs::filesystem_error& e) {
            std::cerr << e.what() << std::endl;
        }
        return "";
    };

    fs::path base_dir = fs::current_path();
    for (size_t depth = 0; depth <= md; ++depth) {
        std::string result = search_in_dir_tree(base_dir, f, md);
        if (!result.empty())
            return result;

        if (depth == md)
            break;

        fs::path parent_dir = base_dir.parent_path();
        if (parent_dir == base_dir)
            break;

        base_dir = parent_dir;
    }

    return "";
}