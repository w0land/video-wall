#ifndef SDLTEXTURE_H_YFTIZBST
#define SDLTEXTURE_H_YFTIZBST

#include "texture.h"
#include "sdlhelpers.h"

struct SDL_Renderer;
struct SDL_Texture;

namespace mars {
namespace widgets {
struct Widget;
} // namespace widgets
namespace windowing {

struct SDLTexture : public Texture {
    SDLTexture(SDL_Renderer* renderer, std::uint16_t width, std::uint16_t height, PixelFormat format);
    SDLTexture(SDL_Renderer* renderer, SDL_Texture* texture, bool fullscreeen = false);

    TextureSize size() const noexcept override;
    void put(const void* buffer, const TextureSize& size) noexcept override;
    void render(const boost::optional<Rect>& srcRect, const boost::optional<Rect>& dstRect) noexcept override;
    void UpdateYUVTexture(const Rect&, std::uint8_t*, int, std::uint8_t*, int, std::uint8_t*, int) noexcept override;

private:
    SDL_Renderer* const _renderer;
    const sdl_helpers::TexturePtr _texture;
};

} // namespace windowing
} // namespace mars

#endif /* end of include guard: SDLTEXTURE_H_YFTIZBST */
