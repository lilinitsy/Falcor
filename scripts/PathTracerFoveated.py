from falcor import *

def render_graph_PathTracerFoveated():
    g = RenderGraph("PathTracerFoveated")
    PathTracerFoveated = createPass("PathTracerFoveated", {'samplesPerPixel': 1})
    g.addPass(PathTracerFoveated, "PathTracerFoveated")
    VBufferRT = createPass("VBufferRT", {'samplePattern': 'Stratified', 'sampleCount': 16, 'useAlphaTest': True})
    g.addPass(VBufferRT, "VBufferRT")
    AccumulatePass = createPass("AccumulatePass", {'enabled': True, 'precisionMode': 'Single'})
    g.addPass(AccumulatePass, "AccumulatePass")
    ToneMapper = createPass("ToneMapper", {'autoExposure': False, 'exposureCompensation': 0.0})
    g.addPass(ToneMapper, "ToneMapper")
    g.addEdge("VBufferRT.vbuffer", "PathTracerFoveated.vbuffer")
    g.addEdge("VBufferRT.viewW", "PathTracerFoveated.viewW")
    g.addEdge("VBufferRT.mvec", "PathTracerFoveated.mvec")
    g.addEdge("PathTracerFoveated.color", "AccumulatePass.input")
    g.addEdge("AccumulatePass.output", "ToneMapper.src")
    g.markOutput("ToneMapper.dst")
    return g

PathTracerFoveated = render_graph_PathTracerFoveated()
try: m.addGraph(PathTracerFoveated)
except NameError: None
