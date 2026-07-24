#pragma once

#include <Unreal/UObject.hpp>
#include <Unreal/CoreUObject/UObject/Class.hpp>
#include <Unreal/FString.hpp>
#include <Unreal/NameTypes.hpp>
#include <Unreal/Core/Containers/Map.hpp>
#include <Unreal/Core/Templates/Function.hpp>
#include <DynamicOutput/DynamicOutput.hpp>
#include <Unreal/TypeChecker.hpp>

namespace RC::Unreal
{
    // Base class for all table row structs to inherit from
    struct RC_UE_API FTableRowBase
    {
        FTableRowBase() {}
        virtual ~FTableRowBase() {}
    };

    class RC_UE_API UDataTable : public UObject
    {
        DECLARE_EXTERNAL_OBJECT_CLASS(UDataTable, Engine);

    public:
        static std::unordered_map<File::StringType, uint32> VTableLayoutMap;

    public:
#include <MemberVariableLayout_HeaderWrapper_UDataTable.hpp>
    
    protected:
        /** Called to add rows to the data table */
        void AddRowInternal(FName RowName, uint8* RowDataPtr);

        /** Deletes the row memory */
        void RemoveRowInternal(FName RowName);

    public:
        /**
         * Get all of the rows in the table, regardless of name
         */
        template <class T>
        void GetAllRows(const TCHAR* ContextString, TArray<T*>& OutRowArray) const
        {
            if (!GetRowStruct())
            {
                Output::send<LogLevel::Error>(STR("UDataTable::GetAllRows : DataTable '{}' has no RowStruct specified ({}).\n"), 
                    GetPathName(), ContextString);
                return;
            }

            if (!GetRowStruct()->IsChildOf(T::StaticStruct()))
            {
                Output::send<LogLevel::Error>(STR("UDataTable::GetAllRows : Incorrect type specified for DataTable '{}' ({}).\n"), 
                    GetPathName(), ContextString);
                return;
            }

            const TMap<FName, unsigned char*>& RowMapRef = GetRowMap();
            OutRowArray.Reserve(OutRowArray.Num() + RowMapRef.Num());
            
            for (auto& Pair : RowMapRef)
            {
                OutRowArray.Add(reinterpret_cast<T*>(Pair.Value));
            }
        }

        template <class T>
        void GetAllRows(const StringType& ContextString, TArray<T*>& OutRowArray) const
        {
            GetAllRows<T>(ContextString, OutRowArray);
        }
        
        /**
         * Function to find the row of a table given its name.
         * @param RowName The name of the row to find
         * @param ContextString String for error reporting
         * @param bWarnIfRowMissing Whether to log a warning if the row is missing
         * @return Pointer to the row data if found, nullptr otherwise
         */
        template <class T>
        T* FindRow(FName RowName, const TCHAR* ContextString, bool bWarnIfRowMissing = true) const
        {
            if (!GetRowStruct())
            {
                if (bWarnIfRowMissing)
                {
                    Output::send<LogLevel::Error>(STR("UDataTable::FindRow : '{}' specified no RowStruct for DataTable '{}'.\n"), 
                        ContextString, GetPathName());
                }
                return nullptr;
            }

            if (!GetRowStruct()->IsChildOf(T::StaticStruct()))
            {
                if (bWarnIfRowMissing)
                {
                    Output::send<LogLevel::Error>(STR("UDataTable::FindRow : '{}' specified incorrect type for DataTable '{}'.\n"), 
                        ContextString, GetPathName());
                }
                return nullptr;
            }

            if (RowName.IsNone())
            {
                if (bWarnIfRowMissing)
                {
                    Output::send<LogLevel::Warning>(STR("UDataTable::FindRow : '{}' requested invalid row 'None' from DataTable '{}'.\n"), 
                        ContextString, GetPathName());
                }
                return nullptr;
            }

            const TMap<FName, unsigned char*>& RowMapRef = GetRowMap();
            unsigned char* const* RowDataPtr = RowMapRef.Find(RowName);
            if (RowDataPtr == nullptr)
            {
                if (bWarnIfRowMissing)
                {
                    Output::send<LogLevel::Warning>(STR("UDataTable::FindRow : '{}' requested row '{}' not in DataTable '{}'.\n"), 
                        ContextString, RowName.ToString(), GetPathName());
                }
                return nullptr;
            }

            unsigned char* RowData = *RowDataPtr;
            return reinterpret_cast<T*>(RowData);
        }

        template <class T>
        T* FindRow(FName RowName, const StringType& ContextString, bool bWarnIfRowMissing = true) const
        {
            return FindRow<T>(RowName, ContextString, bWarnIfRowMissing);
        }

        /**
         * Perform some operation for every row.
         */
        template <class T>
        void ForeachRow(const TCHAR* ContextString, TFunctionRef<void(const FName& Key, const T& Value)> Predicate) const
        {
            if (!GetRowStruct())
            {
                Output::send<LogLevel::Error>(STR("UDataTable::ForeachRow : DataTable '{}' has no RowStruct specified ({}).\n"), 
                    GetPathName(), ContextString);
                return;
            }

            if (!GetRowStruct()->IsChildOf(T::StaticStruct()))
            {
                Output::send<LogLevel::Error>(STR("UDataTable::ForeachRow : Incorrect type specified for DataTable '{}' ({}).\n"), 
                    GetPathName(), ContextString);
                return;
            }

            const TMap<FName, unsigned char*>& RowMapRef = GetRowMap();
            for (auto& Pair : RowMapRef)
            {
                T* Entry = reinterpret_cast<T*>(Pair.Value);
                Predicate(Pair.Key, *Entry);
            }
        }

        template <class T>
        void ForeachRow(const StringType& ContextString, TFunctionRef<void(const FName& Key, const T& Value)> Predicate) const
        {
            ForeachRow<T>(ContextString, Predicate);
        }

        /**
         * High performance version with no type safety
         */
        uint8* FindRowUnchecked(FName RowName) const
        {
            if (!GetRowStruct())
            {
                return nullptr;
            }

            const TMap<FName, unsigned char*>& RowMapRef = GetRowMap();
            unsigned char* const* RowDataPtr = RowMapRef.Find(RowName);
            
            if (RowDataPtr == nullptr)
            {
                return nullptr;
            }

            return *RowDataPtr;
        }

        /** Empty the table info (will not clear RowStruct) */
        void EmptyTable();

        /**
         * Get an array of all the row names
         */
        TArray<FName> GetRowNames() const;

        /** Removes a single row from the DataTable by name. Just returns if row is not found. */
        void RemoveRow(FName RowName);

        /** Copies RowData into table. That is: create Row if not found and copy data into the RowMap based on RowData. This is a "copy in" operation, so changing the passed in RowData after the fact does nothing. */
        void AddRow(FName RowName, const FTableRowBase& RowData);
        void AddRow(FName RowName, const uint8* RowData, const UScriptStruct* RowType);

    protected:
        UScriptStruct& GetEmptyUsingStruct() const;
    };
}