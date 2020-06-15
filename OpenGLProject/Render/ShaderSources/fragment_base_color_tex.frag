const char* fragment_base_color_tex=R"(
	#version 330 core
	in vec2 TexCoord;
	out vec4 FragColor;
	uniform vec3 ourColor;
    uniform sampler2D ourTexture;
	void main()
	{
		FragColor=texture(ourTexture,TexCoord)*vec4(ourColor,1.0f);
	}
)";