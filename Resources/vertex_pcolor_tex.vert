
	#version 330 core
	layout(location=0) in vec3 aPos;
	layout(location=1) in vec3 aColor;
	layout(location=2) in vec2 aTex;
	out vec3 FragCol;
	out vec2 TexCoord;
	void main()
	{
		FragCol=aColor;
		TexCoord=aTex;
		gl_Position=vec4(aPos,1.0);
	}
