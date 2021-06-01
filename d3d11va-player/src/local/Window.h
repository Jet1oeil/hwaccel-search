/* Copyright (c) 2021 Jet1oeil
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef LOCAL_WINDOW_H_
#define LOCAL_WINDOW_H_

#include "D3D11Manager.h" // Must be included in first

namespace dp {
  class VideoTexture;

  class Window {
  public:
    Window(D3D11Manager& d3d11Manager);
    ~Window() = default;

    Window(const Window&) = delete;
    Window(Window&&) = delete;

    Window& operator=(const Window&) = delete;
    Window& operator=(Window&&) = delete;

    bool isActive() const;
    void procMessage();
    void clear();
    void render(const VideoTexture& decodedTexture);

  private:
    const LPCWSTR m_szTitle;
    const LPCWSTR m_szWindowClass;
    bool m_isActive;

    D3D11Manager& m_d3d11Manager;

    // Rendering
    ComPtr<IDXGISwapChain1> m_swapChain;
    ComPtr<ID3D11RenderTargetView> m_renderView;

    // Video processing
    ComPtr<ID3D11VideoProcessorEnumerator> m_videoProcessorEnumerator;
    ComPtr<ID3D11VideoProcessor> m_videoProcessor;
    ComPtr<ID3D11Texture2D> m_textureBGRA;
    ComPtr<ID3D11VideoProcessorOutputView> m_outputView;
  };
}

#endif // LOCAL_WINDOW_H_
