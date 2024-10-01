#include <string>
#include <iostream>
#include <sstream>

#include "row.h"
#include "third_party/leveldb/coding.h"

namespace norodb {

std::string RowHeader::to_string() {
  std::stringstream s;

  s << "RowHeader(check_sum=" << check_sum << ", version=" << version
    << ", key_size=" << key_size << ", val_size=" << val_size
    << ", seq_num=" << seq_num << ")";

  return s.str();
}

// Serializes a header to a bytearray so it can be written to a  file
ByteBuffer* RowHeader::serialize() {
  auto buff = new ByteBuffer();
  buff->putLong(check_sum);
  buff->put(version);
  buff->put(key_size);
  buff->putInt(val_size);
  buff->putLong(seq_num);
  buff->putInt(row_size);

  return buff;
}

// Recreates a header from a byte array
RowHeader* RowHeader::deserialize(ByteBuffer& buff) {
  return new RowHeader(buff.getLong(), buff.get(), buff.get(),
                       buff.getInt(), buff.getLong());
}


Row::Row(ByteBuffer* key, ByteBuffer* val) {
  this->key = key;
  this->val = val;
  header = new RowHeader(0, 0, 0, 0, 0);
}


Row* Row::deserialize(ByteBuffer& buffer) {
  ByteBuffer* key;
  ByteBuffer* val;
  return new Row(key, val);
}

Row::~Row() {
  delete key;
  delete val;
  delete header;
}


} // namespace norodb
