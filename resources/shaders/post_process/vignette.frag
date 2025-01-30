#ifdef GL_ES
precision mediump float;
#endif

uniform vec2 u_resolution;

vec3 g_insideColor = vec3(0.6, 0.5, 0.7);
vec3 g_outsideColor = vec3(0.5, 0.65, 0.5);
vec3 g_edgeColor = vec3(1.0);

float dot2(in vec2 v) { return dot(v, v); }

float sdfCoolS(in vec2 p)
{
    float six = (p.y < 0.0) ? -p.x : p.x;
    p.x = abs(p.x);
    p.y = abs(p.y) - 0.2;
    float rex = p.x - min(round(p.x / 0.4), 0.4);
    float aby = abs(p.y - 0.2) - 0.6;

    float d = dot2(vec2(six, -p.y) - clamp(0.5 * (six - p.y), 0.0, 0.2));
    d = min(d, dot2(vec2(p.x, -aby) - clamp(0.5 * (p.x - aby), 0.0, 0.4)));
    d = min(d, dot2(vec2(rex, p.y - clamp(p.y, 0.0, 0.4))));

    float s = 2.0 * p.x + aby + abs(aby + 0.4) - 0.4;
    return sqrt(d) * sign(s);
}

float sdCircle(vec2 p, float r) { return length(p) - r; }

void main()
{
    vec2 uv = gl_FragCoord.xy / u_resolution;
    vec2 centeredUV = uv - vec2(0.5);

    float d = sdfCoolS(centeredUV * 2.0);

    float edge = step(0.01, abs(d));
    vec3 col = mix(g_edgeColor, mix(g_insideColor, g_outsideColor, step(0.0, d)), edge);

    gl_FragColor = vec4(col, 1.0);
}