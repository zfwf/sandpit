let lib = (function () {

  let gl
  let _getGLContext = function (viewport) {
    try {
      let gl = viewport.getContext("webgl2");
      return gl;
    } catch (e) {
      alert("You are not webgl2 compatible :(") ;
    }
  }

  let _getVShader = function (code) {
    let s = _createAndCompileShader(gl.VERTEX_SHADER, code)
    return s
  }

  let _getFShader = function (code) {
    let s = _createAndCompileShader(gl.FRAGMENT_SHADER, code)
    return s
  }

  let _createAndCompileShader = function (shaderType, code) {
    let shader = gl.createShader(shaderType);
    gl.shaderSource(shader, code);
    gl.compileShader(shader);
    if (!gl.getShaderParameter(shader, gl.COMPILE_STATUS))
      throw new Error(gl.getShaderInfoLog(shader));
  }

  return {
    sizeofFloat32: 4,
    sizeOfUshort: 2,
    lenVec3: 3,
    getGLContext: _getGLContext,
    getVShader: _getVShader,
    getFShader: _getFShader,
  }
})()