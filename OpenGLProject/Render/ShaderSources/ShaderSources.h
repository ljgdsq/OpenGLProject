#pragma once

//����vertex shader ֻ��Ҫ���붥�� in vec3 aPos
extern const char* vertex_shader_0;  
//����fragment shader �̶���ɫ���
extern const char* fragment_shader_0;


//��Ҫ���붥�� �Ͷ���ɫ in vec3 aPos; in vec3 aColor;
extern const char* vertex_shader_pcolor;
//����ɫ 
extern const char* fragment_shader_pcolor;


//���붥�� ����ɫ  ��������   in vec3 aPos;  in vec3 aColor;  in vec2 aTex
extern const char* vertex_shader_pcolor_tex;
//����һ������ ����ɫ   sampler2D ourTexture 
extern const char* fragment_shader_pcolor_tex;


//���붥�� ����ɫ  ��������  MVP����  in vec3 aPos;  in vec3 aColor;  in vec2 aTex 
extern const char* vertex_shader_pcolor_tex_mvp;


//���붥�� ��������  MVP����  in vec3 aPos;  in vec2 aTex 
extern const char* vertex_base_tex_mvp;
//����һ������ sampler2D ourTexture 
extern const char* fragment_base_tex;



//����2������ ��һ����ϱ�	float mixPercent;sampler2D texture1; sampler2D texture2;
extern const char* fragment_base_tex2;