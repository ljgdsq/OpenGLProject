
	#version 330 core
	in vec3 FragCol;
	in vec2 TexCoord;
	out vec4 FragColor;
	uniform sampler2D ourTexture1;
    uniform sampler2D ourTexture2;
    uniform float mixPercent;
	void main()
	{
		FragColor=vec4(FragCol,1.0)*mix(texture(ourTexture1,TexCoord),texture(ourTexture2,TexCoord*2),mixPercent);
	}
