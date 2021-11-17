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
    // Set up Orbit controls for touch/click on web
    controls = new THREE.OrbitControls(camera, element);
    controls.target.set(
        camera.position.x + 0.15,
        camera.position.y,
        camera.position.z
    )
    // Turn off pan and zoom
    controls.noPan = true;
    controls.noZoom = true;
    // Setup device orientation event listener
    window.addEventListener('deviceorientation', setOrientationControls, true);
    // Setup when device supports device orientation
    controls = new THREE.DeviceOrientationControls(camera, true);
    controls.connect();
    controls.update();
    // Mobile device full screen on click
    element.addEventListener('click', fullscreen, false);
    // Controls object added, remove listener
    window.removeEventListener('deviceorientation', setOrientationControls, true);
}

function setOrientationControls(e) {
    if (!e.alpha) {
        return;
    }
}