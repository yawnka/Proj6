// fragment_lit.glsl
uniform sampler2D diffuse;
uniform vec2 lightPosition; // Position of the light source
uniform int currentScene;   // Scene index passed from the game

varying vec2 texCoordVar;
varying vec2 varPosition;

// Function to calculate brightness
float calculate_brightness(int scene) {
    return max(1.0 - (0.2 * float(scene)), 0.0);
}

// Function to calculate spotlight intensity
float spotlight(vec2 pixelPosition, vec2 lightPosition) {
    float distance = distance(pixelPosition, lightPosition);
    float maxRadius = 3.5; // Spotlight radius
    float intensity = 1.0 - smoothstep(0.0, maxRadius, distance);
    return max(intensity, 0.0); // Ensure intensity doesn't go below 0
}

void main() {
    vec4 color = texture2D(diffuse, texCoordVar);

    // Default brightness (global adjustment for all scenes)
    float brightness = calculate_brightness(currentScene);

    // REQUIREMENT 5: SHADERS Apply spotlight effect for 3
    // scene 2 becomes too hard with spotlight :( 
    if (currentScene == 3) {
        brightness *= spotlight(varPosition, lightPosition);
    }

    gl_FragColor = vec4(color.rgb * brightness, color.a);
}
