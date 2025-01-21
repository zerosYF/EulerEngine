#pragma once
#include"Render/EulerTexture.h"
namespace EulerEngine {
	class OpenGLTexture2D :public Texture2D {
	private:
		unsigned int m_RendererID;
		std::string m_Path;
		int m_Width, m_Height;
		unsigned int m_Internal_Format;
		unsigned int m_Data_Format;
		unsigned int m_Wrap_S;
		unsigned int m_Wrap_T;
		int m_Channels;
		//���Ʒ�ʽ��
		unsigned int m_Filter_MIN; //��С���˷�ʽ��
		unsigned int m_Filter_MAX;//�Ŵ���˷�ʽ��
	public:
		OpenGLTexture2D(std::string path, TextureType type);
		~OpenGLTexture2D();
		virtual unsigned int GetWidth() const override { return m_Width; }
		virtual unsigned int GetHeight() const override { return m_Height; }
		virtual void Bind(unsigned int slot) const override;
	};
}