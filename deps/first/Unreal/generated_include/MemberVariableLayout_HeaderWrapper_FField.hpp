static std::unordered_map<File::StringType, int32_t> MemberOffsets;
static std::unordered_map<File::StringType, BitfieldInfo> BitfieldInfos;

private:
    FFieldClass*& GetClassPrivate();
    const FFieldClass*& GetClassPrivate() const;

private:
    FFieldVariant& GetOwner();
    const FFieldVariant& GetOwner() const;

private:
    FField*& GetNext();
    const FField*& GetNext() const;

private:
    FName& GetNamePrivate();
    const FName& GetNamePrivate() const;

public:
    EObjectFlags& GetFlagsPrivate();
    const EObjectFlags& GetFlagsPrivate() const;

public:
    static int32_t& UEP_TotalSize();
