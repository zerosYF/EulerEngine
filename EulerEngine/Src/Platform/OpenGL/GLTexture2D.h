#pragma once
#include"Render/RawData/EulerTexture.h"
namespace EulerEngine {
	class OpenGLTexture2D :public Texture2D {
	private:
		unsigned int m_RendererID;
		int m_Width, m_Height;
		unsigned int m_Internal_Format;
		unsigned int m_Data_Format;
		unsigned int m_Wrap_S;
		unsigned int m_Wrap_T;
		int m_Channels;
	
		unsigned int m_Filter_MIN; 
		unsigned int m_Filter_MAX;
		
		std::string m_Path;
	public:
		OpenGLTexture2D(unsigned int width, unsigned int height);
		OpenGLTexture2D(const std::string& path);
		~OpenGLTexture2D();
		virtual unsigned int GetWidth() const override { return m_Width; }
		virtual unsigned int GetHeight() const override { return m_Height; }
		virtual void SetData(void* data, unsigned int size) override;
		virtual void Bind(unsigned int slot) const override;
		virtual bool operator==(const Texture& another) const override;
		virtual std::string GetPath() const override;
		virtual unsigned int GetRendererID() const override { return m_RendererID; }
	};
}