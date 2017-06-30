// called by body element onload
function main() {
  // Configure the viewport to use WebGL
  var viewport = document.getElementById('viewport');
  var gl = lib.getGLContext(viewport)

  // Vertices to draw, interlaced with color
  var vertices = [-0.5, 0.5, 0.0,
    1.0, 0.0, 0.0, // red
    0.5, 0.5, 0.0,
    0.0, 1.0, 0.0, // green
    0.5, -0.5, 0.0,
    0.0, 0.0, 1.0, // blue
    -0.5, -0.5, 0.0,
    1.0, 1.0, 1.0, // white
  ];

  // Indices of the vertices to draw
  // the vertex attribute pointer will instruct graphics hardware to pick out the vertices from the color in the vertices array above. The indices below can ignore that color is also part of the same array being indexed. 
  var indices = [
    0, 1, 2,
    2, 3, 0,
  ]

  var vao = gl.createVertexArray();
  gl.bindVertexArray(vao);

  var buffer = gl.createBuffer();
  gl.bindBuffer(gl.ARRAY_BUFFER, buffer);
  gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(vertices), gl.STATIC_DRAW);

  var emtBuf = gl.createBuffer()
  gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, emtBuf)
  gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, new Uint16Array(indices), gl.STATIC_DRAW)

  var vertCode =
    `
      attribute vec3 coordinates;
      attribute vec3 color;
      varying vec3 vColor;
      void main() {
        gl_Position = vec4(coordinates, 1.0);
        vColor = color;
      }`

  var vertShader = gl.createShader(gl.VERTEX_SHADER);
  gl.shaderSource(vertShader, vertCode);
  gl.compileShader(vertShader);
  if (!gl.getShaderParameter(vertShader, gl.COMPILE_STATUS))
    throw new Error(gl.getShaderInfoLog(vertShader));

  // Create a simple fragment shader
  //
  var fragCode = `
      precision mediump float; // required
      varying vec3 vColor;
      void main(void) {
         gl_FragColor = vec4(vColor, 1.0); 
      }`

  var fragShader = gl.createShader(gl.FRAGMENT_SHADER);
  gl.shaderSource(fragShader, fragCode);
  gl.compileShader(fragShader);
  if (!gl.getShaderParameter(fragShader, gl.COMPILE_STATUS))
    throw new Error(gl.getShaderInfoLog(fragShader));

  // Put the vertex shader and fragment shader together into
  // a complete program
  //
  var shaderProgram = gl.createProgram();
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
  var coordinatesVar = gl.getAttribLocation(shaderProgram, "coordinates");
  gl.enableVertexAttribArray(coordinatesVar);

  var colorAddr = gl.getAttribLocation(shaderProgram, "color");
  gl.enableVertexAttribArray(colorAddr);

  //Describe layout of the array buffer
  //index, size (vec3 = 3), type, normalized, stride (length to next item from start of current element, interlace with vec3 = (3+3)*4, each item is a float32, hence 4 bytes), offset (from 0, the first element of array buffer)
  gl.vertexAttribPointer(coordinatesVar, 3, gl.FLOAT, false, 
  (lib.lenVec3 + lib.lenVec3) * lib.sizeofFloat32, 0);
  // color is similar to above but start after first vec3
  gl.vertexAttribPointer(colorAddr, 3, gl.FLOAT, false, 
  (lib.lenVec3 + lib.lenVec3) * lib.sizeofFloat32, 
  lib.lenVec3 * lib.sizeofFloat32);


  var animate = function () {
    gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);
    gl.bindVertexArray(vao);
    // Now we can tell WebGL to draw the 3 points that make 
    // up the triangle and another 3 to create the square
    gl.drawElements(gl.TRIANGLES, 6, gl.UNSIGNED_SHORT, 0);

    gl.flush();
    window.requestAnimationFrame(animate);
  };

  animate();
}