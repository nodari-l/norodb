#include "tombstone_entry.h"

namespace norodb {

TombstoneEntry::TombstoneEntry(ByteBuffer& key, uint8_t version, uint64_t seq_num) :
    key(key), version(version), seq_num(seq_num) {

  key_size = key.size();

};

std::shared_ptr<ByteBuffer> TombstoneEntry::serialize() {
  std::shared_ptr<ByteBuffer> buffer(new ByteBuffer());

  buffer->put_long(check_sum);
  buffer->put(version);
  buffer->put_long(seq_num);
  buffer->put(key_size);
  buffer->put(&key);

  return buffer;
}

std::shared_ptr<TombstoneEntry> TombstoneEntry::deserialize(ByteBuffer& buffer) {
  uint64_t check_sum = buffer.get_long();
  uint8_t version = buffer.get();
  uint64_t seq_num = buffer.get_long();
  uint8_t key_size = buffer.get();
  uint8_t key[key_size];

  buffer.get_bytes(key, key_size);
  ByteBuffer key_buffer = ByteBuffer(key, key_size);


  std::shared_ptr<TombstoneEntry> te(new TombstoneEntry(key_buffer, version, seq_num));

  return te;
}

uint64_t TombstoneEntry::get_check_sum() {
  return check_sum;
};

uint8_t TombstoneEntry::get_version() {
  return version;
};

uint64_t TombstoneEntry::get_seq_num() {
  return seq_num;
};

uint8_t TombstoneEntry::get_key_size() {
  return key_size;
};

ByteBuffer TombstoneEntry::get_key() {
  return key;
};

uint8_t TombstoneEntry::get_size() {
  return HEADER_SIZE + key_size;
}

} // namespace norodb
