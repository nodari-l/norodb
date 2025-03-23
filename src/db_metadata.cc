#include "db_metadata.h"

namespace norodb {


DBMetadata::DBMetadata(uint32_t file_id, DBDirectory& dir, DBOptions& options)
    : DBFile{file_id, dir, options}, db_dir(dir) {

  fs::path file_path = db_dir.get_path() / METADATA_FILE_NAME;

  file.open(file_path.string(),
            std::ios::in | std::ios::out | std::ios::app | std::ios::ate | std::ios::binary);
}

std::ostream& operator<<(std::ostream& os, DBMetadata& f) {
  os << "DBMetadata(check_sum=" << f.check_sum << "; version=" << f.version << "; seq_num=" << f.seq_num << "; max_file_size=" << f.max_file_size << ")";

  return os;
};

void DBMetadata::save() {
  ByteBuffer buffer(SIZE);
  buffer.put_long(check_sum);
  buffer.put(version);
  buffer.put_long(seq_num);
  buffer.put(max_file_size);

  write(buffer);
}

void DBMetadata::load_if_exists() {
  if (fs::exists(db_dir.get_path() / METADATA_FILE_NAME)) {
    ByteBuffer buffer(SIZE);
    read(0, SIZE, buffer);

    check_sum = buffer.get_long();
    version = buffer.get();
    seq_num = buffer.get_long();
    max_file_size = buffer.get();
  }
}

} // namespace norodb
