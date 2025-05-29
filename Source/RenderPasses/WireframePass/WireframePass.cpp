/***************************************************************************
 # Copyright (c) 2015-23, NVIDIA CORPORATION. All rights reserved.
 #
 # Redistribution and use in source and binary forms, with or without
 # modification, are permitted provided that the following conditions
 # are met:
 #  * Redistributions of source code must retain the above copyright
 #    notice, this list of conditions and the following disclaimer.
 #  * Redistributions in binary form must reproduce the above copyright
 #    notice, this list of conditions and the following disclaimer in the
 #    documentation and/or other materials provided with the distribution.
 #  * Neither the name of NVIDIA CORPORATION nor the names of its
 #    contributors may be used to endorse or promote products derived
 #    from this software without specific prior written permission.
 #
 # THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS "AS IS" AND ANY
 # EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 # IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 # PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 # CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 # EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 # PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 # PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 # OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 # (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 # OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 **************************************************************************/
#include "WireframePass.h"

extern "C" FALCOR_API_EXPORT void registerPlugin(Falcor::PluginRegistry& registry)
{
    registry.registerClass<RenderPass, WireframePass>();
}

WireframePass::WireframePass(ref<Device> pDevice, const Properties& props) : RenderPass(pDevice), mp_device(pDevice)
{
	mp_program = Program::createGraphics(mp_device, "RenderPasses/WireframePass/WireframePass.slang", "vsMain", "psMain");
    RasterizerState::Desc rasterizer_desc;
    rasterizer_desc.setFillMode(RasterizerState::FillMode::Wireframe);
    rasterizer_desc.setCullMode(RasterizerState::CullMode::None);
    mp_rasterizer_state = RasterizerState::create(rasterizer_desc);

    mp_graphics_state = GraphicsState::create(mp_device);
    mp_graphics_state->setProgram(mp_program);
    mp_graphics_state->setRasterizerState(mp_rasterizer_state);

}

Properties WireframePass::getProperties() const
{
    return {};
}

RenderPassReflection WireframePass::reflect(const CompileData& compileData)
{
    // Define the required resources here
    RenderPassReflection reflector;
    //reflector.addInput("src", "src_tex");
    reflector.addOutput("output", "wireframe_view_texture");
    return reflector;
}

void WireframePass::execute(RenderContext* pRenderContext, const RenderData& renderData)
{
    // Create and bind FBO
    ref<Fbo> p_target_fbo = Fbo::create(mp_device, { renderData.getTexture("output") });
    const float4 clear_colour(0.0f, 0.0f, 0.0f, 1.0f);
    pRenderContext->clearFbo(p_target_fbo.get(), clear_colour, 1.0f, 0.0f, FboAttachmentType::All);
    mp_graphics_state->setFbo(p_target_fbo);

    // Bind shader
    if (mp_scene)
    {
        ShaderVar root_var = mp_program_vars->getRootVar();
        root_var["per_frame_cb"]["g_colour"] = float4(0.0f, 1.0f, 0.0f, 1.0f);

        mp_scene->rasterize(pRenderContext, mp_graphics_state.get(), mp_program_vars.get(), mp_rasterizer_state, mp_rasterizer_state);
    }
}

void WireframePass::setScene(RenderContext* pRenderContext, const ref<Scene>& pScene)
{
    mp_scene = pScene;

    if (mp_scene)
    {
        mp_program->addDefines(mp_scene->getSceneDefines());
    }

    mp_program_vars = ProgramVars::create(mp_device, mp_program.get());
}



void WireframePass::renderUI(Gui::Widgets& widget) {}
