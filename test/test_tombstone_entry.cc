#include <iostream>
#include <memory>

#include "gtest/gtest.h"

#include "tombstone_entry.h"

TEST(TombstoneEntryTest, SerializeDeserialize) {
  // Create a sample TombstoneEntry
  norodb::ByteBuffer key_buffer("test_key");
  uint8_t version = 1;
  uint64_t seq_num = 12345;
  norodb::TombstoneEntry entry(key_buffer, version, seq_num);

  // Serialize the entry
  std::shared_ptr<norodb::ByteBuffer> buffer = entry.serialize();

  // Deserialize the entry
  std::shared_ptr<norodb::TombstoneEntry> deserialized = norodb::TombstoneEntry::deserialize(*buffer);

  // Assertions to check if serialization and deserialization were successful
  ASSERT_EQ(deserialized->get_version(), version);
  ASSERT_EQ(deserialized->get_seq_num(), seq_num);
  ASSERT_EQ(deserialized->get_key_size(), key_buffer.size()); // Check key size

  // Compare the keys (important!)
  ASSERT_EQ(deserialized->get_key().size(), key_buffer.size());
  ASSERT_EQ(deserialized->get_key().to_string(), key_buffer.to_string());
}


int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
