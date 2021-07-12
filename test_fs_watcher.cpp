#include <iostream>
#include "FileWatcher.h"

int main()
{
    FileWatcher fw{"./", std::chrono::milliseconds(1000)};

    fw.start([](std::string path_to_watch, FileStatus status) -> void {
        if (!std::filesystem::is_regular_file(std::filesystem::path(path_to_watch)) && status != FileStatus::erased)
        {
            return;
        }

        switch (status)
        {
        case FileStatus::created:
            std::cout << "File created: " << path_to_watch << '\n';
            break;
        case FileStatus::modified:

            if (path_to_watch.substr(path_to_watch.find_last_of(".") + 1) == "cpp")
            {
                #if defined(_WIN32)
                    system("watch.bat");
                #elif defined(_WIN64)
                    system("watch.bat");
                #elif defined(__CYGWIN__) && !defined(_WIN32)
                    system("watch.bat"); // should this be a .sh?
                #else
                    system("./myfile.sh");
                #endif
            }
            break;
        case FileStatus::erased:
            std::cout << "File erased: " << path_to_watch << '\n';
            break;
        default:
            std::cout << "Error! Unknown file status.\n";
        }
    });
}