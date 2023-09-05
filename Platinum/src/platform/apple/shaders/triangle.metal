
#include <metal_stdlib>
#include <simd/simd.h>

using namespace metal;

struct v2f {
    float4 pos [[position]];
    float4 color;
};

void translate(thread float4x4& mat, float2 tran) {
    mat[0].w += tran.x;
    mat[1].w += tran.y;
}

void scale(thread float4x4& mat, float2 sc) {
    mat[0].x *= sc.x;
    mat[1].y *= sc.y;
}

vertex v2f basic_vertex( uint vertexId [[vertex_id]], device const v2f* vert [[buffer(0)]]) {

    float2 pos = vert[vertexId].pos.xy;

    // model at origin
    float4x4 model(1.0);

    float4x4 view(1.0);
    translate(view, {-1, 1});
    scale(view, {1/480.0, -1/240.0});

    v2f o;
    o.pos = transpose(view) * transpose(model) * float4(pos.xy, 0.0, 1.0);
    o.color = vert[vertexId].color;
    return o;
}

fragment float4 basic_fragment( v2f in [[stage_in]] ) {
    return in.color;
}
