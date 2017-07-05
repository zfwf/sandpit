// called by body element onload
function main() {
  // Configure the viewport to use WebGL
  let viewport = document.getElementById('viewport');
  let gl = lib.getGLContext(viewport)

  // Vertices to draw, interlaced with color
  let vertices = [-0.5, 0.5, -0.5, // front face
    1.0, 0.0, 0.0, // red
    0.5, 0.5, -0.5,
    0.0, 1.0, 0.0, // green
    0.5, -0.5, -0.5,
    0.0, 0.0, 1.0, // blue
    -0.5, -0.5, -0.5,
    1.0, 1.0, 1.0, // white

    -0.5, 0.5, 0.5, // back face
    1.0, 0.0, 0.0, // red
    0.5, 0.5, 0.5,
    0.0, 1.0, 0.0, // green
    0.5, -0.5, 0.5,
    0.0, 0.0, 1.0, // blue
    -0.5, -0.5, 0.5,
    1.0, 1.0, 1.0, // white
  ];

  // Indices of the vertices to draw
  // the vertex attribute pointer will instruct graphics hardware to pick out the vertices from the color in the vertices array above. The indices below can ignore that color is also part of the same array being indexed. 
  let indices = [ // 6 faces
    0, 1, 2, 2, 3, 0,
    4, 5, 6, 6, 7, 4,
    4, 5, 1, 1, 0, 4,
    1, 5, 6, 6, 2, 1,
    7, 6, 2, 2, 3, 7,
    0, 4, 7, 7, 3, 0,
  ]

  let vao = gl.createVertexArray();
  gl.bindVertexArray(vao);

  let buffer = gl.createBuffer();
  gl.bindBuffer(gl.ARRAY_BUFFER, buffer);
  gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(vertices), gl.STATIC_DRAW);

  let emtBuf = gl.createBuffer()
  gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, emtBuf)
  gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, new Uint16Array(indices), gl.STATIC_DRAW)

  let vertCode = `#version 300 es
    uniform mat4 mvp; // model-view-projection
    in vec3 coordinates;
    in vec3 color;
    out vec3 vColor;
    void main() {
      gl_Position = mvp * vec4(coordinates, 1.0);
      vColor = color;
    }`

  let vertShader = lib.getVShader(vertCode)

  // Create a simple fragment shader
  //
  let fragCode = `#version 300 es
      precision mediump float; // required
      in vec3 vColor;
      out vec4 color;
      void main(void) {
         color = vec4(vColor, 1.0); 
      }`

  let fragShader = lib.getFShader(fragCode)

  // Put the vertex shader and fragment shader together into
  // a complete program
  //
  let shaderProgram = gl.createProgram();
  gl.attachShader(shaderProgram, vertShader);
  gl.attachShader(shaderProgram, fragShader);
  gl.linkProgram(shaderProgram);
  if (!gl.getProgramParameter(shaderProgram, gl.LINK_STATUS))
    throw new Error(gl.getProgramInfoLog(shaderProgram));

  // Everything we need has now been copied to the graphics
  // hardware, so we can start drawing

  // Clear the drawing surface
  //
  gl.clearColor(0.0, 0.0, 0.0, 1.0);
  gl.clear(gl.COLOR_BUFFER_BIT);

  // Tell WebGL which shader program to use
  //
  gl.useProgram(shaderProgram);

  // Tell WebGL that the data from the array of triangle
  // coordinates that we've already copied to the graphics
  // hardware should be fed to the vertex shader as the
  // parameter "coordinates"
  let coordinateAddr = gl.getAttribLocation(shaderProgram, "coordinates");
  gl.enableVertexAttribArray(coordinateAddr);

  let colorAddr = gl.getAttribLocation(shaderProgram, "color");
  gl.enableVertexAttribArray(colorAddr);

  //Describe layout of the array buffer
  //index, size (vec3 = 3), type, normalized, stride (length to next item from start of current element, interlace with vec3 = (3+3)*4, each item is a float32, hence 4 bytes), offset (from 0, the first element of array buffer)
  gl.vertexAttribPointer(coordinateAddr, 3, gl.FLOAT, false,
    (lib.lenVec3 + lib.lenVec3) * lib.sizeofFloat32, 0);
  // color is similar to above but start after first vec3
  gl.vertexAttribPointer(colorAddr, 3, gl.FLOAT, false,
    (lib.lenVec3 + lib.lenVec3) * lib.sizeofFloat32,
    lib.lenVec3 * lib.sizeofFloat32);


  // matrices
  let m4 = {
    multiply: function (a, b) {
      var a00 = a[0 * 4 + 0];
      var a01 = a[0 * 4 + 1];
      var a02 = a[0 * 4 + 2];
      var a03 = a[0 * 4 + 3];
      var a10 = a[1 * 4 + 0];
      var a11 = a[1 * 4 + 1];
      var a12 = a[1 * 4 + 2];
      var a13 = a[1 * 4 + 3];
      var a20 = a[2 * 4 + 0];
      var a21 = a[2 * 4 + 1];
      var a22 = a[2 * 4 + 2];
      var a23 = a[2 * 4 + 3];
      var a30 = a[3 * 4 + 0];
      var a31 = a[3 * 4 + 1];
      var a32 = a[3 * 4 + 2];
      var a33 = a[3 * 4 + 3];
      var b00 = b[0 * 4 + 0];
      var b01 = b[0 * 4 + 1];
      var b02 = b[0 * 4 + 2];
      var b03 = b[0 * 4 + 3];
      var b10 = b[1 * 4 + 0];
      var b11 = b[1 * 4 + 1];
      var b12 = b[1 * 4 + 2];
      var b13 = b[1 * 4 + 3];
      var b20 = b[2 * 4 + 0];
      var b21 = b[2 * 4 + 1];
      var b22 = b[2 * 4 + 2];
      var b23 = b[2 * 4 + 3];
      var b30 = b[3 * 4 + 0];
      var b31 = b[3 * 4 + 1];
      var b32 = b[3 * 4 + 2];
      var b33 = b[3 * 4 + 3];
      return [
        b00 * a00 + b01 * a10 + b02 * a20 + b03 * a30,
        b00 * a01 + b01 * a11 + b02 * a21 + b03 * a31,
        b00 * a02 + b01 * a12 + b02 * a22 + b03 * a32,
        b00 * a03 + b01 * a13 + b02 * a23 + b03 * a33,
        b10 * a00 + b11 * a10 + b12 * a20 + b13 * a30,
        b10 * a01 + b11 * a11 + b12 * a21 + b13 * a31,
        b10 * a02 + b11 * a12 + b12 * a22 + b13 * a32,
        b10 * a03 + b11 * a13 + b12 * a23 + b13 * a33,
        b20 * a00 + b21 * a10 + b22 * a20 + b23 * a30,
        b20 * a01 + b21 * a11 + b22 * a21 + b23 * a31,
        b20 * a02 + b21 * a12 + b22 * a22 + b23 * a32,
        b20 * a03 + b21 * a13 + b22 * a23 + b23 * a33,
        b30 * a00 + b31 * a10 + b32 * a20 + b33 * a30,
        b30 * a01 + b31 * a11 + b32 * a21 + b33 * a31,
        b30 * a02 + b31 * a12 + b32 * a22 + b33 * a32,
        b30 * a03 + b31 * a13 + b32 * a23 + b33 * a33,
      ];
    },
    translate: function (x, y, z) {
      return [
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        x, y, z, 1,
      ]
    },
    xRotation: function (angleInRad) {
      let c = Math.cos(angleInRad);
      let s = Math.sin(angleInRad);
      return [
        1, 0, 0, 0,
        0, c, s, 0,
        0, -s, c, 0,
        0, 0, 0, 1,
      ]
    },
    yRotation: function (angleInRad) {
      let c = Math.cos(angleInRad);
      let s = Math.sin(angleInRad);
      return [
        c, 0, -s, 0,
        0, 1, 0, 0,
        s, 0, c, 0,
        0, 0, 0, 1,
      ]
    },
    zRotation: function (angleInRad) {
      let c = Math.cos(angleInRad);
      let s = Math.sin(angleInRad);
      return [
        c, s, 0, 0, -s, c, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1,
      ]
    },
    xRotate: function (m, angleInRad) {
      return m4.multiply(m,m4.xRotation(angleInRad))
    },
    yRotate: function (m, angleInRad) {
      return m4.multiply(m,m4.yRotation(angleInRad))
    },
    zRotate: function (m, angleInRad) {
      return m4.multiply(m,m4.zRotation(angleInRad))
    },
  }



  let matrixAddr = gl.getUniformLocation(shaderProgram, "mvp");
  let rotateby = 0;

  let render = function () {
    lib.resizeMaintainAspect(viewport)
    gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);

    // rotate x by 1 deg per frame, takes 3 second to complete a full 360 deg rotation
    let mvp = m4.xRotation(Math.PI * (rotateby / 180))
    gl.uniformMatrix4fv(matrixAddr, false, mvp);

    gl.bindVertexArray(vao);
    // Now we can tell WebGL to draw the 3 points that make 
    // up the triangle and another 3 to create the square
    gl.drawElements(gl.TRIANGLES, indices.length, gl.UNSIGNED_SHORT, 0);

    gl.flush();
    window.requestAnimationFrame(render);
    rotateby++
    if (rotateby == 360) rotateby = 0
  };

  render();
}