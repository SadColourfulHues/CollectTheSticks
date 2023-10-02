shader_type canvas_item;

uniform lowp float wave_strength : hint_range(0.0, 1.0) = 0.02;
uniform lowp float wave_speed_mod: hint_range(0.1, 2.0) = 0.35;
uniform lowp float wave_world_x_influence = 21.0;
uniform lowp float darken_effect_mix: hint_range(0.0, 1.0) = 0.75;
uniform lowp float pixel_snap = 0.5f;

void vertex()
{
	// world x influence
	float wx = wave_world_x_influence * (vec4(vec3(UV, 0.0), 0.0) * MODEL_MATRIX).x;
	vec2 vertex = VERTEX;

	// Apply wave based on height (masking out the bottom bit)
	float displace = 0.5 + 0.5 * sin(wx + wave_speed_mod * TIME * VERTEX.y) * wave_strength * (min(0.0, VERTEX.y - (VERTEX.y * 0.9145)));

	displace = round(displace / pixel_snap) * pixel_snap;

	vertex.x += displace;
	VERTEX = vertex;
}

void fragment()
{
	lowp vec4 tex = textureLod(TEXTURE, UV, 0);
	lowp float m = textureLod(TEXTURE, UV + vec2(0.0, 0.3), 0).a;
	m = tex.a - m;

	tex = mix(tex, vec4(darken_effect_mix * tex.rgb, 1), m);

	COLOR = tex;
}
