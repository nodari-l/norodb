#ifndef NORO_DB_DB_OPTIONS_H_
#define NORO_DB_DB_OPTIONS_H_

#include <iostream>

namespace norodb {

class DBOptions {
 
  /**
   * 1GB. If current DBFile exceeds this limit a new DBFile will be created
   */
  uint32_t MAX_FILE_SIZE = 1024 * 1024 * 1024;

  /**
   * If is positive buffers will be flushed to the disk once the buffer size grows bigger
   * than this value. If value is 0 it's ignored.
   */
  uint32_t FLUSH_DATA_SIZE_BYTES = 0;

  bool FLUSH_ON_WRITE = true;  // if true, buffers will flushed to the disk after every write
  
public:
  friend std::ostream& operator<<(std::ostream& os, DBOptions& opts) {
    os << "DBOptions(MAX_FILE_SIZE=" << opts.MAX_FILE_SIZE <<
       "; FLUSH_DATA_SIZE_BYTES=" << opts.FLUSH_DATA_SIZE_BYTES <<
       ": FLUSH_ON_WRITE=" << opts.FLUSH_ON_WRITE << ")";

    return os;
  }

  void set_max_file_size(uint32_t size) {
    MAX_FILE_SIZE = size;
  }

  void set_flush_data_size_bytes(uint32_t size) {
    FLUSH_DATA_SIZE_BYTES = size;
  }

  void set_flush_on_write(bool flush) {
    FLUSH_ON_WRITE = flush;
  }

  uint32_t get_max_file_size() {
    return MAX_FILE_SIZE; 
  }

  uint32_t get_flush_data_size_bytes() {
    return FLUSH_DATA_SIZE_BYTES;
  }
  
  bool get_flush_on_write() {
    return FLUSH_ON_WRITE;
  }
};

}  // namespace norodb

#endif
