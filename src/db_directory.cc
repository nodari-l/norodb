#include "db_directory.h"

namespace norodb {

DBDirectory::DBDirectory()  {
  db_dir = fs::path("norodb");
  data_files_dir = db_dir / "data";
  index_files_dir = db_dir / "index";
  tombstones_files_dir = db_dir / "tombstones";
  create_directories();
};


DBDirectory::DBDirectory(fs::path dir) {
  db_dir = dir;
  data_files_dir = dir / "data";
  index_files_dir = dir / "index";
  tombstones_files_dir = db_dir / "tombstones";
  create_directories();
}

void DBDirectory::create_directories() {
  if (!fs::exists(db_dir)) fs::create_directory(db_dir);

  if (!fs::exists(data_files_dir)) fs::create_directory(data_files_dir);

  if (!fs::exists(index_files_dir)) fs::create_directory(index_files_dir);

  if (!fs::exists(tombstones_files_dir)) fs::create_directory(tombstones_files_dir);
}

std::vector<fs::path> DBDirectory::list_index_files() {
  std::vector<fs::path> res;

  for (const auto& _file : fs::directory_iterator(index_files_dir)) {
    res.push_back(_file.path());
  }

  return res;
}

std::vector<fs::path> DBDirectory::list_data_files() {
  std::vector<fs::path> res;

  for (const auto& _file : fs::directory_iterator(data_files_dir)) {
    res.push_back(_file.path());
  }

  return res;
}

}  // namespace norodb
