#ifndef NORO_DB_TOMBSTONE_FILE_H_
#define NORO_DB_TOMBSTONE_FILE_H_

#include <memory>

#include "byte_buffer.h"
#include "db_file.h"
#include "db_directory.h"
#include "db_options.h"
#include "tombstone_entry.h"

namespace norodb {
class TombstoneFile : public DBFile {
  public:
    TombstoneFile(uint32_t file_id, DBDirectory& dir, DBOptions& options);

    /**
     * Writes a tombstone entry to a file
     *
     * @param entry - a reference to a TombstoneEntry object
     * @return - write offset
     */
    void write_entry(TombstoneEntry& entry);

    /**
     * Reads from a file at the location `offset` and deserializes read bytes to a
     * TombstoneEntry object
     *
     * @param offset - location from which a read is done
     * @return a pointer to a TombstoneEntry object
     */
    std::shared_ptr<TombstoneEntry> read_entry(uint64_t offset);
};
} // namespace nododb

#endif

