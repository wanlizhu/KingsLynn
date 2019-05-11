#pragma once

#include <GSZHU/BasicTypes.h>

namespace GSZHU {
    enum ECOMPONENT_TYPE : UINT8 {
        COMPONENT_TYPE_UNDEFINED,
        COMPONENT_TYPE_FLOAT,
        COMPONENT_TYPE_SNORM,
        COMPONENT_TYPE_UNORM,
        COMPONENT_TYPE_UNORM_SRGB,
        COMPONENT_TYPE_SINT,
        COMPONENT_TYPE_UINT,
        COMPONENT_TYPE_DEPTH,
        COMPONENT_TYPE_DEPTH_STENCIL,
        COMPONENT_TYPE_COMPOUND,
        COMPONENT_TYPE_COMPRESSED,
    };
}