const char* fragment_base_tex2=R"(
	#version 330 core
	out vec4 FragColor;

	in vec2 TexCoord;
	uniform float mixPercent;
	// texture samplers
	uniform sampler2D texture1;
	uniform sampler2D texture2;

	void main()
	{
		FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), mixPercent);
	}
)";