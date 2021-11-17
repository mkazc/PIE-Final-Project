var scene,
    camera,
    renderer,
    element,
    container,
    effect,
    video,
    canvas,
    context;

init();

function init(){
    // Set up Three.js scene for elements
    scene = new THREE.Scene();
    // Set up perspective camera(fov,aspect,near,far)
    camera = new THREE.PerspectiveCamera(90, window.innerWidth / window.innerHeight, 0.001, 700);
    camera.position.set(0, 15, 0); // Initial position
    scene.add(camera); // Add camera to scene
    // Define renderer that draws 3D element on page
    renderer = new THREE.WebGLRenderer();
    element = renderer.domElement;
    container = document.getElementById('webglviewer');
    container.appendChild(element);
    // Add VR sterescopic effect
    effect = new THREE.StereoEffect(renderer);
    // Mobile device full screen on click
    element.addEventListener('click', fullscreen, false);
    // Set up Canvas
    canvas = document.getElementById('tempCanvas');
    canvas.width = 512;
    canvas.height = 288;
    // Ensure it works nice as Three.js texture
    canvas.width = nextPowerOf2(canvas.width);
    canvas.height = nextPowerOf2(canvas.height);
    function nextPowerOf2(x) { 
        return Math.pow(2, Math.ceil(Math.log(x) / Math.log(2)));
    }
    // Set up context
    context = canvas.getContext('2d');
    texture = new THREE.Texture(canvas);
    texture.context = context;
    // Create cameraplane
    var cameraPlane = new THREE.PlaneGeometry(512, 512);
    // Create camera mesh
    cameraMesh = new THREE.Mesh(cameraPlane, new THREE.MeshBasicMaterial({
        color: 0xffffff, opacity: 1, map: texture
    }));
    cameraMesh.position.z = -200;
    scene.add(cameraMesh);
    // Drawing latest frame
    animate();
}

function animate() {
    if (context) {
      var piImage = new Image();

      piImage.onload = function() {
        console.log('Drawing image');
        context.drawImage(piImage, 0, 0, canvas.width, canvas.height);

        texture.needsUpdate = true;
      }
      // Change ip when needed, determine from apache server host name
      piImage.src = "http://" + window.location.hostname + "/html/cam_pic.php?time=" + new Date().getTime()
    }

    requestAnimationFrame(animate);

    update();
    render();
}

function resize() {
    // fix size of projection
    var width = container.offsetWidth;
    var height = container.offsetHeight;
    camera.aspect = width/height;
    camera.updateProjectionMatrix();
    renderer.setSize(width,height);
    effect.setSize(width,height);
}

function update(dt) {
    resize();
    camera.updateProjectionMatrix();
}

function render(dt) {
    effect.render(scene, camera);
}

function fullscreen() {
    if (container.requestFullscreen) {
        container.requestFullscreen();
    } else if (container.msRequestFullscreen) {
        container.msRequestFullscreen();
    } else if (container.mozRequestFullScreen) {
        container.mozRequestFullScreen();
    } else if (container.webkitRequestFullscreen) {
        container.webkitRequestFullscreen();
    }
}