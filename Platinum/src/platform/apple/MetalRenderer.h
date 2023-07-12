//
// Created by Oskar Zdziarski on 7/11/23.
//

#pragma once

#include "Renderer.h"

#import <AppKit/AppKit.h>
#import <Metal/Metal.h>
#import <MetalKit/MetalKit.h>

namespace Platinum {
    class MetalRenderer : public Renderer {
        NSWindow* nswin;
        CAMetalLayer* swapchain;
        id<MTLDevice> device;
        id<MTLCommandQueue> cmd;
        id<MTLRenderPipelineState> pso;
    public:
        explicit MetalRenderer(const std::shared_ptr<Window>& win);
        ~MetalRenderer() override;
        void draw() override;
    };
}
