#ifndef VW_SURFACE_YUV_H
#define VW_SURFACE_YUV_H

#include <string>

#include <vdpau/vdpau.h>

#include <VdpWrapper/Device.h>
#include <VdpWrapper/Size.h>

namespace vw {
    class SurfaceYUV {
    public:
        SurfaceYUV(Device& device, SizeU size);
        SurfaceYUV(Device& device, const std::string& filename, SizeU size);
        ~SurfaceYUV();

        SurfaceYUV(const SurfaceYUV&) = delete;
        SurfaceYUV(SurfaceYUV&& other);

        SurfaceYUV& operator=(const SurfaceYUV&) = delete;
        SurfaceYUV& operator=(SurfaceYUV&&) = delete;

        SizeU getSize() const;

    private:
        void allocateVdpSurface(Device& device, const SizeU& size);

    private:
        VdpVideoSurface m_vdpVideoSurface;
        SizeU m_size;

    private:
        friend class Decoder;
        friend class VideoMixer;
    };
}

#endif // VW_SURFACE_YUV_H
