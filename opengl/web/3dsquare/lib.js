var lib = (function () {
  return {
    sizeofFloat32: 4,
    sizeOfUshort: 2,
    lenVec3: 3,
    getGLContext: function (viewport) {
      try {
        let gl = viewport.getContext("webgl2");
        return gl;
      } catch (e) {
        alert("You are not webgl2 compatible :(") ;
      }
    },

  }
})()