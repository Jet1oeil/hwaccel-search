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

#include <cassert>
#include <iostream>

#include "local/D3D11Decoder.h"
#include "local/FileParser.h"
#include "local/Window.h"

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cerr << "Missing parameter" << std::endl;
    std::cerr << "Usage: " << argv[0] << " BITSTREAM_FILE" << std::endl;

    return 1;
  }

  // Remove previous dump file
  bool res = std::filesystem::remove("dump.yuv");
  assert(res);

  dp::FileParser fileParser(argv[1]);
  fileParser.extractPictureSizes();
  auto rawPictureSize = fileParser.getRawPictureSize();

  dp::D3D11Decoder decoder(rawPictureSize);
  dp::Window window;

  MSG msg;
  for (;;) {
    PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
    if (!TranslateAccelerator(msg.hwnd, nullptr, &msg)) {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }

    if (msg.message == WM_QUIT)
      break;

    // Break if user presses escape key
    if (GetAsyncKeyState(VK_ESCAPE)) break;

    if (!fileParser.parseNextNAL()) {
      continue;
    }

    const auto& stream = fileParser.getStream();
    std::cout << "nal_unit_type: " << stream.nal->nal_unit_type << std::endl;

    decoder.decodeSlice(fileParser);
  }

  return 0;
}