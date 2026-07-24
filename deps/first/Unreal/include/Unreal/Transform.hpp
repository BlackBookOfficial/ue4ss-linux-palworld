#pragma once

#include <Unreal/Quat.hpp>
#include <Unreal/UnrealCoreStructs.hpp>

namespace RC::Unreal
{
    // The 'alignas' used in this struct is because UE4 uses more efficient instructions to deal with this struct
    // They want everything aligned a certain way so we must do the same
    // TODO: Investigate FTransform and FVector in UE5.
    struct alignas(16) RC_UE_API FTransform
    {
        //FQuat Rotation;
        //alignas(16) FVector Translation;
        //alignas(16) FVector Scale3D;
//
        //inline FTransform() : Rotation(0.0f, 0.0f, 0.0f, 0.0f), Translation(0.0f, 0.0f, 0.0f), Scale3D(0.0f, 1.0f, 1.0f) {}
        //inline FTransform(FQuat Rotation, FVector Translation, FVector Scale3D) : Rotation(Rotation), Translation(Translation), Scale3D(Scale3D) {}
//
        //FTransform& operator=(const FTransform& Other)
        //{
        //    this->Rotation = Other.Rotation;
        //    this->Translation = Other.Translation;
        //    this->Scale3D = Other.Scale3D;
//
        //    return *this;
        //}

        // Used whenever FTransform needs to be stored in another struct.
        template<typename QuatType, typename VectorType>
        struct alignas(16) TTyped
        {
            QuatType Rotation;
            alignas(16) VectorType Translation;
            alignas(16) VectorType Scale3D;

            inline TTyped() : Rotation(0.0f, 0.0f, 0.0f, 0.0f), Translation(0.0f, 0.0f, 0.0f), Scale3D(0.0f, 1.0f, 1.0f) {}
            inline TTyped(QuatType Rotation, VectorType Translation, VectorType Scale3D) : Rotation(Rotation), Translation(Translation), Scale3D(Scale3D) {}

            TTyped& operator=(const TTyped& Other)
            {
                Rotation = Other.Rotation;
                Translation = Other.Translation;
                Scale3D = Other.Scale3D;

                return *this;
            }

            TTyped& operator=(const FTransform& Other)
            {
                // The 'Data' variable is always the highest size possible out of all implementations across all engine versions.
                // If we cast to a smaller implementation then it should be safe because we never access anything out of bounds.
                if constexpr (std::is_same_v<QuatType, FQuat::AsPre500> && std::is_same_v<VectorType, FVector::AsPre500>)
                {
                    Rotation = *std::bit_cast<FQuat::AsPre500*>(&Other.Data);
                    Translation = *std::bit_cast<FVector::AsPre500*>(&Other.Data[offsetof(FTransform_AsPre500, Translation)]);
                    Scale3D = *std::bit_cast<FVector::AsPre500*>(&Other.Data[offsetof(FTransform_AsPre500, Scale3D)]);
                }
                else
                {
                    Rotation = *std::bit_cast<FQuat::As500Plus*>(&Other.Data);
                    Translation = *std::bit_cast<FVector::As500Plus*>(&Other.Data[offsetof(FTransform_As500Plus, Translation)]);
                    Scale3D = *std::bit_cast<FVector::As500Plus*>(&Other.Data[offsetof(FTransform_As500Plus, Scale3D)]);
                }

                return *this;
            }
        };

        using FTransform_As500Plus = FTransform::TTyped<FQuat::As500Plus, FVector::As500Plus>;
        using FTransform_AsPre500 = FTransform::TTyped<FQuat::AsPre500, FVector::AsPre500>;

        uint8_t Data[sizeof(FTransform_As500Plus)];

        FTransform()
            : FTransform(FQuat(0, 0, 0, 1), FVector(0, 0, 0), FVector(1, 1, 1))
        {
        }
        FTransform(FQuat Rotation, FVector Translation, FVector Scale3D)
        {
            if (Version::IsBelow(5, 0))
            {
                auto* TypedData = std::bit_cast<FTransform_AsPre500*>(&Data);
                TypedData->Rotation = *std::bit_cast<FQuat::AsPre500*>(&Rotation);
                TypedData->Translation = *std::bit_cast<FVector::AsPre500*>(&Translation);
                TypedData->Scale3D = *std::bit_cast<FVector::AsPre500*>(&Scale3D);
            }
            else
            {
                auto* TypedData = std::bit_cast<FTransform_As500Plus*>(&Data);
                TypedData->Rotation = *std::bit_cast<FQuat::As500Plus*>(&Rotation);
                TypedData->Translation = *std::bit_cast<FVector::As500Plus*>(&Translation);
                TypedData->Scale3D = *std::bit_cast<FVector::As500Plus*>(&Scale3D);
            }
        }

        [[deprecated("Use 'GetRotation' instead")]]
        FQuat& Rotation()
        {
            return GetRotation();
        }

        [[deprecated("Use 'GetTranslation' instead")]]
        FVector& Translation()
        {
            return GetTranslation();
        }

        [[deprecated("Use 'GetScale3D' instead")]]
        FVector& Scale3D()
        {
            return GetScale3D();
        }

        FQuat& GetRotation()
        {
            return *std::bit_cast<FQuat*>(&Data);
        }
        FVector& GetTranslation()
        {
            if (Version::IsBelow(5, 0))
            {
                return *std::bit_cast<FVector*>(&Data[offsetof(FTransform_AsPre500, Translation)]);
            }
            else
            {
                return *std::bit_cast<FVector*>(&Data[offsetof(FTransform_As500Plus , Translation)]);
            }
        }
        FVector& GetScale3D()
        {
            if (Version::IsBelow(5, 0))
            {
                return *std::bit_cast<FVector*>(&Data[offsetof(FTransform_AsPre500, Scale3D)]);
            }
            else
            {
                return *std::bit_cast<FVector*>(&Data[offsetof(FTransform_As500Plus, Scale3D)]);
            }
        }
    };

    using FTransform_As500Plus = FTransform::FTransform_As500Plus;
    using FTransform_AsPre500 = FTransform::FTransform_AsPre500;
}

