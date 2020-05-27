const char* fragment_shader_pcolor=R"(
	#version 330 core
	in vec3 FragCol;
	out vec4 FragColor;

	void main()
	{
		FragColor=vec4(FragCol,1.0);
	}
)";