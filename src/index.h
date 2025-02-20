#ifndef NORO_DB_INDEX_H_
#define NORO_DB_INDEX_H_

#include <unordered_map>
#include <string>
#include <memory>
#include <mutex>
#include <atomic>
#include <iostream>

#include "byte_buffer.h"
#include "index_file.h"
#include "db_directory.h"
#include "db_options.h"
#include "index_entry.h"

namespace norodb {

// TODO: replace unordered_map with a B-Tree???
// TODO: separate in-memory and on-disk indices
class DBIndex {
  DBOptions db_options;
  DBDirectory db_dir;
  std::unordered_map<std::string, IndexEntry> data; // in-memory index
  std::unique_ptr<IndexFile> curr_index_file;
  std::atomic<uint32_t> file_id = 0;
  std::mutex write_lock;
  std::atomic<uint64_t> index_entry_id = 0;

  public:
    static IndexEntry dummy; // wtf??

    /**
     * Adds an item to the index
     *
     * @param key - item's key
     * @param entry - index item metadata
     */
    void put(ByteBuffer& key, IndexEntry& entry);

    /**
     * Searches for an record in the index
     */
    IndexEntry get(ByteBuffer& key);

    /**
     * Remove an item from the index
     *
     * @param key - items' key to be removed
     */
    void remove(ByteBuffer& key);

    /**
     * Writes an index entry to the file
     *
     * @param buff - an index entry as a ByteBuffer
     */
    void write_entry(ByteBuffer& buff);

    void roll_over_current_index_file();

    uint32_t get_next_file_id();

    uint64_t get_next_index_entry_id();
};

}  // namespace norodb

#endif
