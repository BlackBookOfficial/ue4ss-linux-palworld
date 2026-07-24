#include <Unreal/Quat.hpp>
#include <Unreal/Rotator.hpp>
#include <Unreal/UnrealVersion.hpp>

namespace RC::Unreal
{
    static void SetX_Internal(FQuat& Quat, double NewX)
    {
        if (Version::IsBelow(5, 0))
        {
            auto* TypedData = std::bit_cast<FQuat::AsPre500*>(&Quat.Data);
            TypedData->X = static_cast<FQuat::AsPre500::StorageType>(NewX);
        }
        else
        {
            auto* TypedData = std::bit_cast<FQuat::As500Plus*>(&Quat.Data);
            TypedData->X = static_cast<FQuat::As500Plus::StorageType>(NewX);
        }
    }

    static void SetY_Internal(FQuat& Quat, double NewY)
    {
        if (Version::IsBelow(5, 0))
        {
            auto* TypedData = std::bit_cast<FQuat::AsPre500*>(&Quat.Data);
            TypedData->Y = static_cast<FQuat::AsPre500::StorageType>(NewY);
        }
        else
        {
            auto* TypedData = std::bit_cast<FQuat::As500Plus*>(&Quat.Data);
            TypedData->Y = static_cast<FQuat::As500Plus::StorageType>(NewY);
        }
    }

    static void SetZ_Internal(FQuat& Quat, double NewZ)
    {
        if (Version::IsBelow(5, 0))
        {
            auto* TypedData = std::bit_cast<FQuat::AsPre500*>(&Quat.Data);
            TypedData->Z = static_cast<FQuat::AsPre500::StorageType>(NewZ);
        }
        else
        {
            auto* TypedData = std::bit_cast<FQuat::As500Plus*>(&Quat.Data);
            TypedData->Z = static_cast<FQuat::As500Plus::StorageType>(NewZ);
        }
    }

    static void SetW_Internal(FQuat& Quat, double NewW)
    {
        if (Version::IsBelow(5, 0))
        {
            auto* TypedData = std::bit_cast<FQuat::AsPre500*>(&Quat.Data);
            TypedData->W = static_cast<FQuat::AsPre500::StorageType>(NewW);
        }
        else
        {
            auto* TypedData = std::bit_cast<FQuat::As500Plus*>(&Quat.Data);
            TypedData->W = static_cast<FQuat::As500Plus::StorageType>(NewW);
        }
    }

    double GetX_Internal(const FQuat& Quat)
    {
        if (Version::IsBelow(5, 0))
        {
            auto* TypedData = std::bit_cast<FQuat::AsPre500*>(&Quat.Data);
            return TypedData->X;
        }
        else
        {
            auto* TypedData = std::bit_cast<FQuat::As500Plus*>(&Quat.Data);
            return TypedData->X;
        }
    }

    double GetY_Internal(const FQuat& Quat)
    {
        if (Version::IsBelow(5, 0))
        {
            auto* TypedData = std::bit_cast<FQuat::AsPre500*>(&Quat.Data);
            return TypedData->Y;
        }
        else
        {
            auto* TypedData = std::bit_cast<FQuat::As500Plus*>(&Quat.Data);
            return TypedData->Y;
        }
    }

    double GetZ_Internal(const FQuat& Quat)
    {
        if (Version::IsBelow(5, 0))
        {
            auto* TypedData = std::bit_cast<FQuat::AsPre500*>(&Quat.Data);
            return TypedData->Z;
        }
        else
        {
            auto* TypedData = std::bit_cast<FQuat::As500Plus*>(&Quat.Data);
            return TypedData->Z;
        }
    }

    double GetW_Internal(const FQuat& Quat)
    {
        if (Version::IsBelow(5, 0))
        {
            auto* TypedData = std::bit_cast<FQuat::AsPre500*>(&Quat.Data);
            return TypedData->W;
        }
        else
        {
            auto* TypedData = std::bit_cast<FQuat::As500Plus*>(&Quat.Data);
            return TypedData->W;
        }
    }

    void FQuat::SetX(double NewX)
    {
        SetX_Internal(*this, NewX);
    }

    void FQuat::SetY(double NewY)
    {
        SetY_Internal(*this, NewY);
    }

    void FQuat::SetZ(double NewZ)
    {
        SetZ_Internal(*this, NewZ);
    }

    void FQuat::SetW(double NewW)
    {
        SetW_Internal(*this, NewW);
    }

    double FQuat::GetX()
    {
        return GetX_Internal(*this);
    }

    double FQuat::GetX() const
    {
        return GetX_Internal(*this);
    }

    double FQuat::GetY()
    {
        return GetY_Internal(*this);
    }

    double FQuat::GetY() const
    {
        return GetY_Internal(*this);
    }

    double FQuat::GetZ()
    {
        return GetZ_Internal(*this);
    }

    double FQuat::GetZ() const
    {
        return GetZ_Internal(*this);
    }

    double FQuat::GetW()
    {
        return GetW_Internal(*this);
    }

    double FQuat::GetW() const
    {
        return GetW_Internal(*this);
    }

    double FQuat::X()
    {
        return GetX();
    }
    double FQuat::X() const
    {
        return GetX();
    }
    double FQuat::Y()
    {
        return GetY();
    }
    double FQuat::Y() const
    {
        return GetY();
    }
    double FQuat::Z()
    {
        return GetZ();
    }
    double FQuat::Z() const
    {
        return GetZ();
    }
    double FQuat::W()
    {
        return GetW();
    }
    double FQuat::W() const
    {
        return GetW();
    }

    FQuat::FQuat(double X_, double Y_, double Z_, double W_)
    {
        SetX(X_);
        SetY(Y_);
        SetZ(Z_);
        SetW(W_);
    }

    FQuat::FQuat(const FRotator& R)
    {
        FQuat Quat = R.Quaternion();

        SetX(Quat.GetX());
        SetY(Quat.GetY());
        SetZ(Quat.GetZ());
        SetW(Quat.GetW());
    }
}
