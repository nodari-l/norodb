#include "index.h"

namespace norodb {

IndexEntry DBIndex::dummy(-1,-1,-1,-1);

void DBIndex::put(ByteBuffer& key, IndexEntry& entry) {
  write_lock.lock();
  IndexEntryHeader ie_header{13, 15, static_cast<uint8_t>(key.size()), 19};
  ByteBuffer buff{IndexEntryHeader::SIZE + key.size() + IndexEntry::SIZE};
  buff.put(ie_header.serialize().get());
  buff.put(&key);
  buff.put(entry.serialize().get());

  // key, entry
  write_entry(buff);
  data[key.to_string()] = entry;
  write_lock.unlock();
}

void DBIndex::write_entry(ByteBuffer& buff) {
  if (!curr_index_file or
      curr_index_file->get_write_offset() + buff.size() > db_options.get_max_file_size()) {
    roll_over_current_index_file();
  }
  curr_index_file->write(buff);
}


void DBIndex::roll_over_current_index_file() {
  if (curr_index_file) {
    curr_index_file->flush();
  }

  curr_index_file = std::unique_ptr<IndexFile>(new IndexFile(get_next_file_id(), db_dir, db_options));
}

IndexEntry DBIndex::get(ByteBuffer& key) {
      auto _key = key.to_string();
      if (data.find(_key) != data.end()) {
        return data[_key];
      }

      return dummy;
    }

void DBIndex::remove(ByteBuffer &key) {
  data.erase(key.to_string());
}

uint32_t DBIndex::get_next_file_id() {
  file_id++;
  return file_id;
}

uint64_t DBIndex::get_next_index_entry_id() {
  index_entry_id += 1;
  return index_entry_id;
}

} // namespace norodb
