#include "db_meta_data.h"

namespace norodb {


DBMetaData::DBMetaData(uint32_t file_id, DBDirectory& dir, DBOptions& options)
    : DBFile{file_id, dir, options} {

  fs::path file_path = db_dir.get_path() / METADATA_FILE_NAME;

  file.open(file_path.string(),
            std::ios::in | std::ios::out | std::ios::app | std::ios::ate | std::ios::binary);
}


void DBMetaData::save() {
  ByteBuffer buffer(SIZE);
  buffer.put_long(check_sum);
  buffer.put(version);
  buffer.put_long(seq_num);
  buffer.put(max_file_size);

  write(buffer);
}


void DBMetaData::load() {
  ByteBuffer buffer(SIZE);
  read(0, SIZE, buffer);

  check_sum = buffer.get_long();
  version = buffer.get();
  seq_num = buffer.get_long();
  max_file_size = buffer.get();
}

} // namespace norodb