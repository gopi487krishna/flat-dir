#include <filesystem>
#include <iostream>

std::uint64_t file_size_warning_threshold = 134217728;

int main(int argc, char **argv) {
  const std::filesystem::path starting_path{std::filesystem::current_path()};

  const char* OUTPUT_ROOT_ENV = std::getenv("OUTPUT_ROOT");

  if (OUTPUT_ROOT_ENV == nullptr)
  {
      std::cerr << "Environment variable OUTPUT_ROOT undefined\n";
      std::abort();
  }

  std::filesystem::path output_root{OUTPUT_ROOT_ENV}; /* Specify where output folders will reside  Example : export OUTPUT_ROOT="/home/cooldev/outputs/" */

  /* Recursively iterate over directories and start checking */
  for(const auto& parent_dirs : std::filesystem::directory_iterator(starting_path))
  {
      int counter  = 0; /*Keep names unique*/

      if (!parent_dirs.is_directory())
      {
          continue;
      }

      std::string parent_dir_name = parent_dirs.path().filename().string();

      /* Create output dir for this one */
      auto output_dir_name = output_root/parent_dir_name;
      std::filesystem::create_directory(output_dir_name);

      for(const auto& entry : std::filesystem::recursive_directory_iterator(parent_dirs))
      {

          auto filename_str = entry.path().filename().string();

          if ( entry.is_directory())
          {
              std::cout <<"[dir:]" << entry.path().filename().string() << '\n';
          }
          else if (entry.is_regular_file())
          {
              if (std::filesystem::file_size(entry) >= file_size_warning_threshold)
              {
                  std::cout<< "[file: size threshold excedded]" << entry.path().filename().string() << '\n';
              }
              else {
              
                  std::cout <<"[file:]" << entry.path().filename().string() << '\n';
              }
              /*Copy the files to main folder with sequence*/
              std::filesystem::copy_file(entry, output_dir_name/(filename_str + '_' + std::to_string(counter++))); 
         }
      }
  }
  return 0;
}
