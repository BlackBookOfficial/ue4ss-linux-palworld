#pragma once

namespace RC::Unreal
{
    // Temporary empty implementation for FHitResult.
    // The purpose is to let users default construct FHitResult and pass it to any functions that require it.
    struct FHitResult
    {
        FHitResult() = default;
    };
}
