from falcor import *

def render_graph_WireframePass():
	g = RenderGraph("WireframePass")
	wireframePass = createPass("WireframePass")
	g.addPass(wireframePass, "WireframePass")
	g.markOutput("WireframePass.output")

	return g

wireframePass = render_graph_WireframePass()
try: m.addGraph(wireframePass)
except NameError: None