const char* fragment_shader_pcolor_tex=R"(
	#version 330 core
	in vec3 FragCol;
	in vec2 TexCoord;
	out vec4 FragColor;

    uniform sampler2D ourTexture;
	void main()
	{
		FragColor=vec4(FragCol,1.0)*texture(ourTexture,TexCoord);
	}
)";