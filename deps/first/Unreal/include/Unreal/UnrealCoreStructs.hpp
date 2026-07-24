#pragma once

#include <Unreal/Common.hpp>
#include <Unreal/UnrealVersion.hpp>

namespace RC::Unreal
{
    enum class ESpawnActorCollisionHandlingMethod : uint8
    {
        /** Fall back to default settings. */
        Undefined,
        /** Actor will spawn in desired location, regardless of collisions. */
        AlwaysSpawn,
        /** Actor will try to find a nearby non-colliding location (based on shape components), but will always spawn even if one cannot be found. */
        AdjustIfPossibleButAlwaysSpawn,
        /** Actor will try to find a nearby non-colliding location (based on shape components), but will NOT spawn unless one is found. */
        AdjustIfPossibleButDontSpawnIfColliding,
        /** Actor will fail to spawn. */
        DontSpawnIfColliding,
    };

    /**
     * Implements a globally unique identifier.
     */
    struct RC_UE_API FGuid
    {
    public:
        /** Default constructor. */
        FGuid() : A(0), B(0), C(0), D(0) {}

        /**
         * Creates and initializes a new GUID from the specified components.
         */
        FGuid(uint32_t InA, uint32_t InB, uint32_t InC, uint32_t InD) : A(InA), B(InB), C(InC), D(InD) {}

    public:
        /**
         * Compares two GUIDs for equality.
         * @return true if the GUIDs are equal, false otherwise.
         */
        friend bool operator==(const FGuid& X, const FGuid& Y)
        {
            return ((X.A ^ Y.A) | (X.B ^ Y.B) | (X.C ^ Y.C) | (X.D ^ Y.D)) == 0;
        }

        /**
         * Compares two GUIDs for inequality.
         * @return true if the GUIDs are not equal, false otherwise.
         */
        friend bool operator!=(const FGuid& X, const FGuid& Y)
        {
            return ((X.A ^ Y.A) | (X.B ^ Y.B) | (X.C ^ Y.C) | (X.D ^ Y.D)) != 0;
        }

        /**
         * Compares two GUIDs.
         * @return true if the first GUID is less than the second one.
         */
        friend bool operator<(const FGuid& X, const FGuid& Y)
        {
            return    ((X.A < Y.A) ? true : ((X.A > Y.A) ? false :
                    ((X.B < Y.B) ? true : ((X.B > Y.B) ? false :
                    ((X.C < Y.C) ? true : ((X.C > Y.C) ? false :
                    ((X.D < Y.D) ? true : ((X.D > Y.D) ? false : false))))))));
        }

        /**
         * Provides access to the GUIDs components.
         * @param Index The index of the component to return (0...3).
         * @return The component.
         */
        uint32_t& operator[](int32_t index)
        {
            switch (index)
            {
                case 0: return A;
                case 1: return B;
                case 2: return C;
                case 3: return D;
            }
            return A;
        }

        /**
         * Provides read-only access to the GUIDs components.
         *
         * @param Index The index of the component to return (0...3).
         * @return The component.
         */
        const uint32_t& operator[](int32_t index) const
        {
            switch (index)
            {
                case 0: return A;
                case 1: return B;
                case 2: return C;
                case 3: return D;
            }
            return A;
        }

    public:
        /**
         * Invalidates the GUID.
         */
        void invalidate()
        {
            A = B = C = D = 0;
        }

        /**
         * Checks whether this GUID is valid or not.
         * A GUID that has all its components set to zero is considered invalid.
         */
        bool is_valid() const
        {
            return ((A | B | C | D) != 0);
        }

        uint32_t GetA()
        {
            return A;
        }

        uint32_t GetB()
        {
            return B;
        }

        uint32_t GetC()
        {
            return C;
        }

        uint32_t GetD()
        {
            return D;
        }

    public:
        /** Holds the first component. */
        uint32_t A;
        /** Holds the second component. */
        uint32_t B;
        /** Holds the third component. */
        uint32_t C;
        /** Holds the fourth component. */
        uint32_t D;
    };

    #define CONSTRUCT_FVECTOR(X_, Y_, Z_) \
    if (RC::Unreal::Version::IsBelow(5, 0)) \
    {                                  \
        FVector::AsPre500(.X = X_, .Y = Y_, .Z = _Z);                               \
    }                                  \
    else                               \
    {                                  \
        FVector::As500Plus(.X = X_, .Y = Y_, .Z = _Z);                               \
    }                                  \
                                       \


    struct FVector
    {
        template<typename InStorageType>
        struct TTyped
        {
            using StorageType = InStorageType;
            StorageType X;
            StorageType Y;
            StorageType Z;

            inline TTyped() = default;
            inline TTyped(StorageType X_, StorageType Y_, StorageType Z_) : X(X_), Y(Y_), Z(Z_) {}

            TTyped& operator=(const TTyped& Other)
            {
                X = Other.X;
                Y = Other.Y;
                Z = Other.Z;

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
        uint8_t Data[sizeof(double) * 3]{};

        static void SetX_Internal(FVector& Vector, double NewX)
        {
            if (Version::IsBelow(5, 0))
            {
                auto* TypedData = std::bit_cast<AsPre500*>(&Vector.Data);
                TypedData->X = static_cast<AsPre500::StorageType>(NewX);
            }
            else
            {
                auto* TypedData = std::bit_cast<As500Plus*>(&Vector.Data);
                TypedData->X = static_cast<As500Plus::StorageType>(NewX);
            }
        }

        static void SetY_Internal(FVector& Vector, double NewY)
        {
            if (Version::IsBelow(5, 0))
            {
                auto* TypedData = std::bit_cast<AsPre500*>(&Vector.Data);
                TypedData->Y = static_cast<AsPre500::StorageType>(NewY);
            }
            else
            {
                auto* TypedData = std::bit_cast<As500Plus*>(&Vector.Data);
                TypedData->Y = static_cast<As500Plus::StorageType>(NewY);
            }
        }

        static void SetZ_Internal(FVector& Vector, double NewZ)
        {
            if (Version::IsBelow(5, 0))
            {
                auto* TypedData = std::bit_cast<AsPre500*>(&Vector.Data);
                TypedData->Z = static_cast<AsPre500::StorageType>(NewZ);
            }
            else
            {
                auto* TypedData = std::bit_cast<As500Plus*>(&Vector.Data);
                TypedData->Z = static_cast<As500Plus::StorageType>(NewZ);
            }
        }

        static double GetX_Internal(const FVector& Vector)
        {
            if (Version::IsBelow(5, 0))
            {
                auto* TypedData = std::bit_cast<AsPre500*>(&Vector.Data);
                return TypedData->X;
            }
            else
            {
                auto* TypedData = std::bit_cast<As500Plus*>(&Vector.Data);
                return TypedData->X;
            }
        }

        static double GetY_Internal(const FVector& Vector)
        {
            if (Version::IsBelow(5, 0))
            {
                auto* TypedData = std::bit_cast<AsPre500*>(&Vector.Data);
                return TypedData->Y;
            }
            else
            {
                auto* TypedData = std::bit_cast<As500Plus*>(&Vector.Data);
                return TypedData->Y;
            }
        }

        static double GetZ_Internal(const FVector& Vector)
        {
            if (Version::IsBelow(5, 0))
            {
                auto* TypedData = std::bit_cast<AsPre500*>(&Vector.Data);
                return TypedData->Z;
            }
            else
            {
                auto* TypedData = std::bit_cast<As500Plus*>(&Vector.Data);
                return TypedData->Z;
            }
        }

        void SetX(double NewX) { SetX_Internal(*this, NewX); }
        void SetY(double NewY) { SetY_Internal(*this, NewY); }
        void SetZ(double NewZ) { SetZ_Internal(*this, NewZ); }

        double GetX() { return GetX_Internal(*this); }
        double GetY() { return GetY_Internal(*this); }
        double GetZ() { return GetZ_Internal(*this); }

        double X() { return GetX_Internal(*this); }
        double Y() { return GetY_Internal(*this); }
        double Z() { return GetZ_Internal(*this); }

        double X() const { return GetX_Internal(*this); }
        double Y() const { return GetY_Internal(*this); }
        double Z() const { return GetZ_Internal(*this); }

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

        inline FVector() = default;
        inline FVector(double X_, double Y_, double Z_)
        {
            SetX(X_);
            SetY(Y_);
            SetZ(Z_);
        }
    };

#define CONSTRUCT_FVECTOR2D(X_, Y_) \
    if (RC::Unreal::Version::IsBelow(5, 0)) \
    {                                  \
        FVector2D::AsPre500(.X = X_, .Y = Y_);                               \
    }                                  \
    else                               \
    {                                  \
        FVector2D::As500Plus(.X = X_, .Y = Y_);                               \
    }                                  \
                                       \

    struct FVector2D
    {
        template<typename InStorageType>
        struct TTyped
        {
            using StorageType = InStorageType;
            StorageType X;
            StorageType Y;

            inline TTyped() = default;
            inline TTyped(StorageType X_, StorageType Y_) : X(X_), Y(Y_) {}

            TTyped& operator=(const TTyped& Other)
            {
                X = Other.X;
                Y = Other.Y;

                return *this;
            }
        };

        using As500Plus = TTyped<double>;
        using AsPre500 = TTyped<float>;

        // This might cause things to be broken in <5.0.
        // If we get an FVector2D from the engine, then it should be fine.
        // If we get an FVector2D in a container (like TArray) then there might be a problem.
        // The problem is that we can't rely on 'sizeof' anymore for element calculations, but we might be doing that somewhere.
        // If we ever construct on of these objects then there might be problems there too because the size is 0x18 in 5.0+ and 0xC in <5.0.
        uint8_t Data[sizeof(double) * 3]{};

        static void SetX_Internal(FVector2D& Vector, double NewX)
        {
            if (Version::IsBelow(5, 0))
            {
                auto* TypedData = std::bit_cast<AsPre500*>(&Vector.Data);
                TypedData->X = static_cast<AsPre500::StorageType>(NewX);
            }
            else
            {
                auto* TypedData = std::bit_cast<As500Plus*>(&Vector.Data);
                TypedData->X = static_cast<As500Plus::StorageType>(NewX);
            }
        }

        static void SetY_Internal(FVector2D& Vector, double NewY)
        {
            if (Version::IsBelow(5, 0))
            {
                auto* TypedData = std::bit_cast<AsPre500*>(&Vector.Data);
                TypedData->Y = static_cast<AsPre500::StorageType>(NewY);
            }
            else
            {
                auto* TypedData = std::bit_cast<As500Plus*>(&Vector.Data);
                TypedData->Y = static_cast<As500Plus::StorageType>(NewY);
            }
        }

        static double GetX_Internal(const FVector2D& Vector)
        {
            if (Version::IsBelow(5, 0))
            {
                auto* TypedData = std::bit_cast<AsPre500*>(&Vector.Data);
                return TypedData->X;
            }
            else
            {
                auto* TypedData = std::bit_cast<As500Plus*>(&Vector.Data);
                return TypedData->X;
            }
        }

        static double GetY_Internal(const FVector2D& Vector)
        {
            if (Version::IsBelow(5, 0))
            {
                auto* TypedData = std::bit_cast<AsPre500*>(&Vector.Data);
                return TypedData->Y;
            }
            else
            {
                auto* TypedData = std::bit_cast<As500Plus*>(&Vector.Data);
                return TypedData->Y;
            }
        }

        void SetX(double NewX) { SetX_Internal(*this, NewX); }
        void SetY(double NewY) { SetY_Internal(*this, NewY); }

        double GetX() { return GetX_Internal(*this); }
        double GetY() { return GetY_Internal(*this); }

        double X() { return GetX_Internal(*this); }
        double Y() { return GetY_Internal(*this); }

        double X() const { return GetX_Internal(*this); }
        double Y() const { return GetY_Internal(*this); }

        static inline int32_t StaticSize()
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

        inline FVector2D() = default;
        inline FVector2D(double X_, double Y_)
        {
            SetX(X_);
            SetY(Y_);
        }
    };
}
