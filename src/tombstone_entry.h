#ifndef NORO_DB_TOMBSTONE_ENTRY_H_
#define NORO_DB_TOMBSTONE_ENTRY_H_

#include <vector>
#include <memory>

#include "byte_buffer.h"

namespace norodb {

class TombstoneEntry {
  static const int CHECKSUM_OFFSET = 0;
  static const int VERSION_OFFSET = 8;
  static const int SEQUENCE_NUMBER_OFFSET = 9;
  static const int KEY_SIZE_OFFSET = 17;

  uint64_t check_sum;
  uint8_t version;
  uint64_t seq_num;
  uint8_t key_size;
  ByteBuffer key;
public:
  TombstoneEntry(ByteBuffer& key, uint8_t version, uint64_t seq_num) :
    key(key), version(version), seq_num(seq_num) {};

  std::shared_ptr<ByteBuffer> serialize();

  static std::shared_ptr<TombstoneEntry> deserialize(ByteBuffer& buffer);
};

}  // namespace norodb

#endif
