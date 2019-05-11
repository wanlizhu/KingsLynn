#pragma once

#include <GSZHU/BasicTypes.h>

namespace GSZHU {
    enum EBLEND_FACTOR : INT8 {
        BLEND_FACTOR_UNDEFINED = 0,
        BLEND_FACTOR_ZERO,
        BLEND_FACTOR_ONE,
        BLEND_FACTOR_SRC_COLOR,
        BLEND_FACTOR_INV_SRC_COLOR,
        BLEND_FACTOR_SRC_ALPHA,
        BLEND_FACTOR_INV_SRC_ALPHA,
        BLEND_FACTOR_DEST_ALPHA,
        BLEND_FACTOR_INV_DEST_ALPHA,
        BLEND_FACTOR_DEST_COLOR,
        BLEND_FACTOR_INV_DEST_COLOR,
        BLEND_FACTOR_SRC_ALPHA_SAT,
        BLEND_FACTOR_BLEND_FACTOR,
        BLEND_FACTOR_INV_BLEND_FACTOR,
        BLEND_FACTOR_SRC1_COLOR,
        BLEND_FACTOR_INV_SRC1_COLOR,
        BLEND_FACTOR_SRC1_ALPHA,
        BLEND_FACTOR_INV_SRC1_ALPHA,
        BLEND_FACTOR_NUM_FACTORS
    };
}