from falcor import *

def render_graph_MinimalPathTracerFoveated():
	g = RenderGraph("MinimalPathTracerFoveated")

	AccumulatePass = createPass("AccumulatePass", {'enabled': True, 'precisionMode': 'Single'})
	g.addPass(AccumulatePass, "AccumulatePass")
	ToneMapper = createPass("ToneMapper", {'autoExposure': False, 'exposureCompensation': 0.0})
	g.addPass(ToneMapper, "ToneMapper")
	MinimalPathTracerFoveated = createPass("MinimalPathTracerFoveated", {'maxBounces': 3})
	g.addPass(MinimalPathTracerFoveated, "MinimalPathTracerFoveated")
	VBufferRT = createPass("VBufferRT", {'samplePattern': 'Stratified', 'sampleCount': 16})
	g.addPass(VBufferRT, "VBufferRT")
	g.addEdge("AccumulatePass.output", "ToneMapper.src")
	g.addEdge("VBufferRT.vbuffer", "MinimalPathTracerFoveated.vbuffer")
	g.addEdge("VBufferRT.viewW", "MinimalPathTracerFoveated.viewW")
	g.addEdge("MinimalPathTracerFoveated.color", "AccumulatePass.input")
	g.markOutput("ToneMapper.dst")
	return g

MinimalPathTracerFoveated = render_graph_MinimalPathTracerFoveated()
try: m.addGraph(MinimalPathTracerFoveated)
except NameError: None
