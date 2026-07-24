#pragma once

#include <Unreal/UObject.hpp>
#include <Unreal/UnrealVersion.hpp>

namespace RC::Unreal
{
    struct RC_UE_API FQuat
    {
        template<typename InStorageType>
        struct TTyped
        {
            using StorageType = InStorageType;
            StorageType X;
            StorageType Y;
            StorageType Z;
            StorageType W;

            TTyped(StorageType X_, StorageType Y_, StorageType Z_, StorageType W_) : X(X_), Y(Y_), Z(Z_), W(W_) {}

            TTyped& operator=(const TTyped& Other)
            {
                X = Other.X;
                Y = Other.Y;
                Z = Other.Z;
                W = Other.W;

                return *this;
            }
        };

        using As500Plus = TTyped<double>;
        using AsPre500 = TTyped<float>;

        // This might cause things to be broken in <5.0.
        // If we get an FVector from the engine, then it should be fine.
        // If we get an FVector in a container (like TArray) then there might be a problem.
        // The problem is that we can't rely on 'sizeof' anymore for element calculations, but we might be doing that somewhere.
        // If we ever construct on of these objects then there might be problems there too because the size is 0x18 in 5.0+ and 0xC in <5.0.
        uint8_t Data[sizeof(double) * 4]{};

        void SetX(double NewX);
        void SetY(double NewY);
        void SetZ(double NewZ);
        void SetW(double NewZ);

        [[deprecated("Use 'GetX' instead")]]
        double X();
        [[deprecated("Use 'GetY' instead")]]
        double Y();
        [[deprecated("Use 'GetZ' instead")]]
        double Z();
        [[deprecated("Use 'GetW' instead")]]
        double W();

        [[deprecated("Use 'GetX' instead")]]
        double X() const;
        [[deprecated("Use 'GetY' instead")]]
        double Y() const;
        [[deprecated("Use 'GetZ' instead")]]
        double Z() const;
        [[deprecated("Use 'GetW' instead")]]
        double W() const;

        double GetX();
        double GetY();
        double GetZ();
        double GetW();

        double GetX() const;
        double GetY() const;
        double GetZ() const;
        double GetW() const;

        inline FQuat() = default;
        FQuat(double X, double Y, double Z, double W);
        FQuat(const struct FRotator& R);

        static inline int32 StaticSize()
        {
            if (Version::IsBelow(5, 0))
            {
                return sizeof(AsPre500);
            }
            else
            {
                return sizeof(As500Plus);
            }
        }
    };
}

