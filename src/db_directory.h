#ifndef NORO_DB_DB_DIRECTORY_H_
#define NORO_DB_DB_DIRECTORY_H_

#include <filesystem>
#include <string>
#include <vector>
#include <iostream>

#include "status.h"

namespace fs = std::filesystem;

namespace norodb {

class DBDirectory {
  fs::path db_dir;
  fs::path data_files_dir;
  fs::path index_files_dir;
  fs::path tombstones_files_dir;

 public:
  /**
   * Creates required folders in the current folder
   */
  DBDirectory();

  /**
   *
   * @param dir - path to a directory where DB's folders and files will be created.
   */
  DBDirectory(fs::path dir);

  /**
   * TODO: implement or get rid of this func
   */
  void close();

  /**
   * Creates required folders:
   *  data - where data files are stored
   *  index - where index files are stored
   *  tombstones - where tombstones' files are stored
   */
  void create_directories();

  /**
   * Returns a path to the DB's parent directory
   */
  fs::path get_path() { return db_dir; };

  /**
   * Returns a path to the directory where the data files are stored
   */
  fs::path get_data_dir() { return data_files_dir; };

  /**
   * Returns a path to the directory where the index files are stored
   */
  fs::path get_index_dir() { return index_files_dir; };

  /**
   * Returns a path to the directory where the tombstone files are stored
   */
  fs::path get_tombstones_dir() { return tombstones_files_dir; };

  /**
   * Lists all the data files. This func is needed during the DB opening to open all availble
   * data files for reading and last data file for writing
   */
  std::vector<fs::path> list_data_files();

  /**
   * Lists all the index files. This func is needed during the DB opening to open all availble
   * index files for reading and last index file for writing
   */
  std::vector<fs::path> list_index_files();

  friend std::ostream& operator<<(std::ostream& os, DBDirectory& dir) {
    os << "DBDirectory(path=" << dir.get_path() << ")";
    return os;
  };
};

}  // namespace norodb

#endif
