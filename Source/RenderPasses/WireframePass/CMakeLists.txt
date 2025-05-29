add_plugin(WireframePass)

target_sources(WireframePass PRIVATE
    WireframePass.cpp
    WireframePass.h
	WireframePass.slang
)

target_copy_shaders(WireframePass RenderPasses/WireframePass)

target_source_group(WireframePass "RenderPasses")
