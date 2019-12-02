#include "Wanlix/Core3D/Graphics/Image.h"
#include "ImageUtility.h"

namespace Wanlix
{
    Image::Image(
        const Extent&      extent,
        const ColorFormat& format,
        const DataType&    dataType,
        ByteBuffer&&       data,
        const Color4F&     fillColor
    ) noexcept
        : mExtent(extent)
        , mFormat(format)
        , mDataType(dataType)
        , mData(std::move(data))
    {
        if (!mData) {
            mData = std::move(GenerateImageBuffer(extent, format, dataType, fillColor));
        }
    }


}