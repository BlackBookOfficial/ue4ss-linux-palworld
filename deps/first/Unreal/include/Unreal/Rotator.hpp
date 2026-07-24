#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

#include <Unreal/UObject.hpp>
#include <Unreal/Quat.hpp>

#pragma warning(disable: 4305)

namespace RC::Unreal
{
    struct RC_UE_API FRotator
    {
        template<typename InStorageType>
        struct TTyped
        {
            using StorageType = InStorageType;
            StorageType Pitch;
            StorageType Yaw;
            StorageType Roll;

            TTyped(StorageType Pitch_, StorageType Yaw_, StorageType Roll_) : Pitch(Pitch_), Yaw(Yaw_), Roll(Roll_) {}

            TTyped& operator=(const TTyped& Other)
            {
                Pitch = Other.Pitch;
                Yaw = Other.Yaw;
                Roll = Other.Roll;

                return *this;
            }
        };

        using As500Plus = TTyped<double>;
        using AsPre500 = TTyped<float>;

    private:
        // This might cause things to be broken in <5.0.
        // If we get an FRotator from the engine, then it should be fine.
        // If we get an FRotator in a container (like TArray) then there might be a problem.
        // The problem is that we can't rely on 'sizeof' anymore for element calculations, but we might be doing that somewhere.
        // If we ever construct on of these objects then there might be problems there too because the size is 0x18 in 5.0+ and 0xC in <5.0.
        uint8_t Data[sizeof(double) * 3]{};

        static void SetPitch_Internal(FRotator& Rotator, double NewPitch)
        {
            if (Version::IsBelow(5, 0))
            {
                auto* TypedData = std::bit_cast<AsPre500*>(&Rotator.Data);
                TypedData->Pitch = static_cast<AsPre500::StorageType>(NewPitch);
            }
            else
            {
                auto* TypedData = std::bit_cast<As500Plus*>(&Rotator.Data);
                TypedData->Pitch = static_cast<As500Plus::StorageType>(NewPitch);
            }
        }

        static void SetYaw_Internal(FRotator& Rotator, double NewYaw)
        {
            if (Version::IsBelow(5, 0))
            {
                auto* TypedData = std::bit_cast<AsPre500*>(&Rotator.Data);
                TypedData->Yaw = static_cast<AsPre500::StorageType>(NewYaw);
            }
            else
            {
                auto* TypedData = std::bit_cast<As500Plus*>(&Rotator.Data);
                TypedData->Yaw = static_cast<As500Plus::StorageType>(NewYaw);
            }
        }

        static void SetRoll_Internal(FRotator& Rotator, double NewRoll)
        {
            if (Version::IsBelow(5, 0))
            {
                auto* TypedData = std::bit_cast<AsPre500*>(&Rotator.Data);
                TypedData->Roll = static_cast<AsPre500::StorageType>(NewRoll);
            }
            else
            {
                auto* TypedData = std::bit_cast<As500Plus*>(&Rotator.Data);
                TypedData->Roll = static_cast<As500Plus::StorageType>(NewRoll);
            }
        }

        static double GetPitch_Internal(const FRotator& Rotator)
        {
            if (Version::IsBelow(5, 0))
            {
                auto* TypedData = std::bit_cast<AsPre500*>(&Rotator.Data);
                return TypedData->Pitch;
            }
            else
            {
                auto* TypedData = std::bit_cast<As500Plus*>(&Rotator.Data);
                return TypedData->Pitch;
            }
        }

        static double GetYaw_Internal(const FRotator& Rotator)
        {
            if (Version::IsBelow(5, 0))
            {
                auto* TypedData = std::bit_cast<AsPre500*>(&Rotator.Data);
                return TypedData->Yaw;
            }
            else
            {
                auto* TypedData = std::bit_cast<As500Plus*>(&Rotator.Data);
                return TypedData->Yaw;
            }
        }

        static double GetRoll_Internal(const FRotator& Rotator)
        {
            if (Version::IsBelow(5, 0))
            {
                auto* TypedData = std::bit_cast<AsPre500*>(&Rotator.Data);
                return TypedData->Roll;
            }
            else
            {
                auto* TypedData = std::bit_cast<As500Plus*>(&Rotator.Data);
                return TypedData->Roll;
            }
        }

    public:

        FRotator() = default;
        inline FRotator(double Pitch, double Yaw, double Roll)
        {
            SetPitch(Pitch);
            SetYaw(Yaw);
            SetRoll(Roll);
        }

        inline FQuat Quaternion() const
        {
            const double DEG_TO_RAD = M_PI/(180.f);
            const double RADS_DIVIDED_BY_2 = DEG_TO_RAD/2.f;
            double SP, SY, SR;
            double CP, CY, CR;

            const double PitchNoWinding = std::fmod(GetPitch(), 360.0f);
            const double YawNoWinding = std::fmod(GetYaw(), 360.0f);
            const double RollNoWinding = std::fmod(GetRoll(), 360.0f);

            SP = std::sin(PitchNoWinding * RADS_DIVIDED_BY_2);
            CP = std::cos(PitchNoWinding * RADS_DIVIDED_BY_2);
            SY = std::sin(YawNoWinding * RADS_DIVIDED_BY_2);
            CY = std::cos(YawNoWinding * RADS_DIVIDED_BY_2);
            SR = std::sin(RollNoWinding * RADS_DIVIDED_BY_2);
            CR = std::cos(RollNoWinding * RADS_DIVIDED_BY_2);

            FQuat RotationQuat;
            RotationQuat.SetX(CR*SP*SY - SR*CP*CY);
            RotationQuat.SetY(CR*SP*CY - SR*CP*SY);
            RotationQuat.SetZ(CR*CP*SY - SR*SP*CY);
            RotationQuat.SetW(CR*CP*CY + SR*SP*SY);

            return RotationQuat;
        }

        inline void SetPitch(double NewPitch) { SetPitch_Internal(*this, NewPitch); }
        inline void SetYaw(double NewYaw) { SetYaw_Internal(*this, NewYaw); }
        inline void SetRoll(double NewRoll) { SetRoll_Internal(*this, NewRoll); }

        inline double GetPitch() { return GetPitch_Internal(*this); }
        inline double GetYaw() { return GetYaw_Internal(*this); }
        inline double GetRoll() { return GetRoll_Internal(*this); }

        inline double GetPitch() const { return GetPitch_Internal(*this); }
        inline double GetYaw() const { return GetYaw_Internal(*this); }
        inline double GetRoll() const { return GetRoll_Internal(*this); }
    };
}

#pragma warning(default: 4305)

