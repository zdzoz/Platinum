//
// Created by Oskar Zdziarski on 7/11/23.
//

#include "MetalRenderer.h"

#include <simd/simd.h>

namespace Platinum {
    Renderer* Renderer::create(const std::shared_ptr<Window>& win) {
        return new MetalRenderer(win);
    }

    MetalRenderer::MetalRenderer(const std::shared_ptr<Window>& win) : nswin((NSWindow*)win->getNativeWindow()) {
        _window = win;
        swapchain = (CAMetalLayer*)nswin.contentView.layer;
        device = [swapchain.device retain];
        cmd = [device newCommandQueue];

        NSURL* libURL = [NSURL URLWithString:@SHADER_DIRECTORY"default.metallib"];

        NSError* error = nullptr;
        id<MTLLibrary> lib = [device newLibraryWithURL:libURL error:&error];
        if (!lib) {
            NSLog(@"Library error: %@\n", error.localizedDescription);
            NSLog(@"URL: %@\n", libURL);
        }

        id<MTLFunction> vert = [lib newFunctionWithName:@"basic_vertex"];
        id<MTLFunction> frag = [lib newFunctionWithName:@"basic_fragment"];

        MTLRenderPipelineDescriptor* psd = [[MTLRenderPipelineDescriptor alloc] init];
        psd.label = @"Simple Pipeline";

        psd.vertexFunction = vert;
        psd.fragmentFunction = frag;
        psd.colorAttachments[0].pixelFormat = MTLPixelFormatRGBA8Unorm_sRGB;

        pso = [device newRenderPipelineStateWithDescriptor:psd error:&error];
    }

    MetalRenderer::~MetalRenderer() {
        [cmd release];
        [device release];
        [pso release];
    }

    void MetalRenderer::draw() {
        struct v2f {
            simd_float2 pos;
            simd_float4 color;
        };
        v2f tri[] = {
                {{ 25.f,  25.f}, {1.f, 0.f, 0.f, 1.f} },
                {{ 25.f, 455.f}, {0.f, 1.f, 0.f, 1.f} },
                {{935.f, 455.f}, {0.f, 0.f, 1.f, 1.f} }
        };

        @autoreleasepool {
            id<CAMetalDrawable> drawable = [swapchain nextDrawable];

            MTLRenderPassDescriptor *rpd = [MTLRenderPassDescriptor renderPassDescriptor];
            rpd.colorAttachments[0].texture = drawable.texture;
            rpd.colorAttachments[0].loadAction  = MTLLoadActionClear;
            rpd.colorAttachments[0].storeAction = MTLStoreActionStore;
            rpd.colorAttachments[0].clearColor = MTLClearColorMake(.12, .12, .12, 1.0);;

            id<MTLCommandBuffer> buffer = [cmd commandBuffer];
            id<MTLRenderCommandEncoder> enc = [buffer renderCommandEncoderWithDescriptor:rpd];

//            [enc setViewport:(MTLViewport){0.0, 0.0, nswin.frame.size.width, nswin.frame.size.height, 0.0, 1.0 }];
            [enc setRenderPipelineState:pso];
            [enc setVertexBytes:tri length:sizeof(tri) atIndex:0];
            simd_float2 winSize = {static_cast<float>(_window->width()), static_cast<float>(_window->height())};
            [enc setVertexBytes:&winSize length:sizeof(winSize) atIndex:1];
            [enc drawPrimitives:MTLPrimitiveTypeTriangle vertexStart:0 vertexCount:3];

            [enc endEncoding];
            [buffer presentDrawable:drawable];
            [buffer commit];
        }
    }
}
