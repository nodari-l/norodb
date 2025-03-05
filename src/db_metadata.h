#ifndef NORO_DB_DB_META_DATA_H_
#define NORO_DB_DB_META_DATA_H_

#include <iostream>

#include "byte_buffer.h"
#include "db_directory.h"
#include "db_options.h"
#include "db_file.h"

namespace norodb {

class DBMetadata : public DBFile {
  DBDirectory db_dir;

  uint64_t check_sum = 0;
  uint8_t version = 0;
  uint64_t seq_num = 0;
  uint8_t max_file_size = 0;

  static const int SIZE = 8 + 1 + 8 + 1;
  static constexpr std::string METADATA_FILE_NAME = "metadata";

public:
  DBMetadata();
  DBMetadata(uint32_t file_id, DBDirectory& dir, DBOptions& options);
  
  friend std::ostream& operator<<(std::ostream& os, DBMetadata& f);
  
  ~DBMetadata() {
    file.close();
  };

  /**
   * Saves metadata to disk
   */
  void save();

  /**
   * Loads metadata from disk
   */
  void load_if_exists();

};

} // namespace nododb

#endif

