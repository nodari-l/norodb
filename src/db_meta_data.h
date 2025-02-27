#ifndef NORO_DB_DB_META_DATA_H_
#define NORO_DB_DB_META_DATA_H_

#include "byte_buffer.h"
#include "db_directory.h"
#include "db_options.h"
#include "db_file.h"

namespace norodb {

class DBMetaData : public DBFile {
  DBDirectory db_dir;

  uint64_t check_sum = 0;
  uint8_t version = 0;
  uint64_t seq_num = 0;
  uint8_t max_file_size = 0;

  static const int SIZE = 8 + 1 + 8 + 1;
  static constexpr std::string METADATA_FILE_NAME = "metadata";

public:
  DBMetaData(uint32_t file_id, DBDirectory& dir, DBOptions& options);

  ~DBMetaData() {
    file.close();
  };

  /**
   * Saves metadata to disk
   */
  void save();

  /**
   * Loads metadata from disk
   */
  void load();

};

} // namespace nododb

#endif

