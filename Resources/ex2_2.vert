    #version 330 core
	layout(location=0) in vec3 aPos;
	layout(location=1) in vec3 aColor;
	uniform vec3 offset;
	out vec3 FragCol;
	void main()
	{
		FragCol=aColor;
		gl_Position=vec4(aPos+offset,1.0);
	}
