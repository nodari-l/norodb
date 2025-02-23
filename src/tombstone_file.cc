#include "tombstone_file.h"

namespace norodb {

TombstoneFile::TombstoneFile(uint32_t file_id, DBDirectory& dir, DBOptions& options)
    : DBFile{file_id, dir, options} {
  std::stringstream fname;
  fname << file_id << ".tombstone";

  fs::path data_file_path = dir.get_tombstones_dir() / fname.str();

  file.open(data_file_path.string(),
            std::ios::in | std::ios::out | std::ios::app | std::ios::ate | std::ios::binary);
}

void TombstoneFile::write_entry(TombstoneEntry& entry) {
  write(*(entry.serialize()));
  write_offset += entry.get_size();
}

std::shared_ptr<TombstoneEntry> TombstoneFile::read_entry(uint64_t offset) {
  uint64_t temp_offset = offset;
  auto header_buff = ByteBuffer(TombstoneEntry::HEADER_SIZE);
  read(temp_offset, TombstoneEntry::HEADER_SIZE, header_buff);

  uint64_t check_sum = header_buff.get_long();
  uint8_t version = header_buff.get();
  uint64_t seq_num = header_buff.get_long();
  uint8_t key_size = header_buff.get();

  temp_offset += TombstoneEntry::HEADER_SIZE;
  auto key = ByteBuffer(key_size);
  read(temp_offset, key_size, key);

  auto entry = std::make_shared<TombstoneEntry>(key, version, seq_num);

  return entry;
}


} // namespace norodb
