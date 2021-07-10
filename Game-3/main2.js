var cubeRotation = 0.0;
var c1=new Array();
var walls=[];
var trains=[];
var planes=[];
var rocks=[];
var obs=[];
var obs1=[];
var planes1=[];
var coins=[];
var shoes=[];
var flies=[];
var gameover=0;
var scorecanvas=document.querySelector('#score');
var ctx=scorecanvas.getContext("2d");
ctx.font= "20px Arial";
var score=0;
main();
var c;
var polices;
var blink=0;
var shoez;
var flyz;
var duckz;
var grayz;
var policez=0;
var hitz=0;
var taken=0;
var grayscale=0;

//
// Start here
//
function main() {
  const canvas = document.querySelector('#glcanvas');
  const gl = canvas.getContext('webgl');

  // If we don't have a GL context, give up now

  if (!gl) {
    alert('Unable to initialize WebGL. Your browser or machine may not support it.');
    return;
  }

const shaderProgram1 = initShaderProgram(gl, vsSource1, fsSource1);

const programInfo1 = {
    program: shaderProgram1,
    attribLocations: {
      vertexPosition: gl.getAttribLocation(shaderProgram1, 'aVertexPosition'),
      vertexColor: gl.getAttribLocation(shaderProgram1, 'aVertexColor'),
      textureCoord: gl.getAttribLocation(shaderProgram1, 'aTextureCoord'),
    },
    uniformLocations: {
      projectionMatrix: gl.getUniformLocation(shaderProgram1, 'uProjectionMatrix'),
      modelViewMatrix: gl.getUniformLocation(shaderProgram1, 'uModelViewMatrix'),
    },
  };


  const shaderProgram2 = initShaderProgram(gl, vsSource, fsSource2);

  const programInfo2 = {
      program: shaderProgram2,
      attribLocations: {
        vertexPosition: gl.getAttribLocation(shaderProgram2, 'aVertexPosition'),
        vertexColor: gl.getAttribLocation(shaderProgram2, 'aVertexColor'),
        textureCoord: gl.getAttribLocation(shaderProgram2, 'aTextureCoord'),
      },
      uniformLocations: {
        projectionMatrix: gl.getUniformLocation(shaderProgram2, 'uProjectionMatrix'),
        modelViewMatrix: gl.getUniformLocation(shaderProgram2, 'uModelViewMatrix'),
      },
    };

    const shaderProgram3 = initShaderProgram(gl, vsSource, fsSource3);

    const programInfo3 = {
        program: shaderProgram3,
        attribLocations: {
          vertexPosition: gl.getAttribLocation(shaderProgram3, 'aVertexPosition'),
          vertexColor: gl.getAttribLocation(shaderProgram3, 'aVertexColor'),
          textureCoord: gl.getAttribLocation(shaderProgram3, 'aTextureCoord'),
        },
        uniformLocations: {
          projectionMatrix: gl.getUniformLocation(shaderProgram3, 'uProjectionMatrix'),
          modelViewMatrix: gl.getUniformLocation(shaderProgram3, 'uModelViewMatrix'),
        },
      };


  // Initialize a shader program; this is where all the lighting
  // for the vertices and so forth is established.
  const shaderProgram = initShaderProgram(gl, vsSource, fsSource);

  // Collect all the info needed to use the shader program.
  // Look up which attributes our shader program is using
  // for aVertexPosition, aTextureCoord and also
  // look up uniform locations.
  const programInfo = {
    program: shaderProgram,
    attribLocations: {
      vertexPosition: gl.getAttribLocation(shaderProgram, 'aVertexPosition'),
      textureCoord: gl.getAttribLocation(shaderProgram, 'aTextureCoord'),
    },
    uniformLocations: {
      projectionMatrix: gl.getUniformLocation(shaderProgram, 'uProjectionMatrix'),
      modelViewMatrix: gl.getUniformLocation(shaderProgram, 'uModelViewMatrix'),
      uSampler: gl.getUniformLocation(shaderProgram, 'uSampler'),
    },
  };

  // Here's where we call the routine that builds all the
  // objects we'll be drawing.
  const buffers = initBuffers(gl);
  document.onkeydown=(e)=>{
    e=e || window.event();
    if(e.keyCode==37){
      // console.log(e.keyCode)
      if(c.lane>=0)
      c.lane-=1;
      c.pos[0]=6*c.lane;
    }
    if(e.keyCode==39){
      // console.log(e.keyCode)
      if(c.lane<=0)
      c.lane+=1;
      c.pos[0]=6*c.lane;
    }
    if(e.keyCode==32){
      // console.log(e.keyCode)
    if(taken==0)
      c.speedy=0.1;
    }
    if(e.keyCode==71){
        // console.log(e.keyCode)
      grayscale=1;
      grayz=c.pos[2];
      }
      if(e.keyCode==67){
        // console.log(e.keyCode)
      grayscale=0;
      }
    if(e.keyCode==68){
      c.scale=0.25;
      duckz=c.pos[2];
    }
  }
//   const texture = loadTexture(gl, 'cubetexture.png');

  var then = 0;

  // Draw the scene repeatedly
  function render(now) {
    now *= 0.001;  // convert to seconds
    const deltaTime = now - then;
    then = now;
    drawScene(gl, programInfo,programInfo1,programInfo2,programInfo3, buffers, deltaTime);
    tick_elements();
    requestAnimationFrame(render);
  }
  requestAnimationFrame(render);
}

function train_collision(){

    px=c.pos[0];
    py=c.pos[1];
    pz=c.pos[2];
    plength=0.5;
    pwidth=0.5*c.scale;
    pheight=0.5;
    var yes=0; 
    for(let i=0;i<trains.length;i++){
    tx=trains[i].pos[0];
    ty=trains[i].pos[1];
    tz=trains[i].pos[2];
    if(Math.abs(tz-c.pos[2])<10){
    tlength=2;
    twidth=2;
    theight=12;
    a=new bounding_box(px,py,pz,plength,pwidth,pheight);
    b=new bounding_box(tx,ty,tz,tlength,twidth,theight);
    if(detect_collision(a,b)){
       yes=1;
       gameover=1;
       break;
    }
    } 
    }


    for(let i=0;i<obs.length;i++){
      ox=obs[i].pos[0];
      oy=obs[i].pos[1];
      oz=obs[i].pos[2];
      if(Math.abs(oz-c.pos[2])<10){
      olength=1;
      owidth=0.75;
      oheight=0.5;
      a=new bounding_box(px,py,pz,plength,pwidth,pheight);
      b=new bounding_box(ox,oy,oz,olength,owidth,oheight);
      if(detect_collision(a,b)){
         yes=1;
         gameover=1;
         break;
      }
      } 
      }


      for(let i=0;i<obs1.length;i++){
        ox1=obs1[i].pos[0];
        oy1=obs1[i].pos[1];
        oz1=obs1[i].pos[2];
        olength1=1.25;
        owidth1=1.25;
        oheight1=0.2;
        if(px==ox1 && Math.abs(py-oy1)<1.1+0.5*c.scale && Math.abs(oz1-pz)<0.5){
          yes=1;
         gameover=1;
         break;
        }
        }


      for(let i=0;i<rocks.length;i++){
        rx=rocks[i].pos[0];
        ry=rocks[i].pos[1];
        rz=rocks[i].pos[2];
        if(Math.abs(rz-c.pos[2])<10){
        rlength=0.75;
        rwidth=0.75;
        rheight=0.5;
        a1=new bounding_box(px,py,pz,plength,pwidth,pheight);
        b1=new bounding_box(rx,ry,rz,rlength,rwidth,rheight);
        if(detect_collision(a1,b1)){
          polices.pos[2]=c.pos[2]+3;
          polices.pos[0]=c.pos[0];
          hitz=c.pos[2];
          policez+=1;
           console.log(policez);
           break;
        }
        } 
        }
    return yes;
}
function collision(){
    px=c.pos[0];
    py=c.pos[1];
    pz=c.pos[2];
    plength=0.5;
    pwidth=0.5;
    pheight=0.5;
    a=new bounding_box(px,py,pz,plength,pwidth,pheight);
    for(let i=0;i<coins.length;i++){
    cx=coins[i].pos[0];
    cy=coins[i].pos[1];
    cz=coins[i].pos[2];
    clength=0.25;
    cwidth=0.25;
    cheight=0.25;
    b=new bounding_box(cx,cy,cz,clength,cwidth,cheight);
    if(detect_collision(a,b)){
      score+=1;
        coins[i].present=0;
    }
    }
    for(let i=0;i<shoes.length;i++){
    sx=shoes[i].pos[0];
    sy=shoes[i].pos[1];
    sz=shoes[i].pos[2];
    slength=0.75;
    swidth=0.75;
    sheight=0.5;
    b=new bounding_box(sx,sy,sz,slength,swidth,sheight);
    if(detect_collision(a,b)){
      score+=10;
        shoes[i].present=0;
        c.jump=3;
        shoez=c.pos[2];
    }
  }
  for(let i=0;i<shoes.length;i++){
    fx=flies[i].pos[0];
    fy=flies[i].pos[1];
    fz=flies[i].pos[2];
    flength=1;
    fwidth=1;
    fheight=0.5;
    b=new bounding_box(fx,fy,fz,flength,fwidth,fheight);
    if(detect_collision(a,b)){
      score+=10;
        flies[i].present=0;
        c.pos[1]=3;
        flyz=c.pos[2];
        taken=1;
        c.speedy=0;
        c.jump=4;
    }
  }


}
function tick_elements(){
  if(c.pos[2]<=-300){
    ctx.clearRect(0,0,ctx.canvas.width,ctx.canvas.height);
  ctx.fillText(`Score:${score}  You WIN`,40,70);
  gameover=2;
  }
  if(gameover==0){
  ctx.clearRect(0,0,ctx.canvas.width,ctx.canvas.height);
  ctx.fillText(`Score:${score}`,200,150);
  }
  if(gameover==1){
    grayscale=1;
    ctx.clearRect(0,0,ctx.canvas.width,ctx.canvas.height);
  ctx.fillText(`Score:${score}  You LOST`,40,70);
  }
  if(gameover==0){
    if(Math.abs(c.pos[2]-flyz) > 30 && taken==1){
         c.speedy=-0.1;
         c.jump=0;
         taken=0;
    }
    if(Math.abs(c.pos[2]-shoez) > 20) c.jump=0;
    if(Math.abs(c.pos[2]-grayz) > 20) grayscale=0;
    if(Math.abs(c.pos[2]-duckz) > 3) c.scale=1;
    c.tick();
    if(Math.abs(hitz-c.pos[2])<30) {
      if(policez>15){
        gameover=1;
        polices.pos[2]=c.pos[2]+1;
  //       ctx.clearRect(0,0,ctx.canvas.width,ctx.canvas.height);
  // ctx.fillText(`Score:${score}  You LOST`,40,70);
      }
      polices.pos[0]=c.pos[0];
      polices.tick();
    }
    if(Math.abs(hitz-c.pos[2])>30){
      policez=0;
    }
    for(let i=0;i<10;i++){
    trains[i].tick();
    }
    for(let i=0;i<20;i++){
    planes[i].tick();
    }
    // console.log(train_collision())
    for(let i=0;i<100;i++){
    coins[i].tick();
    }
    collision();
    train_collision();
  }
  }
//
// initBuffers
//
// Initialize the buffers we'll need. For this demo, we just
// have one object -- a simple three-dimensional cube.
//
function initBuffers(gl) {
  // Create a buffer for the cube's vertex positions.
  c = new player(gl, [0, -2.0, 0.0]);
  polices= new  police(gl,[0,-2.0,3.0]);
  polices.scale=0.5;
  for(let i=0;i<20;i++){
    t1=new track(gl, [0, -4, -20.0*i]);
    t2=new track(gl, [-6, -4, -20.0*i]);
    t3=new track(gl, [6, -4, -20.0*i]);
    c1.push(t1);
    c1.push(t2);
    c1.push(t3);
    }
    for(let i=0;i<40;i++){
    walls.push(new wall(gl, [-10, -5, -10*i]));
    walls.push(new wall(gl, [10, -5, -10*i]));
    }
    for(let i=0;i<10;i++){
        var z=Math.floor(Math.random()*3)-1;
        console.log(z);
        if(i==0) z=-1;
    trains.push(new train(gl, [6*z, -1.5, -64*i]));
    planes.push(new plane(gl, [6*z, -1.5, -64*i],1,1,6,0));
    planes.push(new plane(gl, [6*z, -1.5, -64*i],1,1,6,1));
    } 
    for(let i=0;i<20;i++){ 
        var z=Math.floor(Math.random()*3)-1;
        rocks.push(new rock(gl, [6*z, -2.0, -20*i-12.0]));
    }
    for(let i=0;i<40;i++){
        var z=Math.floor(Math.random()*3)-1;
        if(i==0) z=1;
        obs.push(new obstacle(gl, [6*z, -2.0, -10*i-5.0]));
    }
    for(let i=0;i<20;i++){
        var z=Math.floor(Math.random()*3)-1;
        if(i==0) z=-1;
        // obs1 = new obstacle1(gl, [2, -0.75, -10.0]);
        obs1.push(new obstacle1(gl, [6*z, -0.75, -30.0*i]));
        planes1.push(new plane(gl, [6*z-1.15, -2.25, -30.0*i],0.1,0.25,0,1)); 
        planes1.push(new plane(gl, [6*z+1.125, -2.25, -30.0*i],0.1,0.25,0,1)); 
    }
    for(let i=0;i<100;i++){
        var z=Math.floor(Math.random()*3)-1;
        coins.push(new coin(gl, [6*z, -2.25, -2*i]));
        coins.push(new coin(gl, [6*z, 3, -2*i]));
    }
    for(let i=0;i<10;i++){
      var z=Math.floor(Math.random()*3)-1;
        shoes.push(new shoe(gl, [6*z, -2, -40*i-12.0]));
    }
    for(let i=0;i<10;i++){
          var z=Math.floor(Math.random()*3)-1;
          flies.push(new fly(gl, [6*z, -2, -50*i-18.0]));
    }
  
}

//
// Initialize a texture and load an image.
// When the image finished loading copy it into the texture.
//


//
// Draw the scene.
//
function drawScene(gl, programInfo,programInfo1,programInfo2, programInfo3,buffers,  deltaTime) {
    blink+=1;
    if(blink==128) blink=0;
    if(grayscale==0)
    gl.clearColor(0, 191/255, 1, 1.0);
    // gl.clearColor(1, 1, 1, 1.0);     
    if(grayscale==1)
    gl.clearColor(169/255, 169/255, 169/255, 1.0); 
//   gl.clearColor(0.0, 0.0, 0.0, 1.0);  // Clear to black, fully opaque
  gl.clearDepth(1.0);                 // Clear everything
  gl.enable(gl.DEPTH_TEST);           // Enable depth testing
  gl.depthFunc(gl.LEQUAL);            // Near things obscure far things

  // Clear the canvas before we start drawing on it.

  gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);

  // Create a perspective matrix, a special matrix that is
  // used to simulate the distortion of perspective in a camera.
  // Our field of view is 45 degrees, with a width/height
  // ratio that matches the display size of the canvas
  // and we only want to see objects between 0.1 units
  // and 100 units away from the camera.

  const fieldOfView = 45 * Math.PI / 180;   // in radians
  const aspect = gl.canvas.clientWidth / gl.canvas.clientHeight;
  const zNear = 0.1;
  const zFar = 100.0;
  const projectionMatrix = mat4.create();
  mat4.perspective(projectionMatrix,
    fieldOfView,
    aspect,
    zNear,
    zFar);
  // note: glmatrix.js always has the first argument
  // as the destination to receive the result.
  var cameraMatrix = mat4.create();

    var cameraPosition = [
      0,
      2,
      c.pos[2]+10,
    ];

    var up = [0, 1,0 ];

    mat4.lookAt(cameraMatrix, cameraPosition, [0,0,c.pos[2]], up);

    var viewMatrix = cameraMatrix;//mat4.create();

    //mat4.invert(viewMatrix, cameraMatrix);

    var viewProjectionMatrix = mat4.create();

    mat4.multiply(viewProjectionMatrix, projectionMatrix, viewMatrix);
    var p;
    if(grayscale==0) p=programInfo;
    else p=programInfo2;
    for(let i=0;i<60;i++){
        c1[i].draw(gl, viewProjectionMatrix, p, deltaTime);
    }
    for(let i=0;i<10;i++){
        trains[i].draw(gl, viewProjectionMatrix, p, deltaTime);
    }
    for(let i=0;i<20;i++){
    planes[i].draw(gl, viewProjectionMatrix, p, deltaTime);
    }
    for(let i=0;i<20;i++){
    rocks[i].draw(gl, viewProjectionMatrix, p, deltaTime);
    }
    for(let i=0;i<40;i++){
      obs[i].draw(gl, viewProjectionMatrix, p, deltaTime);
    }
    for(let i=0;i<20;i++){
      obs1[i].draw(gl, viewProjectionMatrix, p, deltaTime);
    }
    for(let i=0;i<40;i++){
    planes1[i].draw(gl, viewProjectionMatrix, p, deltaTime);
    }
    for(let i=0;i<200;i++){
        if(coins[i].present==1)
        coins[i].draw(gl, viewProjectionMatrix, p, deltaTime);
    }
    for(let i=0;i<10;i++){
        if(shoes[i].present==1)
        shoes[i].draw(gl, viewProjectionMatrix, p, deltaTime);
    }
    for(let i=0;i<10;i++){
        if(flies[i].present==1)
        flies[i].draw(gl, viewProjectionMatrix, p, deltaTime);
    }
    c.draw(gl, viewProjectionMatrix, p, deltaTime);
    polices.draw(gl, viewProjectionMatrix, p, deltaTime);
    if(blink<64) p=programInfo3;
    else p=programInfo;
    if(grayscale==1) p=programInfo2;
    for(let i=0;i<80;i++){
      walls[i].draw(gl, viewProjectionMatrix, p, deltaTime);
  } 
// Update the rotation for the next draw
  cubeRotation += deltaTime;
}

//
// Initialize a shader program, so WebGL knows how to draw our data
//
function initShaderProgram(gl, vsSource, fsSource) {
  const vertexShader = loadShader(gl, gl.VERTEX_SHADER, vsSource);
  const fragmentShader = loadShader(gl, gl.FRAGMENT_SHADER, fsSource);

  // Create the shader program

  const shaderProgram = gl.createProgram();
  gl.attachShader(shaderProgram, vertexShader);
  gl.attachShader(shaderProgram, fragmentShader);
  gl.linkProgram(shaderProgram);

  // If creating the shader program failed, alert

  if (!gl.getProgramParameter(shaderProgram, gl.LINK_STATUS)) {
    alert('Unable to initialize the shader program: ' + gl.getProgramInfoLog(shaderProgram));
    return null;
  }

  return shaderProgram;
}

//
// creates a shader of the given type, uploads the source and
// compiles it.
//
function loadShader(gl, type, source) {
  const shader = gl.createShader(type);

  // Send the source to the shader object

  gl.shaderSource(shader, source);

  // Compile the shader program

  gl.compileShader(shader);

  // See if it compiled successfully

  if (!gl.getShaderParameter(shader, gl.COMPILE_STATUS)) {
    alert('An error occurred compiling the shaders: ' + gl.getShaderInfoLog(shader));
    gl.deleteShader(shader);
    return null;
  }

  return shader;
}

function detect_collision(a, b) {
    return (Math.abs(a.x - b.x) * 2 < (a.length + b.length)) &&
           (Math.abs(a.y - b.y) * 2 < (a.width + b.width)) && 
           (Math.abs(a.z - b.z) * 2 < (a.height + b.height));           ;
}
