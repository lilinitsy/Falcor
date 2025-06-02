add_plugin(MinimalPathTracerFoveated)

target_sources(MinimalPathTracerFoveated PRIVATE
    MinimalPathTracerFoveated.cpp
    MinimalPathTracerFoveated.h
)

target_copy_shaders(MinimalPathTracerFoveated RenderPasses/MinimalPathTracerFoveated)

target_source_group(MinimalPathTracerFoveated "RenderPasses")
