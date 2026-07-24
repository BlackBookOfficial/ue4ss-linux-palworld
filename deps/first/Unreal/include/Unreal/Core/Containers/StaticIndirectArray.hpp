// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include <Unreal/Core/CoreTypes.hpp>
#include <Unreal/Core/Misc/AssertionMacros.hpp>
#include <Unreal/Core/HAL/UnrealMemory.hpp>
#include <Unreal/Core/HAL/PlatformAtomics.hpp>
#include <Unreal/Core/HAL/PlatformMisc.hpp>

namespace RC::Unreal
{
    /**
     * Simple array type that can be expanded without invalidating existing entries.
     * This is critical to thread safe FNames.
     *
     * Used by FUObjectArray in UE versions prior to 4.11.
     *
     * @param ElementType Type of the pointer we are storing in the array
     * @param MaxTotalElements absolute maximum number of elements this array can ever hold
     * @param ElementsPerChunk how many elements to allocate in a chunk
     */
    template<typename ElementType, int32 MaxTotalElements, int32 ElementsPerChunk>
    class TStaticIndirectArrayThreadSafeRead
    {
        enum
        {
            // figure out how many elements we need in the master table
            ChunkTableSize = (MaxTotalElements + ElementsPerChunk - 1) / ElementsPerChunk
        };

        /** Static master table to chunks of pointers **/
        ElementType** Chunks[ChunkTableSize];
        /** Number of elements we currently have **/
        int32 NumElements;
        /** Number of chunks we currently have **/
        int32 NumChunks;

        /**
         * Expands the array so that Element[Index] is allocated. New pointers are all zero.
         * @param Index The Index of an element we want to be sure is allocated
         **/
        void ExpandChunksToIndex(int32 Index)
        {
            check(Index >= 0 && Index < MaxTotalElements);
            int32 ChunkIndex = Index / ElementsPerChunk;
            while (1)
            {
                if (ChunkIndex < NumChunks)
                {
                    break;
                }
                // add a chunk, and make sure nobody else tries
                ElementType*** Chunk = &Chunks[ChunkIndex];
                ElementType** NewChunk = (ElementType**)FMemory::Malloc(sizeof(ElementType*) * ElementsPerChunk);
                FMemory::Memzero(NewChunk, sizeof(ElementType*) * ElementsPerChunk);
                if (FPlatformAtomics::InterlockedCompareExchangePointer((void**)Chunk, NewChunk, nullptr))
                {
                    // someone else beat us to the add, we don't support multiple concurrent adds
                    check(0);
                }
                else
                {
                    NumChunks++;
                }
            }
            check(ChunkIndex < NumChunks && Chunks[ChunkIndex]); // should have a valid pointer now
        }

        /**
         * Return a pointer to the pointer to a given element
         * @param Index The Index of an element we want to retrieve the pointer-to-pointer for
         **/
        ElementType const* const* GetItemPtr(int32 Index) const
        {
            int32 ChunkIndex = Index / ElementsPerChunk;
            int32 WithinChunkIndex = Index % ElementsPerChunk;
            check(IsValidIndex(Index) && ChunkIndex < NumChunks && Index < MaxTotalElements);
            ElementType** Chunk = Chunks[ChunkIndex];
            check(Chunk);
            return Chunk + WithinChunkIndex;
        }

    public:
        /** Constructor : Probably not thread safe **/
        TStaticIndirectArrayThreadSafeRead()
            : NumElements(0)
            , NumChunks(0)
        {
            FMemory::Memzero(Chunks);
        }

        /**
         * Return the number of elements in the array
         * Thread safe, but you know, someone might have added more elements before this even returns
         * @return    the number of elements in the array
         **/
        int32 Num() const
        {
            return NumElements;
        }

        /**
         * Return if this index is valid
         * Thread safe, if it is valid now, it is valid forever. Other threads might be adding during this call.
         * @param Index Index to test
         * @return true, if this is a valid
         **/
        bool IsValidIndex(int32 Index) const
        {
            return Index < Num() && Index >= 0;
        }

        /**
         * Return a reference to an element
         * @param Index Index to return
         * @return a reference to the pointer to the element
         * Thread safe, if it is valid now, it is valid forever. This might return nullptr, but by then, some other thread might have made it non-nullptr.
         **/
        ElementType const* const& operator[](int32 Index) const
        {
            ElementType const* const* ItemPtr = GetItemPtr(Index);
            check(ItemPtr);
            return *ItemPtr;
        }

        /**
         * Add more elements to the array
         * @param NumToAdd Number of elements to add
         * @return the number of elements in the container before we did the add. In other words, the add index.
         * Not thread safe. This should only be called by one thread, but the other methods can be called while this is going on.
         **/
        int32 AddZeroed(int32 NumToAdd)
        {
            int32 Result = NumElements;
            check(NumElements + NumToAdd <= MaxTotalElements);
            ExpandChunksToIndex(NumElements + NumToAdd - 1);
            check(Result == NumElements);
            NumElements += NumToAdd;
            FPlatformMisc::MemoryBarrier();
            return Result;
        }

        /**
         * Return a naked pointer to the fundamental data structure for debug visualizers.
         **/
        ElementType*** GetRootBlockForDebuggerVisualizers()
        {
            return Chunks;
        }

        /**
         * Make sure chunks are allocated to hold the specified capacity of items. This is NOT thread safe.
         **/
        void Reserve(int32 Capacity)
        {
            check(Capacity >= 0 && Capacity <= MaxTotalElements);
            if (Capacity > NumElements)
            {
                int32 MaxChunks = (Capacity + ElementsPerChunk - 1) / ElementsPerChunk;
                check(MaxChunks >= NumChunks);
                for (int32 ChunkIndex = 0; ChunkIndex < MaxChunks; ++ChunkIndex)
                {
                    if (!Chunks[ChunkIndex])
                    {
                        ElementType** NewChunk = (ElementType**)FMemory::Malloc(sizeof(ElementType*) * ElementsPerChunk);
                        FMemory::Memzero(NewChunk, sizeof(ElementType*) * ElementsPerChunk);
                        Chunks[ChunkIndex] = NewChunk;
                    }
                }
                NumChunks = MaxChunks;
            }
        }
    };
}
