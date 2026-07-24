#pragma once

namespace RC::Unreal {
    class FStructuredArchive {
    public:
        struct FStream {
            class Dummy {};
            FStructuredArchive::FStream::Dummy EnterElement() {
                return FStructuredArchive::FStream::Dummy{};
            }
        };
        struct FSlot {
            FStructuredArchive::FStream EnterStream() {
                return FStructuredArchive::FStream{};
            }
        };
    };
}