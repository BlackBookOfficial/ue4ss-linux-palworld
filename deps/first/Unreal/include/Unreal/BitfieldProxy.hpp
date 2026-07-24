#pragma once

#include <cstdint>
#include <cstring>

namespace RC::Unreal
{
    /**
     * Runtime bitfield metadata for INI-overridable bit position, length, and storage size.
     */
    struct BitfieldInfo
    {
        uint8_t bit_pos{0};
        uint8_t bit_len{1};
        uint8_t storage_size{1}; // Size in bytes: 1, 2, 4, or 8
    };

    /**
     * Non-templated proxy type for accessing bitfields through a reference-like interface.
     * Allows both reading and writing individual bits within a storage unit.
     * All parameters are runtime values to support INI overrides, including storage size.
     *
     * Usage:
     *   BitfieldProxy proxy(storage_ptr, 0, 1, 4);
     *   bool val = proxy;           // Read bit
     *   proxy = true;               // Write bit
     *   obj.GetSomeBitfield() = true;  // When getter returns BitfieldProxy
     */
    struct BitfieldProxy
    {
        void* storage;
        uint8_t bit_pos;
        uint8_t bit_len;
        uint8_t storage_size;

        BitfieldProxy(void* s, uint8_t pos, uint8_t len, uint8_t size)
            : storage(s), bit_pos(pos), bit_len(len), storage_size(size) {}

        // Read the bitfield value
        operator bool() const
        {
            uint64_t value = 0;
            std::memcpy(&value, storage, storage_size);
            uint64_t mask = (1ULL << bit_len) - 1;
            return static_cast<bool>((value >> bit_pos) & mask);
        }

        // Write the bitfield value
        BitfieldProxy& operator=(bool val)
        {
            uint64_t value = 0;
            std::memcpy(&value, storage, storage_size);
            uint64_t mask = (1ULL << bit_len) - 1;
            value = (value & ~(mask << bit_pos)) | ((static_cast<uint64_t>(val) & mask) << bit_pos);
            std::memcpy(storage, &value, storage_size);
            return *this;
        }

        // Support chained assignment
        BitfieldProxy& operator=(const BitfieldProxy& other)
        {
            return *this = static_cast<bool>(other);
        }
    };

    /**
     * Const version of BitfieldProxy for read-only access.
     * Used when accessing bitfields through const member functions.
     */
    struct ConstBitfieldProxy
    {
        const void* storage;
        uint8_t bit_pos;
        uint8_t bit_len;
        uint8_t storage_size;

        ConstBitfieldProxy(const void* s, uint8_t pos, uint8_t len, uint8_t size)
            : storage(s), bit_pos(pos), bit_len(len), storage_size(size) {}

        // Read the bitfield value
        operator bool() const
        {
            uint64_t value = 0;
            std::memcpy(&value, storage, storage_size);
            uint64_t mask = (1ULL << bit_len) - 1;
            return static_cast<bool>((value >> bit_pos) & mask);
        }
    };
} // namespace RC::Unreal
