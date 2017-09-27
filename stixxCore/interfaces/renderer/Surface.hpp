#ifndef SURFACE_HPP
#define SURFACE_HPP

#include <stdint.h>
#include <utility>

namespace sx
{
    class Window;

    class Surface
    {
    public:
        enum ColorFormat
        {
            Undefined,
            B8G8R8A8_UNORM
        };

        enum ColorSpace
        {
            SrgbNonlinear,
            DisplayP3Nonlinear,
            ExtendedSrgbLinear,
            DciP3Linear,
            DciP3Nonlinear,
            Bt709Linear,
            Bt709Nonlinear,
            Bt2020Linear,
            Hdr10St2084,
            Dolbyvision,
            Hdr10Hlg,
            AdobergbLinear,
            AdobergbNonlinear,
            PassThrough,
            ExtendedSrgbNonlinear,
        };

        enum PresentMode
        {
            Immediate,
            Mailbox,
            Fifo,
            FifoRelaxed,
            SharedDemandRefresh,
            SharedContinuousRefresh,
        };

        enum Transform
        {
            Identity,
            Rotate90,
            Rotate180,
            Rotate270,
            HorizontalMirror,
            HorizontalMirrorRotate90,
            HorizontalMirrorRotate180,
            HorizontalMirrorRotate270,
            Inherit
        };

        struct Extent
        {
            uint32_t width;
            uint32_t height;
        };

        typedef std::pair<ColorFormat, ColorSpace> SurfaceFormat;

    public:
        virtual bool CreateSurface(Window& window) = 0;
        virtual uint32_t MaxImageCount() = 0;
        virtual bool isSupported(const PresentMode type) = 0;
        virtual SurfaceFormat Format() = 0;
        virtual Extent CurrentExtent() = 0;
        virtual Transform CurrentTransform() = 0;
    };
}
#endif