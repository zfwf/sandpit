let lib = (function () {

  let gl // private gl, not prefixed

  function _getGLContext(viewport) {
    try {
      gl = viewport.getContext("webgl2");
      return gl;
    } catch (e) {
      alert("You are not webgl2 compatible :(") ;
    }
  }

  function _getVShader(code) {
    let s = _createAndCompileShader(gl.VERTEX_SHADER, code)
    return s
  }

  function _getFShader(code) {
    let s = _createAndCompileShader(gl.FRAGMENT_SHADER, code)
    return s
  }

  function _createAndCompileShader(shaderType, code) {
    let shader = gl.createShader(shaderType);
    gl.shaderSource(shader, code);
    gl.compileShader(shader);
    if (!gl.getShaderParameter(shader, gl.COMPILE_STATUS))
      throw new Error(gl.getShaderInfoLog(shader));

    return shader
  }

  function _resize(canvas) {
    // Lookup the size the browser is displaying the canvas.
    let displayWidth = canvas.clientWidth;
    let displayHeight = canvas.clientHeight;

    _resizeInternal(canvas, displayWidth, displayHeight)
  }


  function _resizeMaintainAspect(canvas) {
    // Lookup the width the browser is displaying the canvas.
    let displayWidth = canvas.clientWidth;

    // set both width and height the same
    _resizeInternal(canvas, displayWidth, displayWidth)
  }

  function _resizeInternal(canvas, width, height){
    // Check if the canvas is not the same size.
    if (canvas.width !== width ||
      canvas.height !== height) {

      // Make the canvas the same size
      canvas.width = width;
      canvas.height = height;
    }

    // Tell WebGL how to convert from clip space to pixels
    gl.viewport(0, 0, width, height);
  }


  // export
  return {
    sizeofFloat32: 4,
    sizeOfUshort: 2,
    lenVec3: 3,
    getGLContext: _getGLContext,
    getVShader: _getVShader,
    getFShader: _getFShader,
    resize: _resize,
    resizeMaintainAspect: _resizeMaintainAspect,
  }
})()