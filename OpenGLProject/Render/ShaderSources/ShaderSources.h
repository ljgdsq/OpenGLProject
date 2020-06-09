#pragma once

//基础vertex shader 只需要输入顶点 in vec3 aPos
extern const char* vertex_shader_0;  
//基础fragment shader 固定颜色输出
extern const char* fragment_shader_0;


//需要输入顶点 和顶点色 in vec3 aPos; in vec3 aColor;
extern const char* vertex_shader_pcolor;
//顶点色 
extern const char* fragment_shader_pcolor;


//输入顶点 顶点色  纹理坐标   in vec3 aPos;  in vec3 aColor;  in vec2 aTex
extern const char* vertex_shader_pcolor_tex;
//包含一张纹理 顶点色   sampler2D ourTexture 
extern const char* fragment_shader_pcolor_tex;


//输入顶点 顶点色  纹理坐标  MVP矩阵  in vec3 aPos;  in vec3 aColor;  in vec2 aTex 
extern const char* vertex_shader_pcolor_tex_mvp;


//输入顶点 纹理坐标  MVP矩阵  in vec3 aPos;  in vec2 aTex 
extern const char* vertex_base_tex_mvp;
//包含一张纹理 sampler2D ourTexture 
extern const char* fragment_base_tex;



//包含2张纹理 和一个混合比	float mixPercent;sampler2D texture1; sampler2D texture2;
extern const char* fragment_base_tex2;