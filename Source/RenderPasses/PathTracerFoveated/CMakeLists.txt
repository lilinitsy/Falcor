add_plugin(PathTracerFoveated)

target_sources(PathTracerFoveated PRIVATE
    ColorType.slang
    GeneratePaths.cs.slang
    GuideData.slang
    LoadShadingData.slang
    NRDHelpers.slang
    Params.slang
    PathState.slang
    PathTracerFoveated.slang
    PathTracerFoveated.cpp
    PathTracerFoveated.h
    PathTracerFoveatedNRD.slang
    ReflectTypes.cs.slang
    ResolvePass.cs.slang
    StaticParams.slang
    TracePass.rt.slang
)

target_copy_shaders(PathTracerFoveated RenderPasses/PathTracerFoveated)

target_source_group(PathTracerFoveated "RenderPasses")
