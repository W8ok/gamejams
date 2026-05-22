#version 100

precision mediump float;

varying vec2 fragTexCoord;
uniform sampler2D texture0;
uniform vec2 screenSize;
uniform float time;

void main()
{
    // Apply fisheye distortion to UV coordinates
    vec2 uv = fragTexCoord * 2.0 - 1.0;
    float radius = length(uv);
    float distortion = 1.0 + radius * radius * 0.25;
    uv = uv * distortion;
    uv = uv * 0.5 + 0.5;

    // Clamp to edges
    if (uv.x < 0.0 || uv.x > 1.0 || uv.y < 0.0 || uv.y > 1.0)
    {
        gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);
        return;
    }

    // Get the original texture with distorted UVs
    vec4 texColor = texture2D(texture0, uv);

    // Calculate scrolling scanline position
    float scrollSpeed = 0.5;
    float yPos = uv.y * (screenSize.y / 10.0) + time * scrollSpeed;
    float linePos = fract(yPos / 2.0);

    // Simple dither pattern (checkerboard)
    float dither = mod(floor(uv.x * screenSize.x) + floor(yPos), 2.0);

    // Smooth transition at scanline edges
    float edgeWidth = 0.35;
    float alpha;

    if (linePos < edgeWidth)
        alpha = (linePos / edgeWidth) * (0.5 + dither * 0.5);
    else if (linePos > (1.0 - edgeWidth))
        alpha = ((1.0 - linePos) / edgeWidth) * (0.5 + dither * 0.5);
    else
        alpha = 1.0;

    // Binary output
    if (alpha > 0.8) // Adjust this for line thickness
        gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);
    else
        gl_FragColor = texColor;
}
