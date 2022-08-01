#include "OpenGL.h"

/// <summary>
/// Render primitives from array data
/// </summary>
/// <param name="mode">Specifies what kind of primitives to render. Symbolic constants GL_POINTS, GL_LINE_STRIP, 
/// GL_LINE_LOOP, GL_LINES, GL_LINE_STRIP_ADJACENCY, GL_LINES_ADJACENCY, GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN, 
/// GL_TRIANGLES, GL_TRIANGLE_STRIP_ADJACENCY, GL_TRIANGLES_ADJACENCY and GL_PATCHES are accepted.</param>
/// <param name="vertexArray">VAO - Vertex Array Object</param>
/// <param name="elementBuffer">EBO - Element Buffer Object</param>
void OpenGL::drawElements(unsigned int mode, const VertexArrayObject& vertexArray, const ElementBufferObject& elementBuffer)
{
	vertexArray.bind();
	elementBuffer.bind();

	glDrawElements(mode, elementBuffer.getCount(), GL_UNSIGNED_INT, 0);
}

/// <summary>
/// Clear buffers to preset values
/// </summary>
/// <param name="clear">Bitwise OR of masks that indicate the buffers to be cleared. The three masks are 
/// GL_COLOR_BUFFER_BIT, GL_DEPTH_BUFFER_BIT, and GL_STENCIL_BUFFER_BIT</param>
void OpenGL::clear(unsigned int mask)
{
	glClear(mask);
}

/// <summary>
/// Controls the interpretation of polygons for rasterization
/// </summary>
/// <param name="mode">GL_POINT, GL_LINE or GL_FILL</param>
void OpenGL::polygonMode(unsigned int mode)
{
	glPolygonMode(GL_FRONT_AND_BACK, mode);
}

/// <summary>
/// Switches polygon mode back and forth for GL_FILL and GL_LINE
/// </summary>
void OpenGL::switchPolygonMode()
{
	int mode;
	glGetIntegerv(GL_POLYGON_MODE, &mode);
	polygonMode(mode == GL_FILL ? GL_LINE : GL_FILL);
}

/// <summary>
/// Enable or disable server-side GL capabilities
/// </summary>
/// <param name="cap">
/// GL_BLEND
/// If enabled, blend the computed fragment color values with the values in the color buffers.See glBlendFunc.
/// 
/// GL_CLIP_DISTANCE
/// If enabled, clip geometry against user - defined half space i.
/// 
/// GL_COLOR_LOGIC_OP
/// If enabled, apply the currently selected logical operation to the computed fragment colorand color buffer values.See glLogicOp.
/// 
/// GL_CULL_FACE
/// If enabled, cull polygons based on their winding in window coordinates.See glCullFace.
/// 
/// GL_DEBUG_OUTPUT
/// If enabled, debug messages are produced by a debug context.When disabled, the debug message log is silenced.Note that in a non - debug context, very few, if any messages might be produced, even when GL_DEBUG_OUTPUT is enabled.
/// 
/// GL_DEBUG_OUTPUT_SYNCHRONOUS
/// If enabled, debug messages are produced synchronously by a debug context.If disabled, debug messages may be produced asynchronously.In particular, they may be delayed relative to the execution of GL commands, and the debug callback function may be called from a thread other than that in which the commands are executed.See glDebugMessageCallback.
/// 
/// GL_DEPTH_CLAMP
/// If enabled, the −wc≤zc≤wc plane equation is ignored by view volume clipping(effectively, there is no near or far plane clipping).See glDepthRange.
/// 
/// GL_DEPTH_TEST
/// If enabled, do depth comparisonsand update the depth buffer.Note that even if the depth buffer existsand the depth mask is non - zero, the depth buffer is not updated if the depth test is disabled.See glDepthFuncand glDepthRange.
/// 
/// GL_DITHER
/// If enabled, dither color components or indices before they are written to the color buffer.
/// 
/// GL_FRAMEBUFFER_SRGB
/// If enabled and the value of GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING for the framebuffer attachment corresponding to the destination buffer is GL_SRGB, the R, G, and B destination color values(after conversion from fixed - point to floating - point) are considered to be encoded for the sRGB color spaceand hence are linearized prior to their use in blending.
/// 
/// GL_LINE_SMOOTH
/// If enabled, draw lines with correct filtering.Otherwise, draw aliased lines.See glLineWidth.
/// 
/// GL_MULTISAMPLE
/// If enabled, use multiple fragment samples in computing the final color of a pixel.See glSampleCoverage.
/// 
/// GL_POLYGON_OFFSET_FILL
/// If enabled, and if the polygon is rendered in GL_FILL mode, an offset is added to depth values of a polygon's fragments before the depth comparison is performed. See glPolygonOffset.
/// 
/// GL_POLYGON_OFFSET_LINE
/// If enabled, and if the polygon is rendered in GL_LINE mode, an offset is added to depth values of a polygon's fragments before the depth comparison is performed. See glPolygonOffset.
/// 
/// GL_POLYGON_OFFSET_POINT
/// If enabled, an offset is added to depth values of a polygon's fragments before the depth comparison is performed, if the polygon is rendered in GL_POINT mode. See glPolygonOffset.
/// 
/// GL_POLYGON_SMOOTH
/// If enabled, draw polygons with proper filtering.Otherwise, draw aliased polygons.For correct antialiased polygons, an alpha buffer is neededand the polygons must be sorted front to back.
/// 
/// GL_PRIMITIVE_RESTART
/// Enables primitive restarting.If enabled, any one of the draw commands which transfers a set of generic attribute array elements to the GL will restart the primitive when the index of the vertex is equal to the primitive restart index.See glPrimitiveRestartIndex.
/// 
/// GL_PRIMITIVE_RESTART_FIXED_INDEX
/// Enables primitive restarting with a fixed index.If enabled, any one of the draw commands which transfers a set of generic attribute array elements to the GL will restart the primitive when the index of the vertex is equal to the fixed primitive index for the specified index type.The fixed index is equal to 2n−1 where n is equal to 8 for GL_UNSIGNED_BYTE, 16 for GL_UNSIGNED_SHORT and 32 for GL_UNSIGNED_INT.
/// 
/// GL_RASTERIZER_DISCARD
/// If enabled, primitives are discarded after the optional transform feedback stage, but before rasterization.Furthermore, when enabled, glClear, glClearBufferData, glClearBufferSubData, glClearTexImage, and glClearTexSubImage are ignored.
/// 
/// GL_SAMPLE_ALPHA_TO_COVERAGE
/// If enabled, compute a temporary coverage value where each bit is determined by the alpha value at the corresponding sample location.The temporary coverage value is then ANDed with the fragment coverage value.
/// 
/// GL_SAMPLE_ALPHA_TO_ONE
/// If enabled, each sample alpha value is replaced by the maximum representable alpha value.
/// 
/// GL_SAMPLE_COVERAGE
/// If enabled, the fragment's coverage is ANDed with the temporary coverage value. If GL_SAMPLE_COVERAGE_INVERT is set to GL_TRUE, invert the coverage value. See glSampleCoverage.
/// 
/// GL_SAMPLE_SHADING
/// If enabled, the active fragment shader is run once for each covered sample, or at fraction of this rate as determined by the current value of GL_MIN_SAMPLE_SHADING_VALUE.See glMinSampleShading.
/// 
/// GL_SAMPLE_MASK
/// If enabled, the sample coverage mask generated for a fragment during rasterization will be ANDed with the value of GL_SAMPLE_MASK_VALUE before shading occurs.See glSampleMaski.
/// 
/// GL_SCISSOR_TEST
/// If enabled, discard fragments that are outside the scissor rectangle.See glScissor.
/// 
/// GL_STENCIL_TEST
/// If enabled, do stencil testingand update the stencil buffer.See glStencilFuncand glStencilOp.
/// 
/// GL_TEXTURE_CUBE_MAP_SEAMLESS
/// If enabled, cubemap textures are sampled such that when linearly sampling from the border between two adjacent faces, texels from both faces are used to generate the final sample value.When disabled, texels from only a single face are used to construct the final sample value.
/// 
/// GL_PROGRAM_POINT_SIZE
/// If enabledand a vertex or geometry shader is active, then the derived point size is taken from the(potentially clipped) shader builtin gl_PointSizeand clamped to the implementation - dependent point size range.</param>
void OpenGL::enable(unsigned int cap)
{
	glEnable(cap);
}

/// <summary>
/// Specify pixel arithmetic
/// </summary>
/// <param name="sfactor">Specifies how the red, green, blue, and alpha source blending factors are computed. The initial value is GL_ONE.</param>
/// <param name="dfactor">Specifies how the red, green, blue, and alpha destination blending factors are computed. 
/// The following symbolic constants are accepted: GL_ZERO, GL_ONE, GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR, GL_DST_COLOR, GL_ONE_MINUS_DST_COLOR, 
/// GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_DST_ALPHA, GL_ONE_MINUS_DST_ALPHA. GL_CONSTANT_COLOR, GL_ONE_MINUS_CONSTANT_COLOR, GL_CONSTANT_ALPHA, 
/// and GL_ONE_MINUS_CONSTANT_ALPHA. The initial value is GL_ZERO.</param>
void OpenGL::blendFunction(unsigned int sfactor, unsigned int dfactor)
{
	glBlendFunc(sfactor, dfactor);
}

/// <summary>
/// Define front- and back-facing polygons
/// </summary>
/// <param name="mode">Specifies the orientation of front-facing polygons. 
/// GL_CW and GL_CCW are accepted. The initial value is GL_CCW.</param>
void OpenGL::frontFace(unsigned int mode)
{
	glFrontFace(mode);
}
