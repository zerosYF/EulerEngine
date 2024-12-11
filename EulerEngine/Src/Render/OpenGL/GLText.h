#pragma once
//#include<GLFW/glfw3.h>
//#include<glad/glad.h>
//#include"../../Math/EulerMath.h"
//#include<unordered_map>
//#include<ft2build.h>
//#include<iostream>
//#include"GLShader.h"
//#include FT_FREETYPE_H
//struct Character {
//public:
//	unsigned int TextureID;
//	glm::ivec2 Size;//字体大小;
//	glm::ivec2 Bearing;//基准线偏移值;
//	unsigned int Advance;//字符宽度;
//};
//std::unordered_map<char, Character> characters;
//unsigned int VAO;
//unsigned int VBO;
//
//void Configure() {
//	glGenVertexArrays(1,&VAO);
//	glGenBuffers(1,&VBO);
//	glBindVertexArray(VAO);
//	glBindBuffer(GL_ARRAY_BUFFER,VBO);
//	glBufferData(GL_ARRAY_BUFFER,sizeof(float)*6*4,NULL,GL_DYNAMIC_DRAW);
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(0,4,GL_FLOAT,GL_FALSE,4*sizeof(float),(void*)0);
//	glBindBuffer(GL_ARRAY_BUFFER,0);
//	glBindVertexArray(0);
//}
//
//void renderText(Shader &shader, std::string text,float x,float y,float scale,glm::vec3 color) {
//	shader.use();
//	shader.setVec3("textColor",color);
//	glActiveTexture(GL_TEXTURE0);
//	glBindVertexArray(VAO);
//	for (auto&c : text) {
//		Character ch = characters[c];
//		float xPos = x + ch.Bearing.x*scale;
//		float yPos = y - (ch.Size.y - ch.Bearing.y)*scale;
//		float width = ch.Size.x*scale;
//		float height = ch.Size.y*scale;
//
//		float vertices[6][4] = {
//			{xPos,					yPos + height,		0.0,0.0},
//			{xPos,					yPos,					0.0,1.0},
//			{xPos + width,	yPos,					1.0,1.0},
//			{xPos,					yPos + height,		0.0,0.0},
//			{xPos + width,	yPos,					1.0,1.0},
//			{xPos + width,	yPos + height,		1.0,0.0},
//		};
//		glBindTexture(GL_TEXTURE_2D,ch.TextureID);
//		glBindBuffer(GL_ARRAY_BUFFER,VBO);
//		glBufferSubData(GL_ARRAY_BUFFER,0,sizeof(vertices),vertices);
//		glBindBuffer(GL_ARRAY_BUFFER,0);
//		glDrawArrays(GL_TRIANGLES,0,6);
//
//		x += (ch.Advance >> 6)*scale;
//	}
//	glBindVertexArray(0);
//	glBindTexture(GL_TEXTURE_2D,0);
//}
//
//void buildCharacters() {
//	FT_Library ft;
//	if (FT_Init_FreeType(&ft)) {
//		std::cout << "无法初始化freetype" << std::endl;
//	}
//	FT_Face face;
//	if (FT_New_Face(ft, "Fonts/Arial.ttf", 0, &face)) {
//		std::cout << "加载font失败" << std::endl;
//	}
//	FT_Set_Pixel_Sizes(face, 0, 48);
//
//	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
//
//
//	for (unsigned char c = 0; c < 128; c++) {
//		if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
//			std::cout << "加载glyph失败" << std::endl;
//			continue;
//		}
//		unsigned int texture;
//		glGenTextures(1,&texture);
//		glBindTexture(GL_TEXTURE_2D,texture);
//		glTexImage2D(GL_TEXTURE_2D,0,GL_RED,
//			face->glyph->bitmap.width,face->glyph->bitmap.rows,
//			0,GL_RED,GL_UNSIGNED_BYTE,face->glyph->bitmap.buffer);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//		glm::ivec2 size(face->glyph->bitmap.width, face->glyph->bitmap.rows);
//		glm::ivec2 bearing(face->glyph->bitmap_left,face->glyph->bitmap_top);
//		unsigned int advance = face->glyph->advance.x;
//		Character ch = { texture,size,bearing,advance };
//		characters.insert(std::pair<char,Character>(c,ch));
//	}
//	FT_Done_Face(face);
//	FT_Done_FreeType(ft);
//}
