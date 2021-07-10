/// <reference path="webgl.d.ts" />

let obstacle = class {
    constructor(gl, pos) {
        this.rotation = 0.2;
        this.pos = pos;
        this.val=0.375;
        this.val1=0.25;
        this.val2=1.25;
        this.lane=0;
        this.jump=0;
        this.speedy=0;
        this.positions = [
            
            // Front face
            -this.val2, -this.val, this.val1,
            this.val2, -this.val, this.val1,
            this.val, this.val, this.val1,
            -this.val, this.val, this.val1,
            //Back Face
            -this.val2, -this.val, -this.val1,
            this.val2, -this.val, -this.val1,
            this.val, this.val, -this.val1,
            -this.val, this.val, -this.val1,
            //Top Face
            -this.val, this.val, -this.val1,
            this.val, this.val, -this.val1,
            this.val, this.val, this.val1,
            -this.val, this.val, this.val1,
            //Bottom Face
            -this.val2, -this.val, -this.val1,
            this.val2, -this.val, -this.val1,
            this.val2, -this.val, this.val1,
            -this.val2, -this.val, this.val1,
            //Left Face
            -this.val2, -this.val, -this.val1,
            -this.val, this.val, -this.val1,
            -this.val, this.val, this.val1,
            -this.val2, -this.val, this.val1,
            //Right Face
            this.val2, -this.val, -this.val1,
            this.val, this.val, -this.val1,
            this.val, this.val, this.val1,
            this.val2, -this.val, this.val1,
        ];
        this.texture = loadTexture(gl, 'obs.jpeg');
        this.positionBuffer = gl.createBuffer();
        gl.bindBuffer(gl.ARRAY_BUFFER, this.positionBuffer);
        gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(this.positions), gl.STATIC_DRAW);

        const textureCoordBuffer = gl.createBuffer();
        gl.bindBuffer(gl.ARRAY_BUFFER, textureCoordBuffer);
      
        const textureCoordinates = [
          // Front
        //   0.0,  0.0,
        //   1.0,  0.0,
        //   1.0,  1.0,
        //   0.0,  1.0,
        0.0,  1.0,
          1.0,  1.0,
          1.0,  0.0,
          0.0,  0.0,
          // Back
        //   0.0,  0.0,
        //   1.0,  0.0,
        //   1.0,  1.0,
        //   0.0,  1.0,
        0.0,  1.0,
          1.0,  1.0,
          1.0,  0.0,
          0.0,  0.0,
          // Top
          0.0,  0.0,
          1.0,  0.0,
          1.0,  1.0,
          0.0,  1.0,
          // Bottom
          0.0,  0.0,
          1.0,  0.0,
          1.0,  1.0,
          0.0,  1.0,
          // Right
          0.0,  0.0,
          1.0,  0.0,
          1.0,  1.0,
          0.0,  1.0,
          // Left
          0.0,  0.0,
          1.0,  0.0,
          1.0,  1.0,
          0.0,  1.0,
        ];


        gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(textureCoordinates),
        gl.STATIC_DRAW);
        
        
        

        const indexBuffer = gl.createBuffer();
        gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, indexBuffer);
        const indices = [
            0, 1, 2,    0, 2, 3, // front
            4, 5, 6,    4, 6, 7,
            8, 9, 10,   8, 10, 11,
            12, 13, 14, 12, 14, 15,
            16, 17, 18, 16, 18, 19,
            20, 21, 22, 20, 22, 23, 
        ];
        gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, new Uint16Array(indices), gl.STATIC_DRAW);

        this.buffer = {
            position: this.positionBuffer,
            textureCoord: textureCoordBuffer,
            indices: indexBuffer,
        }
        
    }

    draw(gl, projectionMatrix, programInfo, deltaTime) {
        const modelViewMatrix = mat4.create();
        mat4.translate(
            modelViewMatrix,
            modelViewMatrix,
            this.pos
        );
        
        //this.rotation += Math.PI / (((Math.random()) % 100) + 50);

        mat4.rotate(modelViewMatrix,
            modelViewMatrix,
            this.rotation,
            [0, 1, 0]);

            {
                const numComponents = 3;
                const type = gl.FLOAT;
                const normalize = false;
                const stride = 0;
                const offset = 0;
                gl.bindBuffer(gl.ARRAY_BUFFER, this.buffer.position);
                gl.vertexAttribPointer(
                    programInfo.attribLocations.vertexPosition,
                    numComponents,
                    type,
                    normalize,
                    stride,
                    offset);
                gl.enableVertexAttribArray(
                    programInfo.attribLocations.vertexPosition);
              }

        // Tell WebGL how to pull out the colors from the color buffer
        // into the vertexColor attribute.
        {
            const numComponents = 2;
            const type = gl.FLOAT;
            const normalize = false;
            const stride = 0;
            const offset = 0;
            gl.bindBuffer(gl.ARRAY_BUFFER, this.buffer.textureCoord);
            gl.vertexAttribPointer(
                programInfo.attribLocations.textureCoord,
                numComponents,
                type,
                normalize,
                stride,
                offset);
            gl.enableVertexAttribArray(
                programInfo.attribLocations.textureCoord);
          }
        // Tell WebGL which indices to use to index the vertices
        gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, this.buffer.indices);

        // Tell WebGL to use our program when drawing

        gl.useProgram(programInfo.program);

        // Set the shader uniforms

        gl.uniformMatrix4fv(
            programInfo.uniformLocations.projectionMatrix,
            false,
            projectionMatrix);
        gl.uniformMatrix4fv(
            programInfo.uniformLocations.modelViewMatrix,
            false,
            modelViewMatrix);

            gl.activeTexture(gl.TEXTURE0);

            // Bind the texture to texture unit 0
            gl.bindTexture(gl.TEXTURE_2D, this.texture);
          
            // Tell the shader we bound the texture to texture unit 0
            gl.uniform1i(programInfo.uniformLocations.uSampler, 0);

        {
            const vertexCount = 36;
            const type = gl.UNSIGNED_SHORT;
            const offset = 0;
            gl.drawElements(gl.TRIANGLES, vertexCount, type, offset);
        }

    }
tick(){
    if(this.pos[1]>=this.jump) this.speedy=-this.speedy;
  if(this.pos[1]<this.jump  && this.speedy>0) this.pos[1]+=this.speedy;
  if(this.pos[1]>=-2  && this.speedy<0) this.pos[1]+=this.speedy; 
  this.pos[2]-=0.1; 
}
}